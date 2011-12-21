import java.util.*;
import java.io.*;

public class funny_gk {
    static Scanner in;
    static PrintWriter out;
    
    static int MAX_N = 100;
    static int MAX_M = 1000;
    
    static final int MAX_W = 100;
    static final int MIN_CH = 'A';
    static final int MAX_CH = 'Z';
    
    List<int[]> letterss;
    
    static class Entry implements Comparable<Entry> {
    	final String word;
    	final List<Integer> in;
    	
    	Entry(String word, List<Integer> in) {
    		this.word = word;
    		this.in = in;
    	}

		@Override
		public int compareTo(Entry that) {
			return that.in.size() - this.in.size();
		}
    }

    Queue<Entry> queue = new PriorityQueue<Entry>();
    Set<String> queued = new HashSet<String>();
    
	private void enqueue(String word, List<Integer> in) {
		if (queued.add(word)) {
			in = count(word, in);
			if (!in.isEmpty()) {
				queue.add(new Entry(word, in));
			}
		}
	}
	
	private List<Integer> count(String word, List<Integer> in) {
		int[] letters = letters(word);
		List<Integer> result = new ArrayList<Integer>();
		for (Integer i : in) {
			if (match(letters, letterss.get(i))) {
				result.add(i);
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
	
	Set<String> solve(int n, Set<String> words) {
		letterss = new ArrayList<int[]>();
        for (String word : words) {
        	letterss.add(letters(word));
        }
    
        List<Integer> all = new ArrayList<Integer>();
        for (int i = 0; i < words.size(); i++) {
        	all.add(i);
        }
        enqueue("", all);
        
        Set<String> result = new TreeSet<String>();
        int processed = 0;
        while (!queue.isEmpty() && result.size() < n) {
        	Entry entry = queue.remove();
			String word = entry.word;
        	if (word.length() > 0 && !words.contains(word)) {
        		result.add(word);
        	}
        	processed++;
        	
        	for (int i = 0; i < 26; i++) {
        		enqueue(word + (char) ('A' + i), entry.in);
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

        new funny_gk().run();

        in.close();
        out.close();
    }
}
