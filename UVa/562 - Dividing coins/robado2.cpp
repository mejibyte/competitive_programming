//Robado de: http://www.wretch.cc/blog/celiaailec/19559822
//  Q562: Dividing coins
//  2008.05.28     Celia
//  Method: Dynamic Programming (0-1 knapsack)
//  Result: Accepted
//  Time: 0.130
#include <stdio.h>

#define N 101
#define M 25001

int iabs(int n)
{
    return (n > 0)? n : -n;
}
int imax(int n, int m)
{
    return (n > m)? n : m;
}

int a[N], v[N][M];

int main()
{
    int i, j, t, n, m, sum;
    scanf("%d", &t);

    while(t-- > 0)
    {
        scanf("%d", &n);

        for(sum = 0, i = 1; i <= n; i++)
            scanf("%d", &a[i]), sum += a[i];

        m = sum / 2;

        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= m; j++)
            {
                v[i][j] = imax(v[i-1][j], v[i][j-1]);

                if(a[i] <= j)
                    v[i][j] = imax(v[i][j], a[i] + v[i-1][j-a[i]]);
            }
        }

        printf("%d\n", iabs(sum - v[n][m] * 2));
    }

    return 0;
}
