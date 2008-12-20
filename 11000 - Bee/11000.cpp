using namespace std;
#include <iostream>
#include <vector>

const long long limit = (1LL << 32) + 2;
vector<long long> m;

int main(){
  m.push_back(0);
  m.push_back(1);
  for (int i=2; m[i-1] + m[i-2] <= limit; ++i)
    m.push_back(m[i-1] + m[i-2] + 1);

  int n;
  while (scanf("%d", &n)==1 && n!=-1)
    printf("%lld %lld\n", m[n], m[n+1]);

  return 0;
}
