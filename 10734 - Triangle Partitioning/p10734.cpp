#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

vector<vector<double> > t;

bool semejantes(const vector<double> &t1, const vector<double> &t2){
  return (t1[0]/t2[0] == t1[1]/t2[1] && 
	  t1[1]/t2[1] == t1[2]/t2[2] &&
	  t1[2]/t2[2] == t1[0]/t2[0] );
}

void divide(vector<double> v){
  sort(v.begin(), v.end());
  double h = sqrt(2*v[1]*v[1]-v[2]*v[2]+2*v[0]*v[0])/2;
  
  vector<double> h1(3), h2(3);
  h1[0] = h2[0] = h;
  h1[1] = h2[1] = v[2]/2;
  h1[2] = v[0];
  h2[2] = v[1];
  sort(h1.begin(), h1.end());
  sort(h2.begin(), h2.end());

  bool yaEsta = true;
  for (int i=0; i<t.size(); ++i){
    yaEsta = yaEsta && !(semejantes(h1, t[i]));
  }
  if (!yaEsta){
    t.push_back(h1);
    divide(h1);
  }

  yaEsta = true;
  for (int i=0; i<t.size(); ++i){
    yaEsta = yaEsta && !(semejantes(h2, t[i]));
  }
  if (!yaEsta){
    t.push_back(h2);
    divide(h2);
  }
}

int main(){
  int n;
  scanf("%d", &n);
  for (int i=1; i<=n; ++i){
    t.clear();
    vector<double> temp(3);
    for (int j=0; j<3; ++j){
      cin >> temp[i];
    }
    divide(temp);
    cout << t.size() << endl;
    
  }
  return 0;
}
