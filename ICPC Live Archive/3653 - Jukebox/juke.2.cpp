// Andrés Mejía
// Time Limit and Wrong Answer
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
#include <bitset>
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

map<string, int> artist_id;
int total_artists;
int total_songs;
int best_answer;
string artists[6];
vector<int> songs_by[6];
int assign[6];
string titles[30];
int artist_of[30];

const int oo = 1e9;

void generate(int i, int which = 0) {
    if (i == total_artists) {
        // solve here
        int ans = 0;
        for (int i = 0; i < 900 * 10; ++i) {
            ans += i * i;
            ans ^= i;
        }
        best_answer = min(best_answer, ans);

    } else {
        int ans = oo;
        for (int k = -1, m = songs_by[i].size(); k < m; ++k) {
            if (k == -1) {
                assign[i] = k;
            } else {
                assign[i] = songs_by[i][k];
            }
            generate(i + 1);
        }
    }
}


int main(){
    static char buffer[256];
    
    while (scanf("%d", &total_songs) == 1) {
        if (total_songs == 0) break;
        for (int i = 0; i < 6; ++i) songs_by[i].clear();
        artist_id.clear();
        total_artists = 0;
        
        for (int i = 0; i < total_songs; ++i) {
            scanf("%s", buffer);
            titles[i] = string(buffer);
            scanf("%s", buffer);
            string artist(buffer);
            int id = artist_id.count(artist) ? artist_id[artist] : artist_id[artist] = total_artists++;
            artists[id] = artist;
            songs_by[id].push_back(i);
            artist_of[i] = id;
        }
        assert(total_artists <= 6);
        best_answer = oo;
        generate(0);
        cout << best_answer << endl;
    }
    return 0;
}