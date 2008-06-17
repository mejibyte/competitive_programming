//Robado de: http://www.wretch.cc/blog/celiaailec/19569472
//  Q562: Dividing coins
//  2008.05.29     Celia
//  Method: Dynamic Programming
//  Result: Accepted
//  Time: 0.050
#include <stdio.h>
#include <string.h>

#define N 101
#define M 25001

bool v[M];

int iabs(int n)
{
    return (n > 0)? n : -n;
}

int main()
{
    int i, j, t, n, m, sum, a[N];
    scanf("%d", &t);

    while(t-- > 0)
    {
        scanf("%d", &n);

        for(sum = 0, i = 1; i <= n; i++)
            scanf("%d", &a[i]), sum += a[i];

        m = sum / 2;
        memset(v, 0, sizeof(v));
        v[0] = true;

        for(i = 1; i <= n; i++)
            for(j = m; j >= 1; j--)
                if(!v[j])
                    v[j] = (a[i] <= j)? v[j-a[i]] : false;

        for(j = m; j >= 1; j--)
            if(v[j])
                break;

        printf("%d\n", iabs(sum - j * 2));
    }

    return 0;
}
