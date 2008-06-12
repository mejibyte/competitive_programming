/*
* Matt McCutchen's Big Integer Library
*/

#include "BigInteger.hh"

// MANAGEMENT

// Assignment operator
void BigInteger::operator =(const BigInteger &x) {
	// Calls like a = a have no effect
	if (this == &x)
		return;
	// Copy sign
	sign = x.sign;
	// Copy the rest
	BigUnsigned::operator =(x);
}

// Constructor from an array of blocks and a sign
BigInteger::BigInteger(const Blk *b, Index l, Sign s) : BigUnsigned(b, l) {
	switch (s) {
		case zero:
		case positive:
		case negative:
		sign = (len == 0) ? zero : s;
		break;
		default:
		throw "BigInteger::BigInteger(Blk *, Index, Sign): Invalid sign";
	}
}

// Constructor from a BigUnsigned and a sign
BigInteger::BigInteger(const BigUnsigned &x, Sign s) : BigUnsigned(x) {
	switch (s) {
		case zero:
		case positive:
		case negative:
		sign = (len == 0) ? zero : s;
		break;
		default:
		throw "BigInteger::BigInteger(Blk *, Index, Sign): Invalid sign";
	}
}

/*
* The steps for construction of a BigInteger
* from an integral value x are as follows:
* 1. If x is zero, create an empty BigInteger and stop.
* 2. Allocate a one-block number array.
* 3. If x is positive (or of an unsigned type), set the
*    sign of the BigInteger to positive.
* 4. If x is of a signed type and is negative, set the
*    sign of the BigInteger to negative.
* 5. If x is of a signed type, convert x (or -x if x < 0)
*    to the unsigned type of the same length.
* 6. Expand x (or the result of step 5) to a Blk,
*    and store it in the number array.
*
* See remarks in `BigUnsigned.cc' and `NumberlikeArray.hh'
* about new handling of zero-length arrays.
*/

BigInteger::BigInteger(unsigned long x) {
	if (x == 0)
		sign = zero; // NumberlikeArray did the rest
	else {
		cap = 1;
		blk = new Blk[1];
		sign = positive;
		len = 1;
		blk[0] = Blk(x);
	}
}

BigInteger::BigInteger(long x) {
	if (x > 0) {
		cap = 1;
		blk = new Blk[1];
		sign = positive;
		len = 1;
		blk[0] = Blk(x);
	} else if (x < 0) {
		cap = 1;
		blk = new Blk[1];
		sign = negative;
		len = 1;
		blk[0] = Blk(-x);
	} else
	sign = zero;
}

BigInteger::BigInteger(unsigned int x) {
	if (x == 0)
		sign = zero;
	else {
		cap = 1;
		blk = new Blk[1];
		sign = positive;
		len = 1;
		blk[0] = Blk(x);
	}
}

BigInteger::BigInteger(int x) {
	if (x > 0) {
		cap = 1;
		blk = new Blk[1];
		sign = positive;
		len = 1;
		blk[0] = Blk(x);
	} else if (x < 0) {
		cap = 1;
		blk = new Blk[1];
		sign = negative;
		len = 1;
		blk[0] = Blk(-x);
	} else
	sign = zero;
}

BigInteger::BigInteger(unsigned short x) {
	if (x == 0)
		sign = zero;
	else {
		cap = 1;
		blk = new Blk[1];
		sign = positive;
		len = 1;
		blk[0] = Blk(x);
	}
}

BigInteger::BigInteger(short x) {
	if (x > 0) {
		cap = 1;
		blk = new Blk[1];
		sign = positive;
		len = 1;
		blk[0] = Blk(x);
	} else if (x < 0) {
		cap = 1;
		blk = new Blk[1];
		sign = negative;
		len = 1;
		blk[0] = Blk(-x);
	} else
	sign = zero;
}

// CONVERTERS
/*
* The steps for conversion of a BigInteger to an
* integral type are as follows:
* 1. If the BigInteger is zero, return zero.
* 2. If the BigInteger is positive:
*    3. If it is more than one block long or its lowest
*       block has bits set out of the range of the target
*       type, throw an exception.
*    4. Otherwise, convert the lowest block to the
*       target type and return it.
* 5. If the BigInteger is negative:
*    6. If the target type is unsigned, throw an exception.
*    7. If it is more than one block long or its lowest
*       block has bits set out of the range of the target
*       type, throw an exception.
*    8. Otherwise, convert the lowest block to the
*       target type, negate it, and return it.
*/

