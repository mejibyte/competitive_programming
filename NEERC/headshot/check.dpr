(*
    Checker for NEERC'2009 Problem H: Headshot
    (C) Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

function NextOutput(var strm: InStream): String;
begin
  Result := strm.ReadString;
  if (Result <> 'SHOOT') and (Result <> 'ROTATE') and (Result <> 'EQUAL') then
    strm.Quit(_PE, Format('Invalid string: %s', [Result]));
  if not strm.SeekEof then
    strm.Quit(_PE, 'Extra data in output');
end;

var
  ja, pa: String;

begin 
  ja := NextOutput(ans);
  pa := NextOutput(ouf);

  if pa <> ja then
    Quit(_WA, Format('%s istead of %s', [pa, ja]));

  Quit(_OK, Format('%s', [pa]));
end.
