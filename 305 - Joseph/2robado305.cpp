/* Código robado del foro DESPUÉS de haberlo resuelto yo.

http://acm.uva.es/board/viewtopic.php?t=8570

*/



#include <iostream> 
using namespace std; 

int f(int k) 
{ 
   int m, n, p, r; 

   for (n = 2 * k, m = 2;; m++) { 
      for (p = 0, r = n; r > k; r--) 
         if ((p = (p + m - 1) % r) < k) break; 
      if (r == k) return m; 
   } 
}

int main (void) 
{ 
    int k; 
    while ((cin>>k)&&k) 
        cout << f(k) << endl; 
    return 0;
}
