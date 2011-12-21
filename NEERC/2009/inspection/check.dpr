(*
    Checker for NEERC'2009 Problem I: Inspection
    (C) Pavel Mavrin
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;


var
  ja, pa: integer;

  i, j, k, n, x, kk: Integer;
  a, b: array[1..100, 1..100] of boolean;

begin 

  n := inf.readlongint;
  fillchar(a, sizeof(a), 0);
  fillchar(b, sizeof(b), 0);
  for i := 1 to n do begin
    k := inf.readlongint;
    for j := 1 to k do begin
      x := inf.readlongint;
      a[i][x] := true;
    end;
  end;

  pa := ouf.readlongint;
  ouf.nextline;
  for i := 1 to pa do begin
    if (ouf.seekeoln) then Quit(_PE, Format('Empty line in output file: line %d', [i]));
    k := ouf.readlongint;
    if (k < 1) or (k > n) then Quit(_WA, Format('Node number %d is not in range', [k]));
    while not ouf.seekeoln do begin
      kk := ouf.readlongint;
      if (kk < 1) or (kk > n) then Quit(_WA, Format('Node number %d is not in range', [kk]));
      if not a[k][kk] then Quit(_WA, Format('There is no slope from %d to %d', [k, kk]));
      b[k][kk] := true;
      k := kk;
    end;
    ouf.nextline;
  end;

  for i := 1 to n do
    for j := 1 to n do
      if a[i][j] and not b[i][j] then Quit(_WA, Format('Slope from %d to %d was not inspected', [i, j]));

  ja := ans.readlongint;
  if (pa > ja) then 
    Quit(_WA, Format('Not optimal solution: %d instead of %d', [pa, ja]));
  if (pa < ja) then 
    Quit(_FAIL, Format('Jury solution is not optimal : %d instead of %d', [pa, ja]));
  Quit(_OK, Format('%d paths', [pa]));
end.
