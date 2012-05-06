using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <bitset>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

int n, m;
vector<string> words;
set<string> ans;

void build(const string &text) {
    if (text.size() > m) return;
    ans.insert(text);
    for (int i = 0; i < words.size(); ++i) build(text + words[i]);
}


int main(){
    cin >> n >> m;
    words.resize(n);
    for (int i = 0; i < n; ++i) cin >> words[i];

    build("");
    cout << ans.size() << endl;
    
    cerr << "These are the Hyper Super Strings: " << endl;
    int i = 1;
    for (set<string>::iterator s = ans.begin(); s != ans.end(); ++s) {
        cerr << i++ << ": " << *s << endl;
    }
    return 0;
}