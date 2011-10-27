	import java.io.*;
import java.util.*;
//import java.math.*;


class Main {

  public static void main(String[] args) throws IOException {
	 Scanner cin = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
    PrintStream cout = System.out;

    while (cin.hasNextInt()) {
    	int n = cin.nextInt();
    	int d = cin.nextInt();
    	if (n + d == 0) throw new IOException();
//    	BigInteger b = new BigInteger(String.valueOf(n));
//    	b = b.pow(d);
//    	cout.printf("%s\n", (b.toString()));
    	cout.printf("%.0f\n", Math.pow(n, d));
    }
  }
}


/*
class Main
{
    static BufferedReader stdin;
    static PrintWriter stdout;
    
    public static void main(String[] ss) throws Exception
    {
	Reader rdr = new InputStreamReader(System.in);
	stdin      = new BufferedReader(rdr);
	Writer wtr = new OutputStreamWriter(System.out);
	wtr        = new BufferedWriter(wtr);
	stdout     = new PrintWriter(wtr);
	
	(new Main()).run();
	stdout.close();
    }
        
    void run() throws Exception
    {
    	StringTokenizer t = new java.util.StringTokenizer(stdin.readLine());
		int n = Integer.parseInt(t.nextToken());
		int d = Integer.parseInt(t.nextToken());
    	while (n + d != 0){
    		BigInteger b = new BigInteger(String.valueOf(n));
    		b = b.pow(d);
    		stdout.println(b.toString());
        	t = new java.util.StringTokenizer(stdin.readLine());
    		n = Integer.parseInt(t.nextToken());
    		d = Integer.parseInt(t.nextToken());
    	}
    }
}
*/
		
	    
	