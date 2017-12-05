class MaxStack {
public:
    /** initialize your data structure here. */

    set<pair<int, int>> pos_to_val, val_to_pos;
    int next;

    MaxStack() {
        next = 0;
    }

    void push(int x) {
        pos_to_val.insert(make_pair(next, x));
        val_to_pos.insert(make_pair(x, next++));
    }

    int pop() {
        pair<int, int> k = *--pos_to_val.end();
        erase(k.first, k.second);
        return k.second;
    }

    int top() {
        pair<int, int> k = *--pos_to_val.end();
        return k.second;
    }

    int peekMax() {
        pair<int, int> k = *--val_to_pos.end();
        return k.first;
    }

    int popMax() {
        pair<int, int> k = *--val_to_pos.end();
        erase(k.second, k.first);
        return k.first;
    }

    private:
    void erase(int pos, int val) {
        pos_to_val.erase(make_pair(pos, val));
        val_to_pos.erase(make_pair(val, pos));
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack obj = new MaxStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.peekMax();
 * int param_5 = obj.popMax();
 */
