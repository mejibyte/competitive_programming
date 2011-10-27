const
  n = 1234;

var
  i: integer;
begin
  randseed := 4;

  writeln(n);
  for i := 1 to n do begin
    if i > 1 then
      write(' ');
    write(random(2000) - 1000);
  end;
  writeln;
end.
