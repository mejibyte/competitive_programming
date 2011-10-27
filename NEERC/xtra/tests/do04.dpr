const
  n = 1000;

var
  i: integer;
begin
  randseed := 4;

  for i := 1 to n do begin
    writeln(random(2000) + 1);
  end;
  writeln(0);
end.
