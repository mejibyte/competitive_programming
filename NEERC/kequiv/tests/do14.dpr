uses SysUtils;

var f : array [0..10000000] of boolean;
    i, k, j, p : integer;
    s : string;
    a, b : array [1..10000] of integer;

procedure add (s : string);
begin
  f[strtoint (s)] := true;
end;

begin
  randseed := 23478432;
  for i := 1 to 50 do begin
    j := random (9999909) + 1;
    for k := 1 to 50 do 
      f[j + k] := true;
  end;

  for i := 1 to 10 do
    for k := 1 to 9999999 do
      if f[k] then begin
        str (k, s);
        for j := 1 to length (s) do begin
          if s[j] = '1' then begin
            s[j] := '3'; add (s);
            s[j] := '7'; add (s);
            s[j] := '1';
          end;
          if s[j] = '3' then begin
            s[j] := '1'; add (s);
            s[j] := '7'; add (s);
            s[j] := '3';
          end;
          if s[j] = '7' then begin
            s[j] := '3'; add (s);
            s[j] := '7'; add (s);
            s[j] := '1';
          end;
          if s[j] = '2' then begin
            s[j] := '9'; add (s);
            s[j] := '2';
          end;
          if s[j] = '9' then begin
            s[j] := '2'; add (s);
            s[j] := '9';
          end;
          if s[j] = '4' then begin
            s[j] := '5'; add (s);
            s[j] := '6'; add (s);
            s[j] := '4';
          end;
          if s[j] = '5' then begin
            s[j] := '4'; add (s);
            s[j] := '6'; add (s);
            s[j] := '5';
          end;
          if s[j] = '6' then begin
            s[j] := '4'; add (s);
            s[j] := '5'; add (s);
            s[j] := '6';
          end;
        end;
      end;

  p := 0;
  for i := 1 to 1000000 do
    if f[i] <> f[i - 1] then begin
      if f[i] then begin inc (p); a[p] := i end else b[p] := i - 1;
    end;
  writeln (p);
  for i := 1 to p do
    writeln (a[i], ' ', b[i]);
end.
