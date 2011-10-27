program p10110_Accepted;

{$APPTYPE CONSOLE}

uses
  Math;

var
  n, raiz : Double;

begin
  read(n);
  while n <> 0 do
    begin
    raiz := sqrt(n);
    if raiz = floor(raiz) then //Si raiz es entero...
                               //Entonces n es un cuadrado perfecto,
                               //y por lo tanto tiene un número impar
                               //de divisores
      writeLn('yes')
    else
      writeLn('no');
    read(n);
    end;
end.
