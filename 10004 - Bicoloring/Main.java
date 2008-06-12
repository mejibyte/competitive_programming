import java.io.*;
import java.util.*;
import java.math.*;

class Main {

	char[][] cMat;
	int iMid;
	int iLast;
	int iRep;
	int iIni;
	int iLon;
	boolean bEnd = true;
	String sNum;
	
    static String ReadLn (int maxLg){
        byte lin[] = new byte [maxLg];
        int lg = 0, car = -1;
        try{
            while (lg < maxLg){
                car = System.in.read();
                if ((car < 0) || (car == '\n')) break;
                lin [lg++] += car;
            }
        }
        catch (IOException e){
            return (null);
        }

        if ((car < 0) && (lg == 0)) return (null);  // eof
        return (new String (lin, 0, lg));
    }

    public static void main (String args[]){
        Main myWork = new Main();  // create a dinamic instance
        myWork.Begin();            // the true entry point
    }

    void Begin(){    	
    	
    	String input;
    	StringTokenizer idata;
    	int [][] g;
    	int nodos;
    	int aristas;
    	int x, y;
    
    	//Leer nodos
    	input = Main.ReadLn(255);
    	idata = new StringTokenizer(input);
    	nodos = Integer.parseInt(idata.nextToken());
    	while (nodos > 0){
        	g = new int[200][200];
        	input = Main.ReadLn(255);
        	idata = new StringTokenizer(input);
        	aristas = Integer.parseInt(idata.nextToken());
        	while (aristas > 0){
        		//Leer aqui la arista
        		aristas--;
        	}
    		//Leer nodos
        	input = Main.ReadLn(255);
        	idata = new StringTokenizer(input);
        	nodos = Integer.parseInt(idata.nextToken());
    	}
    	
    }
    void Begin2(){
        String input;
        StringTokenizer idata;
        int iNum;
        
        do{
        	if((input = Main.ReadLn (255)) != null){
            	idata = new StringTokenizer (input);
	        	iRep = Integer.parseInt (idata.nextToken());
	        	iNum = Integer.parseInt (idata.nextToken());
	        	sNum = Integer.toString(iNum);
	        	iMid= (2*iRep+3)/2;
				iLast= 2*iRep+2;
				iLon = sNum.length();
		        cMat = new char[2*iRep+3][((2+iRep)*iLon)+(iLon-1)];
		        iIni =0;
		        for(int i=0;i<iLon&&i<8;i++){
		        	write(sNum.charAt(i));
		        	iIni += iRep+3;
		        }
	        	print();
        	}
        }while((iRep!=0)||(!sNum.equals("0")));
    }
	
	void write(char cNum){
		
		switch (cNum){
			case '1':
				seg_b();
				seg_c();
				break;
			case '2':
				horizontal(0);
				seg_b();
				horizontal(iMid);
				seg_e();
				horizontal(iLast);
				break;
			case '3':
				horizontal(0);
				seg_b();
				horizontal(iMid);
				seg_c();
				horizontal(iLast);
				break;
			case '4':
				seg_f();
				seg_b();
				horizontal(iMid);
				seg_c();
				break;
			case '5':
				horizontal(0);
				seg_f();
				horizontal(iMid);
				seg_c();
				horizontal(iLast);
				break;
			case '6':
				horizontal(0);
				seg_f();
				horizontal(iMid);
				seg_e();
				seg_c();
				horizontal(iLast);
				break;
			case '7':
				horizontal(0);
				seg_b();
				seg_c();
				break;
			case '8':
				horizontal(0);
				seg_b();
				seg_c();
				horizontal(iMid);
				seg_e();
				seg_f();
				horizontal(iLast);
				break;
			case '9':
				horizontal(0);
				seg_f();
				seg_b();
				horizontal(iMid);
				seg_c();
				horizontal(iLast);
				break;
			case '0':
				horizontal(0);
				seg_b();
				seg_e();
				seg_c();
				seg_f();
				horizontal(iLast);
				break;
		}
	}
	
	void horizontal(int fila){
		for(int i=1;i<=iRep;i++){
			cMat[fila][iIni+i]='-';
		}
	}
	//char[][] cMat,int iRep
	void seg_b(){
		for(int i=1;i<iMid;i++)
			cMat[i][iIni+iRep+1]='|';
	}
	
	void seg_c(){
		for(int i=iMid+1;i<iLast;i++)
			cMat[i][iIni+iRep+1]='|';
	}
	
	void seg_e(){
		for(int i=iMid+1;i<iLast;i++)
			cMat[i][iIni]='|';
	}
	
	void seg_f(){
		for(int i=1;i<iMid;i++)
				cMat[i][iIni]='|';
	}
    
	void print(){
		char c;
		System.out.println();
		for(int i=0;i<(2*iRep+3);i++){
			for(int j=0;j<((2+iRep)*iLon+iLon-1);j++){
				c=cMat[i][j];
				if(c=='\u0000'){
				 	System.out.print(" ");
				}else{
					System.out.print(cMat[i][j]);
				}
			}
			System.out.println();
			//System.out.println();
		}
	}
}
