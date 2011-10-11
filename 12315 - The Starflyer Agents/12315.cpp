using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

#define dassert(x) if (false) { assert(x); }

struct node {
    string label;
    vector<node> sons;
    node() { }
    node(const string &lbl) : label(lbl) { }
    bool isVariable() {
        dassert(label.size() > 0);
        return sons.size() == 0 and isupper(label[0]);
    }
    bool isConstant() {
        dassert(label.size() > 0);
        return sons.size() == 0 and islower(label[0]);
    }
    bool isFunction() {
        dassert(label.size() > 0);
        if (sons.size() == 0) dassert(islower(label[0]));
        return sons.size() > 0;
    }
};


node parse(const string &s, int i, int j) {
    if (s[j] != ')') { // constant or variable
        return node(s.substr(i, j - i + 1));
    }
    dassert(s[j] == ')');
    
    int k = i; while (s[k] != '(') k++;
    node ans = node(s.substr(i, k - i));
    // split string from [k+1, j-1]
    int balance = 0;
    for (i = k + 1; i < j; ) {
        k = i;
        while (k <= j) {
            if (s[k] == ')') balance--;
            if (s[k] == '(') balance++;
            if (k == j or s[k] == ',' and balance == 0) {
                node son = parse(s, i, k - 1);
                ans.sons.push_back(son);
                break;
            }
            k++;
        }
        i = k + 1;
    }
    dassert(i == j + 1);
    return ans;
}

void print(const node &t, int depth = 0) {
    for (int i = 0; i < depth; ++i) printf(" ");
    printf("%s\n", t.label.c_str());
    for (int i = 0; i < t.sons.size(); ++i) {
        print(t.sons[i], depth + 1);
    }
}


map<string, node> mapping;

bool contains(node r, const string &variable, int depth = 0) {
    while (r.isVariable() and mapping.count(r.label) > 0) r = mapping[r.label];
    if (r.label == variable) return true;
    for (int i = 0; i < r.sons.size(); ++i) {
        if (contains(r.sons[i], variable, depth + 1)) return true;
    }
    return false;
}


bool unify(const node &A, const node &B, int depth = 0) {
    //if (depth > 4) return false; // Remove this and you'll get a runtime error. Change for depth > 4 and you'll get a runtime error too.
    node a = A, b = B;
    while (a.isVariable() and mapping.count(a.label) > 0) {
        a = mapping[a.label];
    }
    while (b.isVariable() and mapping.count(b.label) > 0) {
        b = mapping[b.label];
    }

    if (a.isConstant()) {   
        if (b.isFunction()) return false;
        if (b.isConstant()) {
            if (a.label == b.label) return true;
            else return false;
        }
    }
    
    if (b.isConstant()) {
        if (a.isFunction()) return false;
        if (a.isConstant()) {
            if (a.label == b.label) return true;
            else return false;
        }
    }
    
    if (a.isVariable() and b.isVariable()) {
        if (a.label == b.label) return true;
        else {
            mapping[a.label] = b;
            return true;
        }
    }
    
    if (a.isVariable()) {
        dassert(!b.isVariable());
        if (contains(b, a.label)) return false;
        else {
            mapping[a.label] = b;
            return true;
        }
    }
    
    if (b.isVariable()){
        dassert(!a.isVariable());
        if (contains(a, b.label)) return false;
        else {
            mapping[b.label] = a;
            return true;
        }
    }
    
    // both are functions
    dassert(a.isFunction() and b.isFunction());
    if (a.label != b.label) return false;
    if (a.sons.size() != b.sons.size()) return false;
    for (int i = 0; i < a.sons.size(); ++i) {
        bool r = unify(a.sons[i], b.sons[i], depth + 1);
        if (!r) return false;
    }
    return true;
}

int main(){
    string s = "f(X,g(c))";
    // s = "f(f(Y),Z)";
    // s = "f(c,g(Y,d))";
    // s = "f(f(a),a)";
    // s = "f(f(f(X,a),a),a)";
    // s = "f(f(f(f(f(f(f(f(f(f(f(X)),d)))),e,f,g(c,c))))),a,a,a,a,a)";
    // s = "f(f(f(f(f(f(f(f(f(f(f(X)),d)))),e,f,g(c,c))))),a,a,a,a,a,f(f(f(f(f(a,n,d,y,m,e,j,i,a,f(f(f(f(f(f(X))))))))))))";
    // s = "X";
    // s = "a";
    // s = "x";
    //node t = parse(s, 0, s.size() - 1);
    //print(t);
    string name; int n;
    while (cin >> name >> n) {
        if (name == "END" and n == 0) break;
        vector<node> trees(n);
        for (int i = 0; i < n; ++i) {
            string expression; cin >> expression;
            trees[i] = parse(expression, 0, expression.size() - 1);
        }
        mapping.clear();
        bool works = true;
        for (int i = 0; i < n - 1 and works; ++i) {
            works &= unify(trees[i], trees[i+1]);
        }
        if (works) {
            printf("analysis inconclusive on %s\n", name.c_str());
        } else {
            printf("%s is a Starflyer agent\n", name.c_str());
        }
    }
    return 0;
}