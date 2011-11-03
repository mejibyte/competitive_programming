import java.util.*;
import java.io.*;

class Main {
  public static void main(String [] args) {
    Scanner cin = new Scanner(System.in);
    PrintStream cout = System.out;

    int ways[] = new int[7490];
    ways[0] = 1;
    
    int coins[] = { 1, 5, 10, 25, 50 };
    for (int i = 0; i < 5; ++i) {
      for (int j = coins[i]; j < 7490; ++j) {
        assert j - coins[i] >= 0;
        ways[j] += ways[j - coins[i]];
      }
    }
 
    while (cin.hasNextInt()) {
      int n = cin.nextInt();
      cout.println(ways[n]);
    }
  }
}