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

inline long long absll(long long x) {
    return x < 0 ? -x : x;
}      

#define absll(x) ((x) < 0 ? -(x) : (x))

void check(bool expr, string msg) {
    if (!expr) {
        cerr << msg << endl;
        cerr.flush();
        int * p = NULL;
        cout << *p << endl;
    }
}

void checkBounds(int n, int low, int hi, string nStr) {
    check((low <= n) && (n <= hi), nStr + " is not in range");
}

struct Polyhedron {
    vector<int> x, y, z;
    int n;
    vector< vector<int> > facets;
    long long vpa, vpb, vpc, vpd;
    double xc, yc, zc;
    double minDist;

    void inline vectorProduct(int i, int j, int k) {
        int dx1 = x[j] - x[i];
        int dy1 = y[j] - y[i];
        int dz1 = z[j] - z[i];
        int dx2 = x[k] - x[i];
        int dy2 = y[k] - y[i];
        int dz2 = z[k] - z[i];
        vpa = dy1 * dz2 - dy2 * dz1;
        vpb = -(dx1 * dz2 - dx2 * dz1);
        vpc = dx1 * dy2 - dx2 * dy1;
        vpd = -vpa * x[i] - vpb * y[i] - vpc * z[i];
    }

    void checkConvexFacet(long long a, long long b, long long c, long long d, vector<int> &facet) {
        int m = facet.size();
        int num1 = facet[0];
        for (int i = 1; i < m; i++) {
            for (int j = 1; j + 1 < m; j++) {
                int num2 = facet[j];
                int num3 = facet[j + 1];
                vectorProduct(num1, num2, num3);
                long long sp = a * vpa + b * vpb + c * vpc;
                //check(sp != 0, "Three points on a line");
                if (sp < 0) {
                    facet[j] = num3;
                    facet[j + 1] = num2;
                }
            }
        }
        // for (int i = 0; i < m; i++) {
        //     for (int j = i + 1; j < m; j++) {
        //         for (int k = j + 1; k < m; k++) {
        //             vectorProduct(facet[i], facet[j], facet[k]);
        //             long long sp = a * vpa + b * vpb + c * vpc;
        //             check(sp > 0, "Facet not convex");
        //         }
        //     }
        // }
    }

    long long inline calcVolume(int a, int b, int c, int d) {
        vectorProduct(a, c, d);
        return absll((x[b] - x[a]) * vpa + (y[b] - y[a]) * vpb + (z[b] - z[a]) * vpc);
    }

    Polyhedron() {
        scanf("%d", &n);
        //checkBounds(n, 1, 100, "n");
        x = vector<int>(n);
        y = vector<int>(n);
        z = vector<int>(n);
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &x[i], &y[i], &z[i]);
        }
       
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    bool stop = false;
                    vectorProduct(i, j, k);
                    long long a = vpa;
                    long long b = vpb;
                    long long c = vpc;
                    long long d = vpd;
                   
                    bool negative = false;
                    bool positive = false;
                    for (int u = 0; u < n; u++) {
                        long long dist = a * x[u] + b * y[u] + c * z[u] + d;
                        if (dist < 0) {
                            negative = true;
                        } else if (dist > 0) {
                            positive = true;
                        } else {
                            if ((u < k) && (u != i) && (u != j)) {
                                stop = true;
                            }
                        }
                    }
                    if (stop) continue;
                    //printf("Passed with i = %d, j = %d, k = %d\n", i, j, k);
                    if (positive && negative) {
                        continue;
                    }
                    
                    vector<int> facet;
                    facet.push_back(i);
                    facet.push_back(j);
                    facet.push_back(k);
                    for (int u = k + 1; u < n; u++) {
                        if (a * x[u] + b * y[u] + c * z[u] + d == 0) {
                            facet.push_back(u);
                        }
                    }
//                        System.err.println(Arrays.toString(facet.toArray()));
                    checkConvexFacet(a, b, c, d, facet);
                    facets.push_back(facet);
                }
            }
        }
        //check(facets.size() > 1, "polyhedron is degenerate");
       
        long long totalVolume = 0;
        long long x0 = 0;
        long long y0 = 0;
        long long z0 = 0;
        //printf("facets.size() = %d\n", facets.size());
        for (int k = 0; k < facets.size(); ++k) {
            const vector<int> &facet = facets[k];
            
            //printf("facets[%d] = ", k); for (int i = 0; i < facet.size(); ++i) printf("%d ", facet[i]); printf("\n");
            
            int m = facet.size();
            int num1 = facet[0];
            for (int i = 0; i < m; i++) {
                int num2 = facet[i];
                int num3 = facet[(i + 1) % m];
                long long volume = calcVolume(0, num1, num2, num3);
                totalVolume += volume;
                x0 += (volume) * (x[num1] + x[num2] + x[num3] + x[0]);
                y0 += (volume) * (y[num1] + y[num2] + y[num3] + y[0]);
                z0 += (volume) * (z[num1] + z[num2] + z[num3] + z[0]);
            }
        }
        xc = 1.0 * x0 / totalVolume / 4.0;
        yc = 1.0 * y0 / totalVolume / 4.0;
        zc = 1.0 * z0 / totalVolume / 4.0;
//            System.err.println(xc + " " + yc + " " + zc);
//            System.err.println(totalVolume);
        // printf("x0 = %lld, y0 = %lld, z0 = %lld, totalVolume = %lld\n", x0, y0, z0, totalVolume);
        // printf("Center of mass = (%.4lf, %.4lf, %.4lf)\n", xc, yc, zc);
       
        minDist = 1e100;       
        int m = facets.size();
        for (int k = 0; k < m; ++k) {
            const vector<int> &facet = facets[k];
            vectorProduct(facet[0], facet[1], facet[2]);
            double norm = sqrt(vpa * vpa + vpb * vpb + vpc * vpc);
            double dist = (vpa * xc + vpb * yc + vpc * zc + vpd) / norm;
            dist = abs(dist);
            if (dist < minDist) minDist = dist;
        }
    }
};

void solve() {
    Polyhedron p1;
    Polyhedron p2;
    printf("%.6f\n", p1.minDist + p2.minDist);
}

int main(){
    solve();
    return 0;
}