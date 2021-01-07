// https://github.com/Diusrex/UVA-Solutions/blob/master/307%20Sticks.cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Requirements for bestLength:
    // total % length == 0
    // Greater than all other lengths

int N;
int totalLength, longestStick;

// sort by longest to shortest
vector<int> allSticks;
vector<int> sumAfterInc;
vector<bool> included;

bool CreateAllBunches(const int goalLength);

bool CanCreateUsingAllOthers(int index, int currentLength, const int goalLength)
{
    if (currentLength == goalLength)
    {
        return CreateAllBunches(goalLength);
    }

    for (int i = index; i < N; ++i)
    {
        if (sumAfterInc[i] + currentLength < goalLength)
            return false;

        if (!included[i] && currentLength + allSticks[i] <= goalLength)
        {
            included[i] = true;
            if (CanCreateUsingAllOthers(i + 1, currentLength + allSticks[i], goalLength))
            {
                included[i] = false;
                return true;
            }
            included[i] = false;

            // Current setup will not be possible, since this would be the solution with the least # used
            if (currentLength + allSticks[i] == goalLength)
                return false;

            // Skip equal lengths
            while (i < N && allSticks[i] == allSticks[i + 1])
                ++i;
        }
    }

    return false;
}

bool CreateAllBunches(const int goalLength)
{
    for (int i = 0; i < N; ++i)
        if (!included[i])
        {
            included[i] = true;
            bool ret = CanCreateUsingAllOthers(i + 1, allSticks[i], goalLength);
            included[i] = false;
            return ret;
        }

    return true;
}

int main()
{
    while (cin >> N, N)
    {
        allSticks.resize(N);
        included.assign(N, 0);

        int totalLength = 0;
        for (int i = 0; i < N; ++i)
        {
            cin >> allSticks[i];
            totalLength += allSticks[i];
        }


        sort(allSticks.begin(), allSticks.end(), greater<int>());

        sumAfterInc.resize(N + 1);
        sumAfterInc[N] = 0;
        for (int i = N - 1; i >= 0; --i)
            sumAfterInc[i] = allSticks[i] + sumAfterInc[i + 1];

        int length;
        bool worked = false;
        for (length = allSticks[0]; length * 2 <= totalLength; ++length)
        {
            if (totalLength % length == 0)
            {
                worked = CreateAllBunches(length);
                if (worked)
                    break;
            }
        }

        if (!worked)
            length = totalLength;


        cout << length   << '\n';
    }
}