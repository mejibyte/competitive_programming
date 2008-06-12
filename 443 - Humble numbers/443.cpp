#include <iostream>
#include <queue>

using namespace std;

typedef unsigned long long ull;

ull h[5843];

priority_queue<ull, vector<ull>, greater<ull> > q;

int main(){
  
  q.push(1);
  int i=1;
  while (i <= 5842){
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
    if (top % 2 != 0 && top % 3 != 0 && top % 5 != 0){
      q.push(top*7);
    }
  }
  
  int n;
  while ((cin >> n) && (n > 0)){
    printf("The ");
    cout << n;
    switch(n % 100){
    case 11:
    case 12:
    case 13:
      printf("th");
      break;
    default:
      switch(n % 10){
      case 1:
	printf("st");
	break;
      case 2:
	printf("nd");
	break;
      case 3:
	printf("rd");
	break;
      default:
	printf("th");
	break;
      }
    }
    printf(" humble number is ");
    cout << h[n] << ".\n";
  }
  return 0;
}
