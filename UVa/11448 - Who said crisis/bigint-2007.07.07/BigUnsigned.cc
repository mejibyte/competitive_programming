/*
* Matt McCutchen's Big Integer Library
*/

#include "BigUnsigned.hh"

// The "management" routines that used to be here are now in NumberlikeArray.hh.

/*
* The steps for construction of a BigUnsigned
* from an integral value x are as follows:
* 1. If x is zero, create an empty BigUnsigned and stop.
* 2. If x is negative, throw an exception.
* 3. Allocate a one-block number array.
* 4. If x is of a signed type, convert x to the unsigned
*    type of the same length.
* 5. Expand x to a Blk, and store it in the number array.
*
* Since 2005.01.06, NumberlikeArray uses `NULL' rather
* than a real array if one of zero length is needed.
* These constructors implicitly call NumberlikeArray's
* default constructor, which sets `blk = NULL, cap = len = 0'.
* So if the input number is zero, they can just return.
* See remarks in `NumberlikeArray.hh'.
*/

BigUnsigned::BigUnsigned(unsigned long x) {
	if (x == 0)
		; // NumberlikeArray already did all the work
	else {
		cap = 1;
		blk = new Blk[1];
		len = 1;
		blk[0] = Blk(x);
	}
}

BigUnsigned::BigUnsigned(long x) {
	if (x == 0)
		;
	else if (x > 0) {
		cap = 1;
		blk = new Blk[1];
		len = 1;
		blk[0] = Blk(x);
	} else
	throw "BigUnsigned::BigUnsigned(long): Cannot construct a BigUnsigned from a negative number";
}

BigUnsigned::BigUnsigned(unsigned int x) {
	if (x == 0)
		;
	else {
		cap = 1;
		blk = new Blk[1];
		len = 1;
		blk[0] = Blk(x);
	}
}

BigUnsigned::BigUnsigned(int x) {
	if (x == 0)
		;
	else if (x > 0) {
		cap = 1;
		blk = new Blk[1];
		len = 1;
		blk[0] = Blk(x);
	} else
	throw "BigUnsigned::BigUnsigned(int): Cannot construct a BigUnsigned from a negative number";
}

BigUnsigned::BigUnsigned(unsigned short x) {
	if (x == 0)
		;
	else {
		cap = 1;
		blk = new Blk[1];
		len = 1;
		blk[0] = Blk(x);
	}
}

BigUnsigned::BigUnsigned(short x) {
	if (x == 0)
		;
	else if (x > 0) {
		cap = 1;
		blk = new Blk[1];
		len = 1;
		blk[0] = Blk(x);
	} else
	throw "BigUnsigned::BigUnsigned(short): Cannot construct a BigUnsigned from a negative number";
}

