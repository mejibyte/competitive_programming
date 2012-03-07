import java.util.Scanner;


public class FacebookA1 
{
	
	static int[] solucion = new int[10000001];
	
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		simular();
		solucion[1] = 1;
		for(int caso = 1; caso <= n; caso++)
		{
			int buscado = sc.nextInt();
			int mejor = buscado + 1;
			if(buscado == 1)
				mejor = 2;
			for(int i = 1; i < buscado; i++)
				if(i == 1 || buscado % solucion[i] == 0)
					if(solucion[i] + solucion[buscado / solucion[i]] < 0)
						continue;
					else
						mejor = Math.min(mejor, solucion[i] + solucion[buscado / solucion[i]]);
			System.out.println("Case #" + caso + ": " + mejor);
		}
	}

	
	static long[][] matriz = new long[3001][3001];
	
	private static void simular()
	{
		for(int i = 0; i <= 10000000; i++)
		{
			solucion[i] = Integer.MAX_VALUE;
		}
		matriz[0][0] = 1;
		for(int i = 0; i < 3001; i++)
			for(int j = 0; j < 3001; j++)
			{
				if(i != 0)
				{
					if(matriz[i - 1][j] >= Integer.MAX_VALUE)
					{
						matriz[i][j] = Integer.MAX_VALUE;
						continue;
					}
					else
						matriz[i][j] = matriz[i - 1][j];
				}
				if(j != 0)
				{
					if(matriz[i][j - 1] >= Integer.MAX_VALUE || matriz[i][j] + matriz[i][j - 1] >= Integer.MAX_VALUE)
					{
						matriz[i][j] = Integer.MAX_VALUE;
						continue;
					}
					else
						matriz[i][j] += matriz[i][j - 1];
				}
			}
		for(int i = 0; i < 3001; i++)
			for(int j = 0; j < 3001; j++)
			{
				if(matriz[i][j] <= 10000000)
					solucion[(int) matriz[i][j]] = (int) Math.min(solucion[(int) matriz[i][j]], i + j);
			}
	}	
}