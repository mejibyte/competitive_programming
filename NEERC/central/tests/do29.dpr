const
	maxn = 1000;
var
	i, j, n: longint;
	a: array [1..maxn] of longint;
begin
	randseed := 29747747;
	n := 100 + random(101);

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