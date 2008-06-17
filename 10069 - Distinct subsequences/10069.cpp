#include <iostream>

using namespace std;


const int MAX = 200;

class HugeInt {
public:

        // vars
        char number[MAX];
        int length;

        // constructors
        HugeInt() {
                memset(number,0,sizeof(number));
                length = 1;
        }

        HugeInt(int n) {
                *this = n;
        }

        // operators
        // takes 'r' as right number and writes result to 'this'
        // *veryfied*
        HugeInt* operator= (const HugeInt* r) {
                memset(number,0,sizeof(number));
                strcpy(number,r->number);
                length = r->length;
                return this;
        }

        // *veryfied*
        HugeInt* operator= (const int r) {
                memset(number,0,sizeof(number));
                sprintf(number,"%d",r);
                length = strlen(number);
                for (int i = 0; i < (length >> 1); i++) {
                        char c = number[i];
                        number[i] = number[length-i-1];
                        number[length-i-1] = c;
                }
                for (int j = 0; j < length; j++)
                        number[j] -= '0';
                return this;
        }

        // *veryfied*
        const HugeInt operator+ (const HugeInt& r) {
                int n = max(length,r.length), carry = 0, k, i;
                HugeInt theNew;
                for (i = 0; i < n || carry; i++) {
                        k = number[i] + r.number[i] + carry;
                        theNew.number[i] = k % 10;
                        carry = k / 10;
                }
                theNew.length = i;
                return theNew;
        }

        // slightly veryfied
        void operator+= (const HugeInt& r) {
                *this = *this + r;
        }

        // *slightly veryfied*
        const HugeInt operator* (const int r) {
                int i, k, carry = 0;
                HugeInt theNew;
                for (i = 0; i < length || carry; i++) {
                        k = number[i] * r + carry;
                        theNew.number[i] = k % 10;
                        carry = k / 10;
                }
                theNew.length = i;
                return theNew;
        }

        // *slightly veryfied*
        void operator*= (const int r) {
                *this = *this * r;
                //return this;
        }

        // shifts number left by 'shift' positions
        // useful when multiplying two HugeInt's
        HugeInt operator<< (const int shift) {
                int i;
                HugeInt theNew;
                // don't shift if number is 0 and there is no number
                //if (length == 0 || length == 1 && number[0] == 0) return;
                for (i = length - 1; i >= 0; i--)
                        theNew.number[i + shift] = number[i];
                for (i = 0; i < shift; i++)
                        theNew.number[i] = 0;
                theNew.length = length + shift;
                return theNew;
        }

        HugeInt operator* (HugeInt& r) {
                int i;
                HugeInt theNew = 0;
                for (i = 0; i < length; i++)
                        theNew += (r << i) * number[i];
                truncate(theNew);
                return theNew;
        }

        HugeInt operator*= (HugeInt& r) {
                *this = *this * r;
                return *this;
        }

        int operator % (int r) {
                int n = 0;
                for (int i = length - 1; i >= 0; i--)
                        n = (n * 10 + number[i]) % r;
                return n;
        }

        int operator %= (int r) {
                return (*this % r);
        }

        HugeInt operator/ (int r) {
                HugeInt I = 0;
                int n = 0;
                int j = 0;
                for (int i = length - 1; i >= 0 || n >= r; i--) {
                        n = (n * 10 + number[i]);
                        I.number[j++] = n / r;
                        n %= r;
                }

                // reverse string
                for (int i = 0; i < j / 2; i++)
                        swap(I.number[i],I.number[j-i-1]);
                I.length = j;
                truncate(I);

                return I;
        }

        HugeInt operator /= (int r) {
                return (*this / r);
        }

        // functions
        // *veryfied*
        void print() {
                for (int i = length - 1; i >= 0; i--)
                        putchar(number[i] + '0');
        }

        void truncate(HugeInt& n) {
                for (int i = n.length - 1; i >= 0 && n.number[i] == 0; i--)
                        n.length--;
                if (n.length == 0) {
                        n.number[0] = 0;
                        n.length = 1;
                }
        }

        HugeInt power(int p) {
                HugeInt theNew = 1;
                for (int i = 0; i < p; i++)
                        theNew *= *this;
                return theNew;
        }

        bool operator<(const HugeInt& rhs) {
                if (this->length != rhs.length)
                        return this->length < rhs.length;
                for (int i = 0; i < this->length; i++)
                        if (this->number[i] != rhs.number[i])
                                return this->number[i] < rhs.number[i];
                return false;
        }

        bool isnull() {
                if (length == 1 && number[0] == 0) {
                        return true;
                }
                return false;
        }

};


HugeInt dp[2][10000];
                /*
                  dp[i][j] = cantidad de maneras diferentes
                  en que puedo distribuir las primeras i
                  letras de la subsecuencia (b) terminando
                  en la letra j de la secuencia original (a)
                */

int main(){
  int Casos;
  cin >> Casos;
  string a, b;
  getline(cin, a);
  while (Casos--){
    getline(cin, a);
    getline(cin, b);

    if (b.size() > a.size()){
      cout << "0" << endl;
      continue;
    }

    int A = a.size(), B = b.size();
    dp[0][0] = int(a[0] == b[0]);
    for (int j=1; j<A; ++j){
      dp[0][j] = dp[0][j-1] + int(a[j] == b[0]);
    }

    for (int i=1; i<B; ++i){
      dp[i%2][0] = 0;
      for (int j=1; j<A; ++j){
        dp[i%2][j] = dp[i%2][j-1];
        if (a[j] == b[i]){
          dp[i%2][j] += dp[(i+1)%2][j-1];
        }
      }
    }
    dp[(B-1)%2][A-1].print();
    putchar('\n');

  }
  return 0;
}
