const N = 10000;
var a : array [1..2 * N] of int64;
    i, k, j : integer;
    t : int64;
begin
  randseed := 247892349;
  writeln (N);
  for i := 1 to 2 * N do a[i] := int64 (random (100000000) + 900000000) * 1000000000 + random (1000000000) ;
  for i := 1 to 2 * N do
    for j := i + 1 to 2 * N do
      if a[j] < a[i] then begin t := a[j]; a[j] := a[i]; a[i] := t end;
  for k := 1 to 100 do
   for i := 2 to 2 * N do
     if a[i] <= a[i - 1] + 2 then inc (a[i]);
  for i := 1 to 2 * N do begin
    write (a[i]);
    if odd (i) then write (' ') else writeln;
  end;
end.