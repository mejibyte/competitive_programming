const
	maxn = 200;

var
	i, j, n, p1min, p2min, p1max, p2max: longint;
	a: array [1..maxn] of longint;

function ask(i, j, k: longint): longint;
begin
	writeln(i, ' ', j, ' ', k);
	flush(output);

	readln(result);
end;

procedure find4(i, j, k, l: longint; var r1, r2: longint; s: longint);
var
	v1, v2, v3, v4: longint;
begin
    v1 := ask(i, j, k);
    v2 := ask(i, j, l);
    v3 := ask(i, k, l);
    v4 := ask(j, k, l);
    if v1 = v2 then begin
    	if v1 * s < v3 * s then begin
    		r1 := i;
    		r2 := j;
    	end else begin
    		r1 := k;
    		r2 := l;
    	end;
    end;
    if v1 = v3 then begin
    	if v1 * s < v2 * s then begin
    		r1 := i;
    		r2 := k;
    	end else begin
    		r1 := j;
    		r2 := l;
    	end;
    end;
    if v1 = v4 then begin
    	if v1 * s < v2 * s then begin
    		r1 := j;
    		r2 := k;
    	end else begin
    		r1 := i;
    		r2 := l;
    	end;
    end;
end;
  
begin
	readln(n);
	assert((3 <= n) and (n <= 200));
	if n = 3 then begin
		writeln('OK 1 2 3');
		flush(output);
		halt(0);
	end;

	i := 4;
	p1min := 1;
	p2min := 2;
	p1max := 1;
	p2max := 2;
	while (i <= n) do begin
		find4(p1min, p2min, i - 1, i, p1min, p2min, 1);
		find4(p1max, p2max, i - 1, i, p1max, p2max, -1);
  		i := i + 2;
		if i = n + 1 then begin
			j := 1;
			while (j = p1min) or (j = p2min) do inc(j);
    		find4(p1min, p2min, j, i - 1, p1min, p2min, 1);
			j := 1;
			while (j = p1max) or (j = p2max) do inc(j);
    		find4(p1max, p2max, j, i - 1, p1max, p2max, -1);
		end;
	end;

    for i := 1 to n do begin
		if i = p1min then 
			a[i] := 1
		else if i = p2min then
			a[i] := 2
		else if i = p1max then
			a[i] := n - 1
		else if i = p2max then
			a[i] := n
		else
			a[i] := ask(p1min, i, p1max);
	end;

	write('OK');
	for i := 1 to n do begin
		write(' ', a[i]);
	end;
	writeln;
	flush(output);
end.