const
	maxn = 1000;
var
	i, j, n: longint;
	a: array [1..maxn] of longint;

procedure put(x, y: longint);
var
	i, t: longint;
begin
	for i := 1 to n do begin
		if a[i] = x then begin
			t := a[i]; a[i] := a[y]; a[y] := t;
			exit;
		end;
	end;
end;

begin
	randseed := 30747747;
	n := 200;

	for i := 1 to n do begin
		j := random(i) + 1;
		a[i] := a[j];
		a[j] := i;
	end;

	put(1, n - 3);
	put(2, n - 1);
	put(n - 1, n - 2);
	put(n, n);

	writeln(n);
	for i := 1 to n do begin
		write(a[i]);
		if (i < n) then
			write(' ');
	end;
	writeln;
end.