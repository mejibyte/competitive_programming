/*
* Matt McCutchen's Big Integer Library
*
* Sample program demonstrating the most important features of the Big
* Integer Library
*/

// Standard libraries
#include <string>
#include <iostream>

// For the BigInteger class itself.
#include "BigInteger.hh"

// For the 4 routines `easy BI/BU <=> string' and `iostream' integration.
#include "BigIntegerUtils.hh"

int main() {
	try {
		BigInteger a; // a is 0
		int b = 535;
		
		a = b; // From int to BigInteger...
		b = a; // ...and back, no casts required!
		/*
		* If a were too big for an int you'd get a runtime exception.
		* The Big Integer Library throws C-strings (that is,
		* `const char *'s) when something goes wrong.  It's a good idea
		* to catch them; the `try/catch' construct wrapping all this
		* code is an example of how to do this.  Some C++ compilers need
		* a special command-line option to compile code that uses
		* exceptions.
		*/
		
		BigInteger c(a); // Copy a BigInteger.
		
		// d is -314159265.  The `int' literal is converted to a
		// BigInteger.
		BigInteger d(-314159265);
		
		// This won't compile because the number is too big to be an
		// integer literal.
		//BigInteger e(3141592653589793238462643383279);
		
		// Instead you can convert the number from a string.
		std::string s("3141592653589793238462643383279");
		BigInteger f = easyStringToBI(s);
		
		// You can convert the other way too.
		std::string s2 = easyBItoString(f); 
		
		// f is stringified and send to std::cout.
		std::cout << f << std::endl;
		
		/*
		* Let's do some math!
		*
		* The Big Integer Library provides lots of overloaded operators
		* and corresponding assignment operators.  So you can do `a + b'
		* with BigIntegers just as with normal integers.  The named
		* methods `add', `divideWithRemainder', etc. are more advanced
		* ``put-here operations''; see `BigUnsigned.hh' for details.
		*/
		BigInteger g(314159), h(265);
		// All five ``return-by-value'' arithmetic operators.
		std::cout << (g + h) << '\n' << (g - h) << '\n' << (g * h)
			<< '\n' << (g / h) << '\n' << (g % h) << std::endl;
		
		BigUnsigned i(0xFF0000FF), j(0x0000FFFF);
		// All five ``return-by-value'' bitwise operators.
		std::cout.flags(std::ios::hex | std::ios::showbase);
		std::cout << (i & j) << '\n' << (i | j) << '\n' << (i ^ j) << '\n'
			<< (j << 21) << '\n' << (j >> 10) << '\n';
		std::cout.flags(std::ios::dec);
		
		// Let's do some heavy lifting and calculate powers of 314.
		int maxPower = 10;
		BigUnsigned x(1), big314(314);
		for (int power = 0; power <= maxPower; power++) {
			std::cout << "314^" << power << " = " << x << std::endl;
			x *= big314; // A BigInteger assignment operator
		}
		
		/*
		* If you want to experiment with the library,
		* you can add your own test code here.
		*/
		// std::cout << "Beginning of custom test code:" << std::endl;
		
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}
	
	return 0;
}

/*
Running the sample program produces this output:

3141592653589793238462643383279
314424
313894
83252135
1185
134
0xFF
0xFF00FFFF
0xFF00FF00
0x1FFFE00000
0x3F
314^0 = 1
314^1 = 314
314^2 = 98596
314^3 = 30959144
314^4 = 9721171216
314^5 = 3052447761824
314^6 = 958468597212736
314^7 = 300959139524799104
314^8 = 94501169810786918656
314^9 = 29673367320587092457984
314^10 = 9317437338664347031806976

*/
