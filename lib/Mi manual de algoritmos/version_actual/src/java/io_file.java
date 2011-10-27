import java.io.*;
import java.util.*;
public class BooleanTree {
	public static void main(String[] args) throws FileNotFoundException {
		System.setIn(new FileInputStream("tree.in"));
		System.setOut(new PrintStream("tree.out"));
		Scanner reader = new Scanner(System.in);
		N = reader.nextInt();
		for (int c = 1; c <= N; ++c) {
			int res = 100;
			if (res < 1000)
				System.out.println("Case #" + c + ": " + res);
			else
				System.out.println("Case #" + c + ": IMPOSSIBLE");
		}
	}
}