namespace {
	// These masks are used to test whether a Blk has bits
	// set out of the range of a smaller integral type.  Note
	// that this range is not considered to include the sign bit.
	const BigUnsigned::Blk  lMask = ~0 >> 1;
	const BigUnsigned::Blk uiMask = (unsigned int)(~0);
	const BigUnsigned::Blk  iMask = uiMask >> 1;
	const BigUnsigned::Blk usMask = (unsigned short)(~0);
	const BigUnsigned::Blk  sMask = usMask >> 1;
}

BigInteger::operator unsigned long() const {
	switch (sign) {
		case zero:
		return 0;
		case positive:
		if (len == 1)
			return blk[0];
		else
			throw "BigInteger operator unsigned long() const: Value is too big for an unsigned long";
		case negative:
		throw "BigInteger operator unsigned long() const: Cannot convert a negative integer to an unsigned type";
		default:
		throw "BigInteger: Internal error";
	}
}

BigInteger::operator long() const {
	switch (sign) {
		case zero:
		return 0;
		case positive:
		if (len == 1 && (blk[0] & ~lMask) == 0)
			return long(blk[0]);
		else
			throw "BigInteger operator long() const: Value is too big for a long";
		case negative:
		if (len == 1 && (blk[0] & ~lMask) == 0)
			return -long(blk[0]);
		else
			throw "BigInteger operator long() const: Value is too big for a long";
		default:
		throw "BigInteger: Internal error";
	}
}

BigInteger::operator unsigned int() const {
	switch (sign) {
		case zero:
		return 0;
		case positive:
		if (len == 1 && (blk[0] & ~uiMask) == 0)
			return (unsigned int)(blk[0]);
		else
			throw "BigInteger operator unsigned int() const: Value is too big for an unsigned int";
		case negative:
		throw "BigInteger operator unsigned int() const: Cannot convert a negative integer to an unsigned type";
		default:
		throw "BigInteger: Internal error";
	}
}

BigInteger::operator int() const {
	switch (sign) {
		case zero:
		return 0;
		case positive:
		if (len == 1 && (blk[0] & ~iMask) == 0)
			return int(blk[0]);
		else
			throw "BigInteger operator int() const: Value is too big for an int";
		case negative:
		if (len == 1 && (blk[0] & ~iMask) == 0)
			return -int(blk[0]);
		else
			throw "BigInteger operator int() const: Value is too big for an int";
		default:
		throw "BigInteger: Internal error";
	}
}

BigInteger::operator unsigned short() const {
	switch (sign) {
		case zero:
		return 0;
		case positive:
		if (len == 1 && (blk[0] & ~usMask) == 0)
			return (unsigned short)(blk[0]);
		else
			throw "BigInteger operator unsigned short() const: Value is too big for an unsigned short";
		case negative:
		throw "BigInteger operator unsigned short() const: Cannot convert a negative integer to an unsigned type";
		default:
		throw "BigInteger: Internal error";
	}
}

BigInteger::operator short() const {
	switch (sign) {
		case zero:
		return 0;
		case positive:
		if (len == 1 && (blk[0] & ~sMask) == 0)
			return short(blk[0]);
		else
			throw "BigInteger operator short() const: Value is too big for a short";
		case negative:
		if (len == 1 && (blk[0] & ~sMask) == 0)
			return -short(blk[0]);
		else
			throw "BigInteger operator short() const: Value is too big for a short";
		default:
		throw "BigInteger: Internal error";
	}
}

// COMPARISON
BigInteger::CmpRes BigInteger::compareTo(const BigInteger &x) const {
	// A greater sign implies a greater number
	if (sign < x.sign)
		return less;
	else if (sign > x.sign)
		return greater;
	else switch (sign) {
		// If the signs are the same...
		case zero:
		return equal; // Two zeros are equal
		case positive:
		// Compare the magnitudes
		return BigUnsigned::compareTo(x);
		case negative:
		// Compare the magnitudes, but return the opposite result
		return CmpRes(-BigUnsigned::compareTo(x));
		default:
		throw "BigInteger: Internal error";
	}
}

