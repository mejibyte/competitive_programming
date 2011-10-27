#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<int> partiendo( int x, int y, vector<int> a );
vector<int> deformar(  int i, int h, int j, vector<int> a );
int cortes=0;

int main(){
  int n, x, y, h, cont=0;
  while( scanf("%d",&n) && n!=0 ){
    cortes=0; cont++;
    vector<int> parts;
    h=n; cin >> x >> y;
    int num=0;
    while(h--){ cin >> num; parts.push_back(num); }
    parts=partiendo( x, y, parts );
    if( parts.size()==0 && cortes-1<n ) cout << "Case " << cont << ": Yes" << endl;
    else cout << "Case " << cont << ": No" << endl;
  }
  return 0;
}

vector<int> partiendo( int x, int y, vector<int> a ){

  if( a.size() == 0 ) return a;
  for( int i=0; i< a.size() ; i++ ){
    int b=0;

    for( int h=i; h< a.size() ; h++ ){
      if( h==i ) b+=a[h];
      else if( a[i]==a[h] ) b+=a[h];
      if( b%x==0 && y-(b/x)>-1 ){ cortes+=(h-i)+1; return partiendo( x, y-(b/x), deformar(i,h,-5,a) ); }
      if( b%y==0 && x-(b/y)>-1 ){ cortes+=(h-i)+1; return partiendo( x-(b/y), y, deformar(i,h,-5,a) ); }

      for( int j=h+1; j< a.size() ; j++ ){

        int s=b;
        if( a[i]==a[j] ) s=b+a[j];
        if( s%x==0 && y-(s/x)>-1 ){ cortes+=(h-i)+2; return partiendo( x, y-(s/x), deformar(i,h,j,a) ); }
        if( s%y==0 && x-(s/y)>-1 ){ cortes+=(h-i)+2; return partiendo( x-(s/y), y, deformar(i,h,j,a) ); }

      }
    }
  }
  return a;

}


vector<int> deformar( int i, int h, int j, vector<int> a ){
  vector<int> f;
  for( int g=0; g<a.size(); g++ ) if( g<i || g>h && g!=j ) f.push_back(a[g]);
  return f;
}

