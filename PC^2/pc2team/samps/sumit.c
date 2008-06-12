
/*
 * File:    sum.c
 * Purpose: to sum the integers in the file sumit.dat
 * Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
 *
 * Tue Oct 19 21:32:14 PDT 1999
 *
 * caveat - this is not nice code, copy at own risk ;)
 *
 * $Id: sumit.c,v 1.1 2005/03/06 05:13:57 laned Exp $
 *
 */

#include <stdio.h>

#define INFILENAME "sumit.dat"

main ()
{
	FILE *fp = fopen (INFILENAME,"r");
	int sum = 0;
	int i;

	if (fp)
	{
		while (1==fscanf(fp, "%d", &i))
		{
			sum += i > 0 ? i : 0;
		}
		fclose (fp);
		printf("The sum of the positive integers is %d \n",sum);
	}
	else
	{
		printf("Could not read from file sumit.dat \n");
	}

}

/* eof */
