import java.util.*;
import java.io.*;

class Main {
  public static void main(String [] args) {
    Scanner cin = new Scanner(System.in);
    PrintStream cout = System.out;

    long f[] = new long[51];
    f[0] = 0;
    f[1] = 1;
    f[2] = 2;
    for (int i = 3; i <= 50; ++i) {
      f[i] = f[i-1] + f[i-2];
    }
    
    while (true) {
      int n = cin.nextInt();
      if (n == 0) break;
      cout.println(f[n]);
    }
  }
}