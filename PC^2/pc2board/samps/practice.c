
#include <stdio.h>
#include <stdlib.h>

/*
 * File:    practice.c
 * Purpose: sum of positive integers practice problem
 * Author:  pc2@ecs.csus.edu
 *
 * $Id: practice.c,v 1.1 2005/03/06 05:34:39 laned Exp $
 */

#define INFILE "practice.in"

int main (int argc, char **argv)
{
	int sum = 0;
	int i = 0;
	FILE *fp = fopen (INFILE,  "rt");
	char line[128];

	if (fp != NULL)
	{
		while ( fgets (line, sizeof(line), fp) != NULL)
		{
			long inval = atol (line);
			sum = 0;

			if (inval == 0)
				exit (4);

			if (inval < 1)
			{
				for (i = 1; i >= inval; i --)
				       sum += i;	
			}
			else
			{
				for (i = 1; i <= inval; i ++)
				       sum += i;	
			}
			printf("N = %-3d    Sum = %d\n", inval, sum);
		}

		printf("Did not find trailing zero \n");

	}
	else
	{
		fprintf(stderr,"Could not read file %s \n", INFILE);
	}

	exit (4);
}

/* eof practice.c */
