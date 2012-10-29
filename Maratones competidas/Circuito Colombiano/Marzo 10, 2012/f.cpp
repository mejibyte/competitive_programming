using namespace std;
#include <algorithm>
#include <iostream>
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

#define For (i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int N = 19 * 8;

#include <bitset>

bitset<N> bits;
string output;
int decodedCount;
int pos;
char buffer[1024];

int read(int n) {
    int ans = 0;
    for (int k = 0; k < n; ++k) {
        ans += bits[pos++] << (n - 1 - k);
    }
    return ans;
}

string toStr(int x, int leadingZeros = 0) {
    sprintf(buffer, "%d", x);
    string ans = string(buffer);
    while (ans.size() < leadingZeros) ans = "0" + ans;
    return ans;
}

void print8(unsigned int c) {
    if (0x20 <= c and c <= 0x7e) {
        if (c == '\\') output += "\\\\";
        else if (c == '#') output += "\\#";
        else output += (char)c;
        return;
    }
    sprintf(buffer, "\\%.2X", (unsigned int)c);
    output += string(buffer);
    
}

void printK(unsigned int x) {
    sprintf(buffer, "#%d", !!(x & (1 << 12)) );
    output += string(buffer);
    x = x & ~(1 << 12);
    sprintf(buffer, "%.3X", x);
    output += string(buffer);
    
}

void alpha() {
    string code = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:";
    int count = read(9);
    decodedCount += count;
    
    for (int i = 0; i < count / 2; ++i) {
        int num = read(11);
        
        int a = num / 45;
        int b = num % 45;
        
        output += code[a];
        output += code[b];
    }
    if (count % 2 == 1) {
        output += code[ read(6) ];
    }
}

void numeric() {
    int count = read(10);
    decodedCount += count;

    for (int i = 0; i < count / 3; ++i) {
        int num = read(10);
        output += toStr(num, 3);
    }
    if (count % 3 == 2) {
        output += toStr(read(7), 2);
    } else if (count % 3 == 1) {
        output += toStr(read(4));
    }
}

void eight() {
    int count = read(8);
    decodedCount += count;
    for (int i = 0; i < count; ++i) {
        int byte = read(8);
        print8(byte);
    }
}

void kanji() {
    int count = read(8);
    decodedCount += count;
    for (int i = 0; i < count; ++i) {
        int x = read(13);
        printK(x);
    }
}

void decode() {
    if (pos + 3 >= N) return;
    int mode = read(4);
    if (mode == 1) numeric();
    else if (mode == 2) alpha();
    else if (mode == 4) eight();
    else if (mode == 8) kanji();
    else return;
    decode();
}

void solve(string &s) {
    for (int i = 0; i < s.size(); i += 2) {
        buffer[0] = s[i];
        buffer[1] = s[i + 1];
        buffer[2] = 0;
        int x;
        sscanf(buffer, "%X", &x);
        
        for (int j = 0; j < 8; ++j) {
            int on = !!(x & (1 << j));
            bits[i * 4 + (7 - j)] = on;
        }
    }
    pos = 0;
    decode();
    cout << decodedCount << " " << output << endl;
}

int main() {
    int casos; cin >> casos;
    while (casos--) {
        int id; string s; cin >> id >> s;
        cout << id << " ";
        output = "";
        decodedCount = 0;
        solve(s);
    }
    return 0;
}
