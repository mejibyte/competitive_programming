import java.io.*;
import java.util.*;

public class ExclusiveTestsGen implements Runnable {
	private static final int MAX_N = 100;

	public static void main(String[] args) {
		testNum = 6;
		new Thread(new ExclusiveTestsGen()).start();
	}

	PrintWriter out;

	Random r = new Random(734298743);

	static int testNum;

	static String getName(int i) {
		return i / 10 + "" + i % 10;
	}

	void open() {
		try {
			System.out.println("Generating test " + testNum);
			out = new PrintWriter(getName(testNum));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			System.exit(-1);
		}
	}

	void close() {
		out.close();
		testNum++;
	}

	private void randomTest() {
		open();
		int n = 1 + r.nextInt(100);
		out.println(n);
		for (int i = 0; i < n; i++) {
			int u = r.nextInt('Z' - 'L' + 1);
			int v = r.nextInt('Z' - 'L' + 1);
			while (u == v) {
				v = r.nextInt('Z' - 'L' + 1);
			}
			out.println(((char) ('L' + u)) + " " + ((char) ('L' + v)));
		}
		close();
	}
	
	private void randomSmallTest() {
		open();
		int n = 1 + r.nextInt(15);
		out.println(n);
		for (int i = 0; i < n; i++) {
			int u = r.nextInt('S' - 'L' + 1);
			int v = r.nextInt('S' - 'L' + 1);
			while (u == v) {
				v = r.nextInt('S' - 'L' + 1);
			}
			out.println(((char) ('L' + u)) + " " + ((char) ('L' + v)));
		}
		close();
	}

	private void fullTest(int size) {
		open();
		int n = Math.min(MAX_N, size * (size - 1) / 2);
		out.println(n);
		outer:
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				out.println(((char) ('L' + i)) + " " + ((char) ('L' + j)));
				n--;
				if (n == 0) {
					break outer;
				}
			}
		}
		close();
	}

	private void extendedFullTest(int size, int n) {
		open();
		out.println(n);
		outer:
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				out.println(((char) ('L' + i)) + " " + ((char) ('L' + j)));
				n--;
				if (n == 0) {
					break outer;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			int u = r.nextInt('S' - 'L' + 1);
			int v = r.nextInt('S' - 'L' + 1);
			while (u == v) {
				v = r.nextInt('S' - 'L' + 1);
			}
			out.println(((char) ('L' + u)) + " " + ((char) ('L' + v)));
		}
		close();
	}

	public void generateTests() {
		for (int i = 0; i < 10; i++) {
			randomSmallTest();
		}
		for (int i = 4; i <= 15; i++) {
			fullTest(i);
		}
		for (int i = 4; i <= 14; i++) {
			extendedFullTest(i, MAX_N);
		}
		for (int i = 0; i < 22; i++) {
			randomTest();
		}
	}

	public void run() {
		try {
			generateTests();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(-1);
		}
	}
}
