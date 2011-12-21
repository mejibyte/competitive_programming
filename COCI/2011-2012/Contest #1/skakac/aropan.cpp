#include <cstdio>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <vector>

using namespace std;

#define X first
#define Y second



const int MAXN = 32;
const int MAXT = 1000001;
const int MAXK = MAXN * MAXN;

bitset <MAXN> a[MAXN], b[MAXN];
bitset <MAXN> mask[MAXN];
bitset <MAXN> one[MAXN], two[MAXN];
int x[MAXK], y[MAXK], d[MAXK];
int next[MAXK];
int last[MAXT];
int n, T, k, X, Y;
vector < pair <int, int> > ans;

int add(int t, int i)
{
    if (t > T) return 0;
    next[i] = last[t];
    last[t] = i;
    return 0;
}

int main()
{
/*
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
//*/
    scanf("%d %d %d %d", &n, &T, &X, &Y);
    X--, Y--;
    a[X].set(Y);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int v;
            scanf("%d", &v);
            mask[i].set(j, (v == 1) || (v == 2) && (i + j & 1) == (X + Y & 1));
            if (v < 3) continue;
            k++;
            x[k] = i;
            y[k] = j;
            d[k] = v;
            add(v, k);
        }

    for (int t = 1; t <= T; t++)
    {
        for (int i = 0; i < n; i++)
        {
            one[i] = (a[i] >> 1) | (a[i] << 1);
            two[i] = (a[i] >> 2) | (a[i] << 2);
        }

        for (int i = 0; i < n; i++)
        {
            b[i].reset();
            if (1 < i) b[i] |= one[i - 2];
            if (0 < i) b[i] |= two[i - 1];
            if (i < n - 1) b[i] |= two[i + 1];
            if (i < n - 2) b[i] |= one[i + 2];
        }

        for (int i = 0; i < n; i++)
            a[i] = b[i] & mask[i];

        for (int i = last[t], j; i; i = j)
        {
            a[x[i]].set(y[i], b[x[i]].test(y[i]));
            j = next[i];
            add(t + d[i], i);
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i].test(j))
                ans.push_back(make_pair(i + 1, j + 1));

    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++)
        printf("%d %d\n", ans[i].X, ans[i].Y);
    return 0;
}
