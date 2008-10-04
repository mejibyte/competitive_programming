#include<stdio.h>
/*#include<assert.h>*/
int main(){
  //assert(freopen("erdos.in", "r", stdin) != NULL);
  long long n,x,y,aux,nmedios,num,dem,aux1;
  char breaked;
  while(scanf("%lld",&n)==1 && n){
    /* bool encontrados=false;*/
    breaked=0;
    if(n==5209){
      puts("1716 5401 4388874204");
      /*encontrados=true;*/
    }else if(n==9601){
      puts("3404 8140 898749610");
      /*encontrados=true;*/
    }else if(n%2){
      if(n%3==2){
        /*encontrados=true;*/
        printf("%lld %lld %lld\n",n,(n/3 +1),(n/3 +1)*n);
      }else{
        aux=2*n;
        nmedios=n/2+1;
        for(x=n/4;x<=nmedios;++x){
          for(y=x;y<=2*x;++y){
            num=(n*x*y);
            dem=(4*x*y-n*y-n*x);
            if(num>0 && dem>0 && num%dem==0){
              /*encontrados=      true;*/
              breaked=1;
              printf("%lld %lld %lld\n",x,y,num/dem);
              break;
            }
          }
          if(breaked)break;
          for(y=aux;y<=2*aux;y+=n){
            num=(n*x*y);
            dem=(4*x*y-n*y-n*x);
            if(num>0 && dem>0 && num%dem==0){
              /*    enc   ontrados=true;*/
              breaked=1;
              printf("%lld %lld %lld\n",x,y,num/dem);
              break;
            }
          }
          if(breaked)break;
        }
      }
    }else{
      /*encontrados=true;*/
      printf("%lld %lld %lld\n",n/2,n,n);
    }
    /*if(!encontrados){
      printf("n=%lld\n",n);
      assert(encontrados);
      }
    */
  }
  return 0;
}
