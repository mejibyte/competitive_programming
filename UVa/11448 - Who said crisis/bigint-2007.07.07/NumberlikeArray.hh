/*
* Matt McCutchen's Big Integer Library
*/

/*
* This mechanism prevents files from being included twice.
* Each file gets its own `id' (here `NUMBERLIKEARRAY').
* When `#include'd, this file checks whether its `id' has
* already been flagged.  If not, it flags the `id' and
* loads the declarations.
*/
#ifndef NUMBERLIKEARRAY
#define NUMBERLIKEARRAY

// An essential memory-management constant.
// I wish this were built into C++ just as it is in Java.
#ifndef NULL
#define NULL 0
#endif

/*
* A NumberlikeArray<Blk> object holds a dynamically
* allocated array of Blk.  It provides certain basic
* memory management features needed by both BigUnsigned
* and BigUnsignedInABase, which are both derived from it.
*
* NumberlikeArray provides no information hiding, so make
* sure you know what you are doing if you use it directly.
* Classes derived from it will probably wish to pass on
* some members of NumberlikeArray to their clients while
* keeping some safe for themselves.  These classes should
* use protected inheritance and manually make some members
* public with declarations like this:
*
* public:
*     NumberlikeArray< whatever >::getLength;
*/

template <class Blk>
class NumberlikeArray {
	public:
	
	typedef unsigned int Index; // Type for the index of a block in the array
	static const unsigned int N; // The number of bits in a block, defined below.
	
	// FIELDS
	Index cap; // The current allocated capacity of this NumberlikeArray (in blocks)
	Index len; // The actual length of the value stored in this NumberlikeArray (in blocks)
	Blk *blk; // Dynamically allocated array of the blocks
	
	/*
	* Change made on 2005.01.06:
	*
	* If a zero-length NumberlikeArray is desired, no array is actually allocated.
	* Instead, `blk' is set to `NULL', and `cap' and `len' are zero as usual.
	*
	* `blk' is never dereferenced if the array has zero length.  Furthermore,
	* `delete NULL;' does nothing and causes no error. Therefore, we can use
	* `NULL' as if it were a zero-length array from `new'.
	*
	* This is a great convenience because the only code that need be changed
	* is the array allocation code.  All other code will still work fine.
	*/
	
	// MANAGEMENT
	NumberlikeArray(Index c) : cap(c), len(0) { // Creates a NumberlikeArray with a capacity
		blk = (cap > 0) ? (new Blk[cap]) : NULL;
	}
	void allocate(Index c); // Ensures the array has at least the indicated capacity, maybe discarding contents
	void allocateAndCopy(Index c); // Ensures the array has at least the indicated capacity, preserving its contents
	
	/*
	* Default constructor.
	*
	* If a class derived from NumberlikeArray knows at initializer time what size array
	* it wants, it can call the first constructor listed above in an initializer.
	*
	* Otherwise, this default constructor will be implicitly invoked, pointing `blk' to
	* `NULL', a fake zero-length block array.  The derived class can allocate the desired
	* array itself and overwrite `blk'; it need not `delete [] blk' first.
	*
	* This change fixes a memory leak reported by Milan Tomic on 2005.01.06.
	* Integer-type-to-BigUnsigned (and BigInteger) conversion constructors have always
	* allocated their own array of length 0 or 1 after seeing whether the input is zero.
	* But when the NumberlikeArray transition occurred, these constructors contained an
	* implicit initializer call to the old NumberlikeArray default constructor, which
	* created a real `new'-allocated zero-length array.  This array would then be lost,
	* causing a small but annoying memory leak.
	*/
	NumberlikeArray() : cap(0), len(0) {
		blk = NULL;
	}
	NumberlikeArray(const NumberlikeArray<Blk> &x); // Copy constructor
	void operator=(const NumberlikeArray<Blk> &x); // Assignment operator
	NumberlikeArray(const Blk *b, Index l); // Constructor from an array of blocks
	~NumberlikeArray() { // Destructor
		delete [] blk; // Does nothing and causes no error if `blk' is null.
	}
	
