uses SysUtils;

var f : array [0..1000000] of boolean;
    i, k, j, p : integer;
    s : string;
    a, b : array [1..10000] of integer;

procedure add (s : string);
begin
  f[strtoint (s)] := true;
end;

begin
  for i := 1 to 10 do
    f[random (999999) + 1] := true;

  for i := 1 to 1000 do
    for k := 1 to 999999 do
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
