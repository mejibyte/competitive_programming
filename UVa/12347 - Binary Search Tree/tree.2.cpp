// Andrés Mejía
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

vector<int> a;
vector<int> b;

// [i, j)
void traverse(int i, int j) {
    int k = i + 1;
    while (k < j and a[k] < a[i]) k++;
    // left tree goes from [i + 1, k)
    if (i + 1 < k) {
        traverse(i + 1, k);
    }
    // right tree goes from [k, j)
    if (k < j) {
        traverse(k, j);
    }
    b.push_back(a[i]);
}

int main(){
    for (int x; cin >> x; a.push_back(x));
    traverse(0, a.size());
    for (int i = 0; i < b.size(); ++i) cout << b[i] << endl;
    return 0;
}