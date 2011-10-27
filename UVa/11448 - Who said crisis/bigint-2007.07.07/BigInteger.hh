/*
* Matt McCutchen's Big Integer Library
*/

#ifndef BIGINTEGER
#define BIGINTEGER

#include "BigUnsigned.hh"

/*
* A BigInteger object represents a signed integer of size
* limited only by available memory.  A BigInteger can be
* created from and converted back to most integral types,
* and many math operations are defined on BigIntegers.
*
* The number is stored as a series of blocks in a
* dynamically allocated array.  It is as if the number
* were written digit by digit in base 2 ^ N, **where N is the
* number of bits in an unsigned long.**
*
* This class is derived from BigUnsigned, which represents
* a large nonnegative integer.  BigUnsigned should be studied
* first, as only new or different things are declared here.
* Some things are redeclared so that they use the BigInteger
* versions of methods, rather than the BigUnsigned versions.
*/

class BigInteger : public BigUnsigned {
	
	// TYPES & CONSTANTS
	public:
	enum Sign { negative = -1, zero = 0, positive = 1 }; // Enumeration for the sign of a BigInteger
	
	// FIELDS
	protected:
	Sign sign; // The sign of this BigInteger
	
	// MANAGEMENT
	protected:
	BigInteger(Sign s, Index c) : BigUnsigned(0, c), sign(s) {}; // Creates a BigInteger with a sign and capacity
	public:

	BigInteger() : BigUnsigned(), sign(zero) {} // Default constructor (value is 0)
	BigInteger(const BigInteger &x) : BigUnsigned(x), sign(x.sign) {}; // Copy constructor
	void operator=(const BigInteger &x); // Assignment operator
	BigInteger(const Blk *b, Index l) : BigUnsigned(b, l) { // Constructor from an array of blocks
		sign = (len == 0) ? zero : positive;
	}
	BigInteger(const Blk *b, Index l, Sign s); // Constructor from an array of blocks and a sign
	BigInteger(const BigUnsigned &x) : BigUnsigned(x) { // Constructor from a BigUnsigned
		sign = (len == 0) ? zero : positive;
	}
	BigInteger(const BigUnsigned &x, Sign s); // Constructor from a BigUnsigned and a sign
	// Constructors from integral types
	BigInteger(unsigned long  x);
	BigInteger(         long  x);
	BigInteger(unsigned int   x);
	BigInteger(         int   x);
	BigInteger(unsigned short x);
	BigInteger(         short x);
	// Note that a BigInteger can be converted to a BigUnsigned
	// automatically; this takes its absolute value.
	
	// CONVERTERS to integral types
	public:
	operator unsigned long () const;
	operator          long () const;
	operator unsigned int  () const;
	operator          int  () const;
	operator unsigned short() const;
	operator          short() const;
	
	// PICKING APART
	// These accessors can be used to get the pieces of the number
	public:
	Sign getSign() const;
	
	// COMPARISONS
	public:
	// Compares this to x like Perl's <=>
	CmpRes compareTo(const BigInteger &x) const;
	// Normal comparison operators
	bool operator ==(const BigInteger &x) const {
		return sign == x.sign && BigUnsigned::operator ==(x);
	}
	bool operator !=(const BigInteger &x) const { return !operator ==(x); };
	bool operator < (const BigInteger &x) const { return compareTo(x) == less   ; }
	bool operator <=(const BigInteger &x) const { return compareTo(x) != greater; }
	bool operator >=(const BigInteger &x) const { return compareTo(x) != less   ; }
	bool operator > (const BigInteger &x) const { return compareTo(x) == greater; }
	
	// PUT-HERE OPERATIONS
	/* These store the result of the operation on the arguments into this.
	* a.add(b, c) is equivalent to, but faster than, a = b + c.
	* See explanation of "put-here operations" in BigUnsigned.cc . */
	public:
	void add     (const BigInteger &a, const BigInteger &b); // Addition
	void subtract(const BigInteger &a, const BigInteger &b); // Subtraction
	void multiply(const BigInteger &a, const BigInteger &b); // Multiplication
	/* Divisive stuff
	* `a.divideWithRemainder(b, q)' is like `q = a / b, a %= b'.
	* Semantics similar to Donald E. Knuth's are used for / and %,
	* and these usually differ from the semantics of primitive-type
	* / and % when negatives and/or zeroes are involved.
	* Look in `BigInteger.cc' for details.
	* `a.divideWithRemainder(b, a)' causes an exception: it doesn't make
	* sense to write quotient and remainder into the same variable.
	*/
	void divideWithRemainder(const BigInteger &b, BigInteger &q);
	void divide(const BigInteger &a, const BigInteger &b) {
		BigInteger a2(a);
		a2.divideWithRemainder(b, *this);
		// quotient now in *this
		// don't care about remainder left in a2
	}
	void modulo(const BigInteger &a, const BigInteger &b) {
		*this = a;
		BigInteger q;
		divideWithRemainder(b, q);
		// remainder now in *this
		// don't care about quotient left in q
	}
	void negate(const BigInteger &a); // Negative
	// Some operations are inherently unsigned and are not
	// redefined for BigIntegers.  Calling one of these on
	// a BigInteger will convert it to a BigUnsigned,
	// which takes its absolute value.
	
