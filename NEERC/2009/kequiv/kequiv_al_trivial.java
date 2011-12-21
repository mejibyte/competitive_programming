import java.util.*;
import java.io.*;

public class kequiv_al_trivial {
  static final int MaxN = 10000;
  static final long MaxAB = (long)1e18;
  static final int PL = 19;

  static long rangeLong (long x, long a, long b) {
    if (x < a || x > b) throw new RuntimeException (x + " is not in range " + a + ".." + b);
    return x;
  }
  
  static long rangeLong (String s, long a, long b) {
    return rangeLong (Long.parseLong (s), a, b);
  }

  static long myLong (String s) {
    if (s.length () == 0) return 0; else return Long.parseLong (s);
  }


  static boolean [][] G;
  static int [] C;
  static int cc;


  static void dfs (int x) {
    C[x] = cc;
    for (int j = 1; j <= 9; j++)
      if (C[j] == 0 && G[x][j])
        dfs (j);
  }

  public static void main (String args []) throws Exception {
    BufferedReader in = new BufferedReader (new FileReader ("kequiv.in"));
    PrintWriter out = new PrintWriter ("kequiv.out");
    int n = Integer.parseInt (in.readLine ());
    rangeLong (n, 1, MaxN);

    long [] a = new long [n], b = new long [n];
    long last = -1;

    for (int i = 0; i < n; i++) {
      StringTokenizer tok = new StringTokenizer (in.readLine ());
      String as = tok.nextToken ();
      String bs = tok.nextToken ();
      a[i] = rangeLong (as, last + 2, MaxAB);
      b[i] = rangeLong (bs, a[i], MaxAB);
      if (tok.hasMoreTokens ()) throw new Exception ("EOL expected");
    }

    if (in.ready ()) throw new Exception ("EOF expected");

    G = new boolean [10][10];

    for (int i = 1; i <= 9; i++)
      for (int j = 1; j <= 9; j++)
        G[i][j] = true;

    for (int i = 0; i < n; i++) {
      for (long x = a[i]; x <= b[i]; x++) {
        char [] c = ("" + x).toCharArray ();
        for (int p = 0; p < c.length; p++) {
          if (c[p] != '0') {
            char sav = c[p];
            for (int d = 1; d <= 9; d++) {
              c[p] = (char)(d + '0');
              long y = Long.parseLong (new String (c));
              boolean found = false;
              for (int j = 0; j < n; j++) {
                if (a[j] <= y && y <= b[j]) {
                  found = true;
                }
              }
              if (!found) {
                if (G[sav - '0'][d]) {
                  //System.out.println (x + " -> " + y + " blocks " + sav + " -> " + d);
                }
                G[sav - '0'][d] = false;
                G[d][sav - '0'] = false;
              }
            }
            c[p] = sav;
          }
        }
      }
    }

    C = new int [10];
    cc = 0;

    for (int i = 1; i <= 9; i++) {
      if (C[i] == 0) {
        ++cc;
        dfs (i);
      }
    }

    for (int i = 1; i <= cc; i++) {
      for (int j = 1; j <= 9; j++) {
        if (C[j] == i) {
          out.print (j);
        }
      }
      out.println ();
    }
    out.close ();
  }
}