/*
* Matt McCutchen's Big Integer Library
*/

#ifndef BIGUNSIGNEDINABASE
#define BIGUNSIGNEDINABASE

#include "NumberlikeArray.hh"
#include "BigUnsigned.hh"
#include <string>

/*
* A BigUnsignedInABase object represents a nonnegative
* integer of size limited only by available memory,
* represented in a user-specified base that can fit in
* an `unsigned short' (most can, and this saves memory).
*
* BigUnsignedInABase is intended as an intermediary class
* with little functionality of its own.  BigUnsignedInABase
* objects can be constructed from, and converted to,
* BigUnsigneds (requiring multiplication, mods, etc.) and
* `std::string's (by switching digit values for appropriate
* characters).
*
* BigUnsignedInABase is similar to BigUnsigned.  Note the following:
*
* (1) They represent the number in exactly the same way, except
* that BigUnsignedInABase uses ``digits'' (or Digit) where BigUnsigned uses
* ``blocks'' (or Blk).
*
* (2) Both use the management features of NumberlikeArray.  (In fact,
* my desire to add a BigUnsignedInABase class without duplicating a
* lot of code led me to introduce NumberlikeArray.)
*
* (3) The only arithmetic operation supported by BigUnsignedInABase
* is an equality test.  Use BigUnsigned for arithmetic.
*/

class BigUnsignedInABase : protected NumberlikeArray<unsigned short> {
	
	// TYPES
	public:
	typedef unsigned short Digit; // The digit type that BigUnsignedInABases are built from
	typedef Digit Base;
	
	// FIELDS
	protected:
	Base base; // The base of this BigUnsignedInABase
	
	// MANAGEMENT
	protected:
	// These members generally defer to those in NumberlikeArray, possibly with slight changes.
	// It might be nice if one could request that constructors be inherited in C++.
	
	BigUnsignedInABase(int, Index c) : NumberlikeArray<Digit>(0, c) {} // Creates a BigUnsignedInABase with a capacity
	
	void zapLeadingZeros() { // Decreases len to eliminate leading zeros
		while (len > 0 && blk[len - 1] == 0)
			len--;
	}
	
	//void allocate(Index c); // (NlA) Ensures the number array has at least the indicated capacity, maybe discarding contents
	//void allocateAndCopy(Index c); // (NlA) Ensures the number array has at least the indicated capacity, preserving its contents
	
	public:
	BigUnsignedInABase() : NumberlikeArray<Digit>(), base(2) {} // Default constructor (value is 0 in base 2)
	BigUnsignedInABase(const BigUnsignedInABase &x) : NumberlikeArray<Digit>(x), base(x.base) {} // Copy constructor
	
	void operator =(const BigUnsignedInABase &x) { // Assignment operator
		NumberlikeArray<Digit>::operator =(x);
		base = x.base;
	}
	
	BigUnsignedInABase(const Digit *d, Index l) : NumberlikeArray<Digit>(d, l) { // Constructor from an array of digits
		zapLeadingZeros();
	}
	
	// LINKS TO BIGUNSIGNED
	BigUnsignedInABase(const BigUnsigned &x, Base base);
	operator BigUnsigned() const;
	
	/* LINKS TO STRINGS
	*
	* These use the symbols ``0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'' to represent
	* digits of 0 through 35.  When parsing strings, lowercase is also accepted.
	*
	* All string representations are big-endian (big-place-value digits first).
	* (Computer scientists have adopted zero-based counting; why can't they
	* tolerate little-endian numbers?  It makes a lot of sense!)
	*
	* No string representation has a ``base indicator'' like ``0x''.
	*
	* An exception is made for zero: it is converted to ``0'' and not the empty string.
	*
	* If you want different conventions, write your
	* own routines to go between BigUnsignedInABase and strings.  It's not hard.
	*/
	operator std::string() const;
	BigUnsignedInABase(const std::string &s, Base base);
	
	// PICKING APART
	// These accessors can be used to get the pieces of the number
	public:
	Base getBase() const { return base; }
	NumberlikeArray<Digit>::getCapacity; // (NlA)
	NumberlikeArray<Digit>::getLength; // (NlA)
	// Note that getDigit returns 0 if the digit index is beyond the length of the number.
	// A routine that uses this accessor can safely assume a BigUnsigned has 0s infinitely to the left.
	Digit getDigit(Index i) const { return i >= len ? 0 : blk[i]; }
	// Note how we replace one level of abstraction with another.
	bool isZero() const { return NumberlikeArray<Digit>::isEmpty(); } // Often convenient for loops
	
	// EQUALITY TEST
	public:
	// Equality test
	bool operator ==(const BigUnsignedInABase &x) const {
		return base == x.base && NumberlikeArray<Digit>::operator ==(x);
	}
	bool operator !=(const BigUnsignedInABase &x) const { return !operator ==(x); }
	
};

#endif
