import java.util.*;
import java.io.*;

public class database_gk {
	static BufferedReader in;
	static PrintWriter out;

	public void run() throws IOException {
		String l = in.readLine();
		int n = Integer.parseInt(l.split(" ")[0]);
		int m = Integer.parseInt(l.split(" ")[1]);

		String[][] values = new String[n][];
		for (int i = 0; i < n; i++) {
			String line = in.readLine();
			String[] result = new String[m];
			int index = 0;
			for (int j = 0; j < m - 1; j++) {
				int nindex = line.indexOf(',', index);
				result[j] = line.substring(index, nindex);
				index = nindex + 1;
			}
			result[m - 1] = line.substring(index);
			values[i] =  result;
		}

		Map<String, Integer> intern = new HashMap<String, Integer>();
		int[][] indices = new int[n][m];
		int maxIndex = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				String value = values[i][j];
				Integer index = intern.get(value);
				if (index == null) {
					index = maxIndex++;
					intern.put(value, index);
				}
				indices[i][j] = index;
			}
		}

		for (int c1 = 0; c1 < m; c1++) {
			for (int c2 = c1 + 1; c2 < m; c2++) {
				long[] pairs = new long[n];
				for (int r = 0; r < n; r++) {
					pairs[r] = ((long) indices[r][c1] * maxIndex + indices[r][c2]) * n + r;
				}
				Arrays.sort(pairs);
				for (int i = 0; i < n - 1; i++) {
					if (pairs[i] / n == pairs[i + 1] / n) {
						out.println("NO");
						out.println((pairs[i] % n + 1) + " "  + (pairs[i + 1] % n + 1));
						out.println((c1 + 1) + " "  + (c2 + 1));
						return;
					}
				}
			}
		}
		out.println("YES");
	}

	public static void main(String[] args) throws Exception {        
		in = new BufferedReader(new FileReader("database.in"));
		out = new PrintWriter("database.out");

		new database_gk().run();

		in.close();
		out.close();
	}
}
