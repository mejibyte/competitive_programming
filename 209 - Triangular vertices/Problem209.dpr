program problem209 (input, output);

{$APPTYPE CONSOLE}

type
 TPunto = Record
  Num, Fila,
  PosIzq, //La posición del punto contando desde el primer elemento de la izquierda de la fila
  PosDcha //Lo mismo pero empezando por la derecha
   : Integer;
  end;

var
  i, j, Distancia1 : integer;
  Entrada : String;
  Puntos : Array[0..5] of TPunto; //los puntos en el orden en que entran
  PuntosOrdenados : Array[0..5] of TPunto; //los puntos ordenados de mayor a menor
  Cuenta : Integer; //Cuenta el numero de puntos que le entraron - 1 (Porque el arreglo empieza en 0)
  TempPt : TPunto; //Pt temporal usado para organizarlos de mayor a menor

  PtsCorrectos : Set of Byte;

Function StrToInt(Const S: String): Integer;
Var
  E: Integer;
Begin
  Val(S, Result, E);
End;

procedure PrintIncorrectos();
var i : byte;
begin
for i := 0 to Cuenta do
  Write(Puntos[i].Num, ' ');
WriteLn('are not the vertices of an acceptable figure');
end;

procedure PrintCorrecto(Figura : String);
var i : byte;
begin
for i := 0 to Cuenta do
  Write(Puntos[i].Num, ' ');
WriteLn('are the vertices of a '+Figura);
end;

function GetFila(Numero : Integer) : Integer;
//retorna la fila de un numero o punto
var
 Fila, Acum : Integer;
begin
Fila := 1;
Acum := 0;
repeat
 Acum := Acum + Fila;
 If Acum < Numero then
  Fila := Fila + 1;
until Acum >= Numero;
Result := Fila; //Return
end;

function GetSumaDeFilas(Cuantas : Integer) : Integer;
//retorna la suma de todas las filas hasta Cuantas
var
 i : integer;
begin
Result := 0;
For i := 1 to Cuantas do
 Result := Result + i;
end;

function GetPosIzq(Numero, Fila : Integer) : Integer;
//retorna la posición izquierda respecto a la fila
begin
Result := Numero - (GetSumaDeFilas(Fila)-Fila);
end;

function GetPosDcha(Numero, Fila : Integer) : Integer;
//retorna la posición derecha respecto a la fila
begin
Result := GetSumaDeFilas(Fila) - Numero + 1;
end;

//Empieza!



begin
PtsCorrectos := [3, 4, 6];

  while not eof(input) do
  begin
    FillChar(Puntos, SizeOf(Puntos), 0); //Limpia el arreglo y lo llena todo con 0's
    Cuenta := -1;
    ReadLn(Entrada);
    If Length(Entrada) = 0 then Break; //si no introducen ningun caracter entonces salir
    If Entrada[Length(Entrada)] <> ' ' then Entrada := Entrada + ' '; //Agrega un espacio al final para poder "parsear" todos los numeros
    While Pos(' ', Entrada) > 0 do
      begin
      Cuenta := Cuenta + 1;
      Puntos[Cuenta].Num := StrToInt(Copy(Entrada, 1, Pos(' ', Entrada)-1));
      Delete(Entrada, 1, Pos(' ', Entrada));
      end;
   //Aquí ya he leído todos los puntos y están en el arreglo Puntos. La variable Cuenta contiene el numero de elementos que hay

    if not ((Cuenta+1) in PtsCorrectos) then //No son 3, 4 o 6 pts, entonces es incorrecto
     begin
     PrintIncorrectos();
     Continue; //Salta al pròximo while
     end;

     for i := 0 to Cuenta do
      begin
      Puntos[i].Fila := GetFila(Puntos[i].Num);
      Puntos[i].PosIzq := GetPosIzq(Puntos[i].Num, Puntos[i].Fila);      
      Puntos[i].PosDcha := GetPosDcha(Puntos[i].Num, Puntos[i].Fila);
      end;

      FillChar(PuntosOrdenados, SizeOf(PuntosOrdenados), 0);
      //Organizarlos de mayor a menor

      for i := 0 to Cuenta do
       PuntosOrdenados[i] := Puntos[i]; //copia el arreglo

      for i := 0 to Cuenta do
      begin
       for j := Cuenta downto i+1 do
       begin
       if PuntosOrdenados[j].Num < PuntosOrdenados[j-1].Num then
        begin
        TempPt := PuntosOrdenados[j];
        PuntosOrdenados[j] := PuntosOrdenados[j-1];
        PuntosOrdenados[j-1] := TempPt;
        end;
       end;
      end;
      //Aqui se encuentran todos los puntos organizados de mayor a menor en el arreglo PuntosOrdenados

   case (Cuenta+1) of

/////////////////////////////////////////////
////////////// Triangulo ////////////////////
/////////////////////////////////////////////
         //                         _
     3: //Triangulo : Hay 2 Tipos: \/  y /_\
       begin
       if PuntosOrdenados[0].Fila = PuntosOrdenados[1].Fila then //Tipo 1: Los dos primeros puntos estan en la misma fila
        begin
        Distancia1 := PuntosOrdenados[0].PosDcha - PuntosOrdenados[1].PosDcha;
        if (PuntosOrdenados[2].PosDcha = PuntosOrdenados[0].PosDcha)
           and (PuntosOrdenados[2].PosIzq = PuntosOrdenados[1].PosIzq)
           and ((PuntosOrdenados[2].Fila - PuntosOrdenados[0].Fila) = Distancia1) then
           begin
           PrintCorrecto('triangle');
           Continue;
           end
        else
           begin
           PrintIncorrectos();
           Continue;
           end;
        end
       else if PuntosOrdenados[1].Fila = PuntosOrdenados[2].Fila then //Tipo 2: El 2do y 3er punto estan en la misma fila
        begin
        Distancia1 := PuntosOrdenados[1].PosDcha - PuntosOrdenados[2].PosDcha;
        if (PuntosOrdenados[1].PosIzq = PuntosOrdenados[0].PosIzq)
           and (PuntosOrdenados[2].PosDcha = PuntosOrdenados[0].PosDcha)
           and ((PuntosOrdenados[2].Fila - PuntosOrdenados[0].Fila)=Distancia1) then
           begin
           PrintCorrecto('triangle');
           Continue;
           end
        else
           begin
           PrintIncorrectos();
           Continue;
           end;
        end
       else  //No hay 2 puntos en la misma fila
        begin
        PrintIncorrectos();
        Continue;
        end;
       end;

/////////////////////////////////////////////
////////////// Paralelogramo ////////////////
/////////////////////////////////////////////

     4:
     begin                                                        //       _    _
       if PuntosOrdenados[0].Fila = PuntosOrdenados[1].Fila then // tipo /_/ o \_\
        begin
        Distancia1 := PuntosOrdenados[0].PosDcha - PuntosOrdenados[1].PosDcha;
        if ((PuntosOrdenados[2].PosIzq = PuntosOrdenados[0].PosIzq)
            and (PuntosOrdenados[3].PosIzq = PuntosOrdenados[1].PosIzq)
            and ((PuntosOrdenados[2].Fila-PuntosOrdenados[0].Fila)=Distancia1))
           or
           ((PuntosOrdenados[2].PosDcha = PuntosOrdenados[0].PosDcha)
            and (PuntosOrdenados[3].PosDcha = PuntosOrdenados[1].PosDcha)
            and ((PuntosOrdenados[2].Fila-PuntosOrdenados[0].Fila)=Distancia1)) then
           begin
           PrintCorrecto('parallelogram');
           Continue;
           end
        else
          begin
          PrintIncorrectos();
          Continue;
          end;
        end                                                              //      /\
       else if PuntosOrdenados[1].Fila = PuntosOrdenados[2].Fila then   //  tipo \/
        begin
        Distancia1 := PuntosOrdenados[1].Fila - PuntosOrdenados[0].Fila;
        if (PuntosOrdenados[1].PosIzq = PuntosOrdenados[0].PosIzq)
           and (PuntosOrdenados[2].PosDcha = PuntosOrdenados[0].PosDcha)
           and ((PuntosOrdenados[3].Fila-PuntosOrdenados[1].Fila)=Distancia1)
           and (PuntosOrdenados[3].PosDcha = PuntosOrdenados[1].PosDcha)
           and (PuntosOrdenados[3].PosIzq = PuntosOrdenados[2].PosIzq) then
         begin
         PrintCorrecto('parallelogram');
         Continue;
         end
        else
          begin
          PrintIncorrectos();
          Continue;
          end;
        end
       else
        begin
        PrintIncorrectos();
        Continue;
        end;
       end;


/////////////////////////////////////////////
/////////////// Hexagono ////////////////////
/////////////////////////////////////////////              ___
                                                  //      /   \
     6:                                          //      |    |
       begin //Solo hay un tipo posible         //       \___/
       Distancia1 := PuntosOrdenados[0].PosDcha - PuntosOrdenados[1].PosDcha;
       if (PuntosOrdenados[0].Fila = PuntosOrdenados[1].Fila)
          and (PuntosOrdenados[2].PosIzq = PuntosOrdenados[0].PosIzq)
          and (PuntosOrdenados[3].PosDcha = PuntosOrdenados[1].PosDcha)
          and (PuntosOrdenados[2].Fila - PuntosOrdenados[0].Fila = Distancia1)
          and (PuntosOrdenados[4].PosDcha = PuntosOrdenados[2].PosDcha)
          and (PuntosOrdenados[5].PosIzq = PuntosOrdenados[3].PosIzq)
          and (PuntosOrdenados[4].Fila - PuntosOrdenados[2].Fila = Distancia1) then
        begin
        PrintCorrecto('hexagon');
        Continue;
        end
      else
        begin
        PrintIncorrectos();
        Continue;
        end;
       end;
   end;//case   

  end;
end.
