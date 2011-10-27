// This times out!
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

const int MAXN = 20;
const int MAXK = 27;

struct region {
    short r1, r2, c1, c2;
    region() {}
    region(short r1, short r2, short c1, short c2) : r1(r1), r2(r2), c1(c1), c2(c2) {}
};

struct cell {
    short r, c;
    cell() {}
    cell(short r, short c) : r(r), c(c) {}    
};

int N, K;
char mat[MAXN][MAXN];
cell leaders[MAXK];
int people[MAXK];
vector< region > options[MAXK];

inline bool valid(const region& r) {
    return (0 <= r.r1 and r.r1 <= r.r2 and r.r2 < N and
        0 <= r.c1 and r.c1 <= r.c2 and r.c2 < N);
}

inline bool containsCell(const region &rg, int r, int c) {
    return rg.r1 <= r and r <= rg.r2 and rg.c1 <= c and c <= rg.c2;
}

inline bool containsDifferentLetter(const region &r, char letter) {
    //assert(valid(r));
    for (int i = r.r1; i <= r.r2; ++i) {
        for (int j = r.c1; j <= r.c2; ++j) {
            if (mat[i][j] != '.' and mat[i][j] != letter) return true;
        }
    }
    return false;
}

inline bool sameLetterOutsideRegion(const region &r, char letter) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (containsCell(r, i, j)) continue;
            if (mat[i][j] != '.' and mat[i][j] == letter) return true;
        }
    }
    return false;
    
}

inline bool containsEmptyCell(const region &r) {
    //assert(valid(r));
    for (int i = r.r1; i <= r.r2; ++i) {
        for (int j = r.c1; j <= r.c2; ++j) {
            if (mat[i][j] == '.') return true;
        }
    }
    return false;
}


inline void fillRegion(const region &r, char letter) {
    //assert(valid(r));
    for (int i = r.r1; i <= r.r2; ++i) {
        for (int j = r.c1; j <= r.c2; ++j) {
            mat[i][j] = letter;
        }
    }    
}

bool deduceFixedPositions() {
    bool changed = false;
    
    for (int k = 0; k < K; ++k) {
        int oldOptionsSize = options[k].size();
        
        options[k].clear();
        
        int size = people[k];
        for (int width = 1; width <= size; ++width) {
            if (size % width != 0) continue;
            int height = size / width;
            char leaderLetter = mat[leaders[k].r][leaders[k].c];

            for (int i = max(0, leaders[k].r - height + 1); i + height - 1 < N and i <= leaders[k].r; ++i) {
                for (int j = max(0, leaders[k].c - width + 1); j + width - 1 < N and j <= leaders[k].c; ++j) {
                    region r(i, i + height - 1, j, j + width - 1);
                    assert(valid(r));
                    assert(containsCell(r, leaders[k].r, leaders[k].c));
                    //printf("considering region <r1=%d, r2=%d, c1=%d, c2=%d> for leader %d\n", r.r1, r.r2, r.c1, r.c2, k);
                    if (containsDifferentLetter(r, leaderLetter)) {
                        //printf("discarding because it also has a different letter\n");
                        continue;
                    }
                    if (sameLetterOutsideRegion(r, leaderLetter)) {
                        //printf("discarding because this letter is also outside this region\n");
                        continue;
                    } 
                    options[k].push_back( r );
                }
            }
        }
        
        if (oldOptionsSize != options[k].size()) {
            changed = true;
        }
        
        if (options[k].size() == 1 and containsEmptyCell(options[k][0])) {
            fillRegion(options[k][0], 'A' + k);
            changed = true;
        }
        
        //for (int i = 0; i < options[k].size(); ++i){ region r = options[k][i]; printf("There's a possible region for leader %d at <r1=%d, r2=%d, c1=%d, c2=%d>\n", k, r.r1, r.r2, r.c1, r.c2); }
    }
    
    //for (int i = 0; i < N; ++i) { for (int j = 0; j < N; ++j) { printf("%c", mat[i][j]); } puts(""); }
    
    if (changed) return true;
    
    // Place a letter where there's only a possible leader that covers that cell
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (mat[i][j] != '.') continue;
            int leaderThatContainsMe = -1; int numberOfLeadersThatContainMe = 0;
            for (int k = 0; k < K; ++k) {
                for (int o = 0; o < options[k].size(); ++o) {
                    if (containsCell(options[k][o], i, j)) {
                        leaderThatContainsMe = k;
                        numberOfLeadersThatContainMe++;
                        break;
                    }
                }
            }
            //printf("cell <%d, %d>: number of leaders that contain me = %d\n", i, j, numberOfLeadersThatContainMe);
            //assert(numberOfLeadersThatContainMe > 0);
            if (numberOfLeadersThatContainMe == 1) {
                mat[i][j] = leaderThatContainsMe + 'A';
                changed = true;
            }
        }
    }
    
    //for (int k = 0; k < K; ++k) for (int i = 0; i < options[k].size(); ++i){ region r = options[k][i]; printf("There's a possible region for leader %d at <r1=%d, r2=%d, c1=%d, c2=%d>\n", k, r.r1, r.r2, r.c1, r.c2); }

    if (changed) return true;

    return false;
}

