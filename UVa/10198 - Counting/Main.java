import java.io.*;
import java.math.*;

public class Main{
    public static void main(String args[]) throws Exception{
        BufferedReader cin = new BufferedReader(new InputStreamReader(System.in));

        BigInteger dp[] = new BigInteger[1010];
        for (int i=0; i<1010; ++i) dp[i] = BigInteger.ZERO;
        dp[0] = BigInteger.ONE;
        for (int i=0; i<=1000; ++i){
            dp[i+1] = dp[i+1].add(dp[i]);
            dp[i+1] = dp[i+1].add(dp[i]);
            dp[i+2] = dp[i+2].add(dp[i]);
            dp[i+3] = dp[i+3].add(dp[i]);
        }
        String s;
        while ((s = cin.readLine()) != null){
            System.out.println(dp[Integer.parseInt(s)].toString());
        }
    }
}