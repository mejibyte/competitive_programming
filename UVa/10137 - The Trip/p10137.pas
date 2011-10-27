program p10137;

{$APPTYPE CONSOLE}

uses
  SysUtils, Math;

function isInt(d : double) : boolean;
begin
isInt := (floor(d) = d);
end;

procedure miStringReplace(var s : string; old : char; nuevo : char);
var
i : integer;
begin

for i := 0 to length(s) do
        begin
        if s[i] = old then
                s[i] := nuevo;
        end;

end;

procedure printFloat(d : double);
var
  ReplaceFlags : TReplaceFlags;
  s : String;
begin
  s := format('$%f', [d]);
  miStringReplace(s, ',', '.');
  writeln(s);
  //writeln(StringReplace(format('$%f', [d]), ',', '.'));
  //writeln(StringReplace(format('$%f', [d]), ',', '.' ReplaceFlags));
  //writeln(StringReplace(formatFloat('$#0.00', d), ',', '.', ReplaceFlags));
end;

var
  s : Array[0..1001] of double;
  n, i : integer;
  promedio, mas, menos : double;
  redondee : boolean;
  ReplaceFlags : TReplaceFlags;

begin
  //reset(input, 'inside.txt');
  //reset(output, 'outside.txt');
  read(n);
  while n <> 0 do
    begin
    promedio := 0;
    mas := 0;
    menos := 0;
    for i:=0 to n-1 do
      begin
      read(s[i]);
      promedio := promedio + s[i];
      end;
    promedio := promedio / n;
    if (isInt(promedio * 100)) then
      redondee := false
    else
      begin
      redondee := true;
      promedio := floor(promedio * 100) / 100;
      end;
    //printFloat(promedio); writeLn('(Redondeado hacia abajo)');
    for i:=0 to n-1 do
      begin
      if s[i] < promedio then
        menos := menos + abs(s[i] - promedio)
      else
        if s[i] > promedio then
          begin
          if redondee then
            mas := mas + abs(s[i] - (promedio + 0.01))
          else
            mas := mas + abs(s[i] - promedio);
          end;
      end;
    if mas > menos then
      printFloat(mas)
    else
      printFloat(menos);
    read(n);
    end;
end.
