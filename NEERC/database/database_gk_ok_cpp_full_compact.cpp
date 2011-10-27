#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    ifstream in; in.open("database.in");
    ofstream out; out.open("database.out");

    int n;
    int m;
    in >> n >> m;
    in.ignore();

    cout << n << endl;
    pair<string, int>* pairs = new pair<string, int>[n * m];
    for (int i = 0; i < n; i++) {
        char buffer[100];

        for (int j = 0; j < m - 1; j++) {
            in.getline(buffer, sizeof(buffer) / sizeof(char), ',');
            pairs[j * n + i] = pair<string, int>(buffer, j * n + i);
        }

        in.getline(buffer, sizeof(buffer) / sizeof(char), '\n');
        pairs[(m - 1) * n + i] = pair<string, int>(buffer, (m - 1) * n + i);
    }

    sort(pairs, pairs + n * m);

    int* a = new int[n * m];
    int index = 0;
    string prev = "";
    for (int i = 0; i < n * m; i++) {
        if (prev != pairs[i].first) {
            prev = pairs[i].first;
            index++;
        }
        a[pairs[i].second] = index;
    }

    for (int c1 = 0; c1 < m; c1++) {
        for (int c2 = c1 + 1; c2 < m; c2++) {
            int* col1 = a + c1 * n;
            int* col2 = a + c2 * n;
            for (int r1 = 0; r1 < n; r1++) {
                int val1 = col1[r1];
                int val2 = col2[r1];
                for (int r2 = r1 + 1; r2 < n; r2++) {
                    if (val1 == col1[r2] && val2 == col2[r2]) {
                        out << "NO" << endl;
                        out << (r2 + 1) << " " << (r1 + 1) << endl;
                        out << (c1 + 1) << " " << (c2 + 1) << endl;
                        return 0;
                    }
                }
            }
        }
    }

    out << "YES" << endl;

    in.close();
    out.close();

    return 0;
}