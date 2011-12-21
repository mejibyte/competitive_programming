/* skips prefixes equals to some word. */

import java.util.*;
import java.io.*;

public class funny_gk_wa_skip_words {
    static Scanner in;
    static PrintWriter out;
    
    static int MAX_N = 100;
    static int MAX_M = 1000;
    
    static final int MAX_W = 100;
    static final int MIN_CH = 'A';
    static final int MAX_CH = 'Z';
    
    List<int[]> letterss;
    
    static class Entry implements Comparable<Entry> {
    	int count;
    	String word;
    	
    	Entry(int count, String word) {
    		this.count = count;
    		this.word = word;
    	}

		@Override
		public int compareTo(Entry that) {
			return that.count - this.count;
		}
    }

    Queue<Entry> queue = new PriorityQueue<Entry>();
    Set<String> queued = new HashSet<String>();
    Set<String> words;
    
	private void enqueue(String word) {
		System.out.println(word);
		if (queued.add(word) && !words.contains(word)) {
			int count = count(word);
			if (count != 0) {
				queue.add(new Entry(count, word));
			}
		}
	}
	
	private int count(String word) {
		int[] letters = letters(word);
		int result = 0;
		for (int[] wordLetters : letterss) {
			if (match(letters, wordLetters)) {
				result++;
			}
		}
		return result;
	}

	private boolean match(int[] letters, int[] wordLetters) {
		for (int i = 0; i < 26; i++) {
			if (letters[i] > wordLetters[i]) {
				return false;
			}
		}
		return true;
	}

	private int[] letters(String word) {
		int[] letters = new int[26];
		for (char ch : word.toCharArray()) {
			letters[ch - MIN_CH]++;
		}
		return letters;
	}
	
	int c = 0;

	Set<String> solve(int n, Set<String> words) {
		this.words = words;
		letterss = new ArrayList<int[]>();
        for (String word : words) {
        	letterss.add(letters(word));
        }
    
        enqueue("");
        Set<String> result = new TreeSet<String>();
        while (!queue.isEmpty() && result.size() < n) {
        	String word = queue.remove().word;
        	if (word.length() > 0 && !words.contains(word)) {
        		result.add(word);
        		c += count(word);
        	}
        	
        	for (int i = 0; i < 26; i++) {
        		enqueue(word + (char) ('A' + i));
        	}
        }
        
        System.out.println(result.size());
        
    	StringBuilder sb = new StringBuilder();
    	for (int i = 0; result.size() < n; i++) {
    		sb.append('A');
    		String word = sb.toString();
    		if (!words.contains(word)) {
    			result.add(word);
    		}
    	}
		return result;
	}

	public void run() throws IOException {
    	int n = in.nextInt();
    	int m = in.nextInt();

        assert 1 <= n && n <= MAX_N;
        assert 1 <= m && m <= MAX_M;
        
        Set<String> words = new HashSet<String>();
        for (int i = 0; i < m; i++) {
        	String word = in.next();
            words.add(word);
        	
            assert 1 <= word.length() && word.length() <= MAX_W;            
            for (char ch : word.toCharArray()) {
                assert MIN_CH <= ch && ch <= MAX_CH;
            }
        }
        assert !in.hasNext();

        Set<String> result = solve(n, words);
    	
        for (String word : result) {
        	out.println(word);
        }
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("funny.in"));
        out = new PrintWriter("funny.out");

        new funny_gk_wa_skip_words().run();

        in.close();
        out.close();
    }
}
