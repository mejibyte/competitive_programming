program p579;

{$APPTYPE CONSOLE}

uses
  SysUtils, Math;

procedure leer(var hora : integer; var minuto : integer);
var
  entrada : string;
begin
  readLn(entrada);
  hora := strToInt(copy(entrada, 1, pos(':', entrada) - 1));
  delete(entrada, 1, pos(':', entrada));
  minuto := strToInt(entrada);
end;

var
  h, m : integer; //hora y minuto
  ah, am : double; //angulos que hay entre las 12 en punto y la hora y el minuto
  temp : double;

begin
  reset(input, 'input.txt');
  reset(output, 'output.txt');
  leer(h, m);
  while (h + m > 0) do
    begin
    if h = 12 then
      h := 0;
    ah := h * 30 + m * 0.5;
    am := m * 6;
    temp := abs(ah - am);
    if temp > 180 then
      temp := 360 - temp;
    temp := floor(1000 * temp + 0.5) / 1000; //redondea a 3 cifras
    writeLn(format('%d.%.3d', [floor(temp), floor((temp - floor(temp)) * 1000)]));
    leer(h, m);
    end;
end.
