 //Equipo Poncho, carriel y ruana
// Sala Tayrona, maquina 140
using namespace std;
#include<algorithm>
#include<iostream>
#include<iterator>
#include<sstream>
#include<fstream>
#include<cassert>
#include<climits>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<deque>
#include<stack>
#include<list>
#include<map>
#include<set>

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x ,v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl
#define V(a,n) for (int o=0; o<(n);++o) printf(#a "[%d] = %d\n", o, a[o])

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int N = 1000005;
int str[N];
int rank[N], pos[N];
int cnt[N], next[N];
bool bh[N], b2h[N];

bool smaller_first_char(int a, int b) {
    return str[a] < str[b];    
}

void suffixSort(int n) {
 
    for (int i=0; i<n; i++) {
        pos[i] = i;   
    }
    
    sort(pos, pos+n, smaller_first_char);
    
    for(int i=0; i<n; i++) {
     bh[i] = i == 0 || str[pos[i]] != str[pos[i-1]];
     b2h[i] = false;   
    }
    
    for(int h=1; h < n; h <<= 1) {
        int buckets = 0;
        for (int i=0, j; i<n; i=j) {
            j = i+1;
            while(j<n && !bh[j]) j++;
            next[i] = j;
            buckets++;   
        }
        
        if (buckets == n) break;
        
        for(int i=0; i<n; i = next[i]) {
            cnt[i] = 0;
            for(int j=i; j < next[i]; ++j) {
                rank[pos[j]] = i;
            }   
        }
        
        cnt[rank[n-h]]++;
        b2h[rank[n-h]] = true;
        
        for(int i=0; i<n; i=next[i]) {
            for(int j=i; j < next[i]; ++j) {
                int s = pos[j] - h;
                if (s >= 0) {
                    int head = rank[s];
                    rank[s] = head + cnt[head]++;
                    b2h[rank[s]] = true;    
                }
            }
            for (int j=i; j < next[i]; ++j) {
                int s = pos[j]-h;
                if (s >= 0 && b2h[rank[s]]) {
                    for(int k=rank[s]+1; !bh[k] && b2h[k]; k++) {
                        b2h[k] == false;   
                    }  
                }   
            }
        }
        
        for(int i=0; i<n; i++) {
            pos[rank[i]] = i;
            bh[i] |= b2h[i];   
        }
        
    }
    for (int i=0; i<n; ++i) {
        rank[pos[i]] = i;
    }
}

int height[N];

void getHeight(int n) {
    for(int i=0; i<n; ++i) rank[pos[i]] = i;
    height[0] = 0;
    for(int i=0, h=0; i<n; ++i) {
        if(rank[i] > 0) {
            int j = pos[rank[i]-1];
            while(i + h < n && j + h < n && str[i+h] == str[j+h]) {
                h++;
            }
            height[rank[i]] = h;
            if(h > 0) h--;
        }
    }   
} 

int main() {


   return 0;
}
