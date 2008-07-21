import java.util.*;
import java.io.*;
import java.math.*;

class Main{
	
	public static String clean(String s){
		String r = "";
		s = s.toLowerCase();
		for (int i=0; i<s.length(); ++i){
			if (Character.isLetter(s.charAt(i))){
				r += s.charAt(i);
			}
		}
		if (r.charAt(r.length()-1) == 's'){
			r = r.substring(0, r.length()-1);
		}
		return r;
	}
		
	public void procesarCaso(ArrayList<String> p, String s){
		HashMap<String, Character> m = new HashMap<String, Character>();
		String sufijos[] = s.split(" ");
		String result = "";
		boolean ilegal = false;
		char sufijoActual = 'A';
		for (int i=0; i<p.size(); ++i){
			boolean rimo = false;
			for (int j=0; j<sufijos.length; ++j){
				if (p.get(i).endsWith(sufijos[j])){
					//System.out.println(p.get(i) + " rima con " + sufijos[j]);
					rimo = true;
					if (m.containsKey(sufijos[j])){
						result += m.get(sufijos[j]);
					}else{
						m.put(sufijos[j], Character.valueOf(sufijoActual));
						result += sufijoActual;
						sufijoActual++;
					}
				}
			}
			if (!rimo){
				ilegal = true;
			}
		}
		
		//System.out.println(result);
		
		if (ilegal){
			System.out.println("Not a chance!");
			return;
		}
		if (result.equals("ABBAABBACDECDE") || result.equals("ABBAABBACDEDCE") || result.equals("ABBAABBACDCDCD")){
			System.out.println(result);
			return;
		}
		System.out.println("Not a chance!");
	}


	public static void main(String[] args) throws IOException{
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String line = reader.readLine();
		while (line != null){
			String sufijos = line;
			line = reader.readLine();
			System.out.print(line + ": "); //titulo
			//ahora leamos el cuerpo del poema
			line = reader.readLine();
			ArrayList<String> p = new ArrayList<String>();
			while (line != null && line.trim().length() > 0){
				//System.out.println("Read " + line);
				p.add(clean(line));
				//System.out.println("Added " + p.get(p.size()-1));
				line = reader.readLine();
			}
			Main s = new Main();
			s.procesarCaso(p, sufijos);
			
			line = reader.readLine(); //leer sufijos del siguiente caso
		}
		
	}
}