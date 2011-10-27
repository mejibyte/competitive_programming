#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
struct node{
	struct node *l, *r;
	int val;
};
struct node *root;
struct node *aux1, *aux2;
struct node *splay(struct node *n, int val){
	struct node N, *l, *r;
	l = r = &N;
	N.l = N.r = NULL;
	struct node *y;
	while(1){
		if( n->val > val ){
			if( !n->l ) break;
			if( n->l->val > val ){
				y = n->l;
				n->l = y->r;
				y->r = n;
				n = y;
				if( !n->l ) break;
			}
			r->l = n;
			r = n;
			n = n->l;
		}else if( n->val < val ){
			if( !n->r ) break;
			if( n->r->val < val ){
				y = n->r;
				n->r = y->l;
				y->l = n;
				n = y;
				if( !n->r ) break;
			}
			l->r = n;
			l = n;
			n = n->r;
		}else break;
	}
	r->l = n->r;
	l->r = n->l;
	n->r = N.l;
	n->l = N.r;
	return n;
}
struct node *S1, *S2;
void split(struct node *T, int k ){
	if( !T ) { S1 = S2 = NULL ; return ; }
	struct node *aux = splay(T,k);
	if( aux->val <= k ){
		S2 = aux->r;
		aux->r = NULL;
		S1 = aux;
	}else{
		S1 = aux->l;
		aux->l = NULL;
		S2 = aux;
	}
}
struct node *join(struct node *T1, struct node *T2){
	if( T1 == NULL ) return T2;
	if( T2 == NULL ) return T1;
	T1 = splay(T1, INT_MAX);
	T1->r = T2;
	return T1;
}
struct node *insert(struct node *T, int k){
	struct node *aux = new node;
	aux->val = k;
	split(T, k);
	aux->l = S1;
	aux->r = S2;
	return aux;
}
struct node *deleteval(struct node *T, int k){
	if( T == NULL ) return T;
	T = splay(T, k);
	if( T->val == k ){
		S1 = T->l;
		S2 = T->r;
		delete T;
		T = join(S1, S2);
	}
	return T;
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
	printf("Introduzca números para el árbol ( 1 x insertar... 2 x buscar, 0 x borrar:\n");
	while(1){
		scanf("%i", &i);
		scanf("%i", &k);
		if( i == 1 )root = insert(root, k);
		else if( i == 2 ){
			root = splay( root, k );
			if( root &&  root->val == k  ) printf("Si esta!!!\n");
			else printf("No esta!!!\n");
		}
		else root = deleteval(root, k);
		dfs(root);
		printf("\n");
	}
	return 0;
}