// PUT-HERE OPERATIONS
// These do some messing around to determine the sign of the result,
// then call one of BigUnsigned's put-heres.

// See remarks about aliased calls in BigUnsigned.cc .
#define DOTR_ALIASED(cond, op) \
	if (cond) { \
		BigInteger tmpThis; \
		tmpThis.op; \
		*this = tmpThis; \
		return; \
	}

// Addition
void BigInteger::add(const BigInteger &a, const BigInteger &b) {
	DOTR_ALIASED(this == &a || this == &b, add(a, b));
	// If one argument is zero, copy the other.
	if (a.sign == zero)
		operator =(b);
	else if (b.sign == zero)
		operator =(a);
	// If the arguments have the same sign, take the
	// common sign and add their magnitudes.
	else if (a.sign == b.sign) {
		sign = a.sign;
		BigUnsigned::add(a, b);
	} else {
		// Otherwise, their magnitudes must be compared.
		switch (a.BigUnsigned::compareTo(b)) {
			// If their magnitudes are the same, copy zero.
			case equal:
			len = 0;
			sign = zero;
			break;
			// Otherwise, take the sign of the greater, and subtract
			// the lesser magnitude from the greater magnitude.
			case greater:
			sign = a.sign;
			BigUnsigned::subtract(a, b);
			break;
			case less:
			sign = b.sign;
			BigUnsigned::subtract(b, a);
			break;
		}
	}
}

// Subtraction
void BigInteger::subtract(const BigInteger &a, const BigInteger &b) {
	// Notice that this routine is identical to BigInteger::add,
	// if one replaces b.sign by its opposite.
	DOTR_ALIASED(this == &a || this == &b, subtract(a, b));
	// If a is zero, copy b and flip its sign.  If b is zero, copy a.
	if (a.sign == zero) {
		BigUnsigned::operator =(b);
		// Take the negative of _b_'s, sign, not ours.
		// Bug pointed out by Sam Larkin on 2005.03.30.
		sign = Sign(-b.sign);
	} else if (b.sign == zero)
		operator =(a);
	// If their signs differ, take a.sign and add the magnitudes.
	else if (a.sign != b.sign) {
		sign = a.sign;
		BigUnsigned::add(a, b);
	} else {
		// Otherwise, their magnitudes must be compared.
		switch (a.BigUnsigned::compareTo(b)) {
			// If their magnitudes are the same, copy zero.
			case equal:
			len = 0;
			sign = zero;
			break;
			// If a's magnitude is greater, take a.sign and
			// subtract a from b.
			case greater:
			sign = a.sign;
			BigUnsigned::subtract(a, b);
			break;
			// If b's magnitude is greater, take the opposite
			// of b.sign and subtract b from a.
			case less:
			sign = Sign(-b.sign);
			BigUnsigned::subtract(b, a);
			break;
		}
	}
}

// Multiplication
void BigInteger::multiply(const BigInteger &a, const BigInteger &b) {
	DOTR_ALIASED(this == &a || this == &b, multiply(a, b));
	// If one object is zero, copy zero and return.
	if (a.sign == zero || b.sign == zero) {
		sign = zero;
		len = 0;
		return;
	}
	// If the signs of the arguments are the same, the result
	// is positive, otherwise it is negative.
	sign = (a.sign == b.sign) ? positive : negative;
	// Multiply the magnitudes.
	BigUnsigned::multiply(a, b);
}

