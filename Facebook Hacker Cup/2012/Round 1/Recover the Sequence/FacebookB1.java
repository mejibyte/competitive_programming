import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Scanner;


public class FacebookB1
{
	static LinkedList <Integer> merge_sort(LinkedList <Integer> arr, int a, int b)
	{
	    if(b - a <= 1)
	        return new LinkedList<Integer>(arr.subList(a, b));
		int mid = (b - a) / 2 + a;
	    LinkedList <Integer> first_half = merge_sort(arr, a, mid);
	    LinkedList <Integer> second_half = merge_sort(arr, mid, b);
	    return merge(first_half, second_half);
	}
	
	static LinkedList <Boolean> entrada = new LinkedList <Boolean> ();
	
	static LinkedList <Integer> merge(LinkedList <Integer> arr1, LinkedList <Integer> arr2)
	{
	    LinkedList <Integer> result = new LinkedList <Integer> ();
	    while(arr1.size() > 0 && arr2.size() > 0)
	    {
	        if(entrada.poll())
	            result.add(arr1.poll());
	        else
	        	result.add(arr2.poll());
	    }
	    result.addAll(arr1);
	    result.addAll(arr2);
	    return result;
	}

	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		int nt = sc.nextInt();
		for(int caso = 1; caso <= nt; caso++)
		{
			entrada.clear();
			int n = sc.nextInt();
			for(char c : sc.next().toCharArray())
				entrada.add(c == '1');
			LinkedList <Integer> numeros = new LinkedList <Integer> ();
			for(int i = 1; i <= n; i++)
				numeros.add(i);
			LinkedList <Integer> respuesta = merge_sort(numeros, 0, n);
			int[] secuencia = new int[respuesta.size() + 1];
			int j = 1;
			for(int i : respuesta)
			{
				secuencia[i] = j++;
			}
			System.out.println("Case #" + caso + ": " + checksum(secuencia));
		}
	}
	
	static int checksum(int[] arr)
	{
	    int result = 1;
	    for(int i = 1; i < arr.length; i++)
	        result = (31 * result + arr[i]) % 1000003;
	    return result;
	}
}
