var i, j : integer;
begin
  writeln (8192);
  for i := 0 to 1 shl 13 - 1 do begin
    for j := 12 downto 0 do
      if (i and (1 shl j)) <> 0 then
        write (5)
      else
        write (4);
     write (4, ' ');
    for j := 12 downto 0 do
      if (i and (1 shl j)) <> 0 then
        write (5)
      else
        write (4);
     writeln (5);
  end;
end.