/* Código robado del foro DESPUÉS de haberlo resuelto yo.

http://acm.uva.es/board/viewtopic.php?t=16135

*/



#include <iostream> 
using namespace std; 

int main (void) 
{ 
    int k; 
    while ((cin>>k)&&k) 
    { 
        int p = k*2; 
        int m; 
        for (m=k; ; m++) 
        { 
            int x=p; 
            int y=(m-1)%x; 
            while (y>=k && x>k) 
            { 
                x--; 
                y = (y-1+m)%x; 
            } 
            if (x==k) 
                break; 
        } 
        cout << m << endl; 
    } 
}