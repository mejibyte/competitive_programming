import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class database_gk_generic {
    static final int MAX_N = 10000;
    static final int MAX_M = 100;
    
	static interface Type<V> {
		Pair<Integer, Integer> solve(V[] col1, V[] col2);
	};

	static interface Generator<V, T> {
		T key(V value1, V value2);
	}

	static class HashType<V, T> implements Type<V> {
		Generator<V, T> generator;

		public HashType(Generator<V, T> generator) {
			this.generator = generator;
		}

		@Override
		public Pair<Integer, Integer> solve(V[] col1, V[] col2) {
			Map<T, Integer> map = new HashMap<T, Integer>();
			for (int r1 = 0; r1 < col1.length; r1++) {
				Integer r2 = map.put(generator.key(col1[r1], col2[r1]), r1);
				if (r2 != null) {
					return new Pair<Integer, Integer>(r1, r2);
				}
			}
			return null;
		}
	}

	static class TreeType<V, T> implements Type<V> {
		Generator<V, T> generator;

		public TreeType(Generator<V, T> generator) {
			this.generator = generator;
		}

		@Override
		public Pair<Integer, Integer> solve(V[] col1, V[] col2) {
			Map<T, Integer> map = new TreeMap<T, Integer>();
			for (int r1 = 0; r1 < col1.length; r1++) {
				Integer r2 = map.put(generator.key(col1[r1], col2[r1]), r1);
				if (r2 != null) {
					return new Pair<Integer, Integer>(r1, r2);
				}
			}
			return null;
		}
	}

	static class SortType<V, T extends Comparable<T>> implements Type<V> {
		Generator<V, T> generator;

		public SortType(Generator<V, T> generator) {
			this.generator = generator;
		}

		@Override
		public Pair<Integer, Integer> solve(V[] col1, V[] col2) {
			List<Pair<T, Integer>> pairs = new ArrayList<Pair<T, Integer>>();
			for (int r = 0; r < col1.length; r++) {
				pairs.add(new Pair<T, Integer>(generator.key(col1[r], col2[r]), r));
			}
			Collections.sort(pairs);
			for (int i = 0; i < pairs.size() - 1; i++) {
				if (pairs.get(i).f.compareTo(pairs.get(i + 1).f) == 0) {
					return new Pair<Integer, Integer>(pairs.get(i).s, pairs.get(i + 1).s);
				}
			}
			return null;
		}
	}

	static final Generator<String, String> CONCAT_GENERATOR = new Generator<String, String>() {
		@Override
		public String key(String value1, String value2) {
			return value1 + "," + value2;
		}
	};

	static final Generator<String, String> CONCAT_ERROR_GENERATOR = new Generator<String, String>() {
		@Override
		public String key(String value1, String value2) {
			return value1 + value2;
		}
	};

	static final Generator<Object, Pair<Object, Object>> PAIR_GENERATOR = new Generator<Object, Pair<Object, Object>>() {
		@Override
		public Pair<Object, Object> key(Object value1, Object value2) {
			return new Pair<Object, Object>(value1, value2);
		}
	};

	static final Type<String> HASH_CONCAT = new HashType<String, String>(CONCAT_GENERATOR);
	static final Type<String> HASH_CONCAT_ERROR = new HashType<String, String>(CONCAT_ERROR_GENERATOR);
	static final Type<?> HASH_PAIR = new HashType<Object, Pair<Object, Object>>(PAIR_GENERATOR);
	static final Type<?> TREE_PAIR = new TreeType<Object, Pair<Object, Object>>(PAIR_GENERATOR);
	static final Type<String> SORT_CONCAT = new SortType<String, String>(CONCAT_GENERATOR);
	static final Type<?> SORT_PAIR = new SortType<Object, Pair<Object, Object>>(PAIR_GENERATOR);
	static final Type<?> HASH_NESTED = new Type<Object>(){
		@Override
		public Pair<Integer, Integer> solve(Object[] col1, Object[] col2) {
			Map<Object, Map<Object, Integer>> outter = new HashMap<Object, Map<Object, Integer>>();
			for (int r1 = 0; r1 < col1.length; r1++) {
				Map<Object, Integer> inner = outter.get(col1[r1]);
				if (inner == null) {
					inner = new HashMap<Object, Integer>();
					outter.put(col1[r1], inner);
				}
				Integer r2 = inner.put(col2[r1], r1);
				if (r2 != null) {
					return new Pair<Integer, Integer>(r1, r2);
				}
			}
			return null;
		}
	};
	static final Type<Integer> PACK_LONG = new Type<Integer>(){
		@Override
		public Pair<Integer, Integer> solve(Integer[] col1, Integer[] col2) {
			int n = col1.length;
			long[] pairs = new long[n];
			for (int r = 0; r < n; r++) {
				pairs[r] = ((long) col1[r] * MAX_N * MAX_M + col2[r]) * n + r;
			}
			Arrays.sort(pairs);
			for (int i = 0; i < n - 1; i++) {
				if (pairs[i] / n == pairs[i + 1] / n) {
					return new Pair<Integer, Integer>((int) (pairs[i] % n), (int) (pairs[i + 1] % n));
				}
			}
			return null;
		}
	};

	static Scanner in;
	static PrintWriter out;

	final Type<?> type;
	final boolean compact;

	int n;
	int m;

	database_gk_generic(Type<?> type, boolean compact) {
		this.type = type;
		this.compact = compact;
	}

	static class Pair<F, S> implements Comparable<Pair<F, S>> {
		final F f;
		final S s;

		Pair(F f, S s) {
			this.f = f;
			this.s = s;
		}

		@Override
		@SuppressWarnings("unchecked")
		public int compareTo(Pair<F, S> that) {
			int f = ((Comparable) this.f).compareTo(that.f);
			return f != 0 ? f : ((Comparable) this.s).compareTo(that.s);
		}

		@Override
		public boolean equals(Object o) {
			@SuppressWarnings("unchecked")
			Pair<F, S> that = (Pair<F, S>) o;
			return this.f.equals(that.f) && this.s.equals(that.s);
		}

		@Override
		public int hashCode() {
			return f.hashCode() * 31 + s.hashCode();
		}
	}

	public void run() {
		n = in.nextInt();
		m = in.nextInt();
		in.nextLine();

		String[][] values = new String[m][n];
		for (int i = 0; i < n; i++) {
			String[] parts = in.nextLine().split(",");
			for (int j = 0; j < m; j++) {
				values[j][i] = parts[j];
			}
		}

		if (compact) {
			Map<String, Integer> intern = new HashMap<String, Integer>();
			Integer[][] indices = new Integer[m][n];
			int maxIndex = 0;
			for (int j = 0; j < m; j++) {
				for (int i = 0; i < n; i++) {
					String value = values[j][i];
					Integer index = intern.get(value);
					if (index == null) {
						index = maxIndex++;
						intern.put(value, index);
					}
					indices[j][i] = index;
				}
			}

			@SuppressWarnings("unchecked")
			Type<Integer> type = (Type<Integer>) this.type;
			for (int c1 = 0; c1 < m; c1++) {
				for (int c2 = c1 + 1; c2 < m; c2++) {
					Pair<Integer, Integer> result = type.solve(indices[c1], indices[c2]);
					if (result != null) {
						out.println("NO");
						out.println(((int) result.f + 1) + " "  + ((int) result.s + 1));
						out.println((c1 + 1) + " "  + (c2 + 1));
						return;
					}
				}
			}
		} else {
			@SuppressWarnings("unchecked")
			Type<String> type = (Type<String>) this.type;
			for (int c1 = 0; c1 < m; c1++) {
				for (int c2 = c1 + 1; c2 < m; c2++) {
					Pair<Integer, Integer> result = type.solve(values[c1], values[c2]);
					if (result != null) {
						out.println("NO");
						out.println(((int) result.f + 1) + " "  + ((int) result.s + 1));
						out.println((c1 + 1) + " "  + (c2 + 1));
						return;
					}
				}
			}
		}
		out.println("YES");
	}

	static void run(Type<?> type, boolean compact) throws FileNotFoundException {
		in = new Scanner(new File("database.in"));
		out = new PrintWriter("database.out");

		new database_gk_generic(type, compact).run();

		in.close();
		out.close();
	}
}
