(*
    Checker for NEERC'2006 Problem Y: Yield
    (C) Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

uses
  TestLib, SysUtils;

var
  ja, pa: Integer;
begin
  ja := ans.ReadInteger();
  pa := ouf.ReadInteger();

  if not ouf.SeekEof then 
    Quit(_PE, 'Extra information in the output file');

  if ja <> pa then
    Quit(_WA, Format('%d instead of %d', [pa, ja]))
  else
    Quit(_OK, Format('%d', [ja]));
end.
