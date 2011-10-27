import java.io.*;
import java.util.*;

/**
 * @author Iskander Akishev
 * @author Vladimir Danilov
 */
public class kequiv_ia_vd implements Runnable {

	private static final String FILE_NAME = "kequiv";

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

	enum Type {
		FULL, NORMAL
	}

	private final Node FULL_NODE = new Node(Type.FULL);

	class Node {
		Node[] children;
		Type type;
		int classId = -1;

		Node(Type type) {
			this.type = type;
			children = new Node[10];
		}

		@Override
		public boolean equals(Object o) {
			return hashCode() == o.hashCode();
		}

		@Override
		public int hashCode() {
			if (classId == -1) {
				if (type == Type.FULL) {
					return -12354125;
				}
				classId = children != null ? Arrays.hashCode(children) : 0;
			}
			return classId;
		}

		public int getClassId() {
			return hashCode();
		}
	}

	private void solve() throws Exception {
		in = new BufferedReader(new FileReader(FILE_NAME + ".in"));
		out = new PrintWriter(new File(FILE_NAME + ".out"));

		Node root = new Node(Type.NORMAL);
		int n = Integer.parseInt(in.readLine());
		for (int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			String a = readNumber(st);
			String b = readNumber(st);
			insert(root, a, b, 0);
		}

		int[] col = new int[10];
		for (int i = 1; i < 10; i++) {
			col[i] = i;
		}
		for (int i = 1; i < 10; i++) {
			for (int j = i + 1; j < 10; j++) {
				if (check(root, i, j)) {
					col[j] = col[i] = Math.min(col[j], col[i]);
				}
			}
		}

		for (int i = 1; i < 10; i++) {
			if (col[i] == i) {
				for (int j = 0; j < 10; j++) {
					if (col[j] == col[i]) {
						out.print(j);
					}
				}
				out.println();
			}
		}

		in.close();
		out.close();
	}

	private boolean check(Node r, int a, int b) {
		if (r == null) {
			return true;
		}
		if (r.type == Type.NORMAL) {
			if (r.children[a] == null || r.children[b] == null) {
				if (r.children[a] != r.children[b]) {
					return false;
				}
			} else if (r.children[a].getClassId() != r.children[b].getClassId()) {
				return false;
			}
			for (Node ch : r.children) {
				if (!check(ch, a, b)) {
					return false;
				}
			}
		}
		return true;
	}

	private Node insert(Node root, String a, String b, int h) {
		if (root == null) {
			root = new Node(Type.NORMAL);
		}

		if (h == M + 1) {
			return FULL_NODE;
		}
		if (charsOnly(a, h, '0') && charsOnly(b, h, '9')) {
			return FULL_NODE;
		}
		int ca = a.charAt(h) - '0';
		int cb = b.charAt(h) - '0';

		if (ca == cb) {
			root.children[ca] = insert(root.children[ca], a, b, h + 1);
		} else {
			root.children[ca] = insert(root.children[ca], a, generate(a, h, '9'), h + 1);
			for (int i = ca + 1; i < cb; i++) {
				root.children[i] = FULL_NODE;
			}
			root.children[cb] = insert(root.children[cb], generate(b, h, '0'), b, h + 1);
		}

		return root;
	}

	private String generate(String s, int h, char c) {
		return s.substring(0, h + 1) + chars[c - '0'][M - (h + 1)];
	}

	private boolean charsOnly(String s, int h, char c) {
		for (int i = h; i < M; i++) {
			if (s.charAt(i) != c)
				return false;
		}
		return true;
	}

	final static int M = 19;
	final static String[][] chars;
	static {
		chars = new String[10][M + 1];
		for (int i = 0; i < 10; i++) {
			chars[i][0] = "";
			for (int j = 1; j < M + 1; j++) {
				chars[i][j] = chars[i][j - 1] + i;
			}
		}
	}

	private String readNumber(StringTokenizer st) {
		String res = st.nextToken();
		return chars[0][M - res.length()] + res;
	}

	public static void main(String[] args) {
		new Thread(new kequiv_ia_vd()).start();
	}
}