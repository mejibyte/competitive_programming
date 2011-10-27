import java.io.*;
import java.util.*;

public class funny_rs implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private int[][] w;
	private int n, m;
	private Set<String> answer, originalWords;
	
	private void check(boolean expr, String msg) {
		if (!expr) {
			throw new Error(msg);
		}
	}
	
	private void checkBounds(int n, int low, int hi, String nStr) {
		check((low <= n) && (n <= hi), nStr + " is not in [" + low + ", " + hi + "]");
	}
	
	private class Combination implements Comparable<Combination> {
		public int[] letters;
		public int count, hash;
		
		public Combination(int[] letters) {
			this.letters = new int[26];
			for (int i = 0; i < 26; i++) {
				this.letters[i] = letters[i];
			}
			
			count = 0;
			LOOP:
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < 26; j++) {
					if (w[i][j] < letters[j]) {
						continue LOOP;
					}
				}
				count++;
			}
			
			hash = 0;
			for (int i = 0; i < 26; i++) {
				hash ^= (letters[i] << i);
			}
		}

		public void genWords(String prefix) {
			if (answer.size() == n) {
				return;
			}
			boolean found = false;
			for (int i = 0; i < 26; i++) {
				if (letters[i] > 0) {
					letters[i]--;
					genWords(prefix + (char) ('A' + i));
					letters[i]++;
					found = true;
				}
			}
			if (!found) {
				if (prefix.length() > 0 && !originalWords.contains(prefix)) {
					answer.add(prefix);
				}
			}
		}

		@Override
		public int compareTo(Combination that) {
			return that.count - count;
		}
		
		@Override
		public boolean equals(Object o) {
			Combination that = (Combination) o;
			for (int i = 0; i < letters.length; i++) {
				if (letters[i] != that.letters[i]) {
					return false;
				}
			}
			return true;
		}
		
		@Override
		public int hashCode() {
			return hash;
		}
	}
	
	private void solve() throws IOException {
		StringTokenizer st = new StringTokenizer(in.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		checkBounds(n, 1, 100, "n");
		checkBounds(m, 1, 1000, "m");
		w = new int[m][26];
		originalWords = new HashSet<String>();
		for (int i = 0; i < m; i++) {
			String line = in.readLine();
			originalWords.add(line);
			check(line.length() <= 100, "word length > 100");
			for (int j = 0; j < line.length(); j++) {
				int ch = line.charAt(j) - 'A';
				check((0 <= ch) && (ch < 26), "Invalid chars");
				w[i][ch]++;
			}
		}
		
		PriorityQueue<Combination> queue = new PriorityQueue<Combination>();
		Set<Combination> visited = new HashSet<Combination>();
		
		Combination start = new Combination(new int[26]);
		queue.add(start);
		visited.add(start);
		answer = new HashSet<String>();
		while (answer.size() < n) {
			Combination cur = queue.poll();
			cur.genWords("");
			for (int i = 0; i < 26; i++) {
				cur.letters[i]++;
				Combination newCur = new Combination(cur.letters);
				cur.letters[i]--;
				if (visited.contains(newCur)) {
					continue;
				}
				queue.add(newCur);
			}
		}
		
		for (String w: answer) {
			out.println(w);
		}
	}
	
	public static void main(String[] args) {
		new Thread(new funny_rs()).start();
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
