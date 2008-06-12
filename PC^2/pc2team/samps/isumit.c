
/*
 * File:    isumit.c 
 * Purpose: to sum the integers from stdin
 * Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
 *
 * Thu Oct  2 20:27:08 PDT 2003
 *
 * $Id: isumit.c,v 1.1 2005/03/06 05:34:39 laned Exp $ 
 *
 */

#include <stdio.h>

#define INFILENAME "sumit.dat"

main ()
{
	int sum = 0;
	int i;

	while (1==fscanf(stdin, "%d", &i))
	{
		sum += i > 0 ? i : 0;
	}
	printf("The sum of the positive integers is %d \n",sum);

}

/* eof isumit.c $Id: isumit.c,v 1.1 2005/03/06 05:34:39 laned Exp $ */
