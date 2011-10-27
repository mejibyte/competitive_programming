import java.io.*;
import java.util.*;

/**
 * @author Iskander Akishev
 */
public class funny_ia_wrong implements Runnable {

	private static final String FILE_NAME = "funny";

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
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());

		int[][] w = new int[m][26];
		TreeSet<String> words = new TreeSet<String>();
		for (int i = 0; i < m; i++) {
			String word = in.readLine();
			words.add(word);
			for (char c : word.toCharArray()) {
				w[i][c - 'A']++;
			}
		}

		//todo
		Random rnd = new Random();
		for (int i = 0; i < 1000; i++) {
			String str = "";
			for (int z = 0; z < 100; z++)
				str += (rnd.nextInt(26) + 'A');
			words.add(str);
		}

		TreeSet<NewWord> newWords = new TreeSet<NewWord>();

		for (char c1 = 'A'; c1 <= 'Z'; c1++) {
			int cnt = 0;
			for (int[] ww : w) {
				ww[c1 - 'A']--;
				if (ww[c1 - 'A'] >= 0)
					cnt++;
				ww[c1 - 'A']++;
			}
			String str = String.valueOf(new char[] {c1});
			if (!words.contains(str)) {
				newWords.add(new NewWord(str, cnt));
				if (newWords.size() > n)
					newWords.remove(newWords.last());
			}
		}
		for (char c1 = 'A'; c1 <= 'Z'; c1++) {
			for (char c2 = 'A'; c2 <= 'Z'; c2++) {
				int cnt = 0;
				for (int[] ww : w) {
					ww[c1 - 'A']--;
					ww[c2 - 'A']--;
					if ((ww[c1 - 'A'] >= 0) && (ww[c2 - 'A'] >= 0))
						cnt++;
					ww[c1 - 'A']++;
					ww[c2 - 'A']++;
				}
				String str = String.valueOf(new char[] {c1, c2});
				if (!words.contains(str)) {
					newWords.add(new NewWord(str, cnt));
					if (newWords.size() > n)
						newWords.remove(newWords.last());
				}
			}
		}
		for (char c1 = 'A'; c1 <= 'Z'; c1++) {
			for (char c2 = 'A'; c2 <= 'Z'; c2++) {
				for (char c3 = 'A'; c3 <= 'Z'; c3++) {
					int cnt = 0;
					for (int[] ww : w) {
						ww[c1 - 'A']--;
						ww[c2 - 'A']--;
						ww[c3 - 'A']--;
						if ((ww[c1 - 'A'] >= 0) && (ww[c2 - 'A'] >= 0) && (ww[c3 - 'A'] >= 0))
							cnt++;
						ww[c1 - 'A']++;
						ww[c2 - 'A']++;
						ww[c3 - 'A']++;
					}
					String str = String.valueOf(new char[] {c1, c2, c3});
					if (!words.contains(str)) {
						newWords.add(new NewWord(str, cnt));
						if (newWords.size() > n)
							newWords.remove(newWords.last());
					}
				}
			}
		}
		for (char c1 = 'A'; c1 <= 'Z'; c1++) {
			for (char c2 = 'A'; c2 <= 'Z'; c2++) {
				for (char c3 = 'A'; c3 <= 'Z'; c3++) {
					for (char c4 = 'A'; c4 <= 'Z'; c4++) {
						int cnt = 0;
						for (int[] ww : w) {
							ww[c1 - 'A']--;
							ww[c2 - 'A']--;
							ww[c3 - 'A']--;
							ww[c4 - 'A']--;
							if ((ww[c1 - 'A'] >= 0) && (ww[c2 - 'A'] >= 0) && (ww[c3 - 'A'] >= 0) && (ww[c4 - 'A'] >= 0))
								cnt++;
							ww[c1 - 'A']++;
							ww[c2 - 'A']++;
							ww[c3 - 'A']++;
							ww[c4 - 'A']++;
						}
						String str = String.valueOf(new char[] {c1, c2, c3, c4});
						if (!words.contains(str)) {
							newWords.add(new NewWord(str, cnt));
							if (newWords.size() > n)
								newWords.remove(newWords.last());
						}
					}
				}
			}
		}
//		for (char c1 = 'A'; c1 <= 'Z'; c1++) {
//			for (char c2 = 'A'; c2 <= 'Z'; c2++) {
//				for (char c3 = 'A'; c3 <= 'Z'; c3++) {
//					for (char c4 = 'A'; c4 <= 'Z'; c4++) {
//						for (char c5 = 'A'; c5 <= 'Z'; c5++) {
//							int cnt = 0;
//							for (int[] ww : w) {
//								ww[c1 - 'A']--;
//								ww[c2 - 'A']--;
//								ww[c3 - 'A']--;
//								ww[c4 - 'A']--;
//								ww[c5 - 'A']--;
//								if ((ww[c1 - 'A'] >= 0) && (ww[c2 - 'A'] >= 0) && (ww[c3 - 'A'] >= 0) && (ww[c4 - 'A'] >= 0) && (ww[c5 - 'A'] >= 0))
//									cnt++;
//								ww[c1 - 'A']++;
//								ww[c2 - 'A']++;
//								ww[c3 - 'A']++;
//								ww[c4 - 'A']++;
//								ww[c5 - 'A']++;
//							}
//							String str = "" + c1 + c2 + c3 + c4 + c5;
//							if (!words.contains(str)) {
//								newWords.add(new NewWord(str, cnt));
//								if (newWords.size() > n)
//									newWords.remove(newWords.last());
//							}
//						}
//					}
//				}
//			}
//		}

		for (NewWord nw : newWords) {
			out.println(nw.word);
			n--;
			if (n == 0) {
				break;
			}
		}

		in.close();
		out.close();
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
		new Thread(new funny_ia_wrong()).start();
	}
}