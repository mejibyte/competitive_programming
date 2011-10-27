{$Q-,R-}
var
	sum: int64;
	x: longint;
begin
	sum := 0;
	while true do begin
		readln(x);
		sum := sum + x;
		writeln(sum);
		flush(output);
		if x = 0 then break;
	end;
end.