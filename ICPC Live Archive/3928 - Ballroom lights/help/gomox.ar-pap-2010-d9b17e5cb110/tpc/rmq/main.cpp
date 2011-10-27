#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <utility>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
using namespace std;
#define forit(it,l) for(it=(l).begin();it != (l).end(); it++)
#define forn(i,n) for(unsigned  i= 0; i < ((unsigned)(n)); i++)
#define foreachin(it,s) for(typeof((s).begin()) it = ((s).begin()); it != ((s).end()); it++)
#define forsn(i,s,n) for(int i = (s); i < (n); i++)
void inline llenar_tabla(vector<vector<int> >& tabla, const vector<int>& frec) {
    int n = tabla.size();
    int i, j;
    //init de los intervalos de largo 1
    forn(i,n)
        tabla[i][0] = i;

    //llenado de la tabla desde los mas chicos a los mas grandes
	unsigned t=2;
	unsigned t_ant=1;
    for (j = 1; t <= n; j++) {
        for (i = 0; i + (t) - 1 < n; i++) {
            int k = j - 1;
            if (frec[tabla[i][k]] > frec[tabla[i + (t_ant)][k]])
                tabla[i][j] = tabla[i][k];
            else
                tabla[i][j] = tabla[i + (t_ant)][k];
        }
		t_ant=t;
		t=t<<1;
    }
}


static inline uint32_t log_2(const uint32_t x) {
  uint32_t y;
  asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  return y;
}


 void inline cargar_numeros(int cant_numeros,vector<int>& frec,vector<pair<int,int> >& intervalostupla,vector<int>& intervaloindice,int& intervalo) {
    int i = 0;
    int numero;
    int desde,hasta; //intervalo donde todos los elementos son iguales [ ]
    int actual; //elemento cuya frecuencia estoy construyendo
    while (i < cant_numeros) {
        scanf ("%d",&numero);

        if (i == 0) {
            actual=numero;
            desde=0;
            hasta=0;
        } else {
            if (actual==numero) { //si son iguales, incremento el hasta y su frecuencia
                hasta++;
                frec[intervalo]++;
            }
            // si son distintos, se cerró un intervalo, hay que empezar a armar otro
            else {
                intervalostupla[intervalo] = pair<int,int>(desde,hasta);
                intervalo++;
                hasta++;
                desde=hasta;
                actual = numero;
            }

        }
        intervaloindice[i]=intervalo;

        i++;

    }

    //hack: el ultimo siempre quedaba sin agregar
    intervalostupla[intervalo] = pair<int,int>(desde,hasta);
}

void inline procesar_queries(const int queries,const vector<int>& frec,const vector<pair<int,int> >& intervalostupla,const vector<int>& intervaloindice,int& intervalo) {
    vector<vector<int> > tabla(intervalo+1, vector<int>(log_2(intervalo+1)+1));
    llenar_tabla(tabla,frec);
    unsigned x,y;
    int i=0;
    while (i < queries) {
        scanf("%u %u",&x,&y);
        int desde, hasta;
        //desde y hasta son los intervalos extremos que hay que mirar.
        //No necesariamente estan completos
        desde = intervaloindice[x-1];
        hasta = intervaloindice[y-1];

        int res;
        // Si esos indices son parte del mismo intervalo, la frecuencia es la distancia entre ellos.
        if (desde==hasta) {
            res = y-x+1;
        } else {
            //calculo por separado los intervalos que pueden ser truncos
            int frec_i = intervalostupla[desde].second - x + 2;
            int frec_j = y - intervalostupla[hasta].first ;

            //el siguiente del desde y el anterior del hasta si estan completos
            unsigned int intervalo_completo_i = desde+1;
            unsigned int intervalo_completo_j = hasta-1;

            res = max(frec_i,frec_j);
            if(intervalo_completo_i <= intervalo_completo_j){
                unsigned int k = log_2(intervalo_completo_j - intervalo_completo_i + 1);
                int aux = frec[tabla[intervalo_completo_j-(1<<k)+1][k]];
                if (frec[tabla[intervalo_completo_i][k]] >= aux )
                    res = max(res,frec[tabla[intervalo_completo_i][k]]);
                else
                   res = max(res,aux);
            }
        }

        printf("%d\n",res);
        i++;
    }
}

int main(int argc, char** argv) {		
#ifndef ONLINE_JUDGE
    close (0);
    open ("test.txt", O_RDONLY);
    //close (1);
    //open ("myprog.out", O_WRONLY | O_CREAT, 0600);
#endif

    int cant_numeros,queries;
	scanf ("%d",&cant_numeros);
    

    while (cant_numeros > 0) {
		scanf ("%d",&queries);
        vector<int> frec(cant_numeros,1);//vector de frecuencias
        int intervalo =0;//cantidad de intervalos
        vector<int> intervaloindice(cant_numeros); //dado un indice del arreglo, devuelve el numero de intervalo en el que esta
        vector<pair<int,int> > intervalostupla(cant_numeros); //dado un numero de intervalo, da su desde y hasta

        cargar_numeros(cant_numeros,frec,intervalostupla, intervaloindice, intervalo);
        procesar_queries(queries, frec,intervalostupla, intervaloindice, intervalo);


        scanf ("%d",&cant_numeros);

    }
    return (EXIT_SUCCESS);
}


