// Accepted - runs in 1.172s
import java.io.*;
import java.util.*;
import java.math.*;

public class Main2 {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner cin = new Scanner(System.in);
        //Scanner cin = new Scanner(new FileInputStream(new File("in.txt")));
        int m, k;

        int MAXN = 55;
        BigInteger choose[][] = new BigInteger[MAXN][MAXN];
        choose[0][0] = BigInteger.ONE;
        for (int i = 0; i < MAXN; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                if (i != 0 || j != 0) choose[i][j] = BigInteger.ZERO;
                if (i > 0) choose[i][j] = choose[i][j].add(choose[i-1][j]);
                if (i > 0 && j > 0) choose[i][j] = choose[i][j].add(choose[i-1][j-1]);
            }
        }

        while (true) {
            m = cin.nextInt();
            k = cin.nextInt();
            if (m == 0 && k == 0) break;

            int avail[] = new int[k];
            for (int i = 0; i < k; ++i) {
                avail[i] = cin.nextInt();
            }

            BigInteger dp[][] = new BigInteger[k+1][m+1];
            for (int b = 1; b <= m; ++b) {
               dp[k][b] = BigInteger.ZERO;
            }
            dp[k][0] = BigInteger.ONE;

            for (int i = k - 1; i >= 0; --i) {
                for (int b = 0; b <= m; ++b) {
                    dp[i][b] = dp[i+1][b];
                    for (int n = 1; n <= avail[i] && b - n >= 0; n++) {
                          dp[i][b] = dp[i][b].add(dp[i+1][b-n].multiply(choose[b][n]));
                    }
                }
            }
            System.out.println(dp[0][m]);
        }
    }

}