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
    enum Event {
        ENTER = 0,
        VISIT = 1,
    };

 public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> answer;

        s_.push(make_pair(Event::ENTER, root));
        while (s_.size() > 0) {
            auto next = s_.top();
            s_.pop();
            if (next.second == nullptr) {
                continue;
            }
            if (next.first == Event::ENTER) {
                s_.push(make_pair(Event::ENTER, next.second->right));
                s_.push(make_pair(Event::ENTER, next.second->left));
                s_.push(make_pair(Event::VISIT, next.second));
            } else {  // s.first == Event::VISIT
                answer.push_back(next.second->val);
            }
        }

        return answer;
    }

 private:
    stack<pair<Event, TreeNode*>> s_;

};
