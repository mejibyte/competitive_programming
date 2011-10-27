#include <string.h>
#include <cstdio>
#include <algorithm>

using std::sort;
using std::swap;

static char text[50001];
static unsigned int sa[50000];
static unsigned int rank1[50000]={0};
static unsigned int rank2[50000]={0};

static int N;
static long long total;
static unsigned cuantos;

bool parar;
int bucket, aux, desde, actual;
unsigned int* ahora;
unsigned int* proximo;


// Comparador
struct Comparador {
    const int K;
    const unsigned int* rank;
    Comparador(const int j,const unsigned int* vrank): K(j), rank(vrank) {};

    bool inline operator()(const int i, const int j) const {
        return clave(i) < clave(j);
    }

    int inline clave(const int i) const {
        return (i+K < N ? rank[i+K]+1 : 0);
    }
};


int main(int argc, const char *argv[]) {

    scanf("%d", &cuantos);

    for (int c = 0; c < cuantos; c++) {

        scanf("%s", text);
        N = strlen(text);

        // Suffix Array
        for (int i = 0; i < N; i++) {
            sa[i] = i;
            rank1[i] = text[i];
        }


        sort(sa, sa+N, Comparador(0, rank1));

        bucket = 0;
        rank1[sa[0]] = 0;

        for (int t = 1; t < N; t++) {
            if (text[sa[t-1]] == text[sa[t]]) {
                rank1[sa[t]] = bucket;
            } else {
                bucket = t;
                rank1[sa[t]] = bucket;
            }
        }

        parar = true;
        ahora = rank1;
        proximo = rank2;

        for (int K = 1; K < N; K *= 2) {
            desde = 0;
            actual = 1;
            Comparador comparador(K,ahora);
            while (actual < N) {
                while (actual< N && ahora[sa[actual]] == ahora[sa[actual-1]]) {
                    actual++;
                }
                if (actual > desde+1) {
                    sort(sa+desde, sa+actual, comparador);
                }
                desde = actual;
                actual++;
            }

            bucket = 0;
            proximo[sa[0]] = 0;
            aux = 0;

            for (int t = 1; t < N; t++) {
                if (ahora[sa[t]] == aux && comparador.clave(sa[t-1]) == comparador.clave(sa[t])) {
                    proximo[sa[t]] = bucket;
                    parar = false;
                } else {
                    aux = ahora[sa[t]];
                    bucket = t;
                    proximo[sa[t]] = bucket;
                }
            }

            swap(ahora, proximo);
            if (parar) break;
            parar = true;
        }

        // LCP (Kasai)
        total = 0;
        int k = 0;
        for (int i = 0; i < N; i++) {
            if (k > 0) {
                k--;
            }
            if (ahora[i] == N-1) {
                total += N + 1 - sa[N-1];
                k = 0;
                continue;
            }
            int j = sa[ahora[i]+1];
            while (text[i+k] == text[j+k]) k++;
            total += N - k - sa[ahora[i]];
        }

        // El codigo de arriba pone un -1 en la
        // fila final del LCP en lugar de un 0 en la primera,
        // asi que hay que restarlo ahora.
        total = total - 1;

        printf("%lld\n", total);
    }
}