// CONVERTERS
/*
* The steps for conversion of a BigUnsigned to an
* integral type are as follows:
* 1. If the BigUnsigned is zero, return zero.
* 2. If it is more than one block long or its lowest
*    block has bits set out of the range of the target
*    type, throw an exception.
* 3. Otherwise, convert the lowest block to the
*    target type and return it.
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

BigUnsigned::operator unsigned long() const {
	if (len == 0)
		return 0;
	else if (len == 1)
		return (unsigned long) blk[0];
	else
		throw "BigUnsigned::operator unsigned long: Value is too big for an unsigned long";
}

BigUnsigned::operator long() const {
	if (len == 0)
		return 0;
	else if (len == 1 && (blk[0] & lMask) == blk[0])
		return (long) blk[0];
	else
		throw "BigUnsigned::operator long: Value is too big for a long";
}

BigUnsigned::operator unsigned int() const {
	if (len == 0)
		return 0;
	else if (len == 1 && (blk[0] & uiMask) == blk[0])
		return (unsigned int) blk[0];
	else
		throw "BigUnsigned::operator unsigned int: Value is too big for an unsigned int";
}

BigUnsigned::operator int() const {
	if (len == 0)
		return 0;
	else if (len == 1 && (blk[0] & iMask) == blk[0])
		return (int) blk[0];
	else
		throw "BigUnsigned::operator int: Value is too big for an int";
}

BigUnsigned::operator unsigned short() const {
	if (len == 0)
		return 0;
	else if (len == 1 && (blk[0] & usMask) == blk[0])
		return (unsigned short) blk[0];
	else
		throw "BigUnsigned::operator unsigned short: Value is too big for an unsigned short";
}

BigUnsigned::operator short() const {
	if (len == 0)
		return 0;
	else if (len == 1 && (blk[0] & sMask) == blk[0])
		return (short) blk[0];
	else
		throw "BigUnsigned::operator short: Value is too big for a short";
}

// COMPARISON
BigUnsigned::CmpRes BigUnsigned::compareTo(const BigUnsigned &x) const {
	// A bigger length implies a bigger number.
	if (len < x.len)
		return less;
	else if (len > x.len)
		return greater;
	else {
		// Compare blocks one by one from left to right.
		Index i = len;
		while (i > 0) {
			i--;
			if (blk[i] == x.blk[i])
				continue;
			else if (blk[i] > x.blk[i])
				return greater;
			else
				return less;
		}
		// If no blocks differed, the numbers are equal.
		return equal;
	}
}

// PUT-HERE OPERATIONS

/*
* Below are implementations of the four basic arithmetic operations
* for `BigUnsigned's.  Their purpose is to use a mechanism that can
* calculate the sum, difference, product, and quotient/remainder of
* two individual blocks in order to calculate the sum, difference,
* product, and quotient/remainder of two multi-block BigUnsigned
* numbers.
*
* As alluded to in the comment before class `BigUnsigned',
* these algorithms bear a remarkable similarity (in purpose, if
* not in implementation) to the way humans operate on big numbers.
* The built-in `+', `-', `*', `/' and `%' operators are analogous
* to elementary-school ``math facts'' and ``times tables''; the
* four routines below are analogous to ``long division'' and its
* relatives.  (Only a computer can ``memorize'' a times table with
* 18446744073709551616 entries!  (For 32-bit blocks.))
*
* The discovery of these four algorithms, called the ``classical
* algorithms'', marked the beginning of the study of computer science.
* See Section 4.3.1 of Knuth's ``The Art of Computer Programming''.
*/

/*
 * On most calls to put-here operations, it's safe to read the inputs little by
 * little and write the outputs little by little.  However, if one of the
 * inputs is coming from the same variable into which the output is to be
 * stored (an "aliased" call), we risk overwriting the input before we read it.
 * In this case, we first compute the result into a temporary BigUnsigned
 * variable and then copy it into the requested output variable *this.
 * Each put-here operation uses the DTRT_ALIASED macro (Do The Right Thing on
 * aliased calls) to generate code for this check.
 * 
 * I adopted this approach on 2007.02.13 (see Assignment Operators in
 * BigUnsigned.hh).  Before then, put-here operations rejected aliased calls
 * with an exception.  I think doing the right thing is better.
 * 
 * Some of the put-here operations can probably handle aliased calls safely
 * without the extra copy because (for example) they process blocks strictly
 * right-to-left.  At some point I might determine which ones don't need the
 * copy, but my reasoning would need to be verified very carefully.  For now
 * I'll leave in the copy.
 */
#define DTRT_ALIASED(cond, op) \
	if (cond) { \
		BigUnsigned tmpThis; \
		tmpThis.op; \
		*this = tmpThis; \
		return; \
	}