bool cellWith0CoveringRegions() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < K; ++k) {
                char letter = 'A' + k;
                for (int o = 0; o < options[k].size(); ++o) {
                    const region &r = options[k][o];
                    if (!containsCell(r, i, j)) continue;
                    if (sameLetterOutsideRegion(r, letter)) continue; // can't take this one
                    if (containsDifferentLetter(r, letter)) continue;
                    return false;
                }
            }
        }
    }
    return true;
}

bool backtrack(int k, int placed) {
    //printf("k = %d, K = %d\n", k, K);
    //for (int i = 0; i < N; ++i) { for (int j = 0; j < N; ++j) { printf("%c", mat[i][j]); } puts(""); }
    
    if (k == K or placed == k) {
        // Found solution!
        for (int i = 0; i < N; ++i) {
          for (int j = 0; j < N; ++j) {
            putchar(mat[i][j]);
          }
          putchar('\n');
        }
        return true;
    }
    
    
    if (cellWith0CoveringRegions()) return false;
    
    //for (int i = 0; i < N; ++i) { for (int j = 0; j < N; ++j) { printf("%c", mat[i][j]); } puts(""); }
    
    char letter = mat[leaders[k].r][leaders[k].c];
    
    for (int o = 0; o < options[k].size(); ++o) {        
        const region &r = options[k][o];
        // let's take this region
        if (sameLetterOutsideRegion(r, letter)) continue; // can't take this one
        if (containsDifferentLetter(r, letter)) continue; 
        
        vector< cell > changed;
        for (int i = r.r1; i <= r.r2; ++i) {
            for (int j = r.c1; j <= r.c2; ++j) {
                assert(mat[i][j] == '.' or mat[i][j] == letter);
                if (mat[i][j] == '.') {
                    changed.push_back ( cell(i, j)  );
                    mat[i][j] = letter;
                }
            }
        }
        if (backtrack(k + 1, placed + 1)) return true;
        
        for (int c = 0; c < changed.size(); ++c) {
            mat[changed[c].r][changed[c].c] = '.';
        }
    }
    return false;
}

int main(){
    while (scanf("%d %d", &N, &K) == 2) {
        int currentLeader = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                char c = getchar(); while (isspace(c)) c = getchar();
                mat[i][j] = c;
                if (isdigit(c)) {
                    leaders[currentLeader] = cell(i, j);
                    people[currentLeader] = c - '0';
                    options[currentLeader].clear();
                    mat[i][j] = 'A' + currentLeader;
                    currentLeader++;
                }
            }
        }
        
        // sort leaders by size
        for (int i = 0; i < K; ++i) {
            for (int j = i + 1; j < K; ++j) {
                if (people[j] > people[i]) {
                    swap(mat[leaders[i].r][leaders[i].c], mat[leaders[j].r][leaders[j].c]);
                    swap(leaders[i], leaders[j]);
                    swap(people[i], people[j]);
                }
            }
        }

        //for (int i = 0; i < N; ++i) { for (int j = 0; j < N; ++j) { printf("%c", mat[i][j]); } puts(""); }
        // 
        // for (int i = 0; i < K; ++i) {
        //     printf("There's a leader at <%d, %d> of size %d\n", leaders[i].r, leaders[i].c, people[i]);
        // }

        bool changed = true;
        while (changed) {
            changed = deduceFixedPositions();
        }
        
        // for (int i = 0; i < N; ++i) {
        //   for (int j = 0; j < N; ++j) {
        //     printf("%c", mat[i][j]);
        //   }
        //   printf("\n");           
        // }
        int count = 0;
        for (int k = 0; k < K; ++k) {
            int seen = 0;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    seen += (mat[i][j] == 'A' + k);
                }
            }
            count += (seen == people[k]);
        }
        assert(backtrack(0, count));
    }
    return 0;
}