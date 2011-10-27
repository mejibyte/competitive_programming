#
# Matt McCutchen's Big Integer Library
#

# Mention default target.
all :

# Implicit rule to compile C++ files.  Modify to your taste.
%.o : %.cc
	g++ -c -O2 -Wall -Wextra -pedantic $<

# Components of the library.
library-objects = BigUnsigned.o BigInteger.o BigUnsignedInABase.o BigIntegerUtils.o
library-headers = NumberlikeArray.hh BigUnsigned.hh BigUnsignedInABase.hh BigInteger.hh BigIntegerLibrary.hh

# To ``make the library'', make all its objects using the implicit rule.
library : $(library-objects)

# Extra dependencies from `#include'.
BigUnsigned.o : NumberlikeArray.hh BigUnsigned.hh
BigInteger.o : NumberlikeArray.hh BigUnsigned.hh BigInteger.hh
BigUnsignedInABase.o : NumberlikeArray.hh BigUnsigned.hh BigUnsignedInABase.hh
BigIntegerUtils.o : NumberlikeArray.hh BigUnsigned.hh BigUnsignedInABase.hh BigInteger.hh

# The rules below build a program that uses the library.  They are preset to
# build ``sample'' from ``sample.cc''.  You can change the name(s) of the
# source file(s) and program file to build your own program, or you can write
# your own Makefile.

# Components of the program.
program = sample
program-objects = sample.o

# Conservatively assume all the program source files depend on all the library
# headers.  You can change this if it is not the case.
$(program-objects) : $(library-headers)

# How to link the program.  The implicit rule covers individual objects.
$(program) : $(program-objects) $(library-objects)
	g++ $(program-objects) $(library-objects) -o $(program)

# Delete all generated files we know about.
clean :
	rm -f $(library-objects) $(program-objects) $(program)

# I removed the *.tag dependency tracking system because it had few advantages
# over manually entering all the dependencies.  If there were a portable,
# reliable dependency tracking system, I'd use it, but I know of no such;
# cons and depcomp are almost good enough.

# Come back and define default target.
all : library $(program)
