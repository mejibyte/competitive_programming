import java.io.*;
import java.util.*;

class Main
{
	static BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
	String s;
    public static void main (String args[])
    {
    	try{
    	s = stdin.readLine();
    	}catch{}
    	StringTokenizer tokens = new StringTokenizer(s);
    	int t = Integer.parseInt((tokens.nextToken()));
    	long a, b;
    	for (int i=0; i<t; ++i){
    		try{
    		s = stdin.readLine();
    		}catch{}
    		tokens = new StringTokenizer(s);
    		a = Integer.parseInt(tokens.nextToken());
    		b = Integer.parseInt(tokens.nextToken());
    		if (a < b){
    			System.out.println("<");
    		}else if (a > b){
    			System.out.println(">");
    		}else{
    			System.out.println("=");
    		}
    	}
    }
}