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
    map<TreeNode*, int> time_in, time_out;
    enum { IN, OUT };

    void dfs(TreeNode* t) {
        int time = 0;
        stack<pair<int, TreeNode*>> s;
        s.push(make_pair(IN, t));
        while (s.size() > 0) {
            int type = s.top().first;
            TreeNode* t = s.top().second;
            s.pop();
            if (t == nullptr) continue;
            if (type == IN) {
                time_in[t] = time++;
                s.push(make_pair(OUT, t));
                s.push(make_pair(IN, t->right));
                s.push(make_pair(IN, t->left));
            } else if (type == OUT) {
                time_out[t] = time++;
            }
        }
    }

    bool is_ancestor(TreeNode* a, TreeNode* b) {
        return time_in[a] <= time_in[b] and time_out[b] <= time_out[a];
    }

    TreeNode* find(TreeNode* root, TreeNode* a, TreeNode* b) {
        while (true) {
            assert(root != nullptr and a != nullptr and b != nullptr);
            assert(is_ancestor(root, a));
            assert(is_ancestor(root, b));
            if (root->left != nullptr and is_ancestor(root->left, a) and is_ancestor(root->left, b)) {
                root = root->left;
            } else if (root->right != nullptr and is_ancestor(root->right, a) and is_ancestor(root->right, b)) {
                root = root->right;
            } else {
                return root;
            }
        }
        return root;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root);
        return find(root, p, q);
    }
};
