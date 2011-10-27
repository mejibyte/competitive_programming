#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

int main(){
  string s[2];
  int n[2];
  while (getline(cin,s[0]) && getline(cin,s[1])){
    for (int i=0; i<2; ++i){
      n[i] = 0;
      for (int j=0; j<s[i].size(); ++j){
	char c = tolower(s[i][j]);
	if (isalpha(c)){
	  n[i] += c - 'a' + 1;
	}
      }
      n[i] = (n[i]%9>0 ? n[i]%9 : 9);
    }
    printf("%.2f %\n", (double)MIN(n[0], n[1])*100.0/(double)MAX(n[0], n[1]));
    
  }
  return 0;
}
