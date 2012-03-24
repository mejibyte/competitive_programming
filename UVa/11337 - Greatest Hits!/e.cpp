// Andrés Mejía
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

vector<string> titles;
vector<long long> songs;
vector<int> prices;

inline bool bit(long long mask, int i) {
    return !!(mask & (1LL << i));
}

bool better(int n, long long a, long long b) {
    for (int i = 0; i < n; ++i) {
        if (bit(a, i) and !bit(b, i)) return true;
    }
    return false;
}

int main(){
    int run = 1;
    
    int casos; cin >> casos;
    string s; getline(cin, s);
    
    getline(cin, s);
    while (casos--) {
        titles.clear();
        songs.clear();
        prices.clear();
        
        map<string, int> songId;
        int nextId = 0;
        
        assert(s[0] == '$');
        int budget;
        sscanf(s.c_str() + 1, "%d", &budget);
        //D(budget);
        
        while (getline(cin, s)) {
            if (s[0] == '$') break;
            
            titles.push_back(s);
            
            
            long long mask = 0;
            //cout << "Title: " << s << endl;
            while (getline(cin, s)) {
                if (s[0] == '$') break;
                int which = songId.count(s) ? songId[s] : songId[s] = nextId++;
                
                mask |= (1LL << which);
            }
            
            int price;
            sscanf(s.c_str() + 1, "%d", &price);
            
            prices.push_back(price);
            songs.push_back(mask);
            
            //D(price);
        }
        assert(prices.size() == songs.size());
        assert(titles.size() == songs.size());
        
        int n = prices.size();
        
        int bestCount = -1, bestPrice = -1;
        long long bestDisks = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            
            int totalPrice = 0;
            long long boughtSongs = 0;
            for (int i = 0; i < n; ++i) if (mask & (1 << i)) {
                totalPrice += prices[i];
                boughtSongs |= songs[i];
            }
            if (totalPrice > budget) continue;
            
            int songCount = __builtin_popcountll(boughtSongs);

            if (songCount > bestCount or 
                songCount == bestCount and totalPrice < bestPrice or
                songCount == bestCount and totalPrice == bestPrice and better(n, mask, boughtSongs)) {
                bestCount = songCount;
                bestDisks = mask;
                bestPrice = totalPrice;
            }
        }
        
        printf("Scenario #%d: %d\n", run++, bestCount);
        for (int i = 0; i < n; ++i) if (bit(bestDisks, i)) {
            puts(titles[i].c_str());
        }
        puts("");
    }
    return 0;
}