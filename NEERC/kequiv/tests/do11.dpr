
procedure gensame (x : integer);
var i, j : integer;
begin
  for i := 0 to 1 shl x - 1 do begin
    for j := x - 1 downto 0 do
      if (i and (1 shl j)) <> 0 then
        write (5)
      else
        write (4);
     write (4, ' ');
    for j := x - 1 downto 0 do
      if (i and (1 shl j)) <> 0 then
        write (5)
      else
        write (4);
     writeln (5);
  end;
end;

begin
  writeln (10000);
  gensame (4);
  gensame (8);
  gensame (9);
  gensame (10);
  gensame (13);
end.