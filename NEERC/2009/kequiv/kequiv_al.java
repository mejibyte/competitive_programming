import java.util.*;
import java.io.*;

public class kequiv_al {
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

  static int digdist (int d1, int d2) {
    if (d2 > d1) return d2 - d1; else return d2 - d1 + 10;
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
    long s = System.currentTimeMillis ();
    BufferedReader in = new BufferedReader (new FileReader ("kequiv.in"));
    PrintWriter out = new PrintWriter ("kequiv.out");
    int n = Integer.parseInt (in.readLine ());
    rangeLong (n, 1, MaxN);

    long [] T = new long [PL];
    T[PL - 1] = 1;
    for (int i = PL - 2; i >= 0; i--) T[i] = T[i + 1] * 10;

    long [] a = new long [n], b = new long [n];
    char [][] ac = new char [n][], bc = new char [n][];
    long last = -1;

    for (int i = 0; i < n; i++) {
      StringTokenizer tok = new StringTokenizer (in.readLine ());
      String as = tok.nextToken ();
      String bs = tok.nextToken ();
      a[i] = rangeLong (as, last + 2, MaxAB);
      b[i] = rangeLong (bs, a[i], MaxAB);
      char [] d = new char [PL - as.length ()];
      Arrays.fill (d, '0');
      ac[i] = (new String (d) + as).toCharArray ();
      d = new char [PL - bs.length ()];
      Arrays.fill (d, '0');
      bc[i] = (new String (d) + bs).toCharArray ();
      last = b[i];
      if (tok.hasMoreTokens ()) throw new Exception ("EOL expected");
    }

    if (in.ready ()) throw new Exception ("EOF expected");

    System.out.println ("input: " + (System.currentTimeMillis () - s));

    long [][][] ast = new long[n][10][PL], bfn = new long [n][10][PL];
    long [][][] aln = new long[n][10][PL], bln = new long [n][10][PL];

    long [][] atl = new long[n][PL + 1], btl = new long [n][PL + 1];
    for (int i = 0; i < n; i++)
      for (int j = PL - 1; j >= 0; j--) {
        atl[i][j] = atl[i][j + 1] + (ac[i][j] - '0') * T[j];
        btl[i][j] = btl[i][j + 1] + (bc[i][j] - '0') * T[j];
      }


    for (int i = 0; i < n; i++) 
      for (int d1 = 1; d1 <= 9; d1++)
        for (int p = 0; p < PL; p++) {
          //System.out.println (cur);
          long fR = T[p] - atl[i][p + 1];
          if (ac[i][p] == d1 + '0') {
            ast[i][d1][p] = a[i];
            aln[i][d1][p] = Math.min (fR, b[i] - a[i] + 1);
          } else {
            ast[i][d1][p] = a[i] + fR + (digdist (ac[i][p] - '0', d1) - 1) * T[p];
            aln[i][d1][p] = Math.min (T[p], b[i] - ast[i][d1][p] + 1);
          }
          //System.out.println (i + " " + d1 + " " + " " + p + ": " + fR + " " + ast[i][d1][p]);

          fR = btl[i][p + 1] + 1;
          if (bc[i][p] == d1 + '0') {
            bfn[i][d1][p] = b[i];
            bln[i][d1][p] = Math.min (fR, b[i] - a[i] + 1);
          } else {
            bfn[i][d1][p] = b[i] - fR - (digdist (d1, bc[i][p] - '0') - 1) * T[p];
            bln[i][d1][p] = Math.min (T[p], bfn[i][d1][p] - a[i] + 1);
          }
        }


    System.out.println ("prepare: " + (System.currentTimeMillis () - s));

    G = new boolean [10][10];

    for (int i = 1; i <= 9; i++)
      for (int j = 1; j <= 9; j++)
        G[i][j] = true;


    for (int d1 = 1; d1 <= 9; d1++)
      for (int d2 = 1; d2 <= 9; d2++) {
        for (int p = 0; p < PL; p++) {
          int j = 0;
          for (int i = 0; i < n; i++) {
            if (aln[i][d1][p] > 0) {
              //check A interval
              long tofind = ast[i][d1][p] + (d2 - d1) * T[p];
              //System.out.println ("tofind = " + tofind);
              while (j < n && b[j] < tofind) ++j;
              //System.out.println ("j = " + j + ", a[j] = " + a[j] + ", b[j] = " + b[j]);
              if (j == n || a[j] > tofind)  {
                if (G[d1][d2]) {
                  //System.out.println ("(" + p + "): " + ast[i][d1][p] + " -> " + bfn[i][d1][p] + " blocks " + d1 + " -> " + d2);
                }
                G[d1][d2] = false;
                G[d2][d1] = false;
                break;
              }
              long toend = bfn[i][d1][p] + (d2 - d1) * T[p];
              //System.out.println ("toend = " + toend);
              while (j < n && b[j] < toend) {
                int oj = j;
                do {
                  ++j;
                } while (j < n && aln[j][d2][p] <= 0);
                if (j >= n) {
                  break;
                }
                /*if (ast[j][d2][p] - bfn[oj][d2][p] < 9 * T[p] + 1) {
                  throw new Exception ("bug detected (" + j + ", " + d2 + ", " + p + "): " + ast[j][d2][p] + " " + bfn[oj][d2][p]);
                }*/
                if (ast[j][d2][p] - bfn[oj][d2][p] != 9 * T[p] + 1) {
                  j = n;
                  break;
                }
              }
              if (j == n) {
                //if (G[d1][d2]) {
                  //System.out.println ("(" + p + "): " + ast[i][d1][p] + " -> " + bfn[i][d1][p] + " blocks " + d1 + " -> " + d2);
                //}
                G[d1][d2] = false;
                G[d2][d1] = false;
                break;
              }
              if (a[j] > toend) {
                throw new RuntimeException ("bug detected");
              }
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

    System.out.println ("complete: " + (System.currentTimeMillis () - s));
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