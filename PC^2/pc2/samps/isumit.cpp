
//
// File:    isumit.cpp
// Purpose: to sum the integers from stdin
// Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
//
// Thu Oct  2 20:28:19 PDT 2003
//
// $Id: isumit.cpp,v 1.1 2005/03/06 05:34:39 laned Exp $
//
//

#include <iostream.h>
#include <fstream.h>

main ()
{
	int num;
	int sum;

		sum = 0;

	cin >> num;
	while(num != 0)
	{
		if (num > 0)
		{
			sum += num;
		}
		cin >> num;
	}

	cout << "The sum of the positive integers is " << sum << endl;
}

// eof isumit.c $Id: isumit.cpp,v 1.1 2005/03/06 05:34:39 laned Exp $
