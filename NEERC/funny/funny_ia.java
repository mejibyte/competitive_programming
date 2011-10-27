import java.io.*;
import java.util.*;

/**
 * @author Iskander Akishev
 */
public class funny_ia implements Runnable {

	private static final String FILE_NAME = "funny";
	private int[][] w;
	private TreeSet<String> words;
	private TreeSet<NewWord> newWords;
	private int lim;
	private int n;
	private int m;

	public void run() {
		try {
			solve();
		} catch (Throwable t) {
			t.printStackTrace();
			System.exit(1);
		}
	}

	private BufferedReader in;
	private PrintWriter out;

	private void solve() throws Exception {
		in = new BufferedReader(new FileReader(FILE_NAME + ".in"));
		out = new PrintWriter(new File(FILE_NAME + ".out"));

		StringTokenizer st = new StringTokenizer(in.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());

		w = new int[m][26];
		words = new TreeSet<String>();
		for (int i = 0; i < m; i++) {
			String word = in.readLine();
			words.add(word);
			for (char c : word.toCharArray()) {
				w[i][c - 'A']++;
			}
		}


		lim = m + n + 1;

		newWords = new TreeSet<NewWord>();
		add("");

		NewWord cur = newWords.first();

		for (int k = 0; k < lim; k++) {
			for (char c = 'A'; c <= 'Z'; c++) {
				add(cur.word + c);
			}
			cur = newWords.higher(cur);
		}

		



		newWords.remove(newWords.first());

		for (NewWord nw : newWords) {
			if (words.contains(nw.word)) {
				continue;
			}
			out.println(nw.word);
			n--;
			if (n == 0) {
				break;
			}
		}

		in.close();
		out.close();
	}

	int[] a = new int[26];

	private void add(String s) {
		Arrays.fill(a, 0);
		for (int i = 0; i < s.length(); i++) {
			char c = s.charAt(i);
			a[c - 'A']++;
		}
		int cnt = 0;
		LOOP: for (int[] ww : w) {
			for (int i = 0; i < 26; i++) {
				if (a[i] > ww[i]) {
					continue LOOP;
				}
			}
			cnt++;
		}
		newWords.add(new NewWord(s, cnt));
		if (newWords.size() > lim) {
			newWords.remove(newWords.last());
		}
	}

	static class NewWord implements Comparable<NewWord> {
		String word;
		int score;

		NewWord(String word, int score) {
			this.word = word;
			this.score = score;
		}

		public int compareTo(NewWord o) {
			int res = o.score - score;
			if (res == 0) {
				res = word.compareTo(o.word);
			}
			return res;
		}
	}
	
	public static void main(String[] args) {
		new Thread(new funny_ia()).start();
	}
}