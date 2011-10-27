//Este código produce TLE
//Robado de http://online-judge.uva.es/board/viewtopic.php?t=27307&start=15
//By arsalan_mousavian

#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <cstdio>
#include <utility>
#include <fstream>
#include <string>

using namespace std;
#define ll long long
ll dp [1<<16][5] ;
char input [20];

inline int value ( char ch){
   if ( isalpha ( ch ) ) return 10 + ch - 'A';
   return ch - '0';
}

int main (){
   while ( cin >> input ){
      if ( !strcmp ( input , "#") ) break ;
      
      int n = strlen ( input ) ;
      sort ( input , input + n ) ;
      for (register int mask = 0 ; mask < (1<<n) ; mask ++ ){
         for ( int mod = 0 ; mod < 5 ; mod ++ ){
            if ( mask == 0 ) dp [mask][mod] = 0 ;
            else{
               dp [mask][mod] = 0 ;
               int prev = -1 ;
               for ( int i=0 ; i<n  ; i++ ){
                  if ( mask & ( 1<<i ) ){
                     int next = 0 ;
                     int cur = value ( input [i] );
                     if ( prev == cur ) continue ;
                     prev = cur ;
                     next = ( 500 + mod - cur ) % 5;
                     if ( next == 0 ) dp [mask][mod] ++ ;
                     dp[mask][mod] += dp[mask - (1<<i)][next];
                  }
               }
            }
            if ( mask == (1<<n) - 1 && mod == 0 )
               break ;
         }
      }
      cout << dp [(1<<n)-1][0] << endl;
   }
}