	// NORMAL OPERATORS
	// These perform the operation on this (to the left of the operator)
	// and x (to the right of the operator) and return a new BigInteger with the result.
	public:
	BigInteger operator +(const BigInteger &x) const; // Addition
	BigInteger operator -(const BigInteger &x) const; // Subtraction
	BigInteger operator *(const BigInteger &x) const; // Multiplication
	BigInteger operator /(const BigInteger &x) const; // Division
	BigInteger operator %(const BigInteger &x) const; // Modular reduction
	BigInteger operator -(                   ) const; // Negative
	
	// ASSIGNMENT OPERATORS
	// These perform the operation on this and x, storing the result into this.
	public:
	void operator +=(const BigInteger &x); // Addition
	void operator -=(const BigInteger &x); // Subtraction
	void operator *=(const BigInteger &x); // Multiplication
	void operator /=(const BigInteger &x); // Division
	void operator %=(const BigInteger &x); // Modular reduction
	void flipSign();                       // Negative
	
	// INCREMENT/DECREMENT OPERATORS
	// These increase or decrease the number by 1.  To discourage side effects,
	// these do not return *this, so prefix and postfix behave the same.
	public:
	void operator ++(   ); // Prefix  increment
	void operator ++(int); // Postfix decrement
	void operator --(   ); // Prefix  increment
	void operator --(int); // Postfix decrement
	
};

// PICKING APART
inline BigInteger::Sign BigInteger::getSign() const { return sign; }

// NORMAL OPERATORS
/* These create an object to hold the result and invoke
* the appropriate put-here operation on it, passing
* this and x.  The new object is then returned. */
inline BigInteger BigInteger::operator +(const BigInteger &x) const {
	BigInteger ans;
	ans.add(*this, x);
	return ans;
}
inline BigInteger BigInteger::operator -(const BigInteger &x) const {
	BigInteger ans;
	ans.subtract(*this, x);
	return ans;
}
inline BigInteger BigInteger::operator *(const BigInteger &x) const {
	BigInteger ans;
	ans.multiply(*this, x);
	return ans;
}
inline BigInteger BigInteger::operator /(const BigInteger &x) const {
	BigInteger ans;
	ans.divide(*this, x);
	return ans;
}
inline BigInteger BigInteger::operator %(const BigInteger &x) const {
	BigInteger ans;
	ans.modulo(*this, x);
	return ans;
}
inline BigInteger BigInteger::operator -() const {
	BigInteger ans;
	ans.negate(*this);
	return ans;
}

/*
 * ASSIGNMENT OPERATORS
 * 
 * Now the responsibility for making a temporary copy if necessary
 * belongs to the put-here operations.  See Assignment Operators in
 * BigUnsigned.hh.
 */
inline void BigInteger::operator +=(const BigInteger &x) {
	add(*this, x);
}
inline void BigInteger::operator -=(const BigInteger &x) {
	subtract(*this, x);
}
inline void BigInteger::operator *=(const BigInteger &x) {
	multiply(*this, x);
}
inline void BigInteger::operator /=(const BigInteger &x) {
	// Updated for divideWithRemainder
	BigInteger thisCopy(*this);
	thisCopy.divideWithRemainder(x, *this);
	// quotient left in *this
	// don't care about remainder left in thisCopy
}
inline void BigInteger::operator %=(const BigInteger &x) {
	// Shortcut (woohoo!)
	BigInteger q;
	divideWithRemainder(x, q);
	// remainder left in *this
	// don't care about quotient left in q
}
// This one is trivial
inline void BigInteger::flipSign() {
	sign = Sign(-sign);
}

#endif
