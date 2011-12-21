/* Generates all short words and chooses best. Prefers full matches in the first round. */

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

public class funny_gk_wa_short_eager {
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
        
        Set<Character> letters = new HashSet<Character>();
        assert !in.hasNext();
		letterss = new ArrayList<int[]>();
		for (String word : words) {
			letterss.add(letters(word));
			for (char ch : word.toCharArray()) {
				letters.add(ch);
			}
		}

		int maxWords = 2000000 / words.size();
		List<Entry> queue = new ArrayList<Entry>();
		queue.add(new Entry(m, ""));
		
		int head = 0;
		while (head < queue.size() && queue.size() < maxWords) {
			String word = queue.get(head++).word;
			for (int i = 0; i < 26; i++) {
				String nword = word + (char) ('A' + i);
				int count = count(nword);
				if (count == m) {
					queue.add(new Entry(count, nword));
				}
			}
		}
		
		head = 0;
		while (head < queue.size() && queue.size() < maxWords) {
			String word = queue.get(head++).word;
			for (int i = 0; i < 26; i++) {
				String nword = word + (char) ('A' + i);
				int count = count(nword);
				if (count != 0) {
					queue.add(new Entry(count, nword));
				}
			}
		}
		Collections.sort(queue);
		head = 0;
		Set<String> result = new TreeSet<String>();
		while (head < queue.size() && result.size() < n) {
			String word = queue.get(head++).word;
			if (word.length() > 0 && !words.contains(word)) {
				result.add(word);
			}
		}
		
    	StringBuilder sb = new StringBuilder();
    	for (int i = 0; result.size() < n; i++) {
    		sb.append('A');
    		String word = sb.toString();
    		if (!words.contains(word)) {
    			result.add(word);
    		}
    	}
		
        for (String word : result) {
        	out.println(word);
        }
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("funny.in"));
        out = new PrintWriter("funny.out");

        new funny_gk_wa_short_eager().run();

        in.close();
        out.close();
    }
}
