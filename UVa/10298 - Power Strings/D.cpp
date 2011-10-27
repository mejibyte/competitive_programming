#include <cstdio>
#include <cstring>

char s[2000002];

main(){
   while (gets(s) && strcmp(s,".")) {
      int n = strlen(s), m = n;
      for (int i=2; i<=n; i++) {
         while (n % i == 0) {
            n /= i;

            int j;
            for (j=0; j < m-m/i && s[j] == s[j+m/i]; j++);
            
            if (j == m-m/i) m /= i;
            printf("End of iteration with i = %d: n = %d, m = %d\n", i, n, m);
         }
      }
      printf("%lu\n",strlen(s)/m);
   }
}
