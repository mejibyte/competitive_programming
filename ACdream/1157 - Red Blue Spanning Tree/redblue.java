import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;

public class RedBlue {
	class Edge {
		char c;
		int u, v;
		boolean[] used;

		Edge(char c, int u, int v) {
			this.c = c;
			this.u = u;
			this.v = v;
			used = new boolean[2];
		}

		public String toString() {
			return "(" + u + "," + v + ")";
		}
	}

	private int n, m;
	private int[] s, h, countRB;
	private Edge[] edges;

	private int find(int x) {
		return x == s[x] ? x : (s[x] = find(s[x]));
	}

	private void union(int s1, int s2) {
		if (h[s1] < h[s2]) {
			s[s1] = s2;
		} else {
			s[s2] = s1;
			if (h[s1] == h[s2])
				h[s1]++;
		}
	}

	private Edge[] MST(int rb) {
		Edge[] ret = new Edge[n - 1];
		countRB[0] = countRB[1] = 0;
		int cnt = 0;
		for (int i = 0; i < m; i++) {
			int s1 = find(edges[i].u);
			int s2 = find(edges[i].v);
			if (s1 != s2) {
				union(s1, s2);
				edges[i].used[rb] = true;
				if (edges[i].c == 'R')
					countRB[0]++;
				else
					countRB[1]++;
				ret[cnt++] = edges[i];
				if (cnt == n - 1)
					break;
			}
		}
		return ret;
	}

	private static final int MAX_NODES = 1024;
	private static final int MAX_EDGES = 500500;

	private void work() {
		Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(
				System.in)));
		Edge[] redEdges = new Edge[MAX_EDGES];
		Edge[] blueEdges = new Edge[MAX_EDGES];
		int red, blue;
		s = new int[MAX_NODES];
		h = new int[MAX_NODES];
		countRB = new int[2];
		edges = new Edge[MAX_EDGES];
		while (true) {
			n = sc.nextInt();
			m = sc.nextInt();
			int k = sc.nextInt();
			if ((n | m | k) == 0)
				break;
			red = blue = 0;
			for (int i = 0; i < m; i++) {
				char c = sc.next().charAt(0);
				int u = sc.nextInt() - 1;
				int v = sc.nextInt() - 1;
				Edge e = new Edge(c, u, v);
				if (c == 'R')
					redEdges[red++] = e;
				else
					blueEdges[blue++] = e;
			}
			if (blue < k) {
				System.out.println(0);
				continue;
			}
			for (int i = 0; i < n; i++) {
				s[i] = i;
				h[i] = 0;
			}
			System.arraycopy(redEdges, 0, edges, 0, red);
			System.arraycopy(blueEdges, 0, edges, red, blue);
			Edge[] redTree = MST(0);
			int minBlue = countRB[1];
			for (int i = 0; i < n; i++) {
				s[i] = i;
				h[i] = 0;
			}
			System.arraycopy(redEdges, 0, edges, blue, red);
			System.arraycopy(blueEdges, 0, edges, 0, blue);
			Edge[] blueTree = MST(1);
			int maxBlue = countRB[1];
			// System.out.println(minBlue + " " + maxBlue);
			System.out.println(k >= minBlue && k <= maxBlue ? 1 : 0);

		}
	}

	public static void main(String[] args) {
		new RedBlue().work();
	}

}
