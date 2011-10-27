import java.io.*;
import java.util.*;

class Node{
	int info;
	Node sons[];
	
	Node(){
		info = 0;
		sons = new Node[4];
	}
}
public class Gattaca_Tries {

	public static String letras = "ACGT";
	public static void main(String[] args) throws Exception {
		BufferedReader br=new BufferedReader(new FileReader("gattaca.in"));
		for (int T=Integer.parseInt(br.readLine()),c=0; c<T; c++) {
			String s=br.readLine();
			int n=s.length(), rep=0;
			String ans = "";

			Node root = new Node();

			for (int i=0; i<n; ++i){
				Node foot = root; //Tells me where i'm standing.
				String so_far = "";
				for (int j=i; j<n; ++j){
					//System.out.println("i " + i + " j " + j);
					
					so_far = s.substring(i, j);
					int v = letras.indexOf(s.charAt(j));
					if (foot.sons[v] == null) foot.sons[v] = new Node();
					foot = foot.sons[v];
					int t = ++foot.info;
					if (t > 1 && (so_far.length() > ans.length() || (so_far.length() == ans.length() && so_far.compareTo(ans) < 0))){
						ans = so_far;
						rep = t;
					}
				}
			}
			System.out.println(ans.length() == 0 ?"No repetitions found!":(ans + " " + rep));
		}
		br.close();
	}
}
