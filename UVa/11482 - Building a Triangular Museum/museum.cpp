#include <iostream>

using namespace std;

void ponerEsp(int esp) {
     for(int i =0; i<esp;++i) {
         cout << " ";
     }
}

void ponerLinea(int esp) {
     for(int i =0; i<esp;++i) {
         cout << "_";
     }
}

int main() {
    int m,n;
    cin >> m >> n;
    int count = 1;
    while(m!=0) {
        cout << "Triangular Museum " << count++ << endl;
        int espIni = (n*m)-1;
        for(int i =1; i<=n; ++i) {
            int espEntre = 2*(m-1);
            for(int r= 1; r<=m; ++r) {
                ponerEsp(espIni);
                espIni--;
                for(int j=1; j<=i; ++j) {
                    cout << "/";
                    if(r==m) ponerLinea(2*(m-1));
                    else ponerEsp(2*(r-1));
                    cout << "\\";
                    if((j+1)<=i) {
                        ponerEsp(espEntre);
                    }
                }
                espEntre -= 2;
                cout << endl;
            }
        }
        cout << endl;        
        cin >> m >> n;
    }
    return 0;
}
