using namespace std;
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

int main() {
    int A, D;
    while (cin >> A >> D) {
        if (A == 0 and D == 0) break;
        vector<int> a(A), d(D);
        for (int i = 0; i < A; ++i) cin >> a[i];
        for (int i = 0; i < D; ++i) cin >> d[i];
        sort(d.begin(), d.end());
    
        bool offside = false;
        for (int i = 0; i < A; ++i) {
            if (a[i] < d[1]) offside = true;
        }
        
        if (offside) cout << "Y" << endl;
        else cout << "N" << endl;
    }
    return 0;
}