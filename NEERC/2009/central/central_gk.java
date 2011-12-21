import java.util.*;
import java.io.*;
import static java.lang.System.out;

class central_gk {
    static Scanner in;
    static final int UNDEFINED = -1;

    int ask(int i, int j, int k) {
        out.println((i + 1) + " " + (j + 1) + " " + (k + 1));
        out.flush();
        return in.nextInt();
    }

    Queue<Integer> decide(int[] a, int l, Queue<Integer> queue) {
        while (queue.size() > 2) {
            int x = queue.poll();
            int y = queue.poll();
            int z = queue.poll();

            int za = ask(l, x, y);
            int xa = ask(l, y, z);
            int ya = ask(l, z, x);

            if (xa == ya) {
                a[z] = xa;
                queue.add(x);
                queue.add(y);
            }
            if (ya == za) {
                a[x] = ya;
                queue.add(y);
                queue.add(z);
            }
            if (za == xa) {
                a[y] = za;
                queue.add(z);
                queue.add(x);
            }
        }
        return queue;
    }

    Queue<Integer> take(int[] a, int value) {
        Queue<Integer> result = new LinkedList<Integer>();
        for (int i = 0; i < a.length; i++) {
            if (a[i] == value) {
                result.add(i);
            }
        }
        return result;
    }

    int[] askAll(int n, int l, int r) {
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = (i == l || i == r) ? UNDEFINED : ask(l, r, i);
        }
        return a;
    }

    void run() throws IOException {
        int n = in.nextInt();
        if (n == 3) {
            out.println("OK 1 2 3");
            return;
        }

        for (int j = 1; j < n; j++) {
            int[] a = askAll(n, 0, j);

            int min = UNDEFINED;
            int max = UNDEFINED;
            for (int i = 0; i < n; i++) {
                if (min == UNDEFINED && a[i] != UNDEFINED || min > a[i]) {
                    min = a[i];
                }
                if (max == UNDEFINED && a[i] != UNDEFINED || max < a[i]) {
                    max = a[i];
                }
            }

            if (min == max) {
                Queue<Integer> other = decide(a, 0, take(a, max));
                if (max == 2) {
                    a[0] = 1;
                    a[j] = 2;
                    a[other.remove()] = n - 1;
                    a[other.remove()] = n;
                } else {
                    a[other.remove()] = 1;
                    a[other.remove()] = 2;
                    a[0] = n;
                    a[j] = n - 1;
                }
            } else {
                Queue<Integer> less = decide(a, 0, take(a, min));
                Queue<Integer> greater = decide(a, 0, take(a, max));
                int l = less.remove();
                int r = greater.remove();
                if (!less.isEmpty()) {
                    int p = less.remove();
                    if (p != 0 && p != j) {
                        a[p] = 2;
                    }
                }
                if (!greater.isEmpty()) {
                    int p = greater.remove();
                    if (p != 0 && p != j) {
                        a[p] = n - 1;
                    }
                }

                a[l] = 1;
                a[r] = n;
                if (a[0] == UNDEFINED) {
                    a[0] = ask(l, r, 0);
                }
                if (a[j] == UNDEFINED) {
                    a[j] = ask(l, r, j);
                }
            }

            out.print("OK");
            for (int i : a) {
                out.print(" " + i);
            }
            out.println();
            return;
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(System.in);

        new central_gk().run();

        in.close();
        out.close();
    }
}
