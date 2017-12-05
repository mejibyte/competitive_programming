class Solution {
    vector<string> tokens;
    int at;
    map<string, stack<int>> mem;

    int add() {
        consume("add");
        int x = expr();
        int y = expr();
        return x + y;
    }
    int mult() {
        consume("mult");
        int x = expr();
        int y = expr();
        return x * y;
    }
    int let() {
        consume("let");
        vector<string> changed;
        while (true) { // While there are variables pending to set...
            if (tokens[at] == "(") break; // (let x 3 (...))
            if (tokens[at + 1] == ")") break; // (let x 3 x)

            string var = tokens[at++];
            int val = expr();
            mem[var].push(val);
            changed.push_back(var);
        }
        int ans = expr();
        for (const string &k : changed) { // Revert memory changes since these variables just went out of scope.
            mem[k].pop();
        }
        return ans;
    }

    int expr() {
        if (tokens[at] == "(") {
            consume("(");
            int ans;
            if (tokens[at] == "add") {
                ans = add();
            } else if (tokens[at] == "mult") {
                ans = mult();
            } else if (tokens[at] == "let") {
                ans = let();
            }
            consume(")");
            return ans;
        } else {
            // "Leaf" expression -- either a variable or a literal.
            if (isalpha(tokens[at][0])) {
                // Get the value from our memory map.
                assert(mem.count(tokens[at]));
                return mem[tokens[at++]].top();
            } else {
                return toInt(tokens[at++]);
            }
        }
        return 0;
    }

    void consume(const string& s) {
        assert(tokens[at++] == s);
    }

    int toInt(const string& t) {
        stringstream s(t);
        int ans;
        assert(s >> ans);
        return ans;
    }

public:
    int evaluate(string expression) {
        string s = "";
        // Add spaces around parentheses so it's easier to tokenize.
        for (char c : expression) {
            if (c == '(') s += c + string(" ");
            else if (c == ')') s += string(" ") + c;
            else s += c;
        }
        // Break down into tokens.
        stringstream tokenizer(s);
        for (string t; tokenizer >> t; ) {
            tokens.push_back(t);
        }

        mem.clear();
        at = 0;
        return expr();
    }
};
