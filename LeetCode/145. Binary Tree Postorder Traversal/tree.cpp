// Andrés Mejía
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
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


enum { ENTER, EXIT };

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
      vector<int> ans;
      stack<pair<int, TreeNode*>> s;
      s.push(make_pair(ENTER, root));
      while (s.size() > 0) {
        pair<int, TreeNode*> event = s.top();
        s.pop();
        TreeNode* node = event.second;
        if (node == nullptr) continue;

        if (event.first == EXIT) {
          ans.push_back(node->val);
        } else {
          s.push(make_pair(EXIT, node));
          s.push(make_pair(ENTER, node->right));
          s.push(make_pair(ENTER, node->left));
        }
      }
      return ans;
    }
};

int main(){
    Solution s;
    TreeNode a(1), b(2), c(3), d(4);
    a.left = &b;
    a.right = &c;
    auto ans = s.postorderTraversal(&a);
    for (int k : ans) D(k);
    return 0;
}
