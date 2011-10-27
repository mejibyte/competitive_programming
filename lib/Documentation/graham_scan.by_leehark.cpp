//written by leehark
//any problem please send mail to me: lihe21327@gmail.com (also gtalk)

double det(point a,point b,point c)
{return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}
double dis(point a,point b)
{return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}
void swap(point &a,point &b)
{point tt;tt=a,a=b,b=tt;}
bool cmp(const point &a,const point &b)
{
    if(fabs(det(p[0],a,b))<eps)
        return dis(p[0],a)<dis(p[0],b);
    return det(p[0],a,b)>0;
}


void Convex_Hull(point *p,long n,point *stack,long& top)
{
    long i;
    for(i=1;i<n;i++)
        if(p[i].y<p[0].y||fabs(p[i].y-p[0].y)<eps&&p[i].x<p[0].x)
            swap(p[i],p[0]);
    sort(p+1,p+n,cmp);
    stack[top++]=p[0];
    for(i=1;i<n;i++)
    {
        while(top>=2&&det(stack[top-2],stack[top-1],p[i])<=0)
            top--;
        stack[top++]=p[i];
    }
    sta[top]=p[0];
}
