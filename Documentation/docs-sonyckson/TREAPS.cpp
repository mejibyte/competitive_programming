#include <cstdio>
#include <set>
#include <cassert>
#include <iostream>
#include <cstdlib>
using namespace std;
struct node{
	int val;
	int p;
	struct node * l,* r;
	int hijos;
};
struct node* root;
struct node* RIGHT(struct node * n){
	struct node* aux = n->l;
	n->hijos -= ( aux->hijos + 1 );
	aux->hijos += n->hijos+1;
	if( aux->r ) n->hijos += aux->r->hijos + 1; //, aux->hijos -= aux->r->hijos;
	n->l = aux->r;
	aux->r = n;
	return aux;
}
struct node* LEFT(struct node * n){
	struct node* aux = n->r;
	n->hijos -= (aux->hijos + 1 );
	aux->hijos += n->hijos + 1;
	if( aux->l ) n->hijos += aux->l->hijos + 1; //, aux->hijos -= aux->l->hijos;
	n->r = aux->l;
	aux->l = n;
	return aux;
}
struct node * insert(int val, struct node * r){
	if( r == NULL ){
		struct node * a = new node;
		a->p = rand(), a->val = val, a->l = a->r = NULL, a->hijos = 0;
		return a;
	}
	r->hijos++;
	if( val < r->val ){
		r->l = insert(val, r->l);
		if( r->l->p > r->p ){
			return RIGHT(r);
		}
	}else if( val > r->val ){
		r->r = insert(val, r->r);
		if( r->r->p > r->p ){	
			return LEFT(r);
		}
	}
	return r;
}
struct node* bubbleDown(struct node* n){
	struct node* aux = n;
	if( n->l == n->r ){
		delete n;
		return NULL;
	}else if( n->l && n->r ){
		if( n->l->p > n->r->p ){
			aux = RIGHT(n);
			aux->r = bubbleDown(aux->r);
		}else{
			aux = LEFT(n);
			aux->l = bubbleDown(aux->l);
		}
	}else if( n->l ){
		aux = RIGHT(n);
		aux->r = bubbleDown(aux->r);
	}else{
		aux = LEFT(n);
		aux->l = bubbleDown(aux->l);
	}
	aux->hijos--;
	return aux;
}
// PRECONDICIÖN: val esta en el árbol
struct node* deleteval(int val, struct node* n){
	if( !n ) return NULL;
	if( n->val != val ) n->hijos--;
	if( n->val > val ) n->l = deleteval(val, n->l);
	else if( n->val < val ) n->r = deleteval(val,n->r);
	else n = bubbleDown(n);
	return n;
}
bool search(int val, struct node* n ){
	if( !n ) return false;
	if( n->val == val ) return true;
	if( n->val > val ) return search(val, n->l);
	if( n->val < val ) return search(val, n->r);
}
void dfs(struct node * r ){
	if( r == NULL ) return;
	printf(" %i p%i h%i ", r->val, r->p, r->hijos);
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
	srand(-1);
	printf("Introduzca números para el árbol ( 1 x insertar... 2 x buscar, 0 x borrar:\n");
	while(1){
		scanf("%i", &i);
		scanf("%i", &k);
		if( i == 1 )
			root = insert(k, root);
		else if( i == 2 ){
			if( search(k, root) ) printf("Si esta!!!\n");
			else printf("No esta!!!\n");
		}
		else if( search(k, root) ) root = deleteval(k,root);
		dfs(root);
		printf("\n");
	}
	return 0;
}
