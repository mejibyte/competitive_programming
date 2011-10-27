using namespace std;
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

const int MAXN = 1000010;

vector<int> border;

void preocomputeBorder(const string &needle) {
    int m = needle.size();
    border.resize(m + 1);
    border[0] = -1;
    for (int i = 0; i < m; ++i) {
      border[i+1] = border[i];
      while (border[i+1] > -1 and needle[border[i+1]] != needle[i]) {
        border[i+1] = border[border[i+1]];
      }
      border[i+1]++;
    }
    for (int i = 0; i <= m; ++i) {
        printf("%d ", border[i]);
    }
    puts("");
}

int main(){
    int m;
    while (scanf("%d", &m) == 1) {
        string needle; getline(cin, needle);
        getline(cin, needle);
        preocomputeBorder(needle);
        
        int seen = 0;
        
        for (int i = 0; ; ++i) {
            char c = getchar();
            if (c == '\n' or c == EOF) break;
            assert(c != EOF);
            //cout << c << endl;
            
            while (seen > -1 and needle[seen] != c) {
                seen = border[seen];
            }
            if (++seen == m) {
                printf("%d\n", i - m + 1);
                seen = border[m]; // There are no more characters in needle, so with the next input character let's try with the border of the whole needle.
            }
        }
        puts("");
    }
    return 0;
}