// Addition
void BigUnsigned::add(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, add(a, b));
	// If one argument is zero, copy the other.
	if (a.len == 0) {
		operator =(b);
		return;
	} else if (b.len == 0) {
		operator =(a);
		return;
	}
	// Some variables...
	// Carries in and out of an addition stage
	bool carryIn, carryOut;
	Blk temp;
	Index i;
	// a2 points to the longer input, b2 points to the shorter
	const BigUnsigned *a2, *b2;
	if (a.len >= b.len) {
		a2 = &a;
		b2 = &b;
	} else {
		a2 = &b;
		b2 = &a;
	}
	// Set prelimiary length and make room in this BigUnsigned
	len = a2->len + 1;
	allocate(len);
	// For each block index that is present in both inputs...
	for (i = 0, carryIn = false; i < b2->len; i++) {
		// Add input blocks
		temp = a2->blk[i] + b2->blk[i];
		// If a rollover occurred, the result is less than either input.
		// This test is used many times in the BigUnsigned code.
		carryOut = (temp < a2->blk[i]);
		// If a carry was input, handle it
		if (carryIn) {
			temp++;
			carryOut |= (temp == 0);
		}
		blk[i] = temp; // Save the addition result
		carryIn = carryOut; // Pass the carry along
	}
	// If there is a carry left over, increase blocks until
	// one does not roll over.
	for (; i < a2->len && carryIn; i++) {
		temp = a2->blk[i] + 1;
		carryIn = (temp == 0);
		blk[i] = temp;
	}
	// If the carry was resolved but the larger number
	// still has blocks, copy them over.
	for (; i < a2->len; i++)
		blk[i] = a2->blk[i];
	// Set the extra block if there's still a carry, decrease length otherwise
	if (carryIn)
		blk[i] = 1;
	else
		len--;
}

// Subtraction
void BigUnsigned::subtract(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, subtract(a, b));
	// If b is zero, copy a.  If a is shorter than b, the result is negative.
	if (b.len == 0) {
		operator =(a);
		return;
	} else if (a.len < b.len)
	throw "BigUnsigned::subtract: Negative result in unsigned calculation";
	// Some variables...
	bool borrowIn, borrowOut;
	Blk temp;
	Index i;
	// Set preliminary length and make room
	len = a.len;
	allocate(len);
	// For each block index that is present in both inputs...
	for (i = 0, borrowIn = false; i < b.len; i++) {
		temp = a.blk[i] - b.blk[i];
		// If a reverse rollover occurred, the result is greater than the block from a.
		borrowOut = (temp > a.blk[i]);
		// Handle an incoming borrow
		if (borrowIn) {
			borrowOut |= (temp == 0);
			temp--;
		}
		blk[i] = temp; // Save the subtraction result
		borrowIn = borrowOut; // Pass the borrow along
	}
	// If there is a borrow left over, decrease blocks until
	// one does not reverse rollover.
	for (; i < a.len && borrowIn; i++) {
		borrowIn = (a.blk[i] == 0);
		blk[i] = a.blk[i] - 1;
	}
	// If there's still a borrow, the result is negative.
	// Throw an exception, but zero out this object first just in case.
	if (borrowIn) {
		len = 0;
		throw "BigUnsigned::subtract: Negative result in unsigned calculation";
	} else // Copy over the rest of the blocks
	for (; i < a.len; i++)
		blk[i] = a.blk[i];
	// Zap leading zeros
	zapLeadingZeros();
}

/*
* About the multiplication and division algorithms:
*
* I searched unsucessfully for fast built-in operations like the `b_0'
* and `c_0' Knuth describes in Section 4.3.1 of ``The Art of Computer
* Programming'' (replace `place' by `Blk'):
*
*    ``b_0[:] multiplication of a one-place integer by another one-place
*      integer, giving a two-place answer;
*
*    ``c_0[:] division of a two-place integer by a one-place integer,
*      provided that the quotient is a one-place integer, and yielding
*      also a one-place remainder.''
*
* I also missed his note that ``[b]y adjusting the word size, if
* necessary, nearly all computers will have these three operations
* available'', so I gave up on trying to use algorithms similar to his.
* A future version of the library might include such algorithms; I
* would welcome contributions from others for this.
*
* I eventually decided to use bit-shifting algorithms.  To multiply `a'
* and `b', we zero out the result.  Then, for each `1' bit in `a', we
* shift `b' left the appropriate amount and add it to the result.
* Similarly, to divide `a' by `b', we shift `b' left varying amounts,
* repeatedly trying to subtract it from `a'.  When we succeed, we note
* the fact by setting a bit in the quotient.  While these algorithms
* have the same O(n^2) time complexity as Knuth's, the ``constant factor''
* is likely to be larger.
*
* Because I used these algorithms, which require single-block addition
* and subtraction rather than single-block multiplication and division,
* the innermost loops of all four routines are very similar.  Study one
* of them and all will become clear.
*/

