/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        if (root != nullptr) {
            s.push(make_pair(0, root));
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return s.size() > 0;
    }

    /** @return the next smallest number */
    int next() {
        while (s.size() > 0) {
            auto at = s.top();
            s.pop();

            if (at.first == 1 /* visit */) {
                return at.second->val;
            } else {
                if (at.second->right != nullptr) s.push(make_pair(0, at.second->right));
                s.push(make_pair(1, at.second));
                if (at.second->left != nullptr) s.push(make_pair(0, at.second->left));
            }
        }
        assert(false);
    }
private:
    std::stack<pair<int, TreeNode*> > s;
};



/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
