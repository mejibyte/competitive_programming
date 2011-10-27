const
  n = 10000;

var
  i: integer;
  x: int64;
begin
  randseed := 6;

  writeln(n);
  for i := 1 to n do begin
    if i > 1 then
      write(' ');
    x := int64(random(10000000))*100000000 + random(100000000) + 1;
    if random(2) = 0 then
      x := -x;
    write(x);
  end;
  writeln;
end.
