import java.util.*;
import java.io.*;

public class garbling_gk {
    static Scanner in;
    static PrintWriter out;
    
    int r;
    int c;
    int turns = 0;
    
    class Permutation {
    	final int[] perm;
    	final long[] times;
    	
    	Permutation(int[] perm, long[] times) {
    		this.perm = perm;
    		this.times = times;
    	}

		public Permutation multiply(Permutation that) {
			int n = perm.length;
			int[] perm = new int[n];
			long[] times = new long[n];
			
			for (int i = 0; i < n; i++) {
				int j = this.perm[i];
				times[i] = this.times[i] + that.times[j];
				perm[i] = that.perm[j];
			}
			
			return new Permutation(perm, times);
		}
    }
    
	private void garbleLeft(int[][] f, int i, int j) {
		int t = f[i][j];
		f[i][j] = f[i][j + 1];
		f[i][j + 1] = f[i + 1][j + 1];
		f[i + 1][j + 1] = f[i + 1][j];
		f[i + 1][j] = t;
	}
	
	private void garbleRight(int[][] f, int i, int j) {
		int t = f[i][j];
		f[i][j] = f[i + 1][j];
		f[i + 1][j] = f[i + 1][j + 1];
		f[i + 1][j + 1] = f[i][j + 1];
		f[i][j + 1] = t;
	}

	private int[][] fill() {
		int[][] f = new int[r][c];
    	for (int i = 0; i < r; i++) {
    		for (int j = 0; j < c; j++) {
    			f[i][j] = index(i, j);
    		}
    	}
		return f;
	}

	private long[] garble(long n, char[][] g, int[][] f) {
		long[] times = new long[r * c];
		for (int i = 0; i < r - 1; i++) {
    		for (int j = 0; j < c - 1; j++) {
    			if (n-- == 0) {
    				return times;
    			}
    			times[f[i][j]]++;
    			if (g[i][j] == 'L') {
    				garbleLeft(f, i, j);
    			} else if (g[i][j] == 'R') {
    				garbleRight(f, i, j);
    			}
    		}
    	}
		assert n == 0;
		return times;
	}

	private Permutation garble(long n, char[][] g) {
		int[][] f = fill();

		long[] times = garble(n, g, f);
		int[] perm = new int[r * c];
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				perm[f[i][j]] = index(i, j);
			}
		}
		return new Permutation(perm, times);
	}

	private int index(int i, int j) {
		return i * c + j;
	}
	
    public void run() {
    	r = in.nextInt();
    	c = in.nextInt();
    	long n = in.nextLong();
    	
    	char[][] g = new char[r - 1][];
    	for (int i = 0; i < r - 1; i++) {
    		g[i] = in.next().toCharArray();
    	}
    
    	int loop = (r - 1) * (c - 1);
		Permutation result = garble(n % loop, g);
    	Permutation power = garble(loop, g);
    	long q = n / loop;
    	while (q != 0) {
    		if (q % 2 == 1) {
    			result = power.multiply(result);
    		}
    		power = power.multiply(power);
    		q /= 2;
    	}
    	
    	for (int i = 0; i < r; i++) {
    		for (int j = 0; j < c; j++) {
    			out.println(result.times[index(i, j)]);
    		}
    	}
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("garbling.in"));
        out = new PrintWriter("garbling.out");

        new garbling_gk().run();

        in.close();
        out.close();
    }
}
