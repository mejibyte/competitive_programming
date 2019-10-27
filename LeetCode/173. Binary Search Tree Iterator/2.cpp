/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct Event {
  enum EventType {
    ENTER = 0,
    VISIT = 1,
  };

  TreeNode* at;
  EventType type;

  Event( EventType type, TreeNode* at) : type(type), at(at) {}
};

class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        if (root != nullptr) {
            s_.push(Event(Event::ENTER, root));
        }
    }

    /** @return the next smallest number */
    int next() {
        while (s_.size() > 0) {
            Event current = s_.top();
            s_.pop();
            assert(current.at != nullptr);

            if (current.type == Event::ENTER) {
                if (current.at->right != nullptr) {
                    s_.push(Event(Event::ENTER, current.at->right));
                }

                s_.push(Event(Event::VISIT, current.at));

                if (current.at->left != nullptr) {
                    s_.push(Event(Event::ENTER, current.at->left));
                }
            } else { // Event::VISIT
                return current.at->val;
            }
        }
        assert(false);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return s_.size() > 0;
    }
 private:
    stack<Event> s_;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
