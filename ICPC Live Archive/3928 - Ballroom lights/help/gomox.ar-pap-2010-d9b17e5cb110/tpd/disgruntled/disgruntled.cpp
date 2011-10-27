#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cassert>
#include <list>
using namespace std;
#define forn(i,n) for(int i = 0; i < n; ++i)
#define forsn(i,s,n) for(int i = (s); i < (n); i++)
#define foreachin(it,s) for(__typeof__((s).begin()) it = ((s).begin()); it != ((s).end()); ++it)

#define inverso_de_73_mod_137 122
#define inverso_de_137_mod_73 8
#define coef_137 1096 // 137*8
#define coef_73 8906 // 73*122

static int cuad73[73];
static int cuad137[137];

#define resto(x,y) ((((x) % (y)) + (y)) % (y))

// si (a,b) = 1, deja en x el inverso multiplicativo de a ,mod b
// basicamente es la idea del algoritmo de euclides, pero iterativo
// mas info: www.math.hawaii.edu/~lee/discrete/combination.ps
void combinacion(int a, int b, int&x) {
    int g0 = a;
    int x0 = 1;
//    int y0 = 0;
    int g1 = b;
    int x1 = 0;
//    int y1 = 1;
    while (g0 % g1 != 0) {
//invariante: a*x_1+b*y_1=g1
        int q = g0 / g1;
        int temp = g1;
        g1 = g0 - q * g1;
        g0 = temp;
        temp = x1;
        x1 = x0 - q * x1;
        x0 = temp;
        /*
        	temp = y1;
                y1 = y0 - q * y1;
                y0 = temp;
        */
    }
    x=x1;
}

/* utiliza la ecuacion: a^2*x +a*b+b \equiv y
 * para despejar b, si no es posible, es porque el a no era correcto
 * b*(a+1) \equiv y -a^2
 */
bool obtener_b(int a, int x, int y,int& b) {
    if ((a+1) % 73 == 0) {
        // para poder encontrar un b, la parte derecha tb tiene que ser congruente a 0 modulo 73
        if (y-resto(a*a,73)*x %73 != 0)return false;
        int amas1inv, aux;
        combinacion((a+1),137,amas1inv);
        amas1inv = resto(amas1inv,137);

        int acuad = a*a %137;
        aux = resto((y - acuad*x),137);
        b = aux*amas1inv%137;
        return true;
    }

    if ((a+1)%137 == 0) {
        // para poder encontrar un b, la parte derecha tb tiene que ser congruente a 0 modulo 137
        if (y-resto(a*a,137)*x %137 != 0)return false;
        int amas1inv, aux;
        combinacion((a+1),73,amas1inv);
        amas1inv = resto(amas1inv,73);

        int acuad = a*a % 73;
        aux = resto((y - acuad*x),73);
        b = aux*amas1inv %73;
        return true;
    }
    int amas1inv137, aux;

    combinacion((a+1),137,amas1inv137);
    amas1inv137 = resto(amas1inv137,137);
    int acuad137 = a*a % 137;
    int aux137 = resto((y - acuad137*x),137);
    int b137= aux137*amas1inv137 % 137;
    int amas1inv73;
    combinacion((a+1),73,amas1inv73);
    amas1inv73 = resto(amas1inv73,73);
    int acuad73 = a*a %73;
    int aux73 = resto((y - acuad73*x),73);
    int b73= aux73*amas1inv73 %73;

    //usamos teorema chino del resto, para encontrar b

    b = ((b73*coef_137)+(b137*coef_73)) % 10001;

    return true;

}

static int numeros[101];

bool testear_candidato(int a, int b, int cant,list<int>& res) {
    forn(i,cant) {
        int f = (a*numeros[i]+b)% 10001;
        res.push_back(f);
        if (numeros[i+1] < cant && (a*f+b)% 10001 != numeros[i+1]) {
            break;
        }
    }
    return res.size() == cant;
}

