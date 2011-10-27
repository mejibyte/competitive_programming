unit gen;

interface

procedure GenRandom(r, c, pl, pr, seed: integer);

implementation

procedure GenRandom(r, c, pl, pr, seed: integer);
var
  i, j, k: integer;
begin
  RandSeed := seed;
  Write(r, ' ', c, ' ');
  Write(1 + Random(9));
  for i := 2 to 100 do
    Write(Random(10));
  WriteLn;
  for i := 1 to r - 1 do begin
    for j := 1 to c - 1 do begin
      k := Random(100);
      if k < pl then 
        Write('L')
      else if k < pl + pr then
        Write('R')
      else
        Write('N');
    end;
    WriteLn;
  end;
end;

end.