/*
* This is a little inline function used by both the multiplication
* routine and the division routine.
*
* `getShiftedBlock' returns the `x'th block of `num << y'.
* `y' may be anything from 0 to N - 1, and `x' may be anything from
* 0 to `num.len'.
*
* Two things contribute to this block:
*
* (1) The `N - y' low bits of `num.blk[x]', shifted `y' bits left.
*
* (2) The `y' high bits of `num.blk[x-1]', shifted `N - y' bits right.
*
* But we must be careful if `x == 0' or `x == num.len', in
* which case we should use 0 instead of (2) or (1), respectively.
*
* If `y == 0', then (2) contributes 0, as it should.  However,
* in some computer environments, for a reason I cannot understand,
* `a >> b' means `a >> (b % N)'.  This means `num.blk[x-1] >> (N - y)'
* will return `num.blk[x-1]' instead of the desired 0 when `y == 0';
* the test `y == 0' handles this case specially.
*/
inline BigUnsigned::Blk getShiftedBlock(const BigUnsigned &num,
	BigUnsigned::Index x, unsigned int y) {
	BigUnsigned::Blk part1 = (x == 0 || y == 0) ? 0 : (num.blk[x - 1] >> (BigUnsigned::N - y));
	BigUnsigned::Blk part2 = (x == num.len) ? 0 : (num.blk[x] << y);
	return part1 | part2;
}

// Multiplication
void BigUnsigned::multiply(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, multiply(a, b));
	// If either a or b is zero, set to zero.
	if (a.len == 0 || b.len == 0) {
		len = 0;
		return;
	}
	/*
	* Overall method:
	*
	* Set this = 0.
	* For each 1-bit of `a' (say the `i2'th bit of block `i'):
	*    Add `b << (i blocks and i2 bits)' to *this.
	*/
	// Variables for the calculation
	Index i, j, k;
	unsigned int i2;
	Blk temp;
	bool carryIn, carryOut;
	// Set preliminary length and make room
	len = a.len + b.len;
	allocate(len);
	// Zero out this object
	for (i = 0; i < len; i++)
		blk[i] = 0;
	// For each block of the first number...
	for (i = 0; i < a.len; i++) {
		// For each 1-bit of that block...
		for (i2 = 0; i2 < N; i2++) {
			if ((a.blk[i] & (Blk(1) << i2)) == 0)
				continue;
			/*
			* Add b to this, shifted left i blocks and i2 bits.
			* j is the index in b, and k = i + j is the index in this.
			*
			* `getShiftedBlock', a short inline function defined above,
			* is now used for the bit handling.  It replaces the more
			* complex `bHigh' code, in which each run of the loop dealt
			* immediately with the low bits and saved the high bits to
			* be picked up next time.  The last run of the loop used to
			* leave leftover high bits, which were handled separately.
			* Instead, this loop runs an additional time with j == b.len.
			* These changes were made on 2005.01.11.
			*/
			for (j = 0, k = i, carryIn = false; j <= b.len; j++, k++) {
				/*
				* The body of this loop is very similar to the body of the first loop
				* in `add', except that this loop does a `+=' instead of a `+'.
				*/
				temp = blk[k] + getShiftedBlock(b, j, i2);
				carryOut = (temp < blk[k]);
				if (carryIn) {
					temp++;
					carryOut |= (temp == 0);
				}
				blk[k] = temp;
				carryIn = carryOut;
			}
			// No more extra iteration to deal with `bHigh'.
			// Roll-over a carry as necessary.
			for (; carryIn; k++) {
				blk[k]++;
				carryIn = (blk[k] == 0);
			}
		}
	}
	// Zap possible leading zero
	if (blk[len - 1] == 0)
		len--;
}

