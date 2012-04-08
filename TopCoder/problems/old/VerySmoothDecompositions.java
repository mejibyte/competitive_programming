import java.math.*;
import java.util.ArrayList;
import java.util.Hashtable;


public class VerySmoothDecompositions {
	
	int hashify(long p2, long p3, long p5, long p7, long start) {
		String s = p2 + "_" + p3 + "_" + p5 + "_" + p7 + "_" + start;
		return s.hashCode();
	}
	
	Hashtable<Long, Integer> memo;
	
	int options[][] = {
			{1, 0, 0, 0}, // 2 = 2
			{0, 1, 0, 0}, // 3 = 3
			{2, 0, 0, 0}, // 4 = 2 * 2
			{0, 0, 1, 0}, // 5 = 5
			{1, 1, 0, 0}, // 6 = 2 * 3
			{0, 0, 0, 1}, // 7 = 7
			{3, 0, 0, 0}, // 8 = 2 * 2 * 2
			{0, 2, 0, 0}, // 9 = 3 * 3
			{1, 0, 1, 0}, // 10 = 2 * 5
			{2, 1, 0, 0}, // 12 = 2 * 2 * 3
			{1, 0, 0, 1}, // 14 = 2 * 7
			{0, 1, 1, 0}, // 15 = 3 * 5
			{4, 0, 0, 0}, // 16 = 2 * 2 * 2 * 2
	};
		
	
	public int f(int p2, int p3, int p5, int p7, int start) {
		if (p2 < 0 || p3 < 0 || p5 < 0 || p7 < 0) return 0;
		
		//System.out.printf("Hash for (p2=%d, p3=%d, p5=%d, p7=%d, start=%d) is %d\n", p2, p3, p5, p7, start, hashify(p2, p3, p5, p7, start));
		
		if (p2 == 0 && p3 == 0 && p5 == 0 && p7 == 0) {
			//for (int i = 0; i < depth; ++i) { System.out.print(" "); } System.out.printf("f(p2=%d, p3=%d, p5=%d, p7=%d, start=%d)\n", p2, p3, p5, p7, start);
			//for (int i = 0; i < depth; ++i) { System.out.print(" "); } System.out.printf("= 1\n");			
			return 1;
		}
		
		//for (int i = 0; i < depth; ++i) { System.out.print(" "); } System.out.printf("f(p2=%d, p3=%d, p5=%d, p7=%d, start=%d)\n", p2, p3, p5, p7, start);
		
		
		long hash = hashify(p2, p3, p5, p7, start);
		
		if (memo.containsKey(hash)) {
			//for (int i = 0; i < depth; ++i) { System.out.print(" "); } System.out.printf("= %d (from memo)\n", memo.get(hash));			
			return memo.get(hash);
		}
		
		int ans = 0;
		int mod = 1000000009;
		for (int i = start; i < options.length; ++i) {
			int extra = f(p2 - options[i][0], p3 - options[i][1],
					      p5 - options[i][2], p7 - options[i][3], i);
			
			ans += extra;
			ans = ans % mod;
		}
		
		memo.put(hash, ans);
		//for (int i = 0; i < depth; ++i) { System.out.print(" "); } System.out.printf("= %d\n", ans);
		return ans;
	}

	public int solve(String[] args) {
		String s = "";
		for (int i = 0; i < args.length; ++i) {
			s = s + args[i];
		}

		BigInteger D = new BigInteger(s, 10);
		if (D.compareTo(BigInteger.ONE) == 0) return 1;

		int[] primes = { 2, 3, 5, 7, 11, 13 };

		int divisorCount[] = new int[17];

		for (int i = 0; i < primes.length; ++i) {
			int p = primes[i];
			BigInteger P = new BigInteger(String.valueOf(p));
			while (D.mod(P).compareTo(BigInteger.ZERO) == 0) {
				divisorCount[p]++;
				D = D.divide(P);
			}
		}
		if (D.compareTo(BigInteger.ONE) > 0) {
			return 0;
		}
		
		for (int i = 0; i <= 16; ++i) {
			System.out.printf("divisorCount[i=%d]=%d\n", i, divisorCount[i]);
		}
		
		memo = new Hashtable<Long, Integer>();
		return f(divisorCount[2], divisorCount[3], divisorCount[5], divisorCount[7], 0);
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
