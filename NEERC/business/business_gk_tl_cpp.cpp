/* O(n * m) */
#include <fstream>

using namespace std;

int main() {
    ifstream in; in.open("business.in");
    ofstream out; out.open("business.out");

    int n, m;
    in >> n >> m;

    int result = 1000000000;
    for (int i = 0; i < m; i++) {
        int u, d;
        in >> u >> d;

        for (int j = 0; j <= n; j++) {
            int f = u * j - d * (n - j);
            if (f > 0) {
                result = min(result, f);
            }
        }
    }
    out << result << endl;

    in.close();
    out.close();

    return 0;
}