/*
* DIVISION WITH REMAINDER
* Please read the comments before the definition of
* `BigUnsigned::divideWithRemainder' in `BigUnsigned.cc' for lots of
* information you should know before reading this function.
*
* Following Knuth, I decree that x / y is to be
* 0 if y==0 and floor(real-number x / y) if y!=0.
* Then x % y shall be x - y*(integer x / y).
*
* Note that x = y * (x / y) + (x % y) always holds.
* In addition, (x % y) is from 0 to y - 1 if y > 0,
* and from -(|y| - 1) to 0 if y < 0.  (x % y) = x if y = 0.
*
* Examples: (q = a / b, r = a % b)
*	a	b	q	r
*	===	===	===	===
*	4	3	1	1
*	-4	3	-2	2
*	4	-3	-2	-2
*	-4	-3	1	-1
*/
void BigInteger::divideWithRemainder(const BigInteger &b, BigInteger &q) {
	// Defend against aliased calls;
	// same idea as in BigUnsigned::divideWithRemainder .
	if (this == &q)
		throw "BigInteger::divideWithRemainder: Cannot write quotient and remainder into the same variable";
	if (this == &b || &q == &b) {
		BigInteger tmpB(b);
		divideWithRemainder(tmpB, q);
		return;
	}
	
	// Division by zero gives quotient 0 and remainder *this
	if (b.sign == zero) {
		q.len = 0;
		q.sign = zero;
		return;
	}
	// 0 / b gives quotient 0 and remainder 0
	if (sign == zero) {
		q.len = 0;
		q.sign = zero;
		return;
	}
	
	// Here *this != 0, b != 0.
	
	// Do the operands have the same sign?
	if (sign == b.sign) {
		// Yes: easy case.  Quotient is zero or positive.
		q.sign = positive;
	} else {
		// No: harder case.  Quotient is negative.
		q.sign = negative;
		// Decrease the magnitude of the dividend by one.
		BigUnsigned::operator --();
		/*
		* We tinker with the dividend before and with the
		* quotient and remainder after so that the result
		* comes out right.  To see why it works, consider the following
		* list of examples, where A is the magnitude-decreased
		* a, Q and R are the results of BigUnsigned division
		* with remainder on A and |b|, and q and r are the
		* final results we want:
		*
		*	a	A	b	Q	R	q	r
		*	-3	-2	3	0	2	-1	0
		*	-4	-3	3	1	0	-2	2
		*	-5	-4	3	1	1	-2	1
		*	-6	-5	3	1	2	-2	0
		*
		* It appears that we need a total of 3 corrections:
		* Decrease the magnitude of a to get A.  Increase the
		* magnitude of Q to get q (and make it negative).
		* Find r = (b - 1) - R and give it the desired sign.
		*/
	}
	
	// Divide the magnitudes.
	BigUnsigned::divideWithRemainder(b, q);
	
	if (sign != b.sign) {
		// More for the harder case (as described):
		// Increase the magnitude of the quotient by one.
		q.BigUnsigned::operator ++();
		// Modify the remainder.
		BigUnsigned temp(*this);
		BigUnsigned::subtract(b, temp);
		BigUnsigned::operator --();
	}
	
	// Sign of the remainder is always the sign of the divisor b.
	sign = b.sign;
	
	// Set signs to zero as necessary.  (Thanks David Allen!)
	if (len == 0)
		sign = zero;
	if (q.len == 0)
		q.sign = zero;
	
	// WHEW!!!
}

// Negation
void BigInteger::negate(const BigInteger &a) {
	DOTR_ALIASED(this == &a, negate(a));
	// Copy a's magnitude
	BigUnsigned::operator =(a);
	// Copy the opposite of a.sign
	sign = Sign(-a.sign);
}

// INCREMENT/DECREMENT OPERATORS

// Prefix increment
void BigInteger::operator ++() {
	switch (sign) {
		case zero:
		allocate(1);
		sign = positive;
		len = 1;
		blk[0] = 1;
		break;
		case positive:
		BigUnsigned::operator ++();
		break;
		case negative:
		BigUnsigned::operator --();
		if (len == 0)
			sign = zero;
		break;
	}
}

// Postfix increment: same as prefix
void BigInteger::operator ++(int) {
	operator ++();
}

// Prefix decrement
void BigInteger::operator --() {
	switch (sign) {
		case zero:
		allocate(1);
		sign = negative;
		len = 1;
		blk[0] = 1;
		break;
		case negative:
		BigUnsigned::operator ++();
		break;
		case positive:
		BigUnsigned::operator --();
		if (len == 0)
			sign = zero;
		break;
	}
}

// Postfix decrement: same as prefix
void BigInteger::operator --(int) {
	operator --();
}

