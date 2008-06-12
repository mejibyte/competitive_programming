#include <string>
#include <iostream>

using namespace std;

string text = "the quick brown fox jumps over the lazy dog";
int key;

void encrypt(string s){
  for (int i=0; i<s.size(); ++i){
    if (s[i] == ' '){
      cout << " ";
      continue;
    }
    char c = 'a' + ( (s[i]-'a'+key )%26 );
    cout << c;
  }
  cout << endl;
}

int main(){
  while(cin >> key && key){;
    string s;
    getchar();
    getline(cin, s);
    encrypt(text);
    encrypt(s);
  }
}
