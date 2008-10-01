// GENERALIZACION RARA DE LA INTERSECCION DE RECTANGULOS::: PINTA RECT CON COLORES Y PIDE AREA DE CADA COLOR VISIBLE :)

/*
ID: edestef1
LANG: C++
TASK: rect1
*/
#include <map>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>
#include <iostream>
#include <set>
using namespace std;
FILE *fin, *fout;
typedef struct{
	int x1, y1, x2, y2;
	int color;
}rect;
vector<rect> tod, aux;

int vale(rect &r){
	if( r.x1 == r.x2 || r.y1 == r.y2 ) return 0;
	return 1;
}
int agregar(rect r1, rect r2){
// 	printf("   %i %i %i %i %i\n", r2.x1, r2.x2, r2.y1, r2.y2, r2.color);
	if( r2.x1 >= r1.x2 || r2.x2 <= r1.x1 || r2.y1 >= r1.y2 || r2.y2 <= r1.y1 ) return 1;
	r2.x1 = max(r2.x1, r1.x1);
	r2.x2 = min(r2.x2, r1.x2);
	r2.y1 = max(r2.y1, r1.y1);
	r2.y2 = min(r2.y2, r1.y2);
	
	rect u,d,t,c,s;
	u = r1;
	u.x2 = r2.x1;
	d.color = r1.color;
	d.x1 = r2.x1;d.x2 = r2.x2;
	d.y1 = r1.y1; d.y2 = r2.y1;
	t.color = r1.color;
	t.x1 = r2.x1;t.x2 = r2.x2;
	t.y1 = r2.y2; t.y2 = r1.y2;
// 	c = r2;
	s = r1;
	s.x1 = r2.x2;
	
	if( vale(u) ) aux.push_back(u);
	if( vale(d) ) aux.push_back(d);
	if(vale(t) )aux.push_back(t);
// 	if(vale(c) ) aux.push_back(c);
	if( vale(s) )aux.push_back(s);
	return 0;
}
int main(){
	int i,j ,k;
	fin = fopen("rect1.in", "r"); fout = fopen("rect1.out", "w");
	int A, B, N;
	int color[2501];memset(color, 0, sizeof(color));
	fscanf(fin, "%i %i %i", &A, &B, &N);
	vector<int> X, Y;
	X.push_back(0), X.push_back(A);
	Y.push_back(0), Y.push_back(B);
	int arr[1001][5];

	for(i=0;i<N;i++){
		for(j=0;j<5;j++){
			fscanf(fin, "%i", &arr[i][j]);
		}
	}

	tod.push_back((rect){0,0,A,B,1});
	for(i=0;i<N;i++){
		aux.clear();
		vector<rect> todAux;
		rect r;
		r.x1 = arr[i][0], r.y1 = arr[i][1], r.x2 = arr[i][2], r.y2 = arr[i][3], r.color = arr[i][4];
		for(j=0;j<tod.size();j++){
			if(agregar(tod[j], r))
				todAux.push_back(tod[j]);
		}
		tod = todAux;
		for(j=0;j<aux.size();j++) tod.push_back(aux[j]);
		tod.push_back(r);
	}
	for(i=0;i<tod.size();i++){
		int tot = (tod[i].x2-tod[i].x1)*(tod[i].y2-tod[i].y1);
		color[tod[i].color] += tot;
	}
	for(i=0;i<2501;i++){
		if( color[i] ){
			fprintf(fout, "%i %i\n", i, color[i]);
			printf("%i %i\n", i, color[i]);
		}
	}
	return 0;
}
