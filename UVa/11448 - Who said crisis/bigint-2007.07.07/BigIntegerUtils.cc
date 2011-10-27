/*
* Matt McCutchen's Big Integer Library
*/

#include "BigIntegerUtils.hh"
#include "BigUnsignedInABase.hh"

/*
* This file includes:
* (1) `std::string <=> BigUnsigned/BigInteger' conversion routines easier than `BigUnsignedInABase'
* (2) << and >> operators for BigUnsigned/BigInteger, std::istream/std::ostream
*/

std::string easyBUtoString(const BigUnsigned &x) {
	return std::string(BigUnsignedInABase(x, 10));
}

std::string easyBItoString(const BigInteger &x) {
	return (x.getSign() == BigInteger::negative) ?
		(std::string("-") + easyBUtoString(x)) : (easyBUtoString(x));
}

BigUnsigned easyStringToBU(const std::string &s) {
	return BigUnsigned(BigUnsignedInABase(s, 10));
}

BigInteger easyStringToBI(const std::string &s) {
	return (s[0] == '-') ?
		BigInteger(easyStringToBU(s.substr(1, s.length() - 1)), BigInteger::negative) :
		BigInteger(easyStringToBU(s));
}

// Outputs x to os, obeying the flags `dec', `hex', `bin', and `showbase'.
std::ostream &operator <<(std::ostream &os, const BigUnsigned &x) {
	BigUnsignedInABase::Base base;
	long osFlags = os.flags();
	if (osFlags & os.dec)
		base = 10;
	else if (osFlags & os.hex) {
		base = 16;
		if (osFlags & os.showbase)
			os << "0x";
	} else if (osFlags & os.oct) {
		base = 8;
		if (osFlags & os.showbase)
			os << '0';
	} else
		throw "std::ostream << BigUnsigned: Could not determine the desired base from output-stream flags";
	std::string s = std::string(BigUnsignedInABase(x, base));
	os << s;
	return os;
}
// Outputs x to os, obeying the flags `dec', `hex', `bin', and `showbase'.
// My somewhat arbitrary policy: a negative sign comes before a base indicator (like -0xFF).
std::ostream &operator <<(std::ostream &os, const BigInteger &x) {
	if (x.getSign() == BigInteger::negative)
		os << '-';
	os << (const BigUnsigned &)(x);
	return os;
}
