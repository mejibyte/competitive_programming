const
  n = 1000;

var
  i: integer;
  x: int64;
begin
  randseed := 7;

  for i := 1 to n do begin
    x := random(1000000000) + 1;
    writeln(x);
  end;
  writeln(0);
end.
