/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    map<int, vector<int>> ans;
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        dfs(root);
        vector<vector<int>> v;
        for (auto k : ans) {
            v.emplace_back(std::move(k.second));
        }
        return v;
    }

    int dfs(TreeNode* t) {
        if (t == nullptr) return 0;
        int mine = max(dfs(t->left), dfs(t->right)) + 1;
        ans[mine].push_back(t->val);
        return mine;
    }
};
