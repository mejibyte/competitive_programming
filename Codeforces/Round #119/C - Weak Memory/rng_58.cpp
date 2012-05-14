#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

#define INF (1<<29)

int V,E,K,S,T;
int guide[100010];
vector <int> edge[100010];

queue <int> q;
priority_queue <pair <int, int> > pq;
int dist1[100010],dist2[100010];
bool used[100010];

void add(int x, int d){
    if(d < dist2[x]){
        dist2[x] = d;
        pq.push(make_pair(-d,x));
    }
}

int main(void){
    int i,j,x,y;
    
    scanf("%d%d%d",&V,&E,&K);
    REP(i,K){
        scanf("%d",&guide[i]);
        guide[i]--;
    }
    REP(i,E){
        scanf("%d%d",&x,&y);
        x--; y--;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    scanf("%d%d",&S,&T);
    S--; T--;
    
    REP(i,V) dist1[i] = INF;
    REP(i,K){
        dist1[guide[i]] = 0;
        q.push(guide[i]);
    }
    if(dist1[T] != 0){
        dist1[T] = 0;
        q.push(T);
    }
    
    while(!q.empty()){
        x = q.front(); q.pop();
        REP(i,edge[x].size()){
            int y = edge[x][i];
            if(dist1[y] == INF){
                dist1[y] = dist1[x] + 1;
                q.push(y);
            }
        }
    }
    
//  REP(i,V) cout << dist1[i] << ' ';
//  cout << endl;
    
    REP(i,V) dist2[i] = INF;
    add(S, 0);
    
    while(!pq.empty()){
        int x = pq.top().second; pq.pop();
        if(used[x]) continue;
        used[x] = true;
        
        REP(i,edge[x].size()){
            int y = edge[x][i];
            int d = max(dist2[x], dist1[x] + dist1[y] + 1);
            add(y, d);
        }
    }
    
//  REP(i,V) cout << dist2[i] << ' ';
//  cout << endl;
    
    int ans = dist2[T];
    if(ans == INF) ans = -1;
    cout << ans << endl;
    
    return 0;
}