import java.util.*;


class Item implements Comparable<Item>{
    int destino, peso;

    Item(int destino, int peso){
	this.peso = peso;
	this.destino = destino;
    }
    /*
     * Implementamos toda la javazofia.
     */
    public int compareTo(Item otro){
	// Return < 0 si this < otro
	// Return   0 si this == otro
	// Return > 0 si this > otro  
	return peso - otro.peso; /* Un nodo es menor que otro si tiene menos peso */
    }
    public boolean equals(Object otro){
	if (otro instanceof Item){
	    Item ese = (Item)otro;
	    return destino == ese.destino && peso == ese.peso;
	}
	return false;
    }
    public String toString(){
	return "peso = " + peso + ", destino = " + destino;
    }
}

class Ejemplo {
    public static void main(String[] args) {
	PriorityQueue<Item> q = new PriorityQueue<Item>();
	q.add(new Item(12, 0));
	q.add(new Item(4, 1876));
	q.add(new Item(13, 0));
	q.add(new Item(8, 0));
	q.add(new Item(7, 3));
	while (!q.isEmpty()){
	    System.out.println(q.poll());
	}
	   
    }
}
