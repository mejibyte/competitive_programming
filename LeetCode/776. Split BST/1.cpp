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
public:
    vector<TreeNode*> splitBST(TreeNode* root, int V) {
        if (root == nullptr) {
            return {nullptr, nullptr};
        }
        if (root->val <= V) {
            auto right = splitBST(root->right, V);
            root->right = right[0];
            return {root, right[1]};
        } else {
            auto left = splitBST(root->left, V);
            root->left = left[1];
            return {left[0], root};
        }
    }
};
