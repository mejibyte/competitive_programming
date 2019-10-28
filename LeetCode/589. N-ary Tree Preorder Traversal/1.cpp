/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
    enum Event {
        ENTER = 0,
        VISIT = 1,
    };

public:
    vector<int> preorder(Node* root) {
        vector<int> answer;

        s_.push(make_pair(Event::ENTER, root));
        while (s_.size() > 0) {
            auto next = s_.top();
            s_.pop();
            if (next.second == nullptr) {
                continue;
            }
            if (next.first == Event::ENTER) {
                for (int i = next.second->children.size() - 1; i >= 0; --i) {
                    s_.push(make_pair(Event::ENTER, next.second->children[i]));
                }
                s_.push(make_pair(Event::VISIT, next.second));
            } else {  // s.first == Event::VISIT
                answer.push_back(next.second->val);
            }
        }

        return answer;

    }

 private:
    stack<pair<Event, Node*>> s_;
};
