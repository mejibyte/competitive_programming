/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// O(height + k) amortized.
class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> answer;

        stack<TreeNode*> small;
        stack<TreeNode*> large;

        // This loop is O(height).
        for (TreeNode* at = root; at != nullptr; ) {
            if (at->val < target) {
                small.push(at);
                at = at->right;
            } else {  // at->val >= target
                large.push(at);
                at = at->left;
            }
        }

        // small contains only elements < target, sorted in ascending order (smallest at the bottom
        // and largest at the top). The element at the top is the largest possible element in the
        // tree that is still < target. We can use this stack to iterate the tree starting from that
        // element and going back down one element at a time. In other words, we are iterating over
        // all elements < target in descending order.


        // large contains only elements >= target, sorted in descending order (largest at the bottom
        // and smallest at the top). The element at the top is the smallest possible element in the
        // tree that is still >= target. We can use this stack to iterate the tree starting from
        // that element and going forward one element at a time. In other words, we are iterating
        // over all elements >= target in ascending order.

        auto left = prev(small);
        auto right = next(large);
        // The operations inside this loop are all O(1) amortized, so the complexity of the loop
        // is O(k).
        while (answer.size() < k) {
            assert(left != nullptr or right != nullptr);

            if (left == nullptr) {
                answer.push_back(right->val);
                right = next(large);
            } else if (right == nullptr) {
                answer.push_back(left->val);
                left = prev(small);
            } else if (target - left->val < right->val - target) {
                answer.push_back(left->val);
                left = prev(small);
            } else {
                answer.push_back(right->val);
                right = next(large);
            }
        }
        return answer;

    }

    // Returns the top element in the stack and updates the stack to make sure the new element at
    // the top is the immediately next larger element.
    // The immediately next larger element is either going to be the deepest left element on the
    // right subtree or the smallest larger ancestor (which is already in the stack).
    // Complexity: Amortized O(1) because each element is pushed and popped at most once, so after
    // n calls the total complexity is O(n).
    TreeNode* next(stack<TreeNode*>& large) {
        if (large.size() == 0) return nullptr;
        auto answer = large.top();
        large.pop();
        for (auto at = answer->right; at != nullptr; at = at->left) {
            large.push(at);
        }
        return answer;
    }

    // Returns the top element in the stack and updates the stack to make sure the new element at
    // the top is the immediately previous smaller element.
    // The immediately previous smaller element is either going to be the deepest right element on
    // the left subtree or the largest smaller ancestor (which is already in the stack).
    // Complexity: Amortized O(1) because each element is pushed and popped at most once, so after
    // n calls the total complexity is O(n).
    TreeNode* prev(stack<TreeNode*>& small) {
        if (small.size() == 0) return nullptr;
        auto answer = small.top();
        small.pop();
        for (auto at = answer->left; at != nullptr; at = at->right) {
            small.push(at);
        }
        return answer;
    }
};
