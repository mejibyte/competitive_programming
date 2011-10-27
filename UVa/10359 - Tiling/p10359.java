/*
  Problema: 10359 - Tiling
  Aceptado por el juez de la UVa
  Este código muestra tanto I/O como BigInteger

  Autor: Andrés Mejía-Posada
 */
import java.util.*;
import java.io.*;
import java.math.*;

class Main {
    public static void main(String[] args) throws IOException {
        BigInteger dp[] = new BigInteger[301];
        dp[0] = BigInteger.ONE;
        dp[1] = BigInteger.ONE;
        for (int i=2; i<=300; ++i){
            dp[i] = dp[i-1].add(dp[i-2].add(dp[i-2]));
        }
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line = reader.readLine();
        while (line != null && line.length() > 0){
            int N = Integer.valueOf(line);
            System.out.println(dp[N].toString());
            line = reader.readLine();
        }
    }
}