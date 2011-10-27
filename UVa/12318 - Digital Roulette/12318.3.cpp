// Code written by Andrés Mejía
using namespace std;
#include <iostream>
#include <vector>
#include <set>

int main(){
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 and m == 0) break;
        int k; cin >> k;
        vector<int> a(k + 1);
        // Read coefficients
        for (int i = 0; i < k + 1; ++i) {
            cin >> a[i];
        }
        int mod = n + 1;
        set<int> ans;
        
        // Brute force on x
        for (int x = 0; x <= m; x++){
            // calculate P(x) and store the result in y
            int y = 0, d = 1;
            for (int i = 0; i < a.size(); ++i) {
                // At this point, d == (x^i) % mod
                y = (y + 1LL * a[i] * d) % mod; // the 1LL is to use long longs in the multiplication
                d = (1LL * d * x) % mod;
            }
            ans.insert(y);
        }
        cout << ans.size() << endl;
    }
    return 0;
}
