#include <iostream>
#include <queue>

using namespace std;

typedef unsigned long long ull;

ull h[1501];

priority_queue<ull, vector<ull>, greater<ull> > q;

int main(){

  q.push(1);
  int i=1;
  while (i <= 1500){
    ull top = q.top();
    q.pop();
    h[i++] = top;

    q.push(top*2);
    if (top % 2 != 0) {
      q.push(top*3);
    }
    if (top % 2 != 0 && top % 3 != 0){
      q.push(top*5);
    }
    //    if (top % 2 != 0 && top % 3 != 0 && top % 5 != 0){
    //q.push(top*7);
  }
  //cout << q.size() << endl;
  //int n;
  //while (cin >> n && n > 0) cout << h[n] << endl;
  cout << "The 1500'th ugly number is " << h[1500] << ".\n";
  return 0;
}
