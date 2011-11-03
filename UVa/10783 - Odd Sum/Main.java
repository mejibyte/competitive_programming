import java.util.*;
import java.io.*;

class Main {
  public static void main(String [] args) {
    Scanner cin = new Scanner(System.in);
    PrintStream cout = System.out;

    int T = cin.nextInt();
    for (int c = 1; c <= T; ++c) {
      int a = cin.nextInt();
      int b = cin.nextInt();
      
      int sum = 0;
      
      for (int i = a; i <= b; ++i) {
        if (i % 2 == 1) sum += i;
      }
      
      cout.printf("Case %d: %d\n", c, sum);
    }
  }
}