void llenar_res(int a,int a1,int x, int y,int cant,list<int>& res,int q) {
    int b;
    int candidatos[2] = {a,a1};
    int t = 0;
    while (true) {
        if (obtener_b(candidatos[t],x,y,b)) {
            if (testear_candidato(candidatos[t],b,cant,res))break;
        }
        res.clear();
        t++;
        if (t>1) {
            candidatos[0]=candidatos[0]+q;
            candidatos[1]=candidatos[1]+q;
            t=0;
        }
    }
}

void resolver(const int cuadk[],int k,int x,int y,int qk, int wk,int cant) {
    int qkinv;

    combinacion(qk,k,qkinv);
    qkinv = resto(qkinv,k);
    int acuad = (wk*qkinv)%k;
    int a,a1;
    a = cuadk[acuad];
    a1= k -cuadk[acuad];
    list<int> res;
    llenar_res(a,a1,x,y,cant,res,k);
    foreachin(it,res) {
        printf("%d\n",*it);
    }
}


int main(int argc, char** argv) {
    // cuad73[k] = a / a^2 % 73 == k
    // notar que alcanza mirar hasta 37 (73/2+1)
    // porque j^2 % 73 == (73 - j)^2
    // ademas no hay a1,a2 entre [0,73/2+1) tal que a1^2 % 73 == a2^2 % 73
    forn(each,37) {
        cuad73[(each*each)%73] = each;

    }
    // simil a lo anterior
    forn(each,68) {
        cuad137[(each*each)%137]=each;
    }
    int cant;
    scanf("%d",&cant);
    while (cant > 0) {

        forn(i,cant) {
            scanf("%d",&numeros[i]);

        }
        if (cant < 3) {
            forn(i, cant) {
                printf("%d\n",numeros[cant-1]);
            }
        }
        else {
            int x,y,z;
            x=numeros[0];
            y=numeros[1];
            z=numeros[2];
            int q,w;
            /* Idea:
             a*x + b \equiv 0_1
             a*O_1 + b \equiv y
             a*y + b \equiv O_2
             a*O_2 +b \equiv z
             -----------------
             a^2*x+ab+b \equiv y
             a^2*y+ab+b \equiv z
             --------------------
             a^2(x-y) \equiv (y-z)

             Resolver esa ecuacion modulo 137 y 73 y obtener candidatos para a.
             obtener un b para alguno de los candidatos. usar esa pareja (a,b)
             */
            q = (x-y);
            w = (y-z);

            int q137 = resto(q,137);
            int q73 = resto(q,73);
            int w137 = resto(w,137);
            int w73 = resto(w,73);
            if (q137 == 0) {
                if (q73 == 0) {
                    forn(i,cant) {
                        printf("%d\n",numeros[cant-1]);
                    }
                }
                else {
                    resolver(cuad73,73,x,y,q73,w73,cant);
                }
            }
            else {
                if (q73 == 0) {
                    resolver(cuad137,137,x,y,q137,w137,cant);
                }
                else {
                    int q137inv,q73inv;

                    combinacion(q137,137,q137inv);
                    q137inv = resto(q137inv,137);
                    int acuad137 = (w137*q137inv)%137;
                    combinacion(q73,73,q73inv);
                    q73inv = resto(q73inv,73);
                    int acuad73 = (w73*q73inv)%73;
                    int a,b;
                    int j = cuad73[acuad73];
                    int k = cuad137[acuad137];
                    list<int> res;
                    int candidatos[4] = { resto(j*coef_137 + k* coef_73,10001), resto((73-j)*coef_137 + k* coef_73,10001),
                                          resto((73-j)*coef_137 + (137-k)* coef_73,10001), resto(j*coef_137 + (137-k)* coef_73,10001)
                                        };
                    forn(i, 4) {
                        a =candidatos[i] ;
                        if (obtener_b(a,x,y,b)) {
                            if (testear_candidato(a,b,cant,res)) {
                                break;
                            }
                        }
                        res.clear();
                    }
                    foreachin(it,res) {
                        printf("%d\n",*it);
                    }

                }
            }

        }
        if (scanf("%d\n",&cant)!=1)break;
    }
    return (EXIT_SUCCESS);
}

