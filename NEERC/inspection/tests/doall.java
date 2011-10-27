import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.util.*;

public class doall {

    int tn = 0;
    private static final int MAXN = 100;

    void printTest(String comment, List<List<Integer>> edges) throws FileNotFoundException {
        tn++;
        System.out.println("Test " + String.format("%02d", tn) + ": " + comment);
        PrintWriter out = new PrintWriter(String.format("%02d", tn));
        out.println(edges.size());
        for (List<Integer> list : edges) {
            out.print(list.size());
            for (int i : list) {
                out.print(" ");
                out.print(i + 1);
            }
            out.println();
        }
        out.close();
    }

    Random random = new Random(124234234);

    void printShuffledTest(String comment, int[][] a) throws FileNotFoundException {
        int n = a.length;
        List<Integer> p = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) p.add(i);
        Collections.shuffle(p, random);
        List<List<Integer>> e = new ArrayList<List<Integer>>();
        for (int i = 0; i < n; i++) {
            List<Integer> list = new ArrayList<Integer>();
            for (int j = 0; j < n; j++) {
                if (a[p.get(i)][p.get(j)] > 0) {
                    list.add(j);
                }
            }
            Collections.shuffle(list, random);
            e.add(list);
        }
        printTest(comment, e);
    }

    public static void main(String[] args) {
        try {
            new doall().run();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private void run() throws Exception {
        printTest("Sample test",
                Arrays.asList(
                        Arrays.asList(2),
                        Arrays.asList(6),
                        Arrays.asList(3, 4),
                        Arrays.asList(7),
                        Arrays.asList(7),
                        Arrays.<Integer>asList(),
                        Arrays.asList(5, 4),
                        Arrays.<Integer>asList()
                )
        );
        printShuffledTest("Square",
                new int[][]
                        {{0, 1, 1, 0},
                                {0, 0, 0, 1},
                                {0, 0, 0, 1},
                                {0, 0, 0, 0}}
        );
        printShuffledTest("Full 4 graph",
                new int[][]
                        {{0, 1, 1, 1},
                                {0, 0, 1, 1},
                                {0, 0, 0, 1},
                                {0, 0, 0, 0}}
        );
        printShuffledTest("Square and two edges",
                new int[][]
                        {{0, 1, 1, 0, 0, 0},
                                {0, 0, 0, 1, 0, 0},
                                {0, 0, 0, 1, 0, 0},
                                {0, 0, 0, 0, 1, 0},
                                {0, 0, 0, 0, 0, 0},
                                {1, 0, 0, 0, 0, 0}}
        );
        printShuffledTest("One edge",
                new int[][]
                        {{0, 1},
                                {0, 0}}
        );

        for (int i = 0; i < 10; i++) {
            int n = 5 + random.nextInt(10);
            int[][] a = new int[n][n];
            int m = random.nextInt(n * (n - 1) / 2 + 1);
            for (int k = 0; k < m; k++) {
                int x, y;
                do {
                    x = random.nextInt(n);
                    y = random.nextInt(n);
                } while (y <= x || a[x][y] > 0);
                a[x][y] = 1;
            }
            for (int j = 0; j < n; j++) {
                boolean ok = false;
                for (int k = 0; k < n; k++) {
                    if (a[j][k] == 1 || a[k][j] == 1) ok = true;
                }
                if (!ok) a[j][(j + 1) % n] = 1;
            }
            printShuffledTest("Small random test, n = " + n + " m = " + m, a);
        }

        {
            for (int zzz = 0; zzz < 10; zzz++) {
                int[] d = new int[MAXN];
                int[][] a = new int[MAXN][MAXN];
                boolean[][] b = new boolean[MAXN][MAXN];
                for (int i = 0; i < MAXN / 2 - 1; i++) {
                    int x, y;
                    do {
                        x = random.nextInt(MAXN / 4);
                        y = MAXN / 4 + random.nextInt(MAXN / 4);
                    } while (b[x][y]);
                    a[x][y] = 1;
                    d[x]++;
                    d[y]++;
                    b[x][y] = true;
                    b[y][x] = true;
                    for (int z = 0; z < MAXN / 2; z++) {
                        if (b[z][x]) {
                            b[z][y] = true;
                            b[y][z] = true;
                        }
                        if (b[z][y]) {
                            b[z][x] = true;
                            b[x][z] = true;
                        }
                    }
                }
                for (int i = 0; i < MAXN / 4; i++) {
                    for (int j = 0; j < d[i] + 1; j++) {
                        a[MAXN / 2 + j][i] = 1;
                    }
                }
                for (int i = MAXN / 4; i < MAXN / 2; i++) {
                    for (int j = 0; j < d[i] + 1; j++) {
                        a[i][MAXN / 4 * 3 + j] = 1;
                    }
                }
                printShuffledTest("Bipartite matching test", a);
            }
        }

        {
            int n = MAXN;
            int[][] a = new int[n][n];
            for (int i = 0; i < MAXN - 1; i++) a[i][i + 1] = 1;
            printShuffledTest("One long line", a);
        }

        {
            int n = MAXN;
            int[][] a = new int[n][n];
            for (int i = 0; i < MAXN; i++)
                for (int j = i + 1; j < MAXN && j < i + 5; j++) {
                    a[i][j] = 1;
                }
            printShuffledTest("Each node connected with next 5 nodes", a);
        }

        {
            int n = MAXN;
            int[][] a = new int[n][n];
            int k = 0;
            while ((k + 1) * (k + 1) <= n) k++;
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < k; j++) {
                    if (j < k - 1) a[i * k + j][i * k + j + 1] = 1;
                    if (i < k - 1) a[i * k + j][i * k + j + k] = 1;
                }
            }
            for (int i = k * k; i < n - 1; i++) {
                a[i][i + 1] = 1;
            }
            printShuffledTest("Grid", a);
        }

        {
            int n = MAXN;
            int[][] a = new int[n][n];
            int m = 0;
            while ((m + 1) * (m + 1) <= n) m++;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    if (j < m - 1 && random.nextBoolean()) a[i * m + j][i * m + j + 1] = 1;
                    if (i < m - 1 && random.nextBoolean()) a[i * m + j][i * m + j + m] = 1;
                }
            }
            for (int j = 0; j < n; j++) {
                boolean ok = false;
                for (int k = 0; k < n; k++) {
                    if (a[j][k] == 1 || a[k][j] == 1) ok = true;
                }
                if (!ok) a[j][(j + 1) % n] = 1;
            }
            printShuffledTest("Broken grid", a);
        }

        {
            int n = MAXN;
            int[][] a = new int[n][n];
            for (int i = 0; i < MAXN; i++) {
                for (int j = i + 1; j < MAXN; j++) {
                    a[i][j] = 1;
                }
            }
            printShuffledTest("Full graph", a);
        }

        {
            int n = MAXN;
            int[][] a = new int[n][n];
            for (int i = 0; i < MAXN / 2; i++) {
                for (int j = i + 1; j < MAXN / 2; j++) {
                    a[i][j] = 1;
                }
            }
            a[MAXN / 2 - 1][MAXN / 2] = 1;
            for (int i = MAXN / 2; i < MAXN; i++) {
                for (int j = i + 1; j < MAXN; j++) {
                    a[i][j] = 1;
                }
            }
            printShuffledTest("Two connected full graphs", a);
        }

        {
            int n = MAXN;
            int[][] a = new int[n][n];
            for (int i = 0; i < MAXN / 4; i++) {
                for (int j = MAXN / 4; j < MAXN / 2; j++) {
                    a[i][j] = 1;
                }
            }
            for (int i = MAXN / 4; i < MAXN / 2; i++) {
                a[i][i + MAXN / 4] = 1;
            }
            for (int i = MAXN / 2; i < MAXN / 4 * 3; i++) {
                for (int j = MAXN / 4 * 3; j < MAXN; j++) {
                    a[i][j] = 1;
                }
            }
            printShuffledTest("Two connected bipartite full graphs", a);
        }

        {
            int n = MAXN;
            int[][] a = new int[n][n];
            for (int k = 0; k < MAXN / 10; k++) {
                for (int i = 0; i < 10; i++) {
                    for (int j = i + 1; j < 10; j++) {
                        a[k * 10 + i][k * 10 + j] = 1;
                    }
                }
                if (k > 0) {
                    int j = random.nextInt(k);
                    a[j * 10 + 9][k * 10] = 1;
                }
            }
            printShuffledTest("10 connected full graphs", a);
        }

        {
            int n = MAXN;
            int[][] a = new int[n][n];
            for (int i = 0; i < MAXN / 2; i++) {
                for (int j = MAXN / 2; j < MAXN; j++) {
                    a[i][j] = 1;
                }
            }
            printShuffledTest("Full bipartite graph", a);
        }

        {
            int m = 0;
            while ((m + 1) * (m + 1) <= MAXN) m++;
            int n = m * m;
            int[][] a = new int[n][n];
            for (int i = 0; i < m - 1; i++) {
                for (int j = 0; j < m; j++) {
                    for (int k = 0; j < m; j++) {
                        a[i * m + j][i * m + k + m] = 1;
                    }
                }
            }
            printShuffledTest("Full layered graph", a);
        }

        {
            int n = MAXN;
            while (n % 5 > 0) n--;
            int m = n / 5;
            int[][] a = new int[n][n];
            for (int i = 0; i < m; i++) {
                for (int j = m; j < 2 * m; j++) {
                    a[i][j] = 1;
                }
            }
            for (int j = m; j < 2 * m; j++) {
                a[j][2 * m] = 1;
            }
            for (int i = 2 * m; i < 3 * m - 1; i++) {
                a[i][i + 1] = 1;
            }
            for (int j = 4 * m; j < 5 * m; j++) {
                a[3 * m - 1][j] = 1;
            }
            for (int i = 3 * m; i < 4 * m; i++) {
                for (int j = 4 * m; j < 5 * m; j++) {
                    a[i][j] = 1;
                }
            }
            printShuffledTest("Many long paths", a);
        }

        for (int i = 0; i < 10; i++) {
            int n = MAXN - random.nextInt(5);
            int[][] a = new int[n][n];
            for (int j = 1; j < n; j++) {
                int k = random.nextInt(j);
                a[k][j] = 1;
            }
            printShuffledTest("Random tree", a);
        }

        for (int i = 0; i < 20; i++) {
            int n = MAXN - random.nextInt(5);
            int[][] a = new int[n][n];
            int m = random.nextInt(n * (n - 1) / 2 + 1);
            for (int k = 0; k < m; k++) {
                int x, y;
                do {
                    x = random.nextInt(n);
                    y = random.nextInt(n);
                } while (y <= x || a[x][y] > 0);
                a[x][y] = 1;
            }
            for (int j = 0; j < n; j++) {
                boolean ok = false;
                for (int k = 0; k < n; k++) {
                    if (a[j][k] == 1 || a[k][j] == 1) ok = true;
                }
                if (!ok) a[j][(j + 1) % n] = 1;
            }
            printShuffledTest("Random test, n = " + n + " m = " + m, a);
        }
        //To change body of created methods use File | Settings | File Templates.
    }

}