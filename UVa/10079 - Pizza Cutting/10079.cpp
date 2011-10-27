#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    long long n, max;
    cin >> n;
    while (n >= 0){
          if (n % 2 == 0){
             max = n / 2;
             max *= (n + 1);
             max++;
          }else{
             max = (n + 1) / 2;
             max *= n;
             max++;
          }
          cout << max << endl;
          cin >> n;
    }
    return 0;
}