	// PICKING APART
	// These accessors can be used to get the pieces of the value
	Index getCapacity() const { return cap; }
	Index getLength() const { return len; }
	Blk getBlock(Index i) const { return blk[i]; };
	bool isEmpty() const { return len == 0; }
	
	// Equality comparison: checks if arrays have same length and matching values
	// Derived classes may wish to override these if differing arrays can
	// sometimes be considered equivalent.
	bool operator ==(const NumberlikeArray<Blk> &x) const;
	bool operator !=(const NumberlikeArray<Blk> &x) const { return !operator ==(x);	}
	
};

/*
* =================================
* BELOW THIS POINT are template definitions; above are declarations.
*
* Definitions would ordinarily belong in a file NumberlikeArray.cc so that they would
* be compiled once into NumberlikeArray.o and then linked.
*
* However, because of the way templates are usually implemented,
* template ``definitions'' are treated as declarations by the compiler.
* When someone uses an instance of the template, definitions are generated,
* and the linker is smart enough to toss duplicate definitions for the same
* instance generated by different files.
*
* Thus, the template ``definitions'' for NumberlikeArray must appear in this header file
* so other files including NumberlikeArray will be able to generate real definitions.
*/

template <class Blk>
const unsigned int NumberlikeArray<Blk>::N = 8 * sizeof(Blk);

// MANAGEMENT

// This routine is called to ensure the array is at least a
// certain size before another value is written into it.
template <class Blk>
void NumberlikeArray<Blk>::allocate(Index c) {
	// If the requested capacity is more than the current capacity...
	if (c > cap) {
		// Delete the old number array
		delete [] blk;
		// Allocate the new array
		cap = c;
		blk = new Blk[cap];
	}
}

// This routine is called to ensure the array is at least a
// certain size without losing its contents.
template <class Blk>
void NumberlikeArray<Blk>::allocateAndCopy(Index c) {
	// If the requested capacity is more than the current capacity...
	if (c > cap) {
		Blk *oldBlk = blk;
		// Allocate the new number array
		cap = c;
		blk = new Blk[cap];
		// Copy number blocks
		Index i;
		for (i = 0; i < len; i++)
			blk[i] = oldBlk[i];
		// Delete the old array
		delete [] oldBlk;
	}
}

// Copy constructor
template <class Blk>
NumberlikeArray<Blk>::NumberlikeArray(const NumberlikeArray<Blk> &x) : len(x.len) {
	// Create array
	cap = len;
	blk = new Blk[cap];
	// Copy blocks
	Index i;
	for (i = 0; i < len; i++)
		blk[i] = x.blk[i];
}

// Assignment operator
template <class Blk>
void NumberlikeArray<Blk>::operator=(const NumberlikeArray<Blk> &x) {
	// Calls like a = a have no effect
	if (this == &x)
		return;
	// Copy length
	len = x.len;
	// Expand array if necessary
	allocate(len);
	// Copy number blocks
	Index i;
	for (i = 0; i < len; i++)
		blk[i] = x.blk[i];
}

// Constructor from an array of blocks
template <class Blk>
NumberlikeArray<Blk>::NumberlikeArray(const Blk *b, Index l) : cap(l), len(l) {
	// Create array
	blk = new Blk[cap];
	// Copy blocks
	Index i;
	for (i = 0; i < len; i++)
		blk[i] = b[i];
}


// EQUALITY TEST
// This uses == to compare Blks for equality.
// Therefore, Blks must have an == operator with the desired semantics.
template <class Blk>
bool NumberlikeArray<Blk>::operator ==(const NumberlikeArray<Blk> &x) const {
	// Different lengths imply different objects.
	if (len != x.len)
		return false;
	else {
		// Compare matching blocks one by one.
		Index i;
		for (i = 0; i < len; i++)
			if (blk[i] != x.blk[i])
				return false;
		// If no blocks differed, the objects are equal.
		return true;
	}
}

#endif
