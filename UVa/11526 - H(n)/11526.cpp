#include <iostream>
#include <cstdio>
using namespace std;

long long n;
int main(){
    int t; cin >> t;
    while (t-- && cin >> n){
        if (n <= 0){ cout << "0" << endl; continue; }

        long long res = 0;
        long long i = 1;
        while (i <= n){
            long long start = n / i;
            long long low = i, high = n;
            while (low < high){
                //long long mid = (low + high + 1) / 2;//low + (high - low + 1) / 2;
                long long mid = low + (high - low + 1) / 2;                
                //printf("low=%lld, high=%lld, mid=%lld, i=%lld\n", low, high, mid, i);
                if (n / mid != start) high = mid - 1;
                else low = mid;
            }
            res += (low - i + 1) * start;
            i = low + 1;
        }
        cout << res << endl;
    }
    return 0;    
}
