/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
      if (root != nullptr) {
          pushChainOfLefts(root);
      }
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* next = s_.top();
        s_.pop();
        if (next->right != nullptr) {
            pushChainOfLefts(next->right);
        }
        return next->val;
    }

    void pushChainOfLefts(TreeNode* at) {
        assert(at != nullptr);
        while (at != nullptr) {
            s_.push(at);
            at = at->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return s_.size() > 0;
    }
 private:
    stack<TreeNode*> s_;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
