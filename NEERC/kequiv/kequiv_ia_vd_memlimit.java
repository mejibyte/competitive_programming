import java.io.*;
import java.util.*;

/**
 * @author Iskander Akishev
 * @author Vladimir Danilov
 */
public class kequiv_ia_vd_memlimit implements Runnable {

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
		EMPTY, FULL, NORMAL
	}

	final Map<NodeInfo, Integer> map = new HashMap<NodeInfo, Integer>();
	final NodeInfo EMPTY_INFO = new NodeInfo(null);
	final NodeInfo FULL_INFO = new NodeInfo(null);
	int EMPTY_CLASS_ID = getClassId(EMPTY_INFO);
	int FULL_CLASS_ID = getClassId(FULL_INFO);

	int getClassId(NodeInfo ni) {
		Integer res = map.get(ni);
		if (res == null) {
			map.put(ni, res = map.size());
		}
		return res;
	}

	class NodeInfo {
		int[] classes;

		NodeInfo(int[] classes) {
			this.classes = classes;
		}

		@Override
		public boolean equals(Object o) {
			NodeInfo nodeInfo = (NodeInfo)o;
			if (this == EMPTY_INFO || this == FULL_INFO) {
				return this == o;
			}
			if (o == EMPTY_INFO || o == FULL_INFO) {
				return false;
			}
			if (!Arrays.equals(classes, nodeInfo.classes)) return false;
			return true;
		}

		@Override
		public int hashCode() {
			return classes != null ? Arrays.hashCode(classes) : 0;
		}
	}

	class Node {
		Node[] children;
		Type type;
		int classId = -1;

		Node(Type type) {
			this.type = type;
		}

		public int getClassId() {
			if (classId == -1) {
				if (type == Type.EMPTY) {
					return EMPTY_CLASS_ID;
				} else if (type == Type.FULL) {
					return FULL_CLASS_ID;
				}
				int[] c = new int[10];
				for (int i = 0; i < 10; i++) {
					c[i] = children[i].getClassId();
				}
				classId = kequiv_ia_vd_memlimit.this.getClassId(new NodeInfo(c));
			}
			return classId;
		}
	}

	private void solve() throws Exception {
		in = new BufferedReader(new FileReader(FILE_NAME + ".in"));
		out = new PrintWriter(new File(FILE_NAME + ".out"));

		Node root = new Node(Type.EMPTY);
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
		if (r.type == Type.NORMAL) {
			if (r.children[a].getClassId() != r.children[b].getClassId()) {
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

	private void insert(Node root, String a, String b, int h) {
		if (h == M + 1) {
			root.type = Type.FULL;
			root.children = null;
			return;
		}
		if (charsOnly(a, h, '0') && charsOnly(b, h, '9')) {
			root.type = Type.FULL;
			root.children = null;
			return;
		}
		int ca = a.charAt(h) - '0';
		int cb = b.charAt(h) - '0';

		if (root.type == Type.EMPTY) {
			root.type = Type.NORMAL;
			root.children = new Node[10];
			for (int i = 0; i < 10; i++) {
				root.children[i] = new Node(Type.EMPTY);
			}
		}
		if (ca == cb) {
			insert(root.children[ca], a, b, h + 1);
		} else {
			insert(root.children[ca], a, generate(a, h, '9'), h + 1);
			for (int i = ca + 1; i < cb; i++) {
				root.children[i] = new Node(Type.FULL);
			}
			insert(root.children[cb], generate(b, h, '0'), b, h + 1);
		}
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
		new Thread(new kequiv_ia_vd_memlimit()).start();
	}
}