import java.util.*;
import java.io.*;
import java.math.*;

class Main {
    public static void main(String[] args) throws IOException
      { BufferedReader reader = new BufferedReader(new
      InputStreamReader(System.in)); String line =
      reader.readLine(); StringTokenizer tokenizer = new
      StringTokenizer(line); int N =
      Integer.valueOf(tokenizer.nextToken()); while (N-- > 0){
      String a, b; a = reader.readLine(); b =
      reader.readLine();

        int A = a.length(), B = b.length(); if (B > A){
        System.out.println("0"); }else{ BigInteger dp[][] =
        new BigInteger[2][A];
          /*
            dp[i][j] = cantidad de maneras diferentes
            en que puedo distribuir las primeras i
            letras de la subsecuencia (b) terminando
            en la letra j de la secuencia original (a)
          */

          if (a.charAt(0) == b.charAt(0)){ dp[0][0] =
            BigInteger.ONE; }else{ dp[0][0] = BigInteger.ZERO;
            } for (int j=1; j<A; ++j){ dp[0][j] = dp[0][j-1];
            if (a.charAt(j) == b.charAt(0)){ dp[0][j] =
            dp[0][j].add(BigInteger.ONE); } }

          for (int i=1; i<B; ++i){ dp[i%2][0] =
            BigInteger.ZERO; for (int j=1; j<A; ++j){
            dp[i%2][j] = dp[i%2][j-1]; if (a.charAt(j) ==
            b.charAt(i)){ dp[i%2][j] =
            dp[i%2][j].add(dp[(i+1)%2][j-1]); } } }
            System.out.println(dp[(B-1)%2][A-1].toString()); }
            } } }
