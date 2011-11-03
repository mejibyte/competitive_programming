import java.util.*;

class Main {
  public static void main(String [] args) {
    Scanner cin = new Scanner(System.in);
    int T = cin.nextInt();
    for (int c = 0; c < T; ++c) {
      int n = cin.nextInt();
      int a[] = new int[n];
      int sum = 0;
      for (int i = 0; i < n; ++i) {
        a[i] = cin.nextInt();
        sum += a[i];
      }
      
      double average = 1.0 * sum / n;
      int above = 0;
      for (int i = 0; i < n; ++i) {
        if (a[i] > average) above++;
      }
      
      double answer = 100.0 * above / n;
      System.out.printf(Locale.US, "%.3f%%\n", answer);
    }
  }
}