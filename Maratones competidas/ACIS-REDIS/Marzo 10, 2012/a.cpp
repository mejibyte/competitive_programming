using namespace std;
#include <string>
#include <iostream>

int main() {
    int casos; cin >> casos;
    while (casos--) {
        string s; 
        int id, r;
        cin >> id >> r >> s;
        cout << id << " ";
        for (int i = 0; i < s.size(); ++i) {
            for (int j = 0; j < r; ++j) cout << s[i];
        }
        cout << endl;
    }
    return 0;
}
