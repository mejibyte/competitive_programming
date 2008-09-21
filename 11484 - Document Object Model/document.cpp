#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cassert>
using namespace std;

#define D(x) cout << #x " es " << x << endl

int main(){
    int n, C=1;
    while (cin >> n && n){
        string line;
        getline(cin, line);
        int m = n/2;
        string content[m];
        int parent[m];
        parent[0] = -10000;
        vector<int> childs[m];
        stack<int> stk;
        for (int x = 0, i = 0; x < n; ++x){
            getline(cin, line);            
            if (line == "</n>"){
	      stk.pop();
            }else{
               string s = "";
               int j = line.find_first_of("'");
               char delimiter = line[j];
               while (assert(j < line.size()), line[++j] != delimiter){
                  s += line[j];
               }
               content[i] = s;
               if (stk.size() > 0){
                  childs[stk.top()].push_back(i);
                  parent[i] = stk.top();
                  //D(parent[i]), D(content[i]);
               }
               stk.push(i);
               ++i;
            }
        }
        
        int p = 0, q = 0; //p = nodo en donde estoy, q = id de p en la lista de sus hermanos
        int I;
        cout << "Case " << C++ << ":" << endl;
        cin >> I;
        while (I--){
           string s;
           cin >> s;
           int x, y;
           //D(s), D(p), D(q);
           bool valid = true;
           if (s == "first_child"){
               if (childs[p].size() <= 0) valid = false;
               else{
                   x = childs[p][0];
                   y = 0;
               }
           }else if (s == "next_sibling"){
                 y = q+1;
                 if (parent[p] < 0 || y >= childs[parent[p]].size()) valid = false;
                 else x = childs[parent[p]][y];
           }else if (s == "previous_sibling"){
                 y = q-1;
                 if (parent[p] < 0 || y < 0 || y >= childs[parent[p]].size()) valid = false;
                 else x = childs[parent[p]][y];
           }else if (s == "parent"){
                 x = parent[p], y = 0;
                 if (x < 0) valid = false;
           }
           //D(valid);
           if (valid){
               cout << content[x] << endl;
               p = x, q = y;
           }
           else cout << content[p] << endl;
        }
    }
    return 0;
}
