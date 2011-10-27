#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;
struct node{
	int val;
	int h;
	int contador;
	struct node *l, *r, *p;
};
struct node *root;
int BI(struct node* r ){        /// INDICE DE BALANCEO
	if( r == NULL ) return 0;
	if( r->l && r->r ){
		return r->r->h - r->l->h;
	}else if( r->l ){
		return -r->l->h-1;
	}else if( r->r ) return r->r->h+1;
	else return 0;
}
void suplantar(struct node* p, struct node* h, struct node* n){ 
	if( p == NULL )root = n;
	else if( p->l == h )p->l = n;
	else p->r = n;
}
int maxAltura(struct node* r){
	r->h = 0;
	if( r->l && r->h < r->l->h + 1 ) r->h = r->l->h + 1;
	if( r->r && r->h < r->r->h + 1 ) r->h = r->r->h + 1;
}
void RIGHT(struct node* r){
	struct node* aux = r->l;
	r->l = aux->r;
	if( r->l ){
		r->l->p = r;
	}
	suplantar(r->p, r, aux);
	aux->p = r->p;
	r->p = aux;
	aux->r = r;
	maxAltura(r);
	maxAltura(aux);
}
void LEFT(struct node* r){
	struct node* aux = r->r;
	r->r = aux->l;
	if( r->r ){
		r->r->p = r;
	}
	suplantar(r->p, r, aux);
	aux->p = r->p;
	r->p = aux;
	aux->l = r;
	maxAltura(r);
	maxAltura(aux);
}
void balanceo(struct node* r ){
	if( !r ) return;
	maxAltura(r);
	int balanceIndex = BI(r);
	if( abs(balanceIndex) < 2 ) return;
	if( balanceIndex == 2 ){
		int bis = BI(r->r);
		if( bis == -1 ){
			RIGHT(r->r);
		}
		LEFT(r);
	}else{
		int bis = BI(r->l);
		if( bis == 1 ){
			LEFT(r->l);
		}RIGHT(r);
	}
}
struct node *nuevo(int val, struct node* r ){
	struct node *a = new node;
	a->val = val, a->l = a->r = NULL;
	a->p = r, a->contador = 1;
	a->h = 0;
	return a;
}
void insertr(int val, struct node *r){
	if( r->val == val ){
		r->contador++;return;
	}if( r->val > val ){
		if( r->l == NULL ){
			struct node *a = nuevo(val,r);
			r->l = a;
			r->h = 1;
			return;
		}else{
			insertr(val,r->l);
		}
	}else{
		if( r->r == NULL ){
			struct node *a = nuevo(val,r);
			r->r = a;
			r->h = 1;
			return;
		}else{
			insertr(val, r->r);
		}
	}
	balanceo(r);
}
void insert(int val){
	if( root == NULL ){
		root = new node;
		root->l = root->r = root->p = NULL;
		root->val = val, root->contador = 1, root->h = 0;
		return;
	}
	struct node * aux = root;
	insertr(val,root);
}
int borrarMax(struct node* r){
	int res;
	struct node* a = r;
	if( r->r ) res = borrarMax(r->r);
	else{
		a = r->p;
		suplantar(r->p, r, r->l);
		if( r->l ) r->l->p = r->p;
		res = r->val;
		delete r;
	}
	r = a;
	balanceo(r);
	return res;
}
void deleteval(int val, struct node* r){
	if( !r ) return;
	struct node *a = r;
	if(r->val == val ){
		if( !r->l ){
			suplantar(r->p, r, r->r);
			a = r->p;
			if( r->r )r->r->p = r->p;
			delete r;
		}else if( !r->r ){
			suplantar(r->p, r, r->l);
			a = r->p;
			if( r->l )r->l->p = r->p;
			delete r;
		}else{
			int v = borrarMax(r->l);
			r->val = v;
		}
	}else if( r->val > val ){
		deleteval(val, r->l);
	}else deleteval(val, r->r);
	r = a;
	if( !r ) return;
	balanceo(r);
}
int search(int val, struct node* r){
	if( !r ) return 0; if( r->val == val ) return 1; 
	if( r->val > val ) return search(val, r->l);else return search(val, r->r);
}
void dfs(struct node * r ){
	if( r == NULL ) return;
	printf(" %i ", r->val);
	printf("(");
	dfs(r->l);
	printf(")");
	printf("(");
	dfs(r->r);
	printf(")");
}
int main(){
	int i,j ,k;
	root = NULL;
	// testeo...
	printf("Introduzca números para el árbol:\n");
	while(1){
		scanf("%i", &i);
		scanf("%i", &k);
		if( i == 1 )
		insert(k);
		else if( i == 2 ){
			if( search(k, root) ) printf("Si esta!!!\n");
			else printf("No esta!!!\n");
		}else deleteval(k,root);
		dfs(root);
		printf("\n");
	}
	return 0;
}
