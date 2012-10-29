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

bool hasBit(int mask, int bit) {
    return !!(mask & (1 << bit));
}

int setBit(int mask, int bit) {
    return mask | (1 << bit);
}

int clearBit(int mask, int bit) {
    return mask & (~(1 << bit));
}

// cuales puedo poner en cada fila
int fila[9];
int col[9];
int cuadro[9];

int cuad(int i, int j) {
    int r = i / 3;
    int c = j / 3;
    return r * 3 + c;
}


int board[9][9];
// si tengo esta ficha libre
bool piece[10][10];

bool adentro(int i, int j) {
    if (i < 0 or i >= 9 or j < 0 or j >= 9) return false;
    return true;
}

bool puedoPoner(int i, int j, int n) {
    return (adentro(i, j) and hasBit(fila[i], n) and hasBit(col[j], n) and hasBit(cuadro[cuad(i, j)], n) and board[i][j] == -1);    
}

void poner(int i, int j, int n) {
    assert(puedoPoner(i, j, n));
    board[i][j] = n;
    fila[i] = clearBit(fila[i], n);
    col[j] = clearBit(col[j], n);
    cuadro[cuad(i, j)] = clearBit(cuadro[cuad(i, j)], n);
}

void quitar(int i, int j, int n) {
    assert(adentro(i, j) and !hasBit(fila[i], n) and !hasBit(col[j], n) and !hasBit(cuadro[cuad(i, j)], n) and board[i][j] == n);
    board[i][j] = -1;
    fila[i] = setBit(fila[i], n);
    col[j] = setBit(col[j], n);
    cuadro[cuad(i, j)] = setBit(cuadro[cuad(i, j)], n);    
}

bool found;


void backtrack(int i, int j) {
    if (i == 8 and j == 9) {
        found = true;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                printf("%d", board[i][j]);
            }
            puts("");
        }
        return;
    }
    
    if (j == 9) {
        backtrack(i + 1, 0);
        return;
    }
    
    if (board[i][j] != -1) {
        backtrack(i, j + 1);
        return;
    }
    
    int ni[] = { i,     i + 1};
    int nj[] = { j + 1, j    };
    
    
    for (int a = 1; a <= 9; ++a) {
        for (int b = a + 1; b <= 9; ++b) {
            if (!piece[a][b]) continue;
            
            for (int k = 0; k < 2; ++k) {
                int ii = ni[k], jj = nj[k];
                if (!adentro(ii, jj)) continue;
                
                if (puedoPoner(i, j, a) and puedoPoner(ii, jj, b)) {
                    poner(i, j, a); poner(ii, jj, b);
                    piece[a][b] = false;
                    backtrack(i, j + 1);
                    if (found) return;
                    piece[a][b] = true;
                    quitar(i, j, a); quitar(ii, jj, b);                    
                }

                if (puedoPoner(i, j, b) and puedoPoner(ii, jj, a)) {
                    poner(i, j, b); poner(ii, jj, a);
                    piece[a][b] = false;
                    backtrack(i, j + 1);
                    if (found) return;
                    piece[a][b] = true;
                    quitar(i, j, b); quitar(ii, jj, a);                        
                }
            }        
        }
    }
}

int main(){
    int run = 1;
    
    int n;
    while(cin >> n){
        if (n == 0) break;
        
        for (int i = 1; i <= 9; i++){
            for (int j = i + 1; j <= 9; j++){
                piece[i][j] = true;
            }    
        }
        
        for (int i = 0; i < 9; ++i) {
            fila[i] = col[i] = cuadro[i] = (1 << 10) - 1;
        }
        
        memset(board, -1, sizeof board);
        found = false;
        
        for (int i = 0; i < n; i++){
            int val; string pos;
            cin >> val >> pos;
            int r = pos[0] - 'A';
            int c = pos[1] - '1';
            
            poner(r, c, val);
            
            int val2;
            cin >> val2 >> pos;
            r = pos[0] - 'A';
            c = pos[1] - '1';
            
            poner(r, c, val2);
            
            piece[min(val, val2)][max(val, val2)] = false;
        }
        for (int i = 0; i < 9; i++){
            string pos;
            cin >> pos;
            int r = pos[0] - 'A';
            int c = pos[1] - '1';
            poner(r, c, i + 1); 
        }
        
        printf("Puzzle %d\n", run++);
        backtrack(0, 0);
    }
    return 0;
}
