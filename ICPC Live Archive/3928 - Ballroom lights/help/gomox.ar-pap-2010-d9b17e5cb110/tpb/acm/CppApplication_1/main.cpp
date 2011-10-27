#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
#define foreachin(it,s) for (typeof(s.begin()) it = (s).begin(); it != (s).end(); it++)
#define forn(i,n) for(unsigned short i = 0; i < (n); i++)


class uf_node{
public:
unsigned short name;
unsigned short rank;
uf_node *parent;
};


class union_find{
    public :
    uf_node* S;
    inline union_find(unsigned short n){
        S =new uf_node[n];
        for(unsigned short i=0;i<n;i++){
            S[i].rank=0;
            S[i].name=i;
            S[i].parent=&S[i];
        }
    }
    ~union_find(){delete[] S;}

    inline void Union(unsigned short a, unsigned short b){ //use Union because union is a keyword :P
        unsigned short ranka,rankb;
        ranka=S[a].parent->rank;
        rankb=S[b].parent->rank;
        if(ranka>rankb){
            (S[b].parent)->parent=S[a].parent;
            S[a].rank=ranka+rankb;
        }
        else{
            (S[a].parent)->parent=S[b].parent;
            S[b].rank=ranka+rankb;
        }
    }

    inline void compress_path(uf_node* temp, uf_node* aux, uf_node* stop_point){
        temp=aux->parent;
        aux->parent=stop_point;
        aux=temp;
        while(aux!=stop_point){
            temp=aux->parent;
            aux->parent=stop_point;
            aux=temp;
        }
    }

    inline unsigned short Find(unsigned short a){
        uf_node* temp;
        uf_node* aux;
        unsigned short result;
        aux=&S[a];
        temp=S[a].parent;
        while(aux!=temp){
            aux=temp;
            temp=(*aux).parent;
        }
        result=aux->name;
        uf_node* stop_point;
        stop_point=aux;
        aux=&S[a];
        compress_path(temp,aux,stop_point);

        return result;
    }
};

class edge{
public :
    unsigned short start,end;
    unsigned short cost;
    inline edge(unsigned short start, unsigned short end, unsigned short cost){
        this->start=start;
        this->end=end;
        this->cost=cost;
    }
};


inline bool compare(const edge& a,const edge& b ){
    return a.cost < b.cost;

}

inline void bucket_sort(list<edge>& e,unsigned short max_cost){
    vector<list<edge> > v(max_cost+1);
    while(!e.empty()){
	const edge& ed = e.front();
        v[ed.cost].push_back(ed);
        e.pop_front();
    }
    forn(i, max_cost+1){
        while(!v[i].empty()){
            e.push_back(v[i].back());
            v[i].pop_back();
        }
    }

}

inline unsigned short kruskal(list<edge>& e,unsigned short n, vector<list<edge> >& adj,list<edge>& rejected, unsigned short max_cost, unsigned short m){
    union_find list(n);
    unsigned short res=0;
    if (m > max_cost)
        bucket_sort(e,max_cost);
    else
	e.sort(compare);

    foreachin(it,e){
        unsigned short s,f;
        s=it->start;
        f=it->end;

        if(list.Find(s)==list.Find(f)){

            rejected.push_back(*it);
            continue;
        }
        else{
            list.Union(s,f);
            res += it->cost;
            adj[s].push_back(*it);
	    adj[f].push_back(edge(it->end,it->start,it->cost));
        }
    }

    return res;

}


inline void dfs_fill_max(unsigned short u, unsigned short x,vector<list<edge> >& mst_adjacency, vector<vector<edge*> >& max){
    foreachin(v,(mst_adjacency[x])){
       if( max[u][v->end] == NULL && v->end != u){
           if(x==u || v->cost > max[u][x]->cost){
               max[u][v->end] = &(*v);
           }
           else{
               max[u][v->end] = max[u][x];
           }
           dfs_fill_max(u,v->end,mst_adjacency,max);
       }

    }
}

inline unsigned short second_mst(unsigned short n, vector<list<edge> >& mst_adjacency, list<edge>& rejected,unsigned short minimum_cost){
    vector<vector<edge*> > max(n,vector<edge*>(n,NULL));
    list<edge>::iterator it = rejected.begin();
    unsigned short start = it->start;
    unsigned short end = it->end;
    dfs_fill_max(start,start,mst_adjacency, max);
    unsigned short old_cost=max[start][end]->cost;
    unsigned short new_cost=it->cost;
    unsigned short minimum= new_cost - old_cost;
    it++;
    for(it;it != rejected.end();it++ ){
        start = it->start;
        end = it->end;
        if(max[start][end] == NULL)dfs_fill_max(start,start,mst_adjacency, max);

        unsigned short aux=it->cost- max[start][end]->cost;
        if(aux < minimum){
            if(aux == 0)return minimum_cost;
            minimum= aux;
            new_cost =  it->cost;
            old_cost = max[start][end]->cost;
        }

    }
    return minimum_cost - old_cost + new_cost;
}


int main(){
int cases;
cin>>cases;
unsigned short n;
unsigned short m;
unsigned short from,to,cost;


while(cases > 0){
    scanf("%hu %hu",&n,&m);
    vector<list<edge> > mst_adjacency(n);
    list<edge> rejected;
    list<edge> l;
    unsigned short cant_edges=0;
    unsigned short max_cost = 0;
    while(cant_edges < m){
        scanf("%hu %hu %hu",&from,&to,&cost);
        if(cost > max_cost)max_cost = cost;
        l.push_back(edge(from-1,to-1,cost));
        cant_edges++;
    }
    unsigned short k =kruskal(l,n,mst_adjacency,rejected,max_cost,m);
    //unsigned short k =kruskal(l,n,mst_adjacency,rejected);
    cout << k<<" ";
    cout << second_mst(n,mst_adjacency,rejected,k)<<endl;
    cases--;
}
return 0;
}






