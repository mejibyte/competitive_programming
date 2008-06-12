#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int compara(const void* i, const void* j){
    if (*(int*)i == *(int*)j) return (0);
    if (*(int*)i == 0) return (1);
    if (*(int*)j == 0) return (-1);
    if (*(int*)i > *(int*)j) return (1);
    if (*(int*)i < *(int*)j) return (-1);
}


int main(int argc, char *argv[])
{
    int cases, r, s[500], median, sum;
    //scanf("%d", &cases);
    cin >> cases;
    for (int contadorCases=0; contadorCases < cases; contadorCases++){
        //scanf("%d", &r);
        cin >> r;
        for (int i = 0; i < r; i++){
            //scanf("%d", &s[i]);
            cin >> s[i];
        }
        qsort(s, r, sizeof(int), compara);
        median = s[r/2];
        sum = 0;
        for (int i = 0; i < r; i++){
            sum += abs(s[i] - median);
        }
        //printf("%d\n", sum);
        cout << sum << endl;
        
    }
    return 0;
}
