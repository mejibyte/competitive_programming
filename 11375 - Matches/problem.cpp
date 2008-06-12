#pragma warning (disable:4786) 
#pragma warning (disable:4996) 
#include <time.h>
#include <algorithm> 
#include <iostream>  
#include <sstream> 
#include <string> 
#include <vector> 
#include <queue> 
#include <stack>
#include <set> 
#include <map> 
#include <cstdio> 
#include <cstdlib> 
#include <cctype> 
#include <cmath> 
#include <cassert>
using namespace std;

#define REP(i,n) for(i=1; i<=(n); i++)
#define REPO(i,n) for(int i=0; i<(n); i++) 
#define REPA(i,a,b) for(i=a; i<=(b); i++)
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define init(a) (memset(a,0,sizeof(a)))

void open() {
	#ifndef ONLINE_JUDGE
		freopen("test.in","rt",stdin);
		freopen("test.out","wt",stdout);   
	#endif
}

const int MAX = 1000;

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

int M[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
HugeInt DP[2001][2];
HugeInt A[2001];

void precalc() {
	DP[0][1] = 1;
	for (int i = 1; i <= 2000; i++) {
		DP[i][0] = 0;
		DP[i][1] = 0;
		if (i - M[0] >= 0) {
			if (!DP[i - M[0]][0].isnull())
				DP[i][0] += DP[i - M[0]][0];
			if (!DP[i - M[0]][1].isnull())
				DP[i][0] += DP[i - M[0]][1];
		}
		for (int j = 1; j < 10; j++) if (i - M[j] >= 0) {
			if (!DP[i - M[j]][0].isnull())
				DP[i][1] += DP[i - M[j]][0];
			if (!DP[i - M[j]][1].isnull())
				DP[i][1] += DP[i - M[j]][1];
		}
		//cout << i << ' ';
		//DP[i][0].print();
		//cout << ' ';
		//DP[i][1].print();
		//cout << endl;
	}
}

void go() {
	A[0] = 0;
	for (int i = 1; i <= 2000; i++) {
		A[i] = A[i - 1] + DP[i][1];
		//cout << A[i].length << endl;
	}
}

bool solve() {
	int n;
	if (scanf("%d",&n) != 1)
		return false;
	if (n == 6){
		printf("6\n");
		return true;
	}
	HugeInt ans = A[n];
	HugeInt add = 1;
	if (n >= 6)
		A[n] = A[n] + add;
	A[n].print();
	printf("\n");
	return true;
}

int main() {
	open();
	precalc();
	go();
	while (solve());

	return 0;
}
