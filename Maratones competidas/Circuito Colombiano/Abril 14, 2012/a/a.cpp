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

string toStr(long long x) {
    stringstream sin;
    sin << x;
    return sin.str();
}

int len;

void print(long long num, int trailing) {
    int leading = len - toStr(num).size() - trailing;
    for (int i = 0; i < leading; ++i) cout << " ";
    cout << num << endl;
}

void separator() {
    for (int i = 0; i < len; ++i) printf("-");
    cout << endl;
}

int main(){
    int run = 1;
    long long a, b;
    while (cin >> a  >> b) {
        if (a == 0 and b == 0) break;
        
        long long res = a * b;
        
        len = toStr(res).size();

        vector<long long> p;
        for (long long bb = b; bb > 0; bb /= 10) {
            p.push_back( a * (bb % 10) );
        }
        
        printf("Problem %d\n", run++);
        
        print(a, 0);
        print(b, 0);
        separator();
       
        long long power[15];
        power[0] = 1;
        for (int i = 1; i < 15; ++i) power[i] = power[i - 1]*10;
        
        int count = 0;
        for (int i = 0; i < p.size(); ++i) {
            
            int after = i;
            
            int zeros = 0;
            while (i < p.size() and p[i] == 0) {
                zeros++;
                i++;
            }

            long long num = p[i];
            num *= power[zeros];
            print(num, after);
            count++;
        }
       
        if (count > 1) {
            separator();
            print(a * b, 0);
        }
        
        
    }
    return 0;
}
