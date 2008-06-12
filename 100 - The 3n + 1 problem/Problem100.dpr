
program problem100 (input, output);

{$IFNDEF ONLINE_JUDGE}
{$APPTYPE CONSOLE}
{$ENDIF}

var
  i, j: integer;

function getCycleLength(N: integer): integer;
var k: integer;
begin
  k := 1;
  while N <> 1 do begin
    if odd(N) then N := 3*N + 1
    else N := N div 2;
    k := k + 1;
  end;
  getCycleLength := k;
end;

function getMaxCycleLength(i, j: integer): integer;
var k: integer;
  max, curCL: integer;
begin
  max := 0;
  for k:=i to j do begin
    curCL := getCycleLength(k);
    if curCL > max then max := curCL;
  end;
  getMaxCycleLength := max;
end;

begin
  while not eof(input) do begin
    readln(i, j);
    write(i, ' ', j, ' ');
    if i < j then
      writeln(getMaxCycleLength(i, j))
    else
      writeln(getMaxCycleLength(j, i));
  end;
end.