/*
* DIVISION WITH REMAINDER
* The functionality of divide, modulo, and %= is included in this one monstrous call,
* which deserves some explanation.
*
* The division *this / b is performed.
* Afterwards, q has the quotient, and *this has the remainder.
* Thus, a call is like q = *this / b, *this %= b.
*
* This seemingly bizarre pattern of inputs and outputs has a justification.  The
* ``put-here operations'' are supposed to be fast.  Therefore, they accept inputs
* and provide outputs in the most convenient places so that no value ever needs
* to be copied in its entirety.  That way, the client can perform exactly the
* copying it needs depending on where the inputs are and where it wants the output.
* A better name for this function might be "modWithQuotient", but I would rather
* not change the name now.
*/
void BigUnsigned::divideWithRemainder(const BigUnsigned &b, BigUnsigned &q) {
	/*
	 * Defending against aliased calls is a bit tricky because we are
	 * writing to both *this and q.
	 * 
	 * It would be silly to try to write quotient and remainder to the
	 * same variable.  Rule that out right away.
	 */
	if (this == &q)
		throw "BigUnsigned::divideWithRemainder: Cannot write quotient and remainder into the same variable";
	/*
	 * Now *this and q are separate, so the only concern is that b might be
	 * aliased to one of them.  If so, use a temporary copy of b.
	 */
	if (this == &b || &q == &b) {
		BigUnsigned tmpB(b);
		divideWithRemainder(tmpB, q);
		return;
	}
	
	/*
	* Note that the mathematical definition of mod (I'm trusting Knuth) is somewhat
	* different from the way the normal C++ % operator behaves in the case of division by 0.
	* This function does it Knuth's way.
	*
	* We let a / 0 == 0 (it doesn't matter) and a % 0 == a, no exceptions thrown.
	* This allows us to preserve both Knuth's demand that a mod 0 == a
	* and the useful property that (a / b) * b + (a % b) == a.
	*/
	if (b.len == 0) {
		q.len = 0;
		return;
	}
	
	/*
	* If *this.len < b.len, then *this < b, and we can be sure that b doesn't go into
	* *this at all.  The quotient is 0 and *this is already the remainder (so leave it alone).
	*/
	if (len < b.len) {
		q.len = 0;
		return;
	}
	
	/*
	* At this point we know *this > b > 0.  (Whew!)
	*/
	
	/*
	* Overall method:
	*
	* For each appropriate i and i2, decreasing:
	*    Try to subtract (b << (i blocks and i2 bits)) from *this.
	*        (`work2' holds the result of this subtraction.)
	*    If the result is nonnegative:
	*        Turn on bit i2 of block i of the quotient q.
	*        Save the result of the subtraction back into *this.
	*    Otherwise:
	*        Bit i2 of block i remains off, and *this is unchanged.
	* 
	* Eventually q will contain the entire quotient, and *this will
	* be left with the remainder.
	*
	* We use work2 to temporarily store the result of a subtraction.
	* work2[x] corresponds to blk[x], not blk[x+i], since 2005.01.11.
	* If the subtraction is successful, we copy work2 back to blk.
	* (There's no `work1'.  In a previous version, when division was
	* coded for a read-only dividend, `work1' played the role of
	* the here-modifiable `*this' and got the remainder.)
	*
	* We never touch the i lowest blocks of either blk or work2 because
	* they are unaffected by the subtraction: we are subtracting
	* (b << (i blocks and i2 bits)), which ends in at least `i' zero blocks.
	*/
	// Variables for the calculation
	Index i, j, k;
	unsigned int i2;
	Blk temp;
	bool borrowIn, borrowOut;
	
	/*
	* Make sure we have an extra zero block just past the value.
	*
	* When we attempt a subtraction, we might shift `b' so
	* its first block begins a few bits left of the dividend,
	* and then we'll try to compare these extra bits with
	* a nonexistent block to the left of the dividend.  The
	* extra zero block ensures sensible behavior; we need
	* an extra block in `work2' for exactly the same reason.
	*
	* See below `divideWithRemainder' for the interesting and
	* amusing story of this section of code.
	*/
	Index origLen = len; // Save real length.
	// 2006.05.03: Copy the number and then change the length!
	allocateAndCopy(len + 1); // Get the space.
	len++; // Increase the length.
	blk[origLen] = 0; // Zero the extra block.
	
	// work2 holds part of the result of a subtraction; see above.
	Blk *work2 = new Blk[len];
	
	// Set preliminary length for quotient and make room
	q.len = origLen - b.len + 1;
	q.allocate(q.len);
	// Zero out the quotient
	for (i = 0; i < q.len; i++)
		q.blk[i] = 0;
	
	// For each possible left-shift of b in blocks...
	i = q.len;
	while (i > 0) {
		i--;
		// For each possible left-shift of b in bits...
		// (Remember, N is the number of bits in a Blk.)
		q.blk[i] = 0;
		i2 = N;
		while (i2 > 0) {
			i2--;
			/*
			* Subtract b, shifted left i blocks and i2 bits, from *this,
			* and store the answer in work2.  In the for loop, `k == i + j'.
			*
			* Compare this to the middle section of `multiply'.  They
			* are in many ways analogous.  See especially the discussion
			* of `getShiftedBlock'.
			*/
			for (j = 0, k = i, borrowIn = false; j <= b.len; j++, k++) {
				temp = blk[k] - getShiftedBlock(b, j, i2);
				borrowOut = (temp > blk[k]);
				if (borrowIn) {
					borrowOut |= (temp == 0);
					temp--;
				}
				// Since 2005.01.11, indices of `work2' directly match those of `blk', so use `k'.
				work2[k] = temp; 
				borrowIn = borrowOut;
			}
			// No more extra iteration to deal with `bHigh'.
			// Roll-over a borrow as necessary.
			for (; k < origLen && borrowIn; k++) {
				borrowIn = (blk[k] == 0);
				work2[k] = blk[k] - 1;
			}
			/*
			* If the subtraction was performed successfully (!borrowIn),
			* set bit i2 in block i of the quotient.
			*
			* Then, copy the portion of work2 filled by the subtraction
			* back to *this.  This portion starts with block i and ends--
			* where?  Not necessarily at block `i + b.len'!  Well, we
			* increased k every time we saved a block into work2, so
			* the region of work2 we copy is just [i, k).
			*/
			if (!borrowIn) {
				q.blk[i] |= (Blk(1) << i2);
				while (k > i) {
					k--;
					blk[k] = work2[k];
				}
			} 
		}
	}
	// Zap possible leading zero in quotient
	if (q.blk[q.len - 1] == 0)
		q.len--;
	// Zap any/all leading zeros in remainder
	zapLeadingZeros();
	// Deallocate temporary array.
	// (Thanks to Brad Spencer for noticing my accidental omission of this!)
	delete [] work2;
	
}
/*
* The out-of-bounds accesses story:
* 
* On 2005.01.06 or 2005.01.07 (depending on your time zone),
* Milan Tomic reported out-of-bounds memory accesses in
* the Big Integer Library.  To investigate the problem, I
* added code to bounds-check every access to the `blk' array
* of a `NumberlikeArray'.
*
* This gave me warnings that fell into two categories of false
* positives.  The bounds checker was based on length, not
* capacity, and in two places I had accessed memory that I knew
* was inside the capacity but that wasn't inside the length:
* 
* (1) The extra zero block at the left of `*this'.  Earlier
* versions said `allocateAndCopy(len + 1); blk[len] = 0;'
* but did not increment `len'.
*
* (2) The entire digit array in the conversion constructor
* ``BigUnsignedInABase(BigUnsigned)''.  It was allocated with
* a conservatively high capacity, but the length wasn't set
* until the end of the constructor.
*
* To simplify matters, I changed both sections of code so that
* all accesses occurred within the length.  The messages went
* away, and I told Milan that I couldn't reproduce the problem,
* sending a development snapshot of the bounds-checked code.
*
* Then, on 2005.01.09-10, he told me his debugger still found
* problems, specifically at the line `delete [] work2'.
* It was `work2', not `blk', that was causing the problems;
* this possibility had not occurred to me at all.  In fact,
* the problem was that `work2' needed an extra block just
* like `*this'.  Go ahead and laugh at me for finding (1)
* without seeing what was actually causing the trouble.  :-)
*
* The 2005.01.11 version fixes this problem.  I hope this is
* the last of my memory-related bloopers.  So this is what
* starts happening to your C++ code if you use Java too much!
*/

