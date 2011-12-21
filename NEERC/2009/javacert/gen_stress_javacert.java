import java.util.*;

public class gen_stress_javacert {

	public static void main(String[] args) throws Exception {
		new gen_stress_javacert().go();
	}

	void go() throws Exception {
		stress();
	}

	int k;
	int n;
	int m;
	int[] p;

	static class Pair {
		int wi;
		int ni;

		Pair(int wi, int ni) {
			this.wi = wi;
			this.ni = ni;
		}

		@Override
		public String toString() {
			return wi + " " + ni + " " + (100.0*(ni - wi) / ni);
		}
	}

	int w;
	List<List<Pair>> llpall = new ArrayList<List<Pair>>();
	List<List<Pair>> llp = new ArrayList<List<Pair>>();
	int soldiff;
	int maxsteps;

	Random rnd = new Random();

	void stress() {
		n = 100;
		m = 10;
		wi = new int[m];
		ni = new int[m];
		p = new int[m];
		prebuildPairs();
		presortPairs();
		while (true) {
			checkOne();
		}
	}

	long timelimit;

	private void checkOne() {
		randomSol();
		selectPairs();
		soldiff = Integer.MAX_VALUE;
		long time = System.currentTimeMillis();
		timelimit = time + 10000L;
		int steps = find(0, 0, 0, Integer.MAX_VALUE, Integer.MIN_VALUE);
		time = System.currentTimeMillis() - time;
		assert soldiff < Integer.MAX_VALUE;
		if (steps > maxsteps) {
			System.out.println();
			System.out.printf("%d %d %d%n", k, n, m);
			for (int i = 0; i < m; i++) {
				System.out.printf("%d %d %d%n", p[i], wi[i], ni[i]);
			}
			System.out.printf("%d steps in %d ms%n", steps, time);
			maxsteps = steps;
		} else
			System.out.println(".");
	}

	int[] wi;
	int[] ni;

	private void randomSol() {
		int ns = 0;
		w = 0;
		int epr = rnd.nextInt(20);
		for (int i = 0; i < m; i++) {
			int rem = m - i - 1;
			ni[i] = rem == 0 ? n - ns :
				rnd.nextInt(10) > epr ? Math.min(n - ns - rem, Math.round(n / m)) :
				1 + rnd.nextInt(n - ns - rem);
			wi[i] = rnd.nextInt(ni[i] + 1);
			p[i] = (int)Math.round(100.0 * (ni[i] - wi[i]) / ni[i]);
			ns += ni[i];
			w += wi[i];
		}
		k = n - w;
	}



	private void selectPairs() {
		llp.clear();
		for (int i = 0; i < m; i++) {
			llp.add(llpall.get(p[i]));
		}
	}

	private void prebuildPairs() {
		for (int i = 0; i <= n; i++) {
			llpall.add(new ArrayList<Pair>());
		}
		for (int ni = 1; ni <= n; ni++) {
			for (int wi = 0; wi <= ni; wi++) {
				int ppp = 100 * (ni - wi);
				int pp = (2 * ppp + ni) / (2 * ni);
				if (2 * ppp % ni == 0 && 2 * ppp / ni % 2 == 1 && pp % 2 == 1)
					pp--;
				llpall.get(pp).add(new Pair(wi, ni));
			}
		}
	}

	private void presortPairs() {
		final double mid = n / m;
		for (int i = 0; i <= n; i++) {
		    Collections.sort(llpall.get(i), new Comparator<Pair>() {
			    public int compare(Pair p1, Pair p2) {
				    double d1 = Math.abs(p1.ni - mid);
				    double d2 = Math.abs(p2.ni - mid);
				    return Double.compare(d1, d2);
			    }
		    });
		}
	}

	int find(int i, int ws, int ns, int minni, int maxni) {
		if (ns > n || ws > w)
			return 1;
		int diff = maxni - minni;
		if (diff >= soldiff)
			return 1;
		if (i == m) {
			if (ns < n || ws < w)
				return 1;
			soldiff = diff;
			return 1;
		}
		if (System.currentTimeMillis() > timelimit)
			return 1;
		int res = 0;
		for (Pair p : llp.get(i)) {
			res += find(i + 1, ws + p.wi, ns + p.ni, Math.min(minni, p.ni), Math.max(maxni, p.ni));
		}
		return res;
	}
}