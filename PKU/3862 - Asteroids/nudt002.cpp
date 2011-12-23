// Stolen from  http://acm.hust.edu.cn:8080/judge/problem/viewSource.action?id=149288
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#define swp(x,y) x^=y,y^=x,x^=y

using namespace std;
typedef double db;
const double oo = 1e100;
const double eps = 1e-9;
struct pt{
    db x,y,z;
    pt(){}pt(db x,db y,db z):x(x),y(y),z(z){}
    void getP(){scanf("%lf%lf%lf",&x,&y,&z);}
    void nega(){x=-x,y=-y,z=-z;}
    void div(db c){x/=c,y/=c,z/=c;}
    pt mul(db c){return pt(x*c,y*c,z*c);}
    pt add(pt a){return pt(x+a.x,y+a.y,z+a.z);}
    pt sub(pt a){return pt(x-a.x,y-a.y,z-a.z);}
    pt cross(pt a){return pt(y*a.z-z*a.y,z*a.x-x*a.z,x*a.y-y*a.x);}
    db len(){return sqrt(x*x+y*y+z*z);}
    db dis(pt a){return this->sub(a).len();}
    db dot(pt a){return x*a.x+y*a.y+z*a.z;}
}a[120],pn,C;
struct plane{
    pt p[120],n;
    int d;
}P[120];
char u[120][120][120],np[120],dir;
int nd;
inline int sign(db x){return(x<-eps)?-1:(x>eps);}
inline void set(int x,int y,int z){
    if (x > y) swp(x,y);
    if (y > z) swp(y,z);
    if (x > y) swp(x,y);
    u[x][y][z] = true;
}
pt cross(pt a,pt b,pt c){
    return b.sub(a).cross(c.sub(a));
}
db dot(pt a,pt b,pt c){
    return b.sub(a).dot(c.sub(a));
}
db Det(pt a,pt b,pt c){
    return    a.x*(b.y*c.z-c.y*b.z)-
            a.y*(b.x*c.z-c.x*b.z)+
            a.z*(b.x*c.y-c.x*b.y);
}

db dis(pt o,plane pa){
    int i;
    for (i = 0;i < pa.d;i++){
        if (sign(o.sub(pa.p[i]).dot(pa.p[i+1].sub(pa.p[i]).cross(pa.n))) > 0)
            break;
    }
    if (i < pa.d) return oo;
    return fabs(o.sub(pa.p[0]).dot(pa.n) / pa.n.len());
}
bool cmpP(int i,int j){
    int cs = sign(cross(a[np[0]],a[i],a[j]).dot(pn));
    pt cp = cross(a[np[0]],a[i],a[j]);
    return cs != dir;
}
int main(){
    int n,m,i,j,k,c,x,y,z;
    db r1,r2,cd,V;
    while (scanf("%d",&n) != EOF){
        for (i = 0;i < n;i++)
            a[i].getP();
        memset(u,0,sizeof(u));
        for (i = 0,m = 0;i < n;i++)
            for (j = i+1;j < n;j++)
                for (k = j+1;k < n;k++)if(!u[i][j][k]){
                    plane &cp = P[m];
                    pn = cp.n = cross(a[i],a[j],a[k]);
                    np[0] = i,np[1] = j,np[2] = k;
                    nd = 3;
                    db cr = a[i].dot(cp.n);
                    dir = 0;
                    for (c = 0;c < n;c++)
                        if (c != i && c != j && c != k){
                            int cs = sign(a[c].dot(cp.n)-cr);
                            if (cs == 0)
                                np[nd++] = c;
                            else if (dir == 0)
                                dir = cs;
                            else if (cs != dir)
                                dir = -2;
                        }
                    for (x = 0;x < nd;x++)
                        for (y = x+1;y < nd;y++)
                            for (z = y+1;z < nd;z++)
                                set(np[x],np[y],np[z]);
                    if (dir != -2){
                        sort(np+1,np+nd,cmpP);
                        for (x = 0;x < nd;x++)
                            cp.p[x] = a[np[x]];
                        cp.p[nd] = cp.p[0];
                        cp.d = nd;
                        if (dir == 1)
                            cp.n.nega();
                        m++;
                    }
                }
        V = 0.0,C = pt(0.0,0.0,0.0);
        for (i = 0;i < m;i++){
            plane &cp = P[i];
            for (j = 0;j < cp.d;j++){
                db cd = Det(cp.p[0],cp.p[j],cp.p[j+1]);
                V += cd;
                C = C.add(cp.p[0].add(cp.p[j]).add(cp.p[j+1]).mul(cd));
            }
        }
        if (V < 0) V = -V;
        C.div(V*4.0);
        r1 = oo;
        for (i = 0;i < m;i++){
            cd = dis(C,P[i]);
            if (cd < r1) r1 = cd;
        }
        scanf("%d",&n);
        for (i = 0;i < n;i++)
            a[i].getP();
        memset(u,0,sizeof(u));
        for (i = 0,m = 0;i < n;i++)
            for (j = i+1;j < n;j++)
                for (k = j+1;k < n;k++)if(!u[i][j][k]){
                    plane &cp = P[m];
                    pn = cp.n = cross(a[i],a[j],a[k]);
                    np[0] = i,np[1] = j,np[2] = k;
                    nd = 3;
                    db cr = a[i].dot(cp.n);
                    dir = 0;
                    for (c = 0;c < n;c++)
                        if (c != i && c != j && c != k){
                            int cs = sign(a[c].dot(cp.n)-cr);
                            if (cs == 0)
                                np[nd++] = c;
                            else if (dir == 0)
                                dir = cs;
                            else if (cs != dir)
                                dir = -2;
                        }
                    for (x = 0;x < nd;x++)
                        for (y = x+1;y < nd;y++)
                            for (z = y+1;z < nd;z++)
                                set(np[x],np[y],np[z]);
                    if (dir != -2){
                        sort(np+1,np+nd,cmpP);
                        for (x = 0;x < nd;x++)
                            cp.p[x] = a[np[x]];
                        cp.p[nd] = cp.p[0];
                        cp.d = nd;
                        if (dir == 1)
                            cp.n.nega();
                        m++;
                    }
                }
        V = 0.0,C = pt(0.0,0.0,0.0);
        for (i = 0;i < m;i++){
            plane &cp = P[i];
            for (j = 0;j < cp.d;j++){
                db cd = Det(cp.p[0],cp.p[j],cp.p[j+1]);
                V += cd;
                C = C.add(cp.p[0].add(cp.p[j]).add(cp.p[j+1]).mul(cd));
            }
        }
        if (V < 0) V = -V;
        C.div(V*4.0);
        r2 = oo;
        for (i = 0;i < m;i++){
            cd = dis(C,P[i]);
            if (cd < r2) r2 = cd;
        }
        //printf("%.5lf %.5lf\n", r1, r2);
          printf("%.5lf\n", r1 + r2);
    }
}
