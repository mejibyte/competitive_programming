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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

map<string, long long> removeEmptyProteins(map<string, long long> &config) {
    map<string, long long> ans;
    for (map<string, long long>::iterator i = config.begin(); i != config.end(); ++i) {    
        const string &protein = i->first;
        long long times = i->second;
        if (times > 0) {
            ans[protein] = times;
        }
    }    
    return ans;
}

map<string, long long> mutate(map<string, string> &mutations, map<string, long long> &config) {
    map<string, long long> ans;
    for (map<string, long long>::iterator i = config.begin(); i != config.end(); ++i) {
        const string &protein = i->first;
        long long times = i->second;
        if (mutations.count(protein) > 0) {
            const string &newProtein = mutations[protein];
            ans[  newProtein ] += times;
        } else {
            ans[  protein  ] += times;
        }
    }
    return ans;
}

int solveCase(map<string, string> &mutations, const map<string, long long> &initialConfig, const map<string, long long> &finalConfig, int bound) {
    if (initialConfig == finalConfig) return 0;
        
    map<string, long long> config = initialConfig;
    for (int k = 1; k <= bound; ++k) {
        
        config = mutate(mutations, config);
        config = removeEmptyProteins(config);
        
        // printf("after %d mutations config is:\n", k);
        // for (map<string, long long>::iterator i = config.begin(); i != config.end(); ++i) {
        //     const string &protein = i->first;
        //     long long times = i->second;
        //     printf("%s -> %lld\n", protein.c_str(), times);
        // }
        
        if (config == finalConfig) return k;
    }
    
    return -1;
}

int main(){
    int NM, NI, NC, bound;
    while (cin >> NM >> NI >> NC >> bound) {
        if (NM == 0 and NI == 0 and NC == 0 and bound == 0) break;
        
        bool deterministic = true;
        map<string, string> mutations;
        for (int t = 0; t < NM; ++t) {
            string k, v;
            cin >> k >> v;
            if (mutations.count(k) > 0 and mutations[k] != v) {
                 deterministic = false;
            }
            mutations[k] = v;
        }
        
        map<string, long long> initialConfig, finalConfig;
        for (int i = 0; i < NI; ++i) {
            string protein; long long times;
            cin >> protein >> times;
            initialConfig[protein] = times;
        }

        for (int i = 0; i < NC; ++i) {
            string protein; long long times;
            cin >> protein >> times;
            finalConfig[protein] = times;
        }
        
        if (!deterministic) {
            printf("Protein mutations are not deterministic\n");
            continue;
        }
        
        int ans = solveCase(mutations, initialConfig, finalConfig, bound);
        if (ans == -1) {
            printf("Nostalgia for Infinity is doomed\n");
        } else {
            printf("Cure found in %d mutation(s)\n", ans);
        }
    }
    
    return 0;
}