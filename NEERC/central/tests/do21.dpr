const
	maxn = 1000;
var
	i, j, n: longint;
	a: array [1..maxn] of longint;
begin
	randseed := 21747747;
	n := 200;

	for i := 1 to n do begin
		j := random(i) + 1;
		a[i] := a[j];
		a[j] := i;
	end;

	writeln(n);
	for i := 1 to n do begin
		write(a[i]);
		if (i < n) then
			write(' ');
	end;
	writeln;
end.