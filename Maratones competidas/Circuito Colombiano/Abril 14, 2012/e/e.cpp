using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>


int main()
{
    string line;
    while(getline(cin, line) and line != "END")
    {
        map<char, int> dic;
        bool works = true;
        for(int i = 0; i < line.size() and works; ++i)
        {
            if(line[i] != ' ')
              dic[line[i]] += 1;
            if(dic[line[i]] > 1)
                works = false;
        }
        if(works)
            cout << line << endl;
    }
    return 0;
}