// Bitwise and
void BigUnsigned::bitAnd(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, bitAnd(a, b));
	len = (a.len >= b.len) ? b.len : a.len;
	allocate(len);
	Index i;
	for (i = 0; i < len; i++)
		blk[i] = a.blk[i] & b.blk[i];
	zapLeadingZeros();
}

// Bitwise or
void BigUnsigned::bitOr(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, bitOr(a, b));
	Index i;
	const BigUnsigned *a2, *b2;
	if (a.len >= b.len) {
		a2 = &a;
		b2 = &b;
	} else {
		a2 = &b;
		b2 = &a;
	}
	allocate(a2->len);
	for (i = 0; i < b2->len; i++)
		blk[i] = a2->blk[i] | b2->blk[i];
	for (; i < a2->len; i++)
		blk[i] = a2->blk[i];
	len = a2->len;
}

// Bitwise xor
void BigUnsigned::bitXor(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, bitXor(a, b));
	Index i;
	const BigUnsigned *a2, *b2;
	if (a.len >= b.len) {
		a2 = &a;
		b2 = &b;
	} else {
		a2 = &b;
		b2 = &a;
	}
	allocate(a2->len);
	for (i = 0; i < b2->len; i++)
		blk[i] = a2->blk[i] ^ b2->blk[i];
	for (; i < a2->len; i++)
		blk[i] = a2->blk[i];
	len = a2->len;
	zapLeadingZeros();
}

