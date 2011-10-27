unit gen;
interface

procedure GenRandom(p0, n, seed: integer);

implementation

procedure GenRandom(p0, n, seed: integer);
var
  i: integer;
begin
  RandSeed := seed;
  for i := 1 to n do 
    if Random(100) < p0 then
      Write('0')
    else
      Write('1');
  WriteLn;
end;

end.