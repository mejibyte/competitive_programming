using namespace std;
#include <iostream>
#include <algorithm>
#include <iterator>
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
#include <map>
#include <set>
#include <stack>

#define D(x) cout << #x " = " << (x) << endl
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define For (i, a, b) for (int i = (a); i < (b); i++)

#define MAXN 1000

typedef long long ll;

ll w[MAXN+5];

bool greater_first (const int &a, const int &b) {
    return w[a] > w[b];   
}
bool smaller_first (const int &a, const int &b) {
    return w[a] < w[b];   
}

int main (){
    int run = 1;
    int n;
    while(cin>>n) {
        if (n == 0) break;
        
        string from,to;
        cin>>from>>to;
        for (int i = 0; i < n; ++i) {
            cin>>w[i];   
        }
        
        vector <int> off,on,opt;
        ll acuml=0,acumr=0;
        for (int i = 0; i < n; ++i) {
            if (from[i] == '1' && to[i] == '0'){
                off.push_back(i);   
            }
            else if (from[i] == '0' && to[i] == '1') {
                on.push_back(i);
            }
            else if (from[i] == '1' && to[i] == '1'){
                opt.push_back(i);         
            }
            
            if (from[i] == '1') acuml += w[i];
            if (to[i] == '1') acumr += w[i];
        }
        sort(off.begin(),off.end(), greater_first);
        sort(on.begin(),on.end(), smaller_first);
        sort(opt.begin(),opt.end(), greater_first);
      
       // D(acumr);D(acuml);
        vector <ll> X (off.size());
        vector <ll> Y (on.size());
        
        ll acum = 0;
        for (int i = 0; i < off.size(); ++i) {
            X[i] = acuml-acum;
           //cout<<"X["<<i<<"] = "<<X[i]<<endl;
            acum += w[off[i]];   
        }
        acum = 0;
        for (int i = on.size()-1; i >= 0; --i) {
            acum += w[on[i]];
            Y[i] = acumr-acum;
            //cout<<"Y["<<i<<"] = "<<Y[i]<<endl;
        }
        vector <int> def;
        
        for (int i = 0; i < opt.size(); ++i) {
            //cout<<"opt "<<i<<endl;
             int posoff, poson;
             for (posoff = 0; posoff < off.size(); ++posoff) {
                    if (w[off[posoff]] <= w[opt[i]])break;
             }
             for (poson = on.size(); poson > 0; --poson) {
                    if (w[on[poson-1]] <= w[opt[i]]) break;      
             }
             int coston,costoff;
             if (posoff == off.size()) costoff = Y[0];           
             else costoff = X[posoff];
             if (poson == on.size()){
                 coston = acumr;   
             }
             else coston = Y[poson];
            // coston -= w[opt[i]];
             costoff-=w[opt[i]];
             //D(coston);D(costoff);D(poson);D(posoff);
             ll gain = poson+off.size()-posoff;
             //D(gain);
             if (coston+costoff <= 1LL * gain*w[opt[i]]){
                    def.push_back(opt[i]);   
             }
             else break;
        }
        
        //D(def.size());
        
        for (int i = 0; i < def.size(); ++i) {
            off.push_back(def[i]);
            on.push_back(def[i]);   
        }
        sort(off.begin(),off.end(),greater_first);
        sort(on.begin(),on.end(),smaller_first);
        long long res = 0;
        acum = acuml;
        for (int i = 0; i < off.size(); ++i) {
            acum -= w[off[i]];
            res += acum;
        }
        for (int i = 0; i < on.size(); ++i) {
            acum += w[on[i]];
            res += acum;   
        }
        printf("Case %d: ",run++);
        cout<<res<<endl;
    }

    return 0;
}
