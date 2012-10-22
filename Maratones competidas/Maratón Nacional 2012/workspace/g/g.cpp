// Equipo Ultimatum

using namespace std;
# include <algorithm>
# include <iostream>
# include <iterator>
# include <sstream>
# include <fstream>
# include <cassert>
# include <cstdlib>
# include <string>
# include <cstring>
# include <cstdio>
# include <vector>
# include <cmath>
# include <queue>
# include <stack>
# include <map>
# include <set>

#define For(i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != v.end(); x++)
#define D(x) cout << #x  " = " << (x) << endl

const double EPS = 1e-9;
int cmp (double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

int main () {
    freopen("garden.in", "r", stdin);
    int l,n;
    while(cin>>l>>n) {
        if (l == 0 && n == 0) break;
      //  D(l);D(n);
        if (l == 1) {
            cout<<4*n<<endl;  
            continue; 
        }
        int total = l*l-n;
    //    D(total);
        int perim = 4*l;
        if (total <= 0) {
            cout<<perim<<endl; 
            continue;  
        }
     //   D(perim);
        int next;
        next = ((l-2)*(l-2)+1)/2; //AJEDREZ INTERIOR
        if (next > total && (l&1)) 
            next = ((l-2)*(l-2)-1)/2;
        if (total <= next) { 
            perim += 4*total;
            cout<<perim<<endl;
          //  puts(" fue ajedrez");
            continue;   
        }
        perim += 4*next;
        total -= next;
    //    D(perim);
        if (!(l&1))
            next = 4*(l/2-1); //BORDE (interior)
        else
            next = 2*(l-1);
        if (total <= next) {
            perim += 2*total;
            cout<<perim<<endl;
            continue;
        }
        perim += 2*next;
        total -= next;  
        next = 2-(2*(l&1));
        if (total <= next) { //ESQUINAS
            cout<<perim<<endl;
            continue; 
        }
        total -= next; //RESTO
        perim -= 4*total;
      //  puts("ANS");
        cout<<perim<<endl;
        
    }
    return 0;
}
