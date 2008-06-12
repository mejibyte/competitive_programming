
//
// File:    sum1.cpp
// Purpose: to sum the integers in the file sumit.dat
// Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
//
// Sat Oct 30 12:43:18 PDT 1999
//
// caveat - this is not nice code, copy at own risk ;)
//
// $Id: sumit.cpp,v 1.1 2005/03/06 05:13:57 laned Exp $
//
//

#include <iostream.h>
#include <fstream.h>

main ()
{
	int num;
	int sum;
	ifstream filein("sumit.dat");

	if (filein.fail())
	{
		cerr << "Could not read from file sumit.dat " << endl;
	}
	else
	{

		sum = 0;

		while(!filein.eof())
		{
			filein >> num;

			if (num > 0)
			{
				sum += num;
			}
		}

		cout << "The sum of the positive integers is " << sum << endl;

	}
}

// eof 
