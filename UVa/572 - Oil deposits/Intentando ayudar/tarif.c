#include <stdio.h>
#include <assert.h>

int recur(int,int);

#define ROW 100
#define COL 100

char array[ROW][COL];
int m,n;

int main(void)

{

  int l_1,l_2;
  int grid = 0,z=0;
  char ch;

  for (;;)
    {
      scanf("%d %d", &m, &n);

      if(m==0)
        {

          return 0;
        }

      assert(m>=1 && m<=100 && n>=1 && n<=100);
      for(l_1=0;l_1<m;l_1++)
        {
          for(l_2=0;l_2<n;l_2++)
            {
              scanf("%c", &ch);
              while(ch=='\n' || ch=='\r' || ch==' ')
                {
                  scanf("%c",&ch);
                }

              assert(ch=='@' || ch=='*');
              array[l_1][l_2] = ch;
            }

        }


      for(l_1=0;l_1<m;l_1++)
        {
          for(l_2=0;l_2<n;l_2++)
            {
              if(array[l_1][l_2]=='@')
                {
                  z++;
                  array[l_1][l_2]='c';
                  recur(l_1,l_2);
                }
            }
        }

      //assert(z<=100); //This generates a Runtime Error... Bad problem description!
      printf("%d\n", z);

      z=0;
    }
  return 0;
}


int recur(int mm, int nn)
{


  int k,i,j;

  int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
  int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

  for( k = 0; k < 8; k++)
    {
      i = mm + dx[k];
      j = nn + dy[k];

      if(i >= 0 && i < m && j >= 0 && j < n)
        if(array[i][j]=='@')
          {

            array[i][j] = 'c';
            recur(i,j);
          }
    }

  return 0;
}
