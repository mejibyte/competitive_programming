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
        int r = right;
        right = top;
        top = left;
        left = bottom;
        bottom = r;
    }
    
    void rotateLeft() {
        int l = left;
        left = top;
        top = right;
        right = bottom;
        bottom = l;
    }
    
    void rotateDown() {
        int f = front;
        front = top;
        top = back;
        back = bottom;
        bottom = f;
    }
};

int main(){
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    long long sum = 0;
    Die die;
    for (int i = 0; i < rows; ++i) {
        Die d = die;
        for (int k = 0; k < 4; ++k) { 
            sum += (cols - 1) / 4 * d.top;
            d.rotateRight(); // or left, who cares.
        }
        
        int extra = (cols + 3) % 4;
        sum += die.top;
        for (int k = 0; k < extra; ++k) {
            i % 2 == 0 ? die.rotateRight() : die.rotateLeft();
            sum += die.top;
        }

        die.rotateDown();
    }
    printf("%lld\n", sum);
    
    return 0;
}