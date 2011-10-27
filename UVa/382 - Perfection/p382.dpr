program p382;

{$APPTYPE CONSOLE}

uses
  SysUtils;

function revisar(num : integer) : string;
var
 mitad, i, suma : integer;
begin
if (num = 1) then
  result := 'DEFICIENT'
else
  begin
  suma := 1;
  mitad := (num div 2) + 1;
  for i := 2 to mitad do
      if num mod i = 0 then
        suma := suma + i;
  if suma > num then
    result := 'ABUNDANT'
  else if suma < num then
    result := 'DEFICIENT'
  else
    result := 'PERFECT';
  end;
end;

var
  num : integer;

begin
writeLn('PERFECTION OUTPUT');
read(num);
while num > 0 do
  begin
  write(format('%5d', [num]));
  write('  ');
  writeLn(revisar(num));
  read(num);
  end;
writeLn('END OF OUTPUT');
end.
