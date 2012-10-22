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
#include <bitset>
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

int R, C, P;

vector< pair<int, int> > plants;

bool inside(int r, int c) {
    return 1 <= r and r <= R and 1 <= c and c <= C;
}

void solve(int pos) {
    for (int d = 1; ; ++d) {
        
        set< pair<int, int> > cells;
        for (int r = 1; r <= R; ++r) for (int c = 1; c <= C; ++c) cells.insert(make_pair(r, c));
        
        for (int k = 0; k < plants.size(); ++k) {
            
            pair<int, int> plant = plants[k];
            
            set< pair<int, int> > plant_cells;
            
            for (int c = plant.second - d; c <= plant.second + d; ++c) {
                if (inside(plant.first - d, c)) plant_cells.insert( make_pair(plant.first - d, c) );
                if (inside(plant.first + d, c)) plant_cells.insert( make_pair(plant.first + d, c) );
            }
            
            for (int r = plant.first - d; r <= plant.first + d; ++r) {
                if (inside(r, plant.second - d)) plant_cells.insert( make_pair(r, plant.second - d) );
                if (inside(r, plant.second + d)) plant_cells.insert( make_pair(r, plant.second + d) );
            }
            
            vector< pair<int, int> > intersection;
            set_intersection(plant_cells.begin(), plant_cells.end(), cells.begin(), cells.end(), intersection.begin());
        }
        
        

        D(d); D(cells.size());
        foreach(cell, cells) {
            printf("(%d, %d) ", cell->first, cell->second);
        } puts("");
        
        if (cells.size() < pos) {
            pos -= cells.size();
            continue;
        }
        
        int seen = 0;
        foreach(cell, cells) {
            seen++;
            if (seen == pos) {
                cout << cell->first << " " << cell->second << endl;
                return;
            }
        }
    }
}

int main(){
    while (cin >> R >> C >> P) {
        if (R == 0 and C == 0 and P == 0) break;
        plants.clear();
        
        for (int i = 0; i < P; ++i) {
            int r, c; cin >> r >> c;
            plants.push_back( make_pair(r, c) );
        }
        
        int queries; cin >> queries;
        while (queries--) {
            int position; cin >> position;
            solve(position);
        }
        cout << "-" << endl;
    }
    return 0;
}