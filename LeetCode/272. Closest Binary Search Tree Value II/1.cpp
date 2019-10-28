/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// O(k) amortized.
class Solution {
public:

    string s(TreeNode* u) {
        if (u == nullptr) {
            return "null";
        } else {
            stringstream sin;
            sin << u->val;
            return sin.str();
        }
    }

    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> answer;

        TreeNode* left = find1(root, target, nullptr);
        TreeNode* right = find2(root, target, nullptr);

        //cout << "right: " << s(right) << endl;
        //cout << "parent(right) = " << s(parent[right]) << endl;
        //cout << s(prev(left)) << " " <<  s(left) << " " << s(right) << " " <<  s(next(right)) << endl;
        while (answer.size() < k) {
            assert(left != nullptr || right != nullptr);
            if (left == nullptr) {
                answer.push_back(right->val);
                right = next(right);
                continue;
            }
            if (right == nullptr) {
                answer.push_back(left->val);
                left = prev(left);
                continue;
            }
            // Both not null
            if (target - left->val < right->val - target) {
                answer.push_back(left->val);
                left = prev(left);
            } else {
                answer.push_back(right->val);
                right = next(right);
            }
        }
        return answer;

    }

    // Find largest element <= target
    TreeNode* find1(TreeNode* u, double target, TreeNode* p) {
        if (u == nullptr) return nullptr;
        parent[u] = p;
        if (u->val > target) {
            return find1(u->left, target, u);
        } else {
            assert(u->val <= target);
            // I could be the largest element unless there is one on my right side.
            TreeNode* r = find1(u->right, target, u);
            return r != nullptr ? r : u;
        }
    }

    // Find smallest element > target
    TreeNode* find2(TreeNode* u, double target, TreeNode* p) {
        if (u == nullptr) return nullptr;
        parent[u] = p;
        if (u->val <= target) {
            return find2(u->right, target, u);
        } else {
            assert(u->val > target);
            // I could be the smallest element unless there is one on my left.
            TreeNode* l = find2(u->left, target, u);
            return l != nullptr ? l : u;
        }

    }

    // Finds leftmost element in subtree rooted at u.
    TreeNode* leftmost(TreeNode* u) {
        while (u->left != nullptr) {
            parent[u->left] = u;
            u = u->left;
        }
        return u;
    }

    // Finds rightmost element in subtree rooted at u.
    TreeNode* rightmost(TreeNode* u) {
        while (u->right != nullptr) {
            parent[u->right] = u;
            u = u->right;
        }
        return u;
    }

    // Finds immediately next element in tree.
    TreeNode* next(TreeNode* u) {
        if (u == nullptr) return nullptr;
        if (u->right != nullptr) {
            parent[u->right] = u;
            return leftmost(u->right);
        }
        // Go up and to the left as much as I want
        while (parent[u] != nullptr && parent[u]->right == u) {
            u = parent[u];
        }
        // Then go once up and to the right
        if (parent[u] != nullptr && parent[u]->left == u) {
            return parent[u];
        }
        return nullptr;
    }

    // Finds immediately previous element in tree.
    TreeNode* prev(TreeNode* u) {
        if (u == nullptr) return nullptr;
        if (u->left != nullptr) {
            parent[u->left] = u;
            return rightmost(u->left);
        }
        // Go up and to the left as much as I want
        while (parent[u] != nullptr && parent[u]->left == u) {
            u = parent[u];
        }
        // Then go once up and to the left
        if (parent[u] != nullptr && parent[u]->right == u) {
            return parent[u];
        }
        return nullptr;
    }

 private:
    unordered_map<TreeNode*, TreeNode*> parent;

};
