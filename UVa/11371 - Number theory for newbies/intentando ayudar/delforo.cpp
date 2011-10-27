# include <iostream>
# include <algorithm>
# include <stdlib.h>
# include <string>
using namespace std;


long long int GetIntVal(string strConvert)
{
  long long int intReturn;

  intReturn = atoi(strConvert.c_str());

  return(intReturn);
}



int main()
{
   char num[11];
   while(gets(num))
   {
      int size = strlen(num);
      long long int ReversedNumber,Number,diff,divisor;
      Number = GetIntVal(num);
      sort(num,num+size);
      reverse(num,num+size);
      ReversedNumber = GetIntVal(num);
      diff = ReversedNumber - Number;
      divisor = diff / 9;
      cout<<ReversedNumber<<" - "<<Number<<" = "<<diff<<" = 9 * "<<divisor<<endl;

   }
   return 0;
}
