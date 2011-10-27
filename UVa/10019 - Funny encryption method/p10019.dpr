program p10019;

{$APPTYPE CONSOLE}

uses
  SysUtils;

function decToBin(n : integer) : string;
{Convierte un número decimal a uno binario}
begin
  result := '';
  while (n > 0) do
    begin
    result := intToStr(n mod 2) + result;
    n := n div 2;
    end;
end;

function hexToBin(n : integer) : string;
{Convierte un número hexadecimal a uno binario}
begin
  result := decToBin(strToInt('$' + intToStr(n)));
end;

var
 casos, i, m, b1, b2 : integer;
 s : string;
begin
  readLn(casos);
  while casos > 0 do
    begin
      readLn(m);
      s := decToBin(m);
      b1 := 0;
      for i := 0 to length(s) do
          if s[i] = '1' then
              b1 := b1 + 1;
      s := hexToBin(m);
      b2 := 0;
      for i := 0 to length(s) do
          if s[i] = '1' then
              b2 := b2 + 1;
      writeLn(b1, ' ', b2);
      casos := casos - 1;
    end;
end.
