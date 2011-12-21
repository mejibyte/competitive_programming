(*
    Checker for NEERC'2006 Problem X: Xtrapolation
    (C) Andrew Stankevich
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program check;
uses
  TestLib, SysUtils;

var
  i, ind: longint;
  ja, pa: string;

begin
  ind := 0;
  while not ans.seekeof do begin
    if (ouf.seekeof) then
      Quit(_PE, 'not enough numbers');

    inc(ind);
    ja := ans.readstring;
    pa := ouf.readstring;

    if not (pa[1] in ['-', '0'..'9']) then
      Quit(_PE, 'invalid character in answer');

    for i := 2 to length(pa) do
      if not (pa[i] in ['0'..'9']) then
        Quit(_PE, 'invalid character in answer');

    if ja <> pa then
      Quit(_WA, format('number %d - expected: %s, found: %s', [ind, ja, pa]));
  end;

  if not ouf.seekeof then
    Quit(_PE, 'too many numbers');

  Quit(_OK, format('%d numbers', [ind]));
end.
