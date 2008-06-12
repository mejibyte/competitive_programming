import java.io.*;
import java.text.*;

//
// File:    practice.java
// Purpose: practice program, sigma positive integers 
// Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
// 
// Thu Jul 03 16:03:50 2003
// 
// $Id: practice.java,v 1.1 2005/03/06 05:34:39 laned Exp $
// 

public class practice {
    public static void main(String[] args) 
    {
	try
	{	
		RandomAccessFile file = new RandomAccessFile("practice.in", "r");
		String line;

		int inval = 0;
		int sum = 0;

		while((line = file.readLine()) != null) 
		{			
			inval = new Integer(line.trim()).intValue();
			sum = 0;

			if (inval == 0)
				System.exit (4);

			if (inval < 1)
			{
				for (int i = 1; i >= inval; i --)
				       sum += i;	
			}
			else
			{
				for (int i = 1; i <= inval; i ++)
				       sum += i;	
			}
			System.out.println("N = "+inval+"  Sum = "+sum);
		}

		System.out.println("Did not find trailing zero");
	}
	catch(Exception e)
	{
		System.out.println("Possible trouble reading practice.in");
	}			
    }
}

// eof practice.java $Id: practice.java,v 1.1 2005/03/06 05:34:39 laned Exp $
