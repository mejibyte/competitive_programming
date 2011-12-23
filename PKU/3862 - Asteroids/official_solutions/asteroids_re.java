import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2009 Problem A: Asteroids
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class asteroids_re {
	static final boolean DEBUG = false;

	public static void main(String[] args) throws Exception {
		new asteroids_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	static class V3D {
		double x;
		double y;
		double z;

		V3D(Scanner in) {
			x = in.nextInt();
			y = in.nextInt();
			z = in.nextInt();
			in.nextLine();
			assert Math.abs(x) <= 10000;
			assert Math.abs(y) <= 10000;
			assert Math.abs(z) <= 10000;
		}

		@Override
		public String toString() {
			return "(" + x + "," + y + "," + z + ")";
		}

		boolean isZero() {
			return x == 0 && y == 0 && z == 0;
		}

		double length() {
			return Math.sqrt(x * x + y * y + z * z);
		}

		V3D(double x, double y, double z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}

		V3D add(V3D o) {
			return new V3D(x + o.x, y + o.y, z + o.z);
		}

		V3D sub(V3D o) {
			return new V3D(x - o.x, y - o.y, z - o.z);
		}

		V3D vec(V3D v) {
			return new V3D(
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x);
		}

		double dot(V3D v) {
			return x * v.x + y * v.y + z * v.z;
		}

		V3D mul(double f) {
			return new V3D(x * f, y * f, z * f);
		}

		V3D div(double f) {
			return new V3D(x / f, y / f, z / f);
		}
	}

	static class Face {
		// n.dot(v)  = d
		V3D n;
		double d;

		final List<V3D> verts = new ArrayList<V3D>();

		@Override
		public String toString() {
			return n.toString() + "," + d;
		}

		double side(V3D v) {
			return n.dot(v) - d;
		}

		double angleBetween(V3D u, V3D v) {
			V3D w = n.vec(u);
			double sin = w.dot(v) / w.length() / v.length();
			double cos = u.dot(v) / u.length() / v.length();
			return Math.atan2(sin, cos);			
		}

		public double dist(V3D v) {
			return Math.abs(side(v) / n.length());
		}
	}

	static class Polyhedra {
		int n;
		V3D[] verts;
		final List<Set<Face>> vfaces = new ArrayList<Set<Face>>();
		final List<Face> faces = new ArrayList<Face>();

		Polyhedra(Scanner in) {
			n = in.nextInt();
			in.nextLine();
			assert n >= 4 && n <= 60;
			verts = new V3D[n];
			for (int i = 0; i < n; i++) {
			    verts[i] = new V3D(in);
			}
		}

		void buildFaces() {
			for (int i = 0; i < n; i++) {
			    vfaces.add(new HashSet<Face>());
			}
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
				    for (int k = j + 1; k < n; k++) {
				        checkFace(i, j, k);
				    }
				}
			}
			if (DEBUG) {
				List<Integer> flen = new ArrayList<Integer>();
				for (Face face : faces) {
					flen.add(face.verts.size());
				}
				Collections.sort(flen, Collections.reverseOrder());
				System.out.println("FACES: " + flen);
			}
			assert faces.size() > 1; // non-degenerate!
			for (Set<Face> vface : vfaces) {
				assert !vface.isEmpty(); // convex! (each point on a face)
			}
		}

		void checkFace(int i, int j, int k) {
			if (!intersect(vfaces.get(i), vfaces.get(j), vfaces.get(k)).isEmpty())
				return; // already on a common face
			V3D w = verts[i];
			V3D u = verts[j].sub(w);
			V3D v = verts[k].sub(w);
			final Face f = new Face();
			f.n = u.vec(v);
			assert !f.n.isZero(); // no 3 points on a line
			f.d = f.side(w);
			int side = 0;
			List<Integer> indices = new ArrayList<Integer>();
			for (int t = 0; t < n; t++) {
				V3D tv = verts[t];
			    double tside = f.side(tv);
				if (tside < 0) {
					if (side > 0)
						return; // not a face
					side = -1;
				} else if (tside > 0) {
					if (side < 0)
						return; // not a face
					side = 1;
				} else {
					f.verts.add(tv);
					indices.add(t);
				}
			}
			if (side < 0) {
				// make sure that "inside" has a positive value of side
				f.n = f.n.mul(-1);
				f.d = -f.d;
			}
			faces.add(f);
			for (int t : indices) {
				vfaces.get(t).add(f);
			}
			// sort verices on a face by angle
			final V3D center = avg(f.verts);
			final V3D v0 = w.sub(center);
			assert Math.abs(f.side(center)) < 1; // just sanity check that center is on a plane
			Collections.sort(f.verts, new Comparator<V3D>() {
				public int compare(V3D o1, V3D o2) {
					return Double.compare(f.angleBetween(v0, o1.sub(center)), f.angleBetween(v0, o2.sub(center)));
				}
			});
		}

		double solve() {
			V3D v0 = avg(Arrays.asList(verts));
			V3D vsum = new V3D(0, 0, 0);
			double volume = 0;
			for (Face face : faces) {
				V3D v1 = face.verts.get(0);
				for (int i = 2; i < face.verts.size(); i++) {
					V3D v2 = face.verts.get(i - 1);
					V3D v3 = face.verts.get(i);
					double v = Math.abs(v1.sub(v0).vec(v2.sub(v0)).dot(v3.sub(v0)) / 6);
					vsum = vsum.add(avg(Arrays.asList(v0, v1, v2, v3)).mul(v));
					volume += v;
				}
			}
			V3D center = vsum.div(volume); // center of mass
			double min = Double.MAX_VALUE;
			for (Face face : faces) {
				min = Math.min(min, face.dist(center));
			}
			if (DEBUG) {
				System.out.println("Center: " + center + "; Volume: " + volume + "; Min:" + min);			
			}
			return min;
		}

		boolean containsAny(V3D[] verts) {
			for (V3D vert : verts) {
				if (contains(vert))
					return true;
			}
			return false;
		}

		boolean contains(V3D v) {
			for (Face face : faces) {
				if (face.side(v) < -1e-6)
					return false; // definitely outside
			}
			return true;
		}
	}

	static V3D avg(List<V3D> verts) {
		V3D sum = new V3D(0, 0, 0);
		for (V3D v : verts) {
			sum = sum.add(v);
		}
		return sum.div(verts.size());
	}

	static <T> Set<T> intersect(Set<T> a, Set<T> b, Set<T> c) {
		Set<T> result = new HashSet<T>(a);
		result.retainAll(b);
		result.retainAll(c);
		return result;
	}

	Polyhedra p;
	Polyhedra q;

	void read() throws Exception {
		Scanner in = new Scanner(System.in);
		in.useLocale(Locale.US);
		p = new Polyhedra(in);
		q = new Polyhedra(in);
		in.close();
	}

	double result;

	void solve() {
		p.buildFaces();
		q.buildFaces();
		assert !p.containsAny(q.verts);
		assert !q.containsAny(p.verts);
		result = p.solve() + q.solve();
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter(System.out);
		out.println(result);
		out.close();
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to veryfy 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a soulution source
	 * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public class Scanner {
		private final BufferedReader in;
		private String line = "";
		private int pos;
		private int lineNo;
		private boolean localeset;

		public Scanner(File source) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(source));
			nextLine();
		}
		
		public Scanner(InputStream stream) {
			in = new BufferedReader(new InputStreamReader(stream));
			nextLine();
		}

		public void close() {
			assert line == null : "Extra data at the end of file";
			try {
				in.close();
			} catch (IOException e) {
				throw new AssertionError("Failed to close with " + e);
			}
		}

		public void nextLine() {
			assert line != null : "EOF";
			assert pos == line.length() : "Extra characters on line " + lineNo;
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
		}

		public String next() {
			assert line != null : "EOF";
			assert line.length() > 0 : "Empty line " + lineNo;
			if (pos == 0)
				assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
			else {
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
				pos++;
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(0) > ' ' : "Line " + lineNo + " has double whitespace";
			}
			StringBuilder sb = new StringBuilder();
			while (pos < line.length() && line.charAt(pos) > ' ')
				sb.append(line.charAt(pos++));
			return sb.toString();
		}

		public int nextInt() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Integer.parseInt(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}

		public double nextDouble() {
			assert localeset : "Locale must be set with useLocale(Locale.US)";
			String s = next();
			assert s.length() == 1 || s.startsWith("0.") || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Double.parseDouble(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}

		public void useLocale(Locale locale) {
			assert locale == Locale.US;
			localeset = true;
		}
	}
}
