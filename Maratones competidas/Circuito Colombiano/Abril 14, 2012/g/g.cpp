using namespace std;
#include <algorithm>
#include <cstring>
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

const int MAXN =  20;

bool pared[MAXN][MAXN];
bool hueco[MAXN][MAXN];
bool caja[MAXN][MAXN];

bool vacio(int i, int j) {
    return !pared[i][j] and !caja[i][j];
}

int rows, cols;

bool todoAdentro() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (caja[i][j] and !hueco[i][j]) return false;
            if (hueco[i][j] and !caja[i][j]) return false;
        }
    }
    return true;
}

void print(int yor, int yoc){
  for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                bool estoy = (yor == i and yoc == j);
                
                if (pared[i][j]) {
                    cout << "#";
                    continue;
                }
                
                if (hueco[i][j]) {
                    if (caja[i][j]) cout << "B";
                    else if (estoy) cout << "W";
                    else cout << "+";
                    continue;
                }
               
                if (caja[i][j]) {
                    cout << "b";
                    continue;
                }
                
                if (!estoy) cout << ".";
                else cout << "w";
            }
            cout << endl;
        }    
}

int main(){
    int run = 1;
    while (cin >> rows >> cols) {
        if (rows == 0 and cols == 0) break;
        
        int yor, yoc;
        
        memset(pared, 0, sizeof pared);
        memset(hueco, 0, sizeof hueco);
        memset(caja, 0, sizeof caja);
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                char c; cin >> c;
                if (c == '#') {
                    pared[i][j] = true;
                } else if (c == '.') {
                    
                } else if (c == '+') {
                    hueco[i][j] = true;
                } else if (c == 'b') {
                    caja[i][j] = true;
                } else if (c == 'B') {
                    caja[i][j] = true;
                    hueco[i][j] = true;
                } else if (c == 'w') {
                    yor = i, yoc = j;
                } else if (c == 'W') {
                    hueco[i][j] = true;
                    yor = i, yoc = j;
                } else {
                    assert(false);
                }    
            }
        }

        
        string teclas; cin >> teclas;
        

        
        map<char, int> dr, dc;
        dr['U'] = -1; dc['U'] = 0;
        dr['D'] = +1; dc['D'] = 0;        
        dr['L'] =  0; dc['L'] = -1;
        dr['R'] =  0; dc['R'] = +1;
        
        for (int i = 0; i < teclas.size(); ++i) {
            char t = teclas[i];
            if (todoAdentro()) continue;
            
//            print(yor, yoc); puts("");
                        
            int nr = yor + dr[t], nc = yoc + dc[t];
            if (vacio(nr, nc)) { 
                yor = nr;
                yoc = nc;
                continue;
            }
            
            if (pared[nr][nc]) continue;
            
            if (!pared[nr][nc] and caja[nr][nc]) {
                int cajar = nr + dr[t], cajac = nc + dc[t];
                if (!vacio(cajar, cajac)) continue;
                
                caja[nr][nc] = false;
                caja[cajar][cajac] = true;
                
                yor = nr;
                yoc = nc;
                continue;
            }
        }         
        
        printf("Game %d: %s\n", run++, todoAdentro() ? "complete" : "incomplete");    
        print(yor, yoc);
    }
    
    return 0;
}
