{$r+,q+,o-}
{$apptype console}
uses
	SysUtils, Math;

type
	int = longint;

procedure check(expr: boolean; msg: string);
begin
	if (not expr) then begin
		writeln(erroutput, 'Error: ', msg);
		assert(false);
	end;
end;

procedure checkBounds(n: int; low: int; hi: int; varName: string);
begin
	check((low <= n) and (n <= hi), varName + ' is out of bounds [' + inttostr(low) + ', ' + inttostr(hi) + ']');
end;

var
	n, m, u, d, i: int;
	a, b, f, answer: int;

begin
	reset(input, 'business.in');
	rewrite(output, 'business.out');

	read(n, m);
	checkBounds(n, 1, 1000000, 'n');
	checkBounds(m, 1, 100, 'm');
	answer := 2000000000;
	for i := 1 to m do begin
		read(u, d);
		checkBounds(u, 1, 1000, 'u');
		checkBounds(d, 1, 1000, 'd');
		a := (n * d + u + d - 1) div (u + d);
		b := n - a;
		f := a * u - b * d;
		answer := min(answer, f);
	end;
	writeln(answer);

	close(input);
	close(output);
end.
