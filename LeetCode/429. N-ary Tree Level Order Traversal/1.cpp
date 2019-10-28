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
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> answer;
        if (root == nullptr) return answer;

        queue<pair<Node*, int>> q; // <node, depth>
        q.push(make_pair(root, 1));
        while (q.size() > 0) {
            Node* at = q.front().first;
            int depth = q.front().second;
            q.pop();

            if (answer.size() < depth) {
                answer.push_back(vector<int>());
            }
            answer[depth - 1].push_back(at->val);

            for (Node* c : at->children) {
                q.push(make_pair(c, depth + 1));
            }
        }
        return answer;
    }
};
