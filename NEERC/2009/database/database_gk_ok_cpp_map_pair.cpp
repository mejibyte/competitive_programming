#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
    vector<vector<string>*> values;
    for (int i = 0; i < n; i++) {
        char buffer[100];
        vector<string>* row = new vector<string>();

        for (int j = 0; j < m - 1; j++) {
            in.getline(buffer, sizeof(buffer) / sizeof(char), ',');
            row->push_back(buffer);
        }

        in.getline(buffer, sizeof(buffer) / sizeof(char), '\n');
        row->push_back(buffer);

        values.push_back(row);
    }

    for (int c1 = 0; c1 < m; c1++) {
        cout << c1;
        for (int c2 = c1 + 1; c2 < m; c2++) {
            map<pair<string, string>, int> map;
            for (int r1 = 0; r1 < n; r1++) {
                string s1 = values[r1]->at(c1);
                string s2 = values[r1]->at(c2);
                pair<string, string> s(s1, s2);
                if (map.find(s) != map.end()) {
                    int r2 = map.find(s)->second;

                    out << "NO" << endl;
                    out << (r2 + 1) << " " << (r1 + 1) << endl;
                    out << (c1 + 1) << " " << (c2 + 1) << endl;
                    return 0;
                }
                map[s] = r1;
            }

        }
    }

    out << "YES" << endl;

    in.close();
    out.close();

    return 0;
}