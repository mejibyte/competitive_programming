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
    border.resize(m);
    border[0] = 0;
    for (int i = 1; i < m; ++i) {
      border[i] = border[i - 1];
      while (border[i] > 0 and needle[i] != needle[border[i]]) {
         border[i] = border[border[i] - 1];
      }
      if (needle[i] == needle[border[i]]) border[i]++;
    }

    
    // for (int i = 0; i < m; ++i) {
    //     printf("%d ", border[i]);
    // }
    // puts("");
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
            
            while (seen > 0 and c != needle[seen]) {
                seen = border[seen - 1];
            }
            if (c == needle[seen]) seen++;
            
            if (seen == m) {
                printf("%d\n", i - m + 1);
                seen = border[m - 1]; // There are no more characters in needle, so with the next input character let's try with the border of the whole needle.
            }
        }
        puts("");
    }
    return 0;
}