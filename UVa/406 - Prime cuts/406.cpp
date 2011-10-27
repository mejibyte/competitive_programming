#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 1000;

//criba[i] = false si i es primo
bool criba[SIZE+1];

void buildCriba(){
  memset(criba, false, sizeof(criba));

  criba[0] = criba[1] = true;
  for (int i=2; i<=SIZE; i += 2){
    criba[i] = true;
  }

  for (int i=3; i<=SIZE; i += 2){
    if (!criba[i]){
      for (int j=i+i; j<=SIZE; j += i){
        criba[j] = true;
      }
    }
  }
}

int main(int argc, char const *argv){
  vector<int> primes;
  primes.push_back(1);
  primes.push_back(2);
  buildCriba();
  for (int i=3; i<=SIZE; i+=2){
    if (!criba[i]){
      primes.push_back(i);
    }
  }

  //cout << "primes.size() " << primes.size() << endl;
  //cout << "Last: " << primes.back() << endl;
  int n, c;
  while (cin >> n >> c){
    int end = 0;
    while (end < primes.size() && primes[end] <= n){
      ++end;
    }
    --end;
    //La lista termina en end, inclu铆do. Tiene end+1 elementos.
    //cout << primes[end] << endl;
    int a, b; //imprimir desde primes[a] hasta primes[b]
    if ((end+1)%2 == 0){ //tiene cantidad par de elementos
      //cout << "Cantidad par" << endl;
      a = end/2 - (c-1);
      if (a < 0) a = 0;
      b = end/2 + c;
      if (b > end) b = end;
    }else{ //tiene cantidad impar
      //cout << "Cantidad impar" << endl;
      a = (end+1)/2 - (c-1);
      if (a < 0) a = 0;
      b = (end+1)/2 + (c-1);
      if (b > end) b = end;
    }

    cout << n << " " << c << ":";
    for (int i=a; i<=b; ++i){
      cout << " " << primes[i];
    }
    cout << endl << endl;
  }
  return 0;
}

