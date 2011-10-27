#include <stdio.h>
#include <assert.h>

int array[100];

int main(void)

{
  int n, h,l_1,l_2,set=0,num_bricks=0,bricks_pwal,move=0;

  for( ; ; )
  {
    scanf("%d", &n);
    if(n==0)
    {
      return 0;
    }
    set++;
    assert(n>=1 && n<=50);
    {
       /*will the set increase here or before :( */
      for(l_1=0;l_1<n;l_1++)
      {
          scanf("%d", &h);
              while(h<=0 || h>100)
                {
                  scanf("%d",&h);
                }

              /*assert(ch=='@' || ch=='*');*/
              array[l_1] = h;
              num_bricks +=h;
      }

      if(num_bricks%n==0)
      {
              bricks_pwal = num_bricks/n;

              for(l_2=0;l_2<n;l_2++)
              {
                if(bricks_pwal-array[l_2]>0)
                {
                  move += bricks_pwal-array[l_2];
                }
               }
      }

      printf("Set #%d\n", set);
      printf("The minimum number of moves is %d.\n\n", move);

      move = 0;
      num_bricks = 0;
    }
   }

   /*return 0;*/
}

