// Autor: Alejandro Sotelo
// Por compatibilidad en la codificacion, se eliminaron las tildes de este archivo
import java.io.*;
import java.util.*;
public class gattaca_Sotelo2 {
  public static void main(String[] args) throws Exception {
    BufferedReader br=new BufferedReader(new FileReader("gattaca.in"));
    for (int T=Integer.parseInt(br.readLine()),c=0; c<T; c++) {
      String s=br.readLine();
      int n=s.length(),veces=0;
      String res=null,arr[]=new String[n+1];
      for (int k=0; k<=n; k++) arr[k]=s.substring(k);
      Arrays.sort(arr);
      for (int k=1; k<=n; k++) {
        int i=0;
        while (i<arr[k-1].length()&&i<arr[k].length()&&arr[k-1].charAt(i)==arr[k].charAt(i)) i++;
        if (i==0) continue;
        if (res==null||i>res.length()||(i==res.length()&&arr[k].substring(0,i).compareTo(res)<0)) {
          veces=2;
          res=arr[k].substring(0,i);
        }
        else if (i==res.length()&&arr[k].substring(0,i).equals(res)) veces++;
      }
      System.out.println(res==null?"No repetitions found!":(res+" "+veces));
    }
    br.close();
  }
}
