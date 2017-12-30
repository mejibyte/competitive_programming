#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

void solve() {
    int n;
    long long d;
    cin >> n >> d;
    vector<long long> seen;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        seen.push_back(x);
        sort(seen.begin(), seen.end());

        long long ans = d;
        if (seen.size() == 1) {
            ans = 0;
        } else if (seen.size() == 2) {
            ans = max(d - seen.back() + seen.front(), 0LL);
        } else {
            long long a = seen.front(), b = seen.back();

            vector<long long> uncovered;
            for (int i = 1; i < seen.size()-1; ++i) {
                if (b-d < seen[i] and seen[i] < a+d) {
                    uncovered.push_back(seen[i]);
                }
            }

            // puts("");
            // printf("a=%lld, b=%lld\n", a, b);
            // if (i==n-1) printf("uncovered: "); for (auto x : uncovered) cout << x << " "; cout << endl;

            if (uncovered.size() == 0) {
                ans = 0LL;
            } else {
                ans = min(ans, max(a + d - uncovered.front(), 0LL));
                ans = min(ans, max(uncovered.back() - b + d, 0LL));
                for (int p = 0; p+1 < uncovered.size(); ++p) {
                    long long option = a+d-uncovered[p+1] + uncovered[p]-b+d;
                    ans = min(ans, option);
                }
            }
        }

        if (i > 0) cout << " ";
        cout << (ans < 0 ? 0 : ans);
    }
    cout << endl;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int cases;
    cin >> cases;
    while (cases--) solve();
    return 0;
}
