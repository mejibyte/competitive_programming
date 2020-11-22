import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;
import java.math.BigInteger;

public class Main{
	public static void main(String[] args) {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        while (true) {
          int people, disks;
          people = sc.nextInt();
          disks = sc.nextInt();
          if (people == 0 && disks == 0) break;

          BigInteger p = new BigInteger(String.valueOf(people));
          BigInteger result = p.pow(disks);

          System.out.println(result.toString());
        }
	}
}