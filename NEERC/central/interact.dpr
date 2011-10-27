uses
	sysutils;

const
	maxquestions = 2000;
	maxn = 200;

var
	fin, fout, flog: text;
	a, b: array [1..maxn] of longint;
	questions: longint;
	n, i, j, x, y, z, q, ans: longint;
	qu: array [1..3] of longint;
	s, ss, saves: string;

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

  			for i := 1 to n do begin
  				for j := i + 1 to n do begin
  				    if b[i] = b[j] then
  				    	wa('permutation expected');
  				end;
  			end;         
  			if n = 3 then
  				ok(inttostr(questions) + ' questions');

  			for i := 1 to n do begin
  				if b[i] = 2 then b[i] := 1;
  				if a[i] = 2 then a[i] := 1;
  				if b[i] = n - 1 then b[i] := n;
  				if a[i] = n - 1 then a[i] := n;
  			end;

  			for i := 1 to n do 
  			    if a[i] <> b[i] then
  			    	wa('wrong permutation');
  			    	  
  			ok(inttostr(questions) + ' questions');
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
				x := a[qu[i]];
				y := a[qu[i mod 3 + 1]];
				z := a[qu[(i + 1) mod 3 + 1]];
				if ((y < x) and (x < z)) or ((z < x) and (x < y)) then
					ans := a[qu[i]];
			end;
			writeln(ans);
			flush(output);
			writeln(flog, '< ', ans);
			flush(flog);
		end;
	end;
end.