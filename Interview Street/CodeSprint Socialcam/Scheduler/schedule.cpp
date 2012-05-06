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

typedef long long Int;

map<Int, set<Int> > m;
map<Int, Int> timestamp; // timestamp for id

typedef map<Int, set<Int> >::iterator m_iterator;
typedef set<Int>::iterator set_iterator;

char buffer[32];

int main(){
    FILE * previous = fopen("prev.txt", "r");
    if (previous != NULL) {
        long long t, id;
        int size;
        while (fscanf(previous, "%lld %d", &t, &size) == 2) {
            for (int k = 0; k < size; ++k) {
                fscanf(previous, "%lld", &id);
                m[t].insert(id);
                timestamp[id] = t;
            }
        }
        fclose(previous);
    }
    
    int n; scanf("%d", &n);
    while (n--) {
        scanf("%s", buffer);
        if (buffer[0] == 's') {//set
            long long id, t;
            scanf("%lld %lld", &id, &t);
            
            if (timestamp.count(id) > 0) { // delete old update
                long long old_t = timestamp[id];
                m[old_t].erase(id);
            }
            
            timestamp[id] = t;
            m[t].insert(id);


        } else if (buffer[0] == 'l') { // list
            
            long long bound; scanf("%lld", &bound);

            bool first = true;
            for (m_iterator it = m.begin(); it != m.end(); ++it) {
                if (it->first > bound) break;
                for(set_iterator person = it->second.begin(); person != it->second.end(); ++person) {
                    if (!first) printf(" ");
                    first = false;
                    printf("%lld", *person);
                }
            }
            puts("");
            
        } else if (buffer[0] == 'd') { // del
            long long id; scanf("%lld", &id);
            if (timestamp.count(id) > 0) {
                long long old_t = timestamp[id];
                m[old_t].erase(id);
                timestamp.erase(id);
            }
            
        } else if (buffer[0] == 'c') { // clear
            m.clear();
            timestamp.clear();
            
        } else {
            printf("WTF is this? %s\n", buffer);
            assert(false);
        }
    }
    
    // dump to file
    previous = fopen("prev.txt", "w");
    assert(previous);
    for(m_iterator it = m.begin(); it != m.end(); ++it) {
        int size = it->second.size();
        if (size == 0) continue;
        fprintf(previous, "%lld %d", it->first, size);
        for(set_iterator p = it->second.begin(); p != it->second.end(); ++p) {
            fprintf(previous, " %lld", *p);
        }
        fprintf(previous, "\n");
    }
    fclose(previous);
    
    return 0;
}