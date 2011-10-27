point center(double x1, double y1, double x2, double y2, double x3, double y3){
	point p;
	double A1 = x1-x2;
	double A2 = x2-x3;
	double B1 = y1-y2;
	double B2 = y2-y3;
	double C1 = (A1*(x1+x2) + B1*(y1+y2))/2;
	double C2 = (A2*(x2+x3) + B2*(y2+y3))/2;
	double d = A1*B2-A2*B1;
	if(fabs(d)<1e-7)return p;
	double y = (A1*C2-A2*C1)/d;
	double x = -(B1*C2-B2*C1)/d;
	p.x = x, p.y = y;
	return p;
}
