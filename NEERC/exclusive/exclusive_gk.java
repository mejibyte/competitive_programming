import java.util.*;
import java.io.*;

class exclusive_gk {
    static Scanner in;
    static PrintWriter out;
    
    final static char MIN_CH = 'L';
    final static char MAX_CH = 'Z';
    final static int MAX_N = MAX_CH - MIN_CH + 1;

    int[] minColoring = new int[1 << MAX_N];
    int[] p = new int[1 << MAX_N];
    boolean[] forbidden = new boolean[1 << MAX_N];
    
    private int minColoring(int mask) {
    	if (minColoring[mask] == Integer.MAX_VALUE) {
    		int result = minColoring[mask]; 
    		for (int j = mask; j > 0; j = mask & (j - 1)) {
    			if (!forbidden[j] && result > minColoring(mask & ~j) + 1) {
    				result = minColoring[mask & ~j] + 1;
    				p[mask] = j;
    			}
    		}
    		minColoring[mask] = result;
    	}
    	return minColoring[mask];
	}

    void run() throws IOException {
        int n = in.nextInt();
        
        int[][] locks = new int[n][2];
        for (int i = 0; i < n; i++) {
        	locks[i][0] = in.next().charAt(0) - MIN_CH;
        	locks[i][1] = in.next().charAt(0) - MIN_CH;
        }
        
        for (int i = 0; i < n; i++) {
        	int mask = (1 << locks[i][0]) | (1 << locks[i][1]);
			for (int j = 0; j < 1 << MAX_N; j++) {
				forbidden[j] |= (j & mask) == mask;
			}
        }

        Arrays.fill(minColoring, Integer.MAX_VALUE);
        minColoring[0] = 0;
        
        out.println(minColoring((1 << MAX_N) - 1) - 2);
        
        int[] colors = new int[MAX_N];
        int color = 1;
        for (int mask = (1 << MAX_N) - 1; mask != 0; mask &= ~p[mask]) {
        	for (int j = 0; j < MAX_N; j++) {
        		if (((p[mask] >> j) & 1) != 0) {
        			colors[j] = color;
        		}
        	}
        	color++;
        }
        
        for (int i = 0; i < n; i++) {
        	int q = colors[locks[i][0]] < colors[locks[i][1]] ? 0 : 1;
    		out.println((char) (locks[i][q] + MIN_CH) + " " + (char) (locks[i][1 - q] + MIN_CH));
        }
    }

	public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("exclusive.in"));
        out = new PrintWriter("exclusive.out");
        
        new exclusive_gk().run();

        in.close();
        out.close();
    }
}
