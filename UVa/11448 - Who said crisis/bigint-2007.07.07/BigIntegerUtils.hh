/*
* Matt McCutchen's Big Integer Library
*/

#ifndef BIGINTEGERUTILS
#define BIGINTEGERUTILS

#include "BigInteger.hh"
#include <string>
#include <iostream>

/*
* This file includes:
* (1) `std::string <=> BigUnsigned/BigInteger' conversion routines easier than `BigUnsignedInABase'
* (2) << and >> operators for BigUnsigned/BigInteger, std::istream/std::ostream
*/

// Conversion routines.  Base 10 only.
std::string easyBUtoString(const BigUnsigned &x);
std::string easyBItoString(const BigInteger &x);
BigUnsigned easyStringToBU(const std::string &s);
BigInteger easyStringToBI(const std::string &s);

// Creates a BigInteger from data such as `char's; read below for details.
template <class T>
BigInteger easyDataToBI(const T* data, BigInteger::Index length, BigInteger::Sign sign);

// Outputs x to os, obeying the flags `dec', `hex', `bin', and `showbase'.
std::ostream &operator <<(std::ostream &os, const BigUnsigned &x);

// Outputs x to os, obeying the flags `dec', `hex', `bin', and `showbase'.
// My somewhat arbitrary policy: a negative sign comes before a base indicator (like -0xFF).
std::ostream &operator <<(std::ostream &os, const BigInteger &x);

/*
* =================================
* BELOW THIS POINT are template definitions; above are declarations.  See `NumberlikeArray.hh'.
*/

/*
* Converts binary data to a BigInteger.
* Pass an array `data', its length, and the desired sign.
*
* Elements of `data' may be of any type `T' that has the following
* two properties (this includes almost all integral types):
*
* (1) `sizeof(T)' correctly gives the amount of binary data in one
* value of `T' and is a factor of `sizeof(Blk)'.
*
* (2) When a value of `T' is casted to a `Blk', the low bytes of
* the result contain the desired binary data.
*/
template <class T>
BigInteger easyDataToBI(const T* data, BigInteger::Index length, BigInteger::Sign sign) {
	// really ceiling(numBytes / sizeof(BigInteger::Blk))
	unsigned int pieceSizeInBits = 8 * sizeof(T);
	unsigned int piecesPerBlock = sizeof(BigInteger::Blk) / sizeof(T);
	unsigned int numBlocks = (length + piecesPerBlock - 1) / piecesPerBlock;
	
	// Allocate our block array
	BigInteger::Blk *blocks = new BigInteger::Blk[numBlocks];
	
	BigInteger::Index blockNum, pieceNum, pieceNumHere;
	
	// Convert
	for (blockNum = 0, pieceNum = 0; blockNum < numBlocks; blockNum++) {
		BigInteger::Blk curBlock = 0;
		for (pieceNumHere = 0; pieceNumHere < piecesPerBlock && pieceNum < length;
			pieceNumHere++, pieceNum++)
			curBlock |= (BigInteger::Blk(data[pieceNum]) << (pieceSizeInBits * pieceNumHere));
		blocks[blockNum] = curBlock;
	}
	
	// Create the BigInteger.
	BigInteger x(blocks, numBlocks, sign);
	
	delete blocks;
	return x;
}

#endif
