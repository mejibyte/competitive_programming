uses
	sysutils;

const
	maxquestions = 2000;
	maxn = 200;

var
	fin, fout, flog: text;
	a, b: array [1..maxn] of longint;
	questions: longint;
	n, i, x, y, z, q, ans: longint;
	qu: array [1..3] of longint;
	s, ss, saves: string;
	p: array [1..maxn] of longint;
	fok: boolean;

procedure ok(s: string);
begin
	rewrite(fout, 'central.out');
	writeln(fout, 0);
	writeln(fout, s);
	close(fout);
	halt(0);
end;

procedure pe(s: string);
begin
	rewrite(fout, 'central.out');
	writeln(fout, 2);
	writeln(fout, s);
	close(fout);
	halt(1);
end;

procedure wa(s: string);
begin
	rewrite(fout, 'central.out');
	writeln(fout, 1);
	writeln(fout, s);
	close(fout);
	halt(1);
end;

begin
	reset(fin, 'central.in');
	readln(fin, n);
	rewrite(flog, 'central.log');
	for i := 1 to n do begin
		read(fin, a[i]);
		p[a[i]] := i;
	end;

	writeln(n);
	flush(output);
	writeln(flog, '< ', n);
	flush(flog);

	questions := 0;
	while true do begin
		readln(s);
		writeln(flog, '> ', s);
		flush(flog);
		if (copy(s, 1, 2) = 'OK') then begin
			delete(s, 1, 2);
			if (s = '') or (s[1] <> ' ') then
				pe('space expected after OK');
			delete(s, 1, 1);
			s := s + ' ';
			for i := 1 to n do begin
				q := pos(' ', s);
				if (q = 0) then
					pe('n numbers expected after OK');
				ss := copy(s, 1, q - 1);
				val(ss, b[i], z);
				if (z <> 0) then
					pe('n numbers expected after OK, ' + ss + ' found instead of number ' + inttostr(i));
				delete(s, 1, q);
			end;
  			if (s <> '') then
  				pe('n numbers expected after OK');

  			fok := true;
  			for i := 1 to n do begin
  				if (a[i] <> b[i]) then begin
  					fok := false;
  				end;
  			end;
			if fok then
  				ok(inttostr(questions) + ' questions');
  			fok := true;
  			for i := 1 to n do begin
  				if (a[i] <> b[n - i + 1]) then begin
  					fok := false;
  				end;
  			end;
			if fok then
  				ok(inttostr(questions) + ' questions');

  			wa('neither of two possiblities');
		end else begin
			inc(questions);
			if (questions > maxquestions) then
				wa('too many questions');
			s := s + ' ';
			saves := s;
			for i := 1 to 3 do begin
				q := pos(' ', s);
				if (q = 0) then
					pe('3 numbers expected');
				ss := copy(s, 1, q - 1);
				val(ss, qu[i], z);
				if (z <> 0) then
					pe('3 numbers expected, ' + ss + ' found instead of number ' + inttostr(i));
				delete(s, 1, q);
			end;

			if (qu[1] < 1) or (qu[1] > n) then
				wa('invalid question: ' + saves);
			if (qu[2] < 1) or (qu[2] > n) then
				wa('invalid question: ' + saves);
			if (qu[3] < 1) or (qu[3] > n) then
				wa('invalid question: ' + saves);

			if (qu[1] = qu[2]) or (qu[1] = qu[3]) or (qu[2] = qu[3]) then
				wa('invalid question: ' + saves);

			ans := 0;	
			for i := 1 to 3 do begin
				x := p[qu[i]];
				y := p[qu[i mod 3 + 1]];
				z := p[qu[(i + 1) mod 3 + 1]];
				if ((y < x) and (x < z)) or ((z < x) and (x < y)) then
					ans := qu[i];
			end;
			writeln(ans);
			flush(output);
			writeln(flog, '< ', ans);
			flush(flog);
		end;
	end;
end.