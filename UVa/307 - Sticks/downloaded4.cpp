// http://naivered.github.io/2016/04/08/Problem_Solving/UVa/UVa-307-Sticks/

#include<cstdio>
#include<algorithm>
#define N 100
using namespace std;

bool isUsed[N];
int sticks[N],n;
bool backtracking(int idx, int count, int now, int len);
int main()
{
    int i;
    while (scanf("%d", &n) && n)
    {
        int all = 0;
        for (i = 0; i < n; i++)
        {
            scanf("%d", &sticks[i]);
            all += sticks[i];
        }

        //從大的開始接，減少回溯次數
        sort(sticks, sticks + n, [](const int& a, const int& b)->bool{return a > b; });
        fill(isUsed, isUsed + n, false);

        int len;
        //完整棍子的長度最小為最長的切後棍子。
        for (len = sticks[0]; len <= all; len++)
        {
            if (all%len)//一定為總長的因數，因為完整的棍子長度皆相同
                continue;

            if (backtracking(0, 0, 0, len))
                break;
        }

        printf("%d\n", len);
    }

    return 0;
}
bool backtracking(int idx, int count, int now, int len)//(目前index,已使用棍子數,目前長度,目標長度)
{
    //完成一根完整的棍子
    if (now == len)
    {
        //所有切後的棍子都用完，且長度達到 len
        if (count == n)
            return true;
        now = 0;
    }

    if (!now)
    {
        //要組成完整棍子的第一根，此時總長還沒有組任何棍子，長度為 0 (now)。所以如果第一根接上的就不行，接下來也不會行，因為第一根會剩下來。
        for (idx = 0; isUsed[idx]; idx++);
        isUsed[idx] = true;
        if (backtracking(idx + 1, count+1, sticks[idx], len))
            return true;
        isUsed[idx] = false;
    }
    else
    {
        for (int i = idx; i < n; i++)
        {
            if (isUsed[i] || (i&&sticks[i] == sticks[i - 1] && !isUsed[i - 1]))//一樣的長度，且沒有用到的，不需要再做
                continue;

            if (now + sticks[i] <= len)
            {
                isUsed[i] = true;
                if (backtracking(i + 1, count+1, now + sticks[i], len))
                    return true;
                isUsed[i] = false;

                //代表此長度不管怎麼擺，後來都會有組無法完成
                if (now + sticks[i] == len)
                    return false;
            }
        }
    }

    return false;
}