// Bitwise shift left
void BigUnsigned::bitShiftLeft(const BigUnsigned &a, unsigned int b) {
	DTRT_ALIASED(this == &a, bitShiftLeft(a, b));
	Index shiftBlocks = b / N;
	unsigned int shiftBits = b % N;
	// + 1: room for high bits nudged left into another block
	len = a.len + shiftBlocks + 1;
	allocate(len);
	Index i, j;
	for (i = 0; i < shiftBlocks; i++)
		blk[i] = 0;
	for (j = 0, i = shiftBlocks; j <= a.len; j++, i++)
		blk[i] = getShiftedBlock(a, j, shiftBits);
	// Zap possible leading zero
	if (blk[len - 1] == 0)
		len--;
}

// Bitwise shift right
void BigUnsigned::bitShiftRight(const BigUnsigned &a, unsigned int b) {
	DTRT_ALIASED(this == &a, bitShiftRight(a, b));
	// This calculation is wacky, but expressing the shift as a left bit shift
	// within each block lets us use getShiftedBlock.
	Index rightShiftBlocks = (b + N - 1) / N;
	unsigned int leftShiftBits = N * rightShiftBlocks - b;
	// Now (N * rightShiftBlocks - leftShiftBits) == b
	// and 0 <= leftShiftBits < N.
	if (rightShiftBlocks >= a.len + 1) {
		// All of a is guaranteed to be shifted off, even considering the left
		// bit shift.
		len = 0;
		return;
	}
	// Now we're allocating a positive amount.
	// + 1: room for high bits nudged left into another block
	len = a.len + 1 - rightShiftBlocks;
	allocate(len);
	Index i, j;
	for (j = rightShiftBlocks, i = 0; j <= a.len; j++, i++)
		blk[i] = getShiftedBlock(a, j, leftShiftBits);
	// Zap possible leading zero
	if (blk[len - 1] == 0)
		len--;
}

// INCREMENT/DECREMENT OPERATORS

// Prefix increment
void BigUnsigned::operator ++() {
	Index i;
	bool carry = true;
	for (i = 0; i < len && carry; i++) {
		blk[i]++;
		carry = (blk[i] == 0);
	}
	if (carry) {
		// Matt fixed a bug 2004.12.24: next 2 lines used to say allocateAndCopy(len + 1)
		// Matt fixed another bug 2006.04.24:
		// old number only has len blocks, so copy before increasing length
		allocateAndCopy(len + 1);
		len++;
		blk[i] = 1;
	}
}

// Postfix increment: same as prefix
void BigUnsigned::operator ++(int) {
	operator ++();
}

// Prefix decrement
void BigUnsigned::operator --() {
	if (len == 0)
		throw "BigUnsigned::operator --(): Cannot decrement an unsigned zero";
	Index i;
	bool borrow = true;
	for (i = 0; borrow; i++) {
		borrow = (blk[i] == 0);
		blk[i]--;
	}
	// Zap possible leading zero (there can only be one)
	if (blk[len - 1] == 0)
		len--;
}

// Postfix decrement: same as prefix
void BigUnsigned::operator --(int) {
	operator --();
}
