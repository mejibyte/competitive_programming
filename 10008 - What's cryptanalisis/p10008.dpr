program p10008;

{$APPTYPE CONSOLE}
uses
  SysUtils;

var
  a : Array[0..25] of integer;
  b : Array[0..25] of char;
  lineas :  integer;
  entrada : string;
  i,j, tempi : integer;
  tempc : char;

begin
  for i := 0 to 25 do
    b[i] := char(i+65);
  fillChar(a, 26, 0);
  readLn(lineas);
  while (lineas > 0) do
    begin
      readLn(entrada);
      for i := 1 to length(entrada) do
        begin
          entrada[i] := uppercase(entrada[i])[1];
          if ((integer(entrada[i]) >= 65) and (integer(entrada[i]) <= 90)) then
            begin
              inc(a[integer(entrada[i]) - 65], 1);
            end;
        end;
      lineas := lineas - 1;
    end;
  for i := 0 to 24 do
    for j := i + 1 to 25 do
      begin
        if a[i] < a[j] then
          begin
            tempi := a[i];
            a[i] := a[j];
            a[j] := tempi;
            tempc := b[i];
            b[i] := b[j];
            b[j] := tempc;
          end
        else if a[i] = a[j] then
          begin
            if integer(b[i]) > integer(b[j]) then
              begin
            tempi := a[i];
            a[i] := a[j];
            a[j] := tempi;
            tempc := b[i];
            b[i] := b[j];
            b[j] := tempc;
              end;
          end;
      end;
  for i := 0 to 25 do
    begin
      if a[i] > 0 then
        writeLn(b[i], ' ', a[i]);
    end;
end.
