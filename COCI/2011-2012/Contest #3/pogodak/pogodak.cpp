// Andrés Mejía
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

struct Die {
    int top, bottom, front, back, left, right;
    Die() {
        top = 1; bottom = 6; front = 2; back = 5; left = 4; right = 3;
    }
    
    void rotateRight() {
        int t = top, bo = bottom, f = front, ba = back, l = left, r = right;
        right = t;
        top = l;
        left = bo;
        bottom = r;
    }
    
    void rotateLeft() {
        int t = top, bo = bottom, f = front, ba = back, l = left, r = right;
        left = t;
        top = r;
        right = bo;
        bottom = l;
    }
    
    void rotateDown() {
        int t = top, bo = bottom, f = front, ba = back, l = left, r = right;
        
        front = t;
        top = ba;
        back = bo;
        bottom = f;
    }
};

int main(){
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    long long sum = 0;
    Die die;
    for (int i = 0; i < rows; ++i) {
        if (i % 2 == 0) { // right
            int period[4];
            
            Die d = die;
            for (int i = 0; i < 4; ++i) { period[i] = d.top; d.rotateRight(); }
            
            for (int i = 0; i < 4; ++i) sum += period[i] * ((cols - 1) / 4);

            int extra = (cols + 3) % 4;
            
            sum += die.top;
            for (int i = 0; i < extra; ++i) {
                die.rotateRight();
                sum += die.top;
            }
            
        } else { // left
            int period[4];
            
            Die d = die;
            for (int i = 0; i < 4; ++i) { period[i] = d.top; d.rotateLeft(); }
            
            for (int i = 0; i < 4; ++i) sum += period[i] * ((cols - 1) / 4);

            int extra = (cols + 3) % 4;
            
            sum += die.top;
            for (int i = 0; i < extra; ++i) {
                die.rotateLeft();
                sum += die.top;
            }
            
        }
        die.rotateDown();
    }
    printf("%lld\n", sum);
    
    return 0;
}