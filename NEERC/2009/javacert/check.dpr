(*
    Checker for NEERC'2009 Problem J: Java Certification
    (C) Pavel Mavrin
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

type
  output = record
    n: array[1..100] of integer;
    w: array[1..100] of integer;
    res: integer;
  end;
  
var
  ja, pa: output;
  m: integer;
  nn, kk: integer;
  p: array[1..100] of integer;  

function rint(a: double): integer;
var
  res: integer;
begin
  res := round(a);
  if (abs(abs(res - a) - 0.5) < 1e-9) then begin
    if (res mod 2 = 1) then begin
      if (res > a) then res := res - 1 else res := res + 1;
    end;
  end;  
  rint := res;
end;

procedure readoutput(var res: output; var strm: InStream; isPA: boolean);
var
  i, s, min, max, pp: integer;
begin
  for i := 1 to m do begin
    res.w[i] := strm.readlongint;
    res.n[i] := strm.readlongint;
    if (isPA) then begin
      if (res.n[i] < 1) or (res.n[i] > 100) then
        quit(_WA, format('Invalid number of questions: %d, must be 1..100', [res.n[i]]));   
      if (res.w[i] < 0) or (res.w[i] > res.n[i]) then
        quit(_WA, format('Invalid number of wrong answers: %d, must be 0..%d', [res.w[i], res.n[i]]));
    end;
  end;
  if isPA then begin
    s := 0;
    for i := 1 to m do begin
      s := s + res.n[i];
    end;
    if (s <> nn) then quit(_WA, format('Wrong sum of questions: %d, must be %d', [s, nn]));
    s := 0;
    for i := 1 to m do begin
      s := s + (res.n[i] - res.w[i]);
    end;
    if (s <> kk) then quit(_WA, format('Wrong sum of correct answers: %d, must be %d', [s, kk]));
    for i := 1 to m do begin
      pp := rint(100 * (res.n[i] - res.w[i]) / res.n[i]);
      if (pp <> p[i]) then quit(_WA, format('Wrong percentage for category %d: %d instead of %d', [i, pp, p[i]]));
    end;
  end;
  min := 1000;
  max := 0;
  for i := 1 to m do begin
    if (res.n[i] < min) then min := res.n[i];
    if (res.n[i] > max) then max := res.n[i];
  end;
  res.res := max - min;
end;

var
  i: integer;

begin 

  kk := inf.readlongint;
  nn := inf.readlongint;
  m := inf.readlongint;
  for i := 1 to m do 
    p[i] := inf.readlongint;
    
  readoutput(pa, ouf, true);
  readoutput(ja, ans, false);

  if (pa.res > ja.res) then quit(_WA, format('Not optimal soluton: %d instead of %d', [pa.res, ja.res]));
  if (pa.res < ja.res) then quit(_FAIL, format('Jury solution is not optimal: %d instead of %d', [pa.res, ja.res]));

  quit(_OK, '');
end.
