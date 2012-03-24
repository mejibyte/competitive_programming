import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.StringTokenizer;


public class C
{
	static class Scanner
	{
		BufferedReader br;
		StringTokenizer st;
		
		public Scanner()
		{
	    	System.setOut(new PrintStream(new BufferedOutputStream(System.out), true));
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		
		public String next()
		{
			while(st == null || !st.hasMoreTokens())
			{
				try { st = new StringTokenizer(br.readLine()); }
				catch(Exception e) { throw new RuntimeException(); }
			}
			return st.nextToken();
		}

		public int nextInt()
		{
			return Integer.parseInt(next());
		}
		
		public double nextDouble()
		{
			return Double.parseDouble(next());
		}
		
		public String nextLine()
		{
			st = null;
			try { return br.readLine(); }
			catch(Exception e) { throw new RuntimeException(); }
		}
		
		public boolean endLine()
		{
			try 
			{
				String next = br.readLine();
				while(next != null && next.trim().isEmpty())
					next = br.readLine();
				if(next == null)
					return true;
				st = new StringTokenizer(next);
				return !st.hasMoreTokens();
			}
			catch(Exception e) { throw new RuntimeException(); }
		}
	}
	
	static int f;
	static int menor;
	static int nFactores;
	static long sumaTotal;
	final static int[] valores = new int[100000];
	final static int[] factores = new int[100];
	final static int[] nveces = new int[100];
	
	private static void generar(int i, long acum) 
	{
		if(i == nFactores)
		{
			if(acum > Integer.MAX_VALUE)
				return;
			sumaTotal += intentar((int) acum);
		}
		else
		{
			int cuenta = 1;
			for(int j = 0; j <= nveces[i]; j++)
			{
				generar(i + 1, cuenta * acum);
				cuenta *= factores[i];
			}
		}
	}
	
	static int GCD(int a, int b)
	{
	   if (b == 0) return a;
	   return GCD(b, a % b);
	}
	
	static long modInverse(long a, long n) 
	{
		 long i = n, v = 0, d = 1;
		 while (a > 0)
		 {
			  long t = i / a, x = a;
			  a = i % x;
			  i = x;
			  x = d;
			  d = v - t * x;
			  v = x;
		 }
		 v %= n;
		 if (v < 0) v = (v + n) % n;
		 return v;
	}
	
	private static long intentar(int factor) 
	{
		for(int i = 0; i < f; i++)
		{
			if(valores[i] % (factor*f) != 0)
				return 0;
		}
		if(factor == 0)
			return 0;
		if(factor * (long)f > menor)
			return 0;
		if(menor % (factor*f) == 0) //????
			return (menor / (factor * f)) - 1;
		int siguiente = menor % (factor * f);
		if(menor % factor != 0)
			return 0;
		siguiente = menor - siguiente;
		return (siguiente / (factor * f));
	}


	public static void main(String[] args)
	{
		Scanner sc = new Scanner();
		while(true)
		{
			f = sc.nextInt();
			if(f == 0)
				return;
			menor = Integer.MAX_VALUE;
			long sumatoria = 0;
			for(int i = 0; i < f; i++)
			{
				valores[i] = sc.nextInt();
				sumatoria += valores[i];
				menor = Math.min(menor, valores[i]);
			}
			if(sumatoria % f != 0)
			{
				System.out.println(0);
				continue;
			}
			for(int i = 0; i < f; i++)
				valores[i] -= menor;
			boolean paila = false;
			for(int i = 0; i < f; i++)
			{
				if(valores[i] % f != 0)
					paila = true;
			}
			if(paila)
			{
				System.out.println(0);
				continue;
			}
			nFactores = 0;
			int raiz = (int) (Math.sqrt(sumatoria) + 10);
			for(int i = 2; sumatoria != 1 && i <= raiz; i++)
			{
				int cuenta = 0;
				while(sumatoria % i == 0)
				{
					cuenta++;
					sumatoria /= i;
					raiz = (int) (Math.sqrt(sumatoria) + 10);
				}
				if(cuenta > 0)
				{
					factores[nFactores] = i;
					nveces[nFactores++] = cuenta;
				}
			}
			if(sumatoria != 1) {
				factores[nFactores] = (int)sumatoria;
				nveces[nFactores++] = 1;
			}
			sumaTotal = 0;
			generar(0, 1);
			System.out.println(sumaTotal);
		}
	}
}