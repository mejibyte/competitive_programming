const
	maxn = 1000;
var
	i, n: longint;
	a: array [1..maxn] of longint;
begin
	n := 100;
	for i := 1 to n do begin
		a[i] := i;
	end;

	writeln(n);
	for i := 1 to n do begin
		write(a[i]);
		if (i < n) then
			write(' ');
	end;
	writeln;
end.