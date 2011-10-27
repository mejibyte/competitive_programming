import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.ListIterator;
import java.util.Random;
import java.util.Set;

public class doall {
	static final int MAX_N = 100;
	static final int MAX_M = 1000;
	static final int MAX_W = 100;
    static final int MIN_CH = 'A';
    static final int MAX_CH = 'Z';
    static final Random random = new Random(1932840934230493244L);
    
    static PrintWriter out;
	
    static int test = 0;
    
    String description;
    final int n;
    List<String> words = new ArrayList<String>(); 
    Set<String> wordsSet = new HashSet<String>(); 
    
    public doall(String description, int n) {
    	this.description = description;
    	this.n = n;
	}

    public doall(int n) {
    	this("", n);
	}

	public void write() {
        test++;
    
        System.out.println("Writing test " + test + " (" + description + ")");
        out.format("%02d %s\n", test, description);
        
        assert 1 <= words.size() && words.size() <= MAX_M;
        
        assert new HashSet<String>(words).size() == words.size();
        
        for (String word : words) {
        	assert 1 <= word.length() && word.length() <= MAX_W;
            for (char ch : word.toCharArray()) {
                assert MIN_CH <= ch && ch <= MAX_CH : word;
            }
        }
        
        try {
            PrintWriter out = new PrintWriter(String.format("%02d", test));
            out.println(n + " " + words.size());
            for (String word : words) {
            	out.println(word);
            }
            out.close();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
	
    static int random(int max) {
    	return random.nextInt(max);
    }
    
    static int random(int min, int max) {
    	return min + random(max - min);
    }
    
	static char randomChar(int min, int max) {
		return (char) random(min, max);
	}	
	
	static String randomWord(int w, int maxChar) {
		StringBuilder sb = new StringBuilder();
    	for (int i = 0; i < w; i++) {
    		sb.append(randomChar(MIN_CH, maxChar + 1));
    	}
    	return sb.toString();
	}
    
    private doall hand(String... words) {
    	description = Arrays.toString(words);
    	this.words.addAll(Arrays.asList(words));
    	this.wordsSet.addAll(Arrays.asList(words));
    	return this;
    }

	private void addWord(String word) {
		if (wordsSet.add(word)) {
			words.add(word);
		}
	}

	private doall repeat(int m, String ... words) {
		for (String word : words) {
			addDescription("1.." + m + "*" + word + " ");
			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < m; i++) {
				sb.append(word);
				addWord(sb.toString());
			}
		}
		return this;
	}

	private doall randomWords(int m, int w, int dw, int maxChar) {
		addDescription(m + " random " + (dw == 0 ? "" : (w - dw) + "..") + w + "-letter words"); 
		for (int i = 0; i < m; i++) {
			addWord(randomWord(w - random(dw + 1), maxChar));
		}
		return this;
	}

	private String addLetters(String letters, String word) {
		int i = 0;
		int j = 0;
		StringBuilder sb = new StringBuilder();
		while (i < letters.length() && j < word.length()) {
			sb.append(random(2) == 0 ? letters.charAt(i++) : word.charAt(j++));
		}
		while (i < letters.length()) {
			sb.append(letters.charAt(i++));
		}
		while (j < word.length()) {
			sb.append(word.charAt(j++));
		}
		return sb.toString();
	}

	private doall addLetters(String letters) {
		addDescription(" with " + letters.length() + " common letters"); 
		for (ListIterator<String> i = words.listIterator(); i.hasNext(); ) {
			i.set(addLetters(letters, i.next()));
		}
		wordsSet.clear();
		wordsSet.addAll(words);
		return this;
	}

	private doall shuffle() {
		Collections.shuffle(words, random);
		return this;
	}

	private doall sequences(int m, int w) {
		for (int i = 0; i < m; i++) {
			repeat(w, "" + (char) ('A' + i));
		}
		return this;
	}

	private doall addDescription(String string) {
		description += string;
		return this;
	}

	private doall addSmallWords() {
		int c = Math.min(MAX_M - words.size(), words.size() / 10);
		addDescription(", " + c + " 2-letter words added");
		for (int i = 0; i < 26 && c > 0; i++) {
			for (int j = 0; j < 26 && c > 0; j++) {
				addWord((char) ('A' + i) + "" + (char) ('A' + j));
				c--;
			}
		}
		return this;
	}

	private doall removeRandom(int m) {
		addDescription(", " + m + " random words removed");
		for (int i = 0; i < m; i++) {
			String word = words.remove(random(words.size()));
			wordsSet.remove(word);
		}
		return this;
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		out = new PrintWriter("tests.lst");
		
		new doall("Example test", 3).hand("A", "ACM", "ICPC", "CONTEST", "NEERC").write();
		new doall(2).hand("A", "AB", "ABA").write();
		new doall("A, AA, AAA", 2).repeat(3, "A").write();
		
		new doall(10).randomWords(10, 3, 0, MIN_CH + 2).addDescription(" of ABC").write();
		new doall(10).randomWords(10, 3, 0, MAX_CH).write();
		new doall(10).randomWords(10, 10, 0, MAX_CH).write();
		
		new doall(MAX_N / 10).randomWords(MAX_M / 100, 10, 3, MAX_CH).removeRandom(1).addSmallWords().addLetters("RVL").write();
		new doall(10).sequences(25, 3).removeRandom(3).addSmallWords().shuffle().write();
		new doall(MAX_N / 10).repeat(Math.min(MAX_W / 4, MAX_M), "AB", "CD").removeRandom(3).addSmallWords().shuffle().write();
		
		new doall(MAX_N).sequences(MAX_M / MAX_W, MAX_W).removeRandom(5).shuffle().write();
		new doall(MAX_N).repeat(Math.min(MAX_W / 2, MAX_M), "AB").removeRandom(10).shuffle().write();		
		new doall(MAX_N).repeat(Math.min(MAX_W / 10, MAX_M), "FD", "PQR").removeRandom(2).shuffle().write();		
		
		new doall(MAX_N).repeat(Math.min(MAX_W, MAX_M), "C").removeRandom(MAX_W / 10).shuffle().write();		
		new doall(MAX_N / 10).randomWords(MAX_M / 10, 10, 3, MAX_CH).addLetters("QQQ").addSmallWords().write();
		new doall(MAX_N / 2 - 17).randomWords(MAX_M / 3, MAX_W, 10, MAX_CH).addSmallWords().write();
		new doall(MAX_N / 2 - 3).randomWords(MAX_M / 2, MAX_W, 0, MAX_CH).addSmallWords().write();
		
		new doall(MAX_N).randomWords(MAX_M * 9 / 10, MAX_W - 3, 10, MAX_CH).addLetters("GFK").write();
		new doall(MAX_N).randomWords(MAX_M, MAX_W - 3, 10, MAX_CH).addLetters("AAA").write();
		new doall(MAX_N).randomWords(MAX_M, MAX_W - 3, 10, MAX_CH).addLetters("QZF").write();
		new doall("Random almost max test: ", MAX_N).randomWords(MAX_M, MAX_W, 10, MAX_CH).write();
		new doall("Random max test: ", MAX_N).randomWords(MAX_M, MAX_W, 0, MAX_CH).write();
//		
//		random.setSeed(3409543954354545522L);
//		new doall("Random max test with max answer: ", MAX_N).randomWords(MAX_M, MAX_W, 0, MAX_CH - 10).write();
//		
//		for (int i = 0; i < 1000; i++) {
//			random.setSeed(3409543954354545522L + i);
//			doall test = new doall("Random max test with max answer", MAX_N).randomWords(MAX_M, MAX_W, 0, MAX_CH - 10);
//			funny_gk funnyGk = new funny_gk();
//			funnyGk.solve(MAX_N, new HashSet<String>(test.words));
//			System.out.println(i + " " + funnyGk.c);
//			if (funnyGk.c == MAX_N * MAX_M) {
//				break;
////				System.out.println(3409543954354545517L + i);
//			}
//		}
		out.close();
	}
}
