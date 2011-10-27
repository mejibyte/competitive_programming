program p591;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var
  b : array[0..49] of byte;
  n, //cantidad de stacks
  altura,  caso, i, suma, movs : integer;
begin
  caso := 0;
  read(n);
  while (n <> 0) do
    begin
      for i := 0 to n - 1 do
        read(b[i]);
      readLn;
      //Terminé de leer. Procesar caso aquí
      caso := caso + 1;
      altura := 0;
      for i := 0 to n - 1 do
        altura := altura + b[i];
      altura := altura div n;
      movs := 0;
      for i := 0 to n - 1 do
        if b[i] > altura then
          movs := movs + (b[i] - altura);
      write('Set #'); writeLn(caso);
      write('The minimum number of moves is ', movs); writeLn('.');
      writeLn;
      read(n);
    end;
end.
