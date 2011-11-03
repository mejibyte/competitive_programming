import java.util.*;
import java.io.*;

class Main {
  public static void main(String [] args) {
    Scanner cin = new Scanner(System.in);
    PrintStream cout = System.out;
    
    int set = 1;
    while (true) {
      int n = cin.nextInt();
      if (n == 0) break;

      int h[] = new int[n];
      int sum = 0;
      for (int i = 0; i < n; ++i) {
        h[i] = cin.nextInt();
        sum += h[i];
      }

      assert sum % n == 0;
      int average = sum / n;

      int answer = 0;
      for (int i = 0; i < n; ++i) {
        if (h[i] > average) {
          answer += h[i] - average;
        }
      }
      
      cout.printf("Set #%d\nThe minimum number of moves is %d.\n\n", set++, answer);
    }
  }
}