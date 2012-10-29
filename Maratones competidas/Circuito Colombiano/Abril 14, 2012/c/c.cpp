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

vector <pair <long double, int> > price;

const long double pi = 2 * acos(0);

int main(){
   int n;
   int run = 1;
   while (cin >> n){
        if (n == 0)break;
        price.clear();
        for (int i = 0; i < n; i++){
            int d, p;
            cin >> d >> p;
            long double area = pi * d * d / 4.0;
            price.push_back(make_pair(p / area, d));
        }
        sort(price.begin(), price.end());
        printf("Menu %d: %d\n", run++, price[0].second);
    }
    return 0;
}

