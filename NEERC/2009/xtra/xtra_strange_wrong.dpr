{$O-}
var
  sum, num: int64;
begin
  sum := 0;
  while (true) do 
  begin
    read(num);
    if (num = 0) then 
    begin
      sum := sum mod num;
      writeln('non-integer');
      break;
    end;
    sum := sum + num;
    writeln(sum);
    flush(output);
  end;
end.
