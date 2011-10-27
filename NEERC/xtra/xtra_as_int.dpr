{$Q-,R-}
var
	sum: longint;
	x: longint;
begin
	sum := 0;
	while true do begin
		readln(x);
		if x = 0 then break;
		sum := sum + x;
		writeln(sum);
		flush(output);
	end;
end.