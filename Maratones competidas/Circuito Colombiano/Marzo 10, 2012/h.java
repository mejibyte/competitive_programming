import java.math.BigInteger;
import java.util.Scanner;


public class h {

    public static void main(String[] args) {

        int MAXN = 25;
        BigInteger choose[][] = new BigInteger[MAXN][MAXN];

        for (int i = 0; i < MAXN; ++i) for (int j = 0; j < MAXN; ++j) choose[i][j] = BigInteger.ZERO;
        choose[0][0] = BigInteger.ONE;

        for (int i = 1; i < MAXN; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                choose[i][j] = choose[i][j].add(choose[i - 1][j]);
                if (j - 1 >= 0) choose[i][j] = choose[i][j].add(choose[i - 1][j - 1]);
            }
        }

        BigInteger fact[] = new BigInteger[MAXN];
        fact[0] = BigInteger.ONE;
        for (int i = 1; i < MAXN; ++i) fact[i] = fact[i - 1].multiply(BigInteger.valueOf(i));


        Scanner cin = new Scanner(System.in);
        int casos = cin.nextInt();
        for (int q = 0; q < casos; q++) {
            int id, n, k;
            id = cin.nextInt();
            n = cin.nextInt();
            k = cin.nextInt();

            System.out.print(id + " ");

            if (k == 1) {
                System.out.println(fact[n - 1]);
                continue;
            }

            BigInteger ans = BigInteger.ZERO;
            for (int r = 0; r <= k - 2; ++r) {
                BigInteger t = choose[k - 2][r].multiply(fact[r + 1]).multiply(fact[n - 2 - r]);
                ans = ans.add(t);
            }

            System.out.println(ans);
        }
    }
}
