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
            map<string, map<string, int>*> outter;
            for (int r1 = 0; r1 < n; r1++) {
                map<string, int>* inner;
                map<string, map<string, int>*>::iterator iter = outter.find(values[r1]->at(c1));
                if (iter != outter.end()) {
                    inner = iter->second;
                } else {
                    inner = new map<string, int>();
                    outter[values[r1]->at(c1)] = inner;
                }
                if (inner->find(values[r1]->at(c2)) != inner->end()) {
                    int r2 = inner->find(values[r1]->at(c2))->second;

                    out << "NO" << endl;
                    out << (r2 + 1) << " " << (r1 + 1) << endl;
                    out << (c1 + 1) << " " << (c2 + 1) << endl;
                    return 0;
                } else {
                    (*inner)[values[r1]->at(c2)] = r1;
                }
            }
        }
    }

    out << "YES" << endl;

    in.close();
    out.close();

    return 0;
}