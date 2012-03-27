program p10127;

{$APPTYPE CONSOLE}

function procesar(n : integer) : integer;
{Explicación del algoritmo:

Para hallar la longitud del múltiplo más pequeño que sea una cadena de 1111's
lo que hago es hallar primero el múltiplo que me da en la posición de las
unidades un 1 (Nótese que por ser un múltiplo no divisible por 2 ó 5 al construir
su tabla del 0 al 9 habrá un múltiplo que termina en 0, otro en 1, otro 2, ... y
otro en 9). Una vez hallado el mútiplo que me da un 1 en las unidades, lo
multiplico por N y lo que "lleva" lo acumulo en la variable carry e incremento
la cuenta correspondiente al resultado. Ahora repito lo mismo, sólo que no tengo
que encontrar el múltiplo que sus unidades sean 1 sino el múltiplo que al sumarle
carry sus unidades sean 1. Esto se hace hasta que carry sea 0.

}
var
  tabla : Array[0..9] of integer;
  carry, multiplo, i, ultimaCifra : integer;
begin
  result := 0;
  for i := 0 to 9 do
    tabla[i] := n * i;

  ultimaCifra := 1;
  carry := 0;

  repeat
    //2
    multiplo := 0;
    while tabla[multiplo] mod 10 <> ultimaCifra do
      multiplo := multiplo + 1;
    //3 y 5
    carry := (n * multiplo + carry) div 10;
    //6
    i := carry;
    while (i mod 10 <> 1) do
      i := i + 1;
    ultimaCifra := i - carry;
    //4
    result := result + 1;
  until carry = 0;

end;

var
  n : integer;
begin
  while not EOF do
    begin
      readLn(n);
      writeLn(procesar(n));
    end;
end.
 