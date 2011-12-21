(*
    Checker for NEERC'2006 Problem Z: Zero-complexity Transposition
    (C) Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

uses
  TestLib, SysUtils;

var
  n, i, j: Integer;
  ja, pa: String;
  wa: String;
begin
  n := inf.readInteger;
  wa := '';

  for i := 1 to n do begin
    if ouf.SeekEoln then
      Quit(_PE, 'Unexpected line end');

    ja := ans.readWord(blanks, blanks);
    pa := ouf.readWord(blanks, blanks);

    for j := 1 to Length(pa) do begin
      if not (pa[j] in ['-', '0'..'9']) then
        Quit(_PE, 'Invalid character'); 
    end;

    if (wa = '') and (ja <> pa) then
      wa := Format('%s instead of %s', [pa, ja]);
  end;

  if not ouf.SeekEof then 
    Quit(_PE, 'Extra information in the output file');

  if wa <> '' then
    Quit(_WA, wa);

  Quit(_OK, Format('%d', [n]));
end.
