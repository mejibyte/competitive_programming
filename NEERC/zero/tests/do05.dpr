const
  n = 9999;

var
  i: integer;
begin
  randseed := 5;

  writeln(n);
  for i := 1 to n do begin
    if i > 1 then
      write(' ');
    if random(2) = 0 then
      write(1000000000000000)
    else
      write(-1000000000000000);
  end;
  writeln;
end.
