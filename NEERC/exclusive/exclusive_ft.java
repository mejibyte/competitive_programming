import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.util.HashSet;

public class exclusive_ft implements Runnable {

	private static final int MAX_N = 100;
	private static final int INF = (int) 1e9;
	private BufferedReader in;
	private StringTokenizer st;
	private PrintWriter out;

	public exclusive_ft() throws IOException {
		in = new BufferedReader(new FileReader(new File("exclusive.in")));
		st = new StringTokenizer("");
		out = new PrintWriter(new FileWriter(new File("exclusive.out")));
	}
	
	public static void main(String[] args) throws IOException {
		new Thread(new exclusive_ft()).start();
	}
	
	public void run() {
		try {
			solve();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		} finally { 
			out.close();
		}
	}

	private String nextToken() throws IOException {
		while (!st.hasMoreTokens()) {
			st = new StringTokenizer(in.readLine());
		}
		return st.nextToken();
	}
	
	private int nextInt() throws NumberFormatException, IOException {
		return Integer.parseInt(nextToken());
	}

	private void myAssert(boolean u, String message) {
		if (!u) {
			throw new Error("Assertion failed!!! " + message);
		}
	}

	private void checkBounds(int x, int min, int max, String name) {
		myAssert((min <= x) && (x <= max), name + " is out of bounds: min = " + min + ", max = " + max + ", " + name + " = " + x);
	}


	private void solve() throws NumberFormatException, IOException {
		int n = nextInt();
		int[][] process = new int[n][];
		int[] cntNeed = new int['Z' - 'L' + 1];
		checkBounds(n, 1, MAX_N, "n");
		for (int i = 0; i < n; i++) {
			String r1 = nextToken();
			String r2 = nextToken();
			myAssert(r1.length() == 1, "");
			myAssert(r2.length() == 1, "");
			char resource1 = r1.charAt(0);
			char resource2 = r2.charAt(0);
			myAssert(('L' <= resource1) && (resource1 <= 'Z'), "Wrong resource: " + r1 + " (process " + (i + 1) + ")");
			myAssert(('L' <= resource2) && (resource2 <= 'Z'), "Wrong resource: " + r2 + " (process " + (i + 1) + ")");
			myAssert(resource1 != resource2, "Process " + (i + 1) + " needs the same resource two times");
			process[i] = new int[] {resource1 - 'L', resource2 - 'L'};
			cntNeed[resource1 - 'L']++;
			cntNeed[resource2 - 'L']++;
		}
		int[] map = new int['Z' - 'L' + 1];
		Arrays.fill(map, -1);
		int size = 0;
		
		for (int i = 0; i < 'Z' - 'L' + 1; i++) {
			map[i] = size++;
		}
		
		boolean[][] edge = new boolean[size][size];
		for (int i = 0; i < n; i++) {
			int r1 = process[i][0];
			int r2 = process[i][1];
			edge[r1][r2] = true;
			edge[r2][r1] = true;
		}
		
		boolean[] isIndependent = new boolean[1 << size];
		for (int mask = 0; mask < (1 << size); mask++) {
			isIndependent[mask] = true;
			checkIndependent:
			for (int i = 0; i < size; i++) {
				if ((mask | (1 << i)) != mask) {
					continue;
				}
				for (int j = i + 1; j < size; j++) {
					if ((mask | (1 << j)) != mask) {
						continue;
					}
					if (edge[i][j]) {
						isIndependent[mask] = false;
						break checkIndependent;
					}
				}
			}
		}
		int all = (1 << size) - 1;
		int[] minColor = new int[1 << size];
		int[] prev = new int[1 << size];
		Arrays.fill(minColor, INF);
		Arrays.fill(prev, -1);
		minColor[0] = 0;
		for (int colored = 0; colored < (1 << size); colored++) {
			if (minColor[colored] == INF) {
				continue;
			}
			int notColored = all & (~colored);
			for (int subset = notColored; subset > 0; subset = (subset - 1) & notColored) {
				if (isIndependent[subset]) {
					int newColored = colored | subset;
					if (minColor[newColored] > minColor[colored] + 1) {
						minColor[newColored] = minColor[colored] + 1;
						prev[newColored] = colored;
					}
				}
			}
		}
		
		int[] coloring = new int[size];
		int curColor = minColor[all]; 
		int curMask = all;
		while (curMask >= 0) {
			int prevMask = prev[curMask];
			int diff = curMask & (~prevMask);
			for (int i = 0; i < size; i++) {
				if ((diff | (1 << i)) != diff) {
					continue;
				}
				coloring[i] = curColor;
			}
			curMask = prevMask;
			curColor--;
		}

		out.println(minColor[all] - 2);
		for (int i = 0; i < n; i++) {
			int r1 = process[i][0];
			int r2 = process[i][1];
			if (coloring[map[r1]] < coloring[map[r2]]) {
				out.println(((char) ('L' + r1)) + " " + ((char) ('L' + r2)));
			} else {
				out.println(((char) ('L' + r2)) + " " + ((char) ('L' + r1)));
			}
		}
		
	} 

}
