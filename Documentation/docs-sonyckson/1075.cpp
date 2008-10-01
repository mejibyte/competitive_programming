// THREAD IN THE SPACE....

#include <cstdio>
#include <cmath>
#include <cstdlib>
typedef struct{
	double x, y , z;
}point;
void read(point & A){
	scanf("%lf %lf %lf", &(A.x), &(A.y), &(A.z));
}
double dist(point p1, point p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z));
}
double Pi;
double acos1(double x){
	if( x > 1 ) x = 1;
	if( x < -1 ) x = -1;
	double res = acos(x);
	while( res < 0.0 ) res += 2.0*Pi;
	if( res >= Pi ) res = 2.0*Pi - res;
	return res;
}


int main(){
	int i,j ,k;
	Pi = acos(-1.0);
	point A, B, C;
	read(A), read(B), read(C);
	if( A.x == B.x && A.y == B.y && A.z == B.z ){
		printf("0.00\n");
		return 0;
	}
	double R;
	scanf("%lf", &R);
	double dab, dbc, dac;
	dab = dist(A, B);
	dbc = dist(B, C);
	dac = dist(A, C);
	double s = (dab+dbc+dac)/2.0;
	double area = sqrt(s*(s-dac)*(s-dbc)*(s-dab));
	double alt = (area*2.0)/dab;
	if( fabs(alt-R) < 1e-7 || alt > R ){
		printf("%.2lf\n", dab);
		return 0;
	}
	if (((dac*dac + 1e-7) >= (dab *dab+ dbc*dbc)) || ((dbc*dbc+1e-7) >= dab*dab+ dac*dac)){
		
		printf("%.2lf\n", dab);
		return 0;
	}
	double l1, l2;
	l1 = sqrt(dac*dac - R * R);
	l2 = sqrt(dbc*dbc - R * R);
	double angleacb, anglel1ca, anglel2cb;
	double a, b, c;
	c = dab;
	b = dbc, a = dac;
	angleacb = acos1((c*c-a*a-b*b)/(-2.0*a*b));
	
	c = l1, b = R, a = dac;
	anglel1ca = acos1((c*c-a*a-b*b)/(-2.0*a*b));
	
	c = l2; a = dbc;
	anglel2cb =  acos1((c*c-a*a-b*b)/(-2.0*a*b));

	double alfa = angleacb - anglel1ca - anglel2cb;
	
	double di = (Pi*(R+R)) * alfa / (2.*Pi);

	printf("%.2lf\n",( di + l1 + l2 ));
	return 0;
}
