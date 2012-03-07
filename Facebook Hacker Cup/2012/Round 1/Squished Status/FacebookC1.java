import java.util.Scanner;


public class FacebookC1 
{
	static final long mod = 4207849484L;
	
	static Long[] dp;
	
	static String mensaje;
	static int m;
	
	static long dp(int actual)
	{
		if(dp[actual] != null)
			return dp[actual];
		if(mensaje.charAt(actual) == '0')
			return dp[actual] = 0L;
		long cuenta = 0;
		for(int i = actual + 1; i <= Math.min(mensaje.length(), actual + 4); i++)
		{
			if(Integer.parseInt(mensaje.substring(actual, i)) <= m)
			{
				cuenta += dp(i);
				cuenta %= mod;
			}
		}
		return dp[actual] = cuenta;
	}
	
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		for(int caso = 1; caso <= n; caso++)
		{
			m = sc.nextInt();
			mensaje = sc.next();
			dp = new Long[mensaje.length() + 1];
			dp[mensaje.length()] = 1L;
			System.out.println("Case #" + caso + ": " + dp(0));
		}
	}

}
