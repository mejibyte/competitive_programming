import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class doall {
	static final int MAX_N = 10000;
	static final int MAX_M = 10;
	static final int MAX_W = 80;
    static final int MIN_CH = 32;
    static final int MAX_CH = 126;
    static final Random random = new Random(7509843543298434535L);
    
    static PrintWriter out;
	
    static int test = 0;
    
    final String description;    
    List<List<String>> values = new ArrayList<List<String>>(); 
    
    public doall(String description) {
    	this.description = description;
	}

	public void write() {
        test++;
    
        System.out.println("Writing test " + test + " (" + description + ")");
        out.format("%02d %s\n", test, description);
        assert 0 <= values.size() && values.size() <= MAX_N;
        
        int m = values.get(0).size();
        for (List<String> row : values) {
        	assert row.size() == m;
        	for (String value : row) {
        		assert value.indexOf(',') == -1;
                for (char ch : value.toCharArray()) {
                    assert MIN_CH <= ch && ch <= MAX_CH;
                }
        	}
        }
        
        try {
            PrintWriter out = new PrintWriter(String.format("%02d", test));
            out.println(values.size() + " " + m);
            for (List<String> row : values) {
            	boolean first = true;
            	for (String value : row) {
            		if (first) {
            			first = false;
            		} else {
            			out.print(",");
            		}
            		out.print(value);
            	}
            	out.println();
            }
            out.close();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
    
    private doall hand(String... lines) {
    	for (String line : lines) {
    		values.add(Arrays.asList(line.split(",")));
    	}
    	return this;
    }
    
    private int random(int max) {
    	return random.nextInt(max);
    }
    
    private int random(int min, int max) {
    	return min + random(max - min);
    }
    
    private int random(int min, int max, int except) {
    	int value = random(min, max);
    	return value == except ? random(min, max, except) : value;
    }
	
	private char randomChar(int min, int max) {
		return (char) random(min, max, ',');
	}
	
    private String randomValue(int w) {
    	return randomValue(w, MAX_CH);
	}

	private String randomValue(int w, int maxChar) {
		StringBuilder sb = new StringBuilder();
		sb.append(randomChar(MIN_CH + 1, maxChar + 1));
    	for (int i = 0; i < w - 2; i++) {
    		sb.append(randomChar(MIN_CH, maxChar + 1));
    	}
    	if (w != 1) {
    		sb.append(randomChar(MIN_CH + 1, maxChar + 1));
    	}
		return sb.toString();
	}
	
    private String randomValue(String prefix, int w) {
    	final int tail = 2;
    	if (w <= tail) {
    		return randomValue(w);
    	}
    	return prefix.substring(0, w - tail) + randomValue(tail);
	}

	private List<String> randomLine(int m, int width, int maxChar) {
		int[] widths = new int[m];
		for (int i = 0; i < width - 2 * m + 1; i++) {
			widths[random(m)]++;
		}
		List<String> result = new ArrayList<String>();
		for (int w : widths) {
			result.add(randomValue(w + 1, maxChar));
		}
		return result;
	}

	private List<String> randomLine(String prefix, int m, int width) {
		int[] widths = new int[m];
		for (int i = 0; i < width - 2 * m + 1; i++) {
			widths[random(m)]++;
		}
		List<String> result = new ArrayList<String>();
		for (int w : widths) {
			result.add(randomValue(prefix, w + 1));
		}
		return result;
	}

	private doall randomLines(int n, int m, int width, int deltaWidth, int maxChar) {
		for (int i = 0; i < n; i++) {
    		values.add(randomLine(m, width - random(deltaWidth + 1), maxChar));
    	}
		return this;
	}

	private doall randomLines(int n, int m, int width, int deltaWidth) {
		return randomLines(n, m, width, deltaWidth, MAX_CH);
	}

	private doall randomLines(int n, int m, int width) {
		return randomLines(n, m, width, 0);
	}
	
	private doall randomLinesPrefix(int n, int m, int width, int deltaWidth) {
		String prefix = randomValue(width);
		for (int i = 0; i < n; i++) {
    		values.add(randomLine(prefix, m, width - random(deltaWidth + 1)));
    	}
		return this;
	}
	
	private doall randomLinesPrefix(int n, int m, int width) {
		return randomLinesPrefix(n, m, width, 0);
	}

	private void makeEqual(int r1, int r2, int c) {
		List<String> row1 = values.get(r1);
		List<String> row2 = values.get(r2);
		String value1 = row1.get(c);
		String value2 = row2.get(c);
		if (value1.length() < value2.length()) {
			row2.set(c, value1);
		} else {
			row1.set(c, value2);
		}
	}

	private doall hack() {
		int r1 = random(values.size());
		int r2 = random(0, values.size(), r1);
		int c1 = random(values.get(0).size());
		int c2 = random(0, values.get(0).size(), c1);
		makeEqual(r1, r2, c1);
		makeEqual(r1, r2, c2);
		return this;
	}
	
	private doall hack(int n) {
		for (int i = 0; i < n; i++) {
			hack();
		}
		return this;
	}

	public static void main(String[] args) throws FileNotFoundException {
		out = new PrintWriter("tests.lst");
		
		new doall("Example test 1").hand(
				"How to compete in ACM ICPC,Peter,peter@neerc.ifmo.ru",
				"How to win ACM ICPC,Michael,michael@neerc.ifmo.ru",
				"Notes from ACM ICPC champion,Michael,michael@neerc.ifmo.ru"
		).write();
		new doall("Example test 2").hand(
				"1,Peter,peter@neerc.ifmo.ru",
				"2,Michael,michael@neerc.ifmo.ru"
		).write();
		new doall("Manual test for concatenation without comma").hand(
				"a,bc",
				"ab,c"
		).write();
		new doall("3 rows, 5 columns").randomLines(3, 5, 10).write();
		new doall("5 rows, 3 columns, NO").randomLines(5, 3, 10).hack().write();
		new doall("Random test for concatenation without comma").randomLines(10, 3, 10, 3, 2 + MIN_CH).write();
		new doall("1 row, 1 column").randomLines(1, 1, 1).write();
		new doall("1 row, 2 columns").randomLines(1, 2, 10, 3).write();
		new doall("2 rows, 1 column").randomLines(2, 1, 10, 3).write();
		new doall("2 rows, 2 columns, YES").randomLines(2, 2, 10, 3).write();
		new doall("2 rows, 2 columns, NO").randomLines(2, 2, 10, 3).hack().write();
		
		new doall("10 rows, 2 columns, NO").randomLines(3, 5, 10).hack().write();
		new doall("10 rows, 9 columns, NO").randomLines(3, 5, 10).hack().write();
		
		new doall("47 rows, 9 columns, NO").randomLines(1000, 9, MAX_W).hack().write();
		new doall("100 rows, 9 columns, NO").randomLines(1000, 9, MAX_W).hack().write();
		new doall("637 rows, 8 columns, NO").randomLines(1000, 8, MAX_W).hack().write();
		new doall("1024 rows, 10 columns, YES").randomLines(1000, 10, MAX_W).hack().write();
		new doall("5073 rows, 10 columns, NO").randomLines(1000, 10, MAX_W).hack().write();
		
		new doall("max all, common prefix, NO").randomLinesPrefix(MAX_N, MAX_M, MAX_W).hack().write();
		new doall("max all, common prefix, YES").randomLinesPrefix(MAX_N, MAX_M, MAX_W).write();
		
		new doall("almost max rows, almost max columns, almost max width, common prefix, massive NO").randomLinesPrefix(MAX_N - 3, MAX_M - 1, MAX_W, 10).hack(MAX_N * MAX_M).write();
		new doall("almost max rows, almost max columns, almost max width, common prefix, NO").randomLinesPrefix(MAX_N - 3, MAX_M - 1, MAX_W, 10).hack().write();
		new doall("almost max rows, max columns, almost max width, common prefix, YES").randomLinesPrefix(MAX_N - 5, MAX_M, MAX_W, 10).write();

		random.setSeed(75098435432984345L);
		new doall("Large test for concatenation without comma").randomLines(MAX_N, MAX_M, MAX_W, 3, 6 + MIN_CH).write();
		
		new doall("max all, NO").randomLines(MAX_N, MAX_M, MAX_W).hack().write();
		random.setSeed(7509843543298434435L);
		new doall("max all, YES").randomLines(MAX_N, MAX_M, MAX_W).write();
		new doall("max all, common prefix, NO").randomLinesPrefix(MAX_N, MAX_M, MAX_W).hack().write();
		new doall("max all, common prefix, YES").randomLinesPrefix(MAX_N, MAX_M, MAX_W).write();
		
		out.close();
	}
}
