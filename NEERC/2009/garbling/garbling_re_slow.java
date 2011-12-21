import java.util.*;
import java.io.*;

/**
 * This solutions simulates the game until the whole map state loops.
 * then it figures out repeating part. 
 *
 * @author Roman Elizarov
 */
public class garbling_re_slow {
	private static final boolean FULL_SIMULATION = false; // VERY SLOW MODE

	static class Field implements Cloneable {
		int[][] a;

		Field(int r, int c) {
			a = new int[r][c];
			int n = 0;
			for (int i = 0; i < r; i++) {
			    for (int j = 0; j < c; j++) {
			        a[i][j] = ++n;
			    }
			}
		}

		void garbleLeft(int i, int j) {
			int t = a[i][j];
			a[i][j] = a[i][j + 1];
			a[i][j + 1] = a[i + 1][j + 1];
			a[i + 1][j + 1] = a[i + 1][j];
			a[i + 1][j] = t;
		}

		void garbleRight(int i, int j) {
			int t = a[i][j];
			a[i][j] = a[i + 1][j];
			a[i + 1][j] = a[i + 1][j + 1];
			a[i + 1][j + 1] = a[i][j + 1];
			a[i][j + 1] = t;
		}

		@Override
		public Field clone()  {
			try {
				Field f = (Field)super.clone();
				f.a = f.a.clone();
				for (int i = 0; i < f.a.length; i++) {
				    f.a[i] = f.a[i].clone();    
				}
				return f;
			} catch (CloneNotSupportedException e) {
			    throw new AssertionError(e);
			}
		}

		@Override
		public boolean equals(Object obj) {
			if (!(obj instanceof Field))
				return false;
			int[][] b = ((Field)obj).a;
			for (int i = 0; i < a.length; i++) {
				if (!Arrays.equals(a[i], b[i]))
					return false;
			}
			return true;
		}

		@Override
		public int hashCode() {
			int result = 0;
			for (int[] row : a) {
				result = result * 997 + Arrays.hashCode(row);
			}
			return result;
		}
	}

	static class State implements Cloneable {
		long turns;
		long[] written;

		State(int rc) {
			written = new long[rc];
		}

		@Override
		public State clone()  {
			try {
				State s = (State)super.clone();
				s.written = s.written.clone();
				return s;
			} catch (CloneNotSupportedException e) {
			    throw new AssertionError(e);
			}
		}
	}

	int r;
	int c;
	long n;
	char[][] map;

	public static void main(String[] args) throws FileNotFoundException {
		new garbling_re_slow().go();
	}

	void go() throws FileNotFoundException {
		read();
		State s = solve();
		write(s);
//		stressTest();
	}

	private void read() throws FileNotFoundException {
		Scanner in = new Scanner(new File("garbling.in"));
		r = in.nextInt();
		c = in.nextInt();
		n = in.nextLong();
		map = new char[r - 1][];
		for (int i = 0; i < r - 1; i++) {
			map[i] = in.next().toCharArray();
		}
		in.close();
	}

	private void write(State s) throws FileNotFoundException {
		PrintWriter out = new PrintWriter(new File("garbling.out"));
		for (int i = 0; i < r * c; i++) {
			out.println(s.written[i]);
		}
		out.close();
	}
	
//	private void stressTest() {
//		Random rnd = new Random(1);
//		while (true) {
//			r = rnd.nextInt(11) + 90;
//			c = rnd.nextInt(11) + 90;
//			map = new char[r - 1][c - 1];
//			for (int i = 0; i < r - 1; i++) {
//				for (int j = 0; j < c - 1; j++) {
//					int t = rnd.nextInt(4);
//					map[i][j] = t <= 1 ? 'N' : t == 2 ? 'L' : 'R';
//				}
//			}
//			solve();
//		}
//	}

	State solve() {
		int rc = r * c;
		Field f = new Field(r, c);
		State s = new State(rc);
		Map<Field, State> fields = new HashMap<Field, State>();
		long time = System.currentTimeMillis();
		while (FULL_SIMULATION || !fields.keySet().contains(f)) {
			if (!FULL_SIMULATION)
				fields.put(f.clone(), s.clone());
			if (garbleFieldOnce(f, s))
				break;
		}
		System.out.printf("%d turns on %d x %d field in %d ms%n",
			s.turns, r, c, System.currentTimeMillis() - time);
		if (s.turns >= n) 
			return s;
		// whole field looped -- fastforward repeating part
		State p = fields.get(f);
		long stretch = s.turns - p.turns;
		long times = (n - s.turns) / stretch;
		s.turns += times * stretch;
		for (int i = 0; i < rc; i++) {
			s.written[i] += times * (s.written[i] - p.written[i]);
		}
		System.out.printf("Fast forward %d x %d turns%n", times, stretch);
		// finish remaining steps
		while (true) {
			if (garbleFieldOnce(f, s))
				break;
		}
		return s;
	}

	private boolean garbleFieldOnce(Field f, State s) {
		for (int i = 0; i < r - 1; i++) {
		    for (int j = 0; j < c - 1; j++) {
			    if (s.turns >= n)
			        return true;
			    s.turns++;
			    s.written[f.a[i][j] - 1]++;
			    switch (map[i][j]) {
			    case 'L': f.garbleLeft(i, j); break;
			    case 'R': f.garbleRight(i, j); break;
			    }
		    }
		}
		return false;
	}

//	private String showMap() {
//		StringBuilder sb = new StringBuilder();
//		sb.append('|');
//		for (char[] row : map) {
//			sb.append(row);
//			sb.append('|');
//		}
//		return sb.toString();
//	}
}
