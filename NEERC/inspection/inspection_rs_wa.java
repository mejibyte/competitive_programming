import java.io.*;
import java.util.*;

public class inspection_rs_wa implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	
	private void check(boolean expr, String msg) {
		if (!expr) {
			throw new Error(msg);
		}
	}
	
	private void checkBounds(int n, int low, int hi, String nStr) {
		check((low <= n) && (n <= hi), nStr + " is not in [" + low + ", " + hi + "]");
	}
	
	private boolean[][] go;
	private boolean[] mark;
	private int[] topsort;
	private int n, count;
	
	private List<List<Integer>>[] paths;
	
	private void dfs(int u) {
		mark[u] = true;
		for (int v = 0; v < n; v++) {
			if (!mark[v] && go[u][v]) {
				dfs(v);
			}
		}
		topsort[--count] = u;
	}

	@SuppressWarnings("unchecked")
	private void solve() throws IOException {
		n = Integer.parseInt(in.readLine());
		checkBounds(n, 1, 100, "n");
		go = new boolean[n][n];
		for (int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int w = Integer.parseInt(st.nextToken());
			for (int j = 0; j < w; j++) {
				int u = Integer.parseInt(st.nextToken()) - 1;
				check(u != i, "Edge from vertix to itself");
				check(!go[i][u], "Duplicate edges");
				go[i][u] = true;
			}
		}
		mark = new boolean[n];
		topsort = new int[n];
		count = n;
		for (int i = 0; i < n; i++) {
			if (!mark[i]) {
				dfs(i);
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				check(!go[topsort[j]][topsort[i]], "graph is not acyclic");
			}
		}
		
		paths = new List[n];
		for (int i = 0; i < n; i++) {
			paths[i] = new ArrayList<List<Integer>>();
		}
		int totalPaths = 0;
		for (int ii = 0; ii < n; ii++) {
			int i = topsort[ii];
			for (int jj = 0; jj < ii; jj++) {
				int j = topsort[jj];
				if (!go[j][i]) {
					continue;
				}
				if (!paths[j].isEmpty()) {
					List<Integer> path = paths[j].get(paths[j].size() - 1);
					paths[j].remove(paths[j].size() - 1);
					
					path.add(i);
					paths[i].add(path);
					continue;
				}
				
				List<Integer> path = new ArrayList<Integer>();
				path.add(j);
				path.add(i);
				paths[i].add(path);
				totalPaths++;
			}
		}
		
		out.println(totalPaths);
		for (int i = 0; i < n; i++) {
			for (List<Integer> path: paths[i]) {
				for (int j: path) {
					out.print((j + 1) + " ");
				}
				out.println();
			}
		}
	}
	
	public static void main(String[] args) {
		new Thread(new inspection_rs_wa()).start();
	}

	public void run() {
		String problem = getClass().getName().split("_")[0];
		try {
			in = new BufferedReader(new FileReader(new File(problem + ".in")));
			out = new PrintWriter(new File(problem + ".out"));
			solve();
			in.close();
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}
