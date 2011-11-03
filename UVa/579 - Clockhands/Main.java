import java.util.*;
import java.io.*;

class Main {
  public static void main(String [] args) throws IOException {
    BufferedReader cin = new BufferedReader(new InputStreamReader(System.in));
    PrintStream cout = System.out;
    
    while (true) {
      String s = cin.readLine();
      if (s.equals("0:00")) break;
      
      int hour = Integer.valueOf(s.split(":")[0]);
      int minute = Integer.valueOf(s.split(":")[1]);

      if (hour == 12) hour = 0;
      double angle1 = 30 * hour + minute * 0.5;
      double angle2 = minute * 6;
      double answer = Math.abs(angle1 - angle2);
      if (answer > 180) answer = 360 - answer;
      cout.printf("%.3f\n", answer);
      
    }
  }
}