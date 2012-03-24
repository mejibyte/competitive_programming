// Andrés Mejía
// Wrong Answer
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

bool punctuation(wchar_t c) {
    if (iswalpha(c)) return false;
    if (iswspace(c)) return true;
    
    wstring s = L"¡!,.:;¿?- \t\n";
    for (int i = 0; i < s.size(); ++i) if (c == s[i]) return true;
    return false;
    
}

map<char, wstring> suffixes;

bool ends_with(const wstring &a, const wstring &b) {
    if (a.size() < b.size()) return false;
    for (int i = 0, bb = b.size() - 1, aa = a.size() - 1; i < b.size(); ++i) {
        if (b[bb] != a[aa]) return false;
        bb--;
        aa--;
    }
    return true;
}

string check(vector<wstring> &text) {
    if (text.size() != 14) return "";
    
    string ans = "";
    for (int i = 0; i < text.size(); ++i) {
        wstring s = L"";
        for (int j = 0; j < text[i].size(); ++j) {
            wchar_t c = text[i][j];
            if (punctuation(c)) continue;
            //s += towlower(c);
            s += c;
        }
        if (s[s.size() - 1] == L's' or s[s.size() - 1] == L'S') s.resize(s.size() - 1);
        
        //wcout << s << endl;
        
        bool found = false;
        foreach(k, suffixes) {
            if (ends_with(s, k->second)) {
                ans += k->first;
                found = true;
            }
        }
        if (!found) {
            return "";
        }
    }
    if (ans != "ABBAABBACDCDCD" and ans != "ABBAABBACDECDE" and ans != "ABBAABBACDEDCE") return "";
    return ans;  
}

int main(){
  assert(setlocale(LC_ALL, "en_US.UTF-8") != NULL);
  
  wstring s;
  while (getline(wcin, s)){
      
      suffixes.clear();
      wstringstream sin(s);
      
      vector<wstring> vsuffixes;
      for (char next = 'A'; sin >> s; next++) {
          //for (int i = 0; i < s.size(); ++i) s[i] = towlower(s[i]);
          vsuffixes.push_back(s);
          //wcout << next << " " << s << endl;
      }
      
      wstring title;
      getline(wcin, title);
      
      vector<wstring> text;
      while (getline(wcin, s)) {
          
          bool allSpaces = true;
          for (int i = 0; i < s.size(); ++i) if (s[i] != L' ') allSpaces = false;
          
          if (allSpaces) break;
          text.push_back(s);
      }

      string ans = "";
      
      string letters = "";
      for (int i = 0; i < vsuffixes.size(); ++i) letters += ('A' + i);
      
      do {
          for (int i = 0; i < vsuffixes.size(); ++i) suffixes[letters[i]] = vsuffixes[i];
          ans = check(text);
          if (ans != "") break;
      } while (next_permutation(letters.begin(), letters.end()));
      
      
      wcout << title << ": ";
      if (ans.size() > 0) {
          cout << ans << endl;
      } else {
          wcout << "Not a chance!" << endl;
      }
  }
  return 0;
}
