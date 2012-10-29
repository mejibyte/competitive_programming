using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

#define D(x) cout << #x " = " << (x) << endl

struct Gor{
    double x, y, r;
    
    Gor (double a, double b, double c){
        x = a; y = b; r = c;    
    }
    
    bool meet(Gor g){
        double d = sqrt((g.x - x)*(g.x - x) + (g.y - y)*(g.y - y));
        if (d <= max(g.r, r)) return true;
        return false;
    }
};

vector <Gor> a;

void merge(){
    while (true){
        vector <int> go;
        bool found = false;
        int n = a.size();
        for (int i = 0; i < n - 1; i++){
            if (a[n-1].meet(a[i])){
                found = true;
                go.push_back(i);
            }
        }  
        if (!found) return; 
        go.push_back(n - 1);
        sort(go.begin(), go.end(), greater<int>());
        
        double new_x = 0;
        double new_y = 0;
        double new_r = 0;
        
        for (int i = 0; i < go.size(); i++){
            new_x += a[go[i]].x;
            new_y += a[go[i]].y; 
            new_r += a[go[i]].r * a[go[i]].r;  
            a.erase(a.begin() + go[i]);
        }
        
        new_x = new_x / go.size();
        new_y = new_y / go.size();
        new_r = sqrt(new_r);        
        
        a.push_back(Gor(new_x, new_y, new_r));        
    }    
}

int main(){
    int n;
    while (cin >> n){
        if (n == 0) break;
        a.clear();
        for (int i = 0; i < n; i++){
            double x, y, r;
            cin >> x >> y >> r;
            a.push_back(Gor(x, y, r));
            merge();    
        }
        cout << a.size() << endl;
    }
    
    
    
    return 0;
}
