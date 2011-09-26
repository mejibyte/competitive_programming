import java.util.*;
public class Ejemplo {
    public static void main(String[] args){
        /*
         * Mapas
         * Tanto el HashMap como el TreeMap funcionan,
         * pero tienen diferentes detalles
         * y difieren en algunos métodos (Ver API).
         */
        System.out.println("Maps"); //TreeMap<String, Integer>
        m = new TreeMap<String, Integer>(); HashMap<String,
        Integer> m = new HashMap<String, Integer>();
        m.put("Hola", new Integer(465));
        System.out.println("m.size() = " + m.size()); if
        (m.containsKey("Hola")){
        System.out.println(m.get("Hola")); }
        System.out.println(m.get("Objeto inexistente"));
        /*
         * Sets
         * La misma diferencia entre TreeSet y HashSet.
         */
        System.out.println("\nSets");
        /*
         * *OJO: El HashSet no está en orden, el TreeSet sí.
         */
        //HashSet<Integer> s = new HashSet<Integer>();
        TreeSet<Integer> s = new TreeSet<Integer>();
        s.add(3576); s.add(new Integer("54")); s.add(new
        Integer(1000000007)); if (s.contains(54)){
        System.out.println("54 presente."); } if (s.isEmpty()
        == false){ System.out.println("s.size() = " +
        s.size()); Iterator<Integer> i = s.iterator(); while
        (i.hasNext()){ System.out.println(i.next());
        i.remove(); } System.out.println("s.size() = " +
        s.size()); } } }

