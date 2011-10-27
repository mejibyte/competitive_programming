#include <stdio.h> 

int main() 

{ 
   unsigned int num,i,j; 
   char step; 

   scanf("%d",&num); 

   while (num!=0) 
   { 
      step=0; 
      i=4; 
      j=5; 

      while (num>i && i>0) 
      { 
         i+=j; 
         j+=2; 
      } 

      if (num==i) printf("yes\n"); 
      else printf("no\n"); 
      scanf("%d",&num); 
   } 

   return 0; 
} 
