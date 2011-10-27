import java.io.*;
import java.util.*;

public class database_md {
	private static String fileName = database_md.class.getSimpleName().replaceFirst("_.*", "");
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;

	public void run() {
		int n = in.nextInt();
		int m = in.nextInt();
		in.nextLine();
		String[][] table = new String[n][];
		for (int i = 0; i < n; i++) {
			table[i] = in.nextLine().split(",");
		}
		int[][] val = new int[n][m];
		for (int j = 0; j < m; j++) {
			Map<String, Integer> map = new HashMap<String, Integer>();
			for (int i = n - 1; i >= 0; i--) {
				map.put(table[i][j], i);
			}
			for (int i = 0; i < n; i++) {
				val[i][j] = map.get(table[i][j]);
			}
		}
		int[] pair = new int[n];
		for (int j = 0; j < m; j++) {
			for (int k = j + 1; k < m; k++) {
				for (int i = 0; i < n; i++) {
					pair[i] = val[i][j] * n + val[i][k];
				}
				Arrays.sort(pair);
				int found = -1;
				for (int i = 0; i < n - 1; i++) {
					if (pair[i] == pair[i + 1]) {
						found = pair[i];
					}
				}
				if (found >= 0) {
					out.println("NO");
					int f = 0;
					for (int i = 0; i < n && f < 2; i++) {
						if (found == val[i][j] * n + val[i][k]) {
							out.print((i + 1) + " ");
						}
					}
					out.println();
					out.println((j + 1) + " " + (k + 1));
					return;
				}
			}
		}
		out.println("YES");
	}

	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new FileReader(inputFileName));
		out = new PrintWriter(outputFileName);
		new database_md().run();
		in.close();
		out.close();
	}
}
