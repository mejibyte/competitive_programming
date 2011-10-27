#include <stdio.h>

int ram[1000];
int r[10];
int i,ip,a,b,c;

main(){
   while (1 == scanf("%d",&ram[i++])){} 
   for (i=1;;i++){
      a = ram[ip]/100;
      b = ram[ip]/10%10;
      c = ram[ip]%10;
      ip++;
      if (a == 1) break;
      if (a == 2) r[b] = c;
      else if (a == 3) r[b] = (r[b]+c)%1000;
      else if (a == 4) r[b] = (r[b]*c)%1000;
      else if (a == 5) r[b] = r[c];
      else if (a == 6) r[b] = (r[b]+r[c])%1000;
      else if (a == 7) r[b] = (r[b]*r[c])%1000;
      else if (a == 8) r[b] = ram[r[c]];
      else if (a == 9) ram[r[c]] = r[b];
      else if (a == 0 && r[c] !=0) ip = r[b];
   }
   printf("%d\n",i);
}
