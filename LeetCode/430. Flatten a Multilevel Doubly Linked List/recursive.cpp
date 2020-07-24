/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};
*/
class Solution {
public:
    Node* flatten(Node* head) {
        auto f = flattenImpl(head);
        return f.first;
    }

    // Flattens the given list inline and returns a pointer to the head and tail.
    pair<Node*, Node*> flattenImpl(Node* head) {
        if (head == nullptr) return {nullptr, nullptr};

        auto children = flattenImpl(head->child);
        auto next = flattenImpl(head->next);
        head->child = nullptr;

        Node* tail = head;
        if (children.first != nullptr) {
            append(tail, children.first);
            tail = children.second;
        }
        if (next.first != nullptr) {
            append(tail, next.first);
            tail = next.second;
        }
        return {head, tail};
    }

    void append(Node* tail, Node* next) {
        assert(tail != nullptr and next != nullptr);
        tail->next = next;
        tail->next->prev = tail;
    }
};