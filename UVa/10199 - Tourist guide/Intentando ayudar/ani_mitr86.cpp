#include<cstdio>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
//#include<conio.h>

void articulation_point_visit
(vector<int> *list, int* d, int* low, int* child_cnt, int n, int& time){
   low[n]=d[n]=time++;
   int l=list[n].size();
   for(int v, i=0; i<l; i++){
      v=list[n][i];
      if(d[v]==0){
         child_cnt[n]++;
         articulation_point_visit(list, d, low, child_cnt, v, time);
         low[n]<?=low[v];
      }
      else low[n]<?=d[v];
   }
   return;
}

vector<int> articulation_point(vector<int> *list, int sz){
   bool root[sz+1];
   int d[sz+1], low[sz+1], child_cnt[sz+1], time=1, l;
   for(int i=1; i<=sz; i++){ root[i]=false; d[i]=0; child_cnt[i]=0;}
   vector<int> points;

   for(int i=1; i<=sz; i++) if(d[i]==0){
      root[i]=true;
      articulation_point_visit(list, d, low, child_cnt, i, time);
   }
   for(int i=1; i<=sz; i++){
      if(root[i]&&(child_cnt[i]>1)) points.push_back(i);
      if(!root[i]){
         l=list[i].size();
         for(int j=0; j<l; j++) if(d[i]<=low[list[i][j]]){ points.push_back(i); break;}
      }
   }

   return points;
}

int main(){
    //freopen("input.txt", "r", stdin);
   int n, r, cnt=1;
   string str, u, v;
   map<string, int> m;
   map<int, string> mi;
   vector<string> vec;
   vector<int> points;
   while(1){
      scanf("%d", &n);
      if(n==0) break;
      if(cnt>1) printf("\n");
      m.clear(); mi.clear(); vec.clear();
      for(int c=1, i=0; i<n; i++, c++){
         cin>>str;
         m[str]=c; mi[c]=str;
      }
      scanf("%d", &r);
      vector<int> list[n+1];
      for(int x, y, i=0; i<r; i++){
         cin>>u>>v;
         x=m[u]; y=m[v];
         list[x].push_back(y);
         list[y].push_back(x);
      }
      points=articulation_point(list, n);
      printf("City map #%d: %d camera(s) found\n", cnt++, points.size());
      for(vector<int>::iterator it=points.begin(); it!=points.end(); it++)
         vec.push_back(mi[*it]);
      sort(vec.begin(), vec.end());
      for(vector<string>::iterator it=vec.begin(); it!=vec.end(); it++) cout<<*it<<endl;
   }
   //getch();
   return 0;
}
