(*
    Checker for NEERC'2009 Problem G: Garbling Game
    (C) Roman Elizarov
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program Check;

uses
  TestLib, SysUtils;

type 
  Output = array of integer;

function NextOutput(var strm: InStream): Output;
begin
  SetLength(Result, 0);
  while not strm.SeekEof do begin
    SetLength(Result, Length(Result) + 1);
    Result[Length(Result) - 1] := strm.ReadInteger();
  end;
end;

var
  ja, pa: Output;
  i: Integer;

begin 
  ja := NextOutput(ans);
  pa := NextOutput(ouf);

  if not ouf.SeekEof then
    Quit(_PE, 'Extra data in output');

  if Length(pa) <> Length(ja) then
    Quit(_WA, Format('%d numbers instead of %d', [Length(pa), Length(ja)]));

  for i := 1 to Length(pa) do
    if pa[i - 1] <> ja[i - 1] then
      Quit(_WA, Format('%d instead of %d on line %d', [pa[i - 1], ja[i - 1], i]));

  Quit(_OK, Format('%d numbers', [Length(pa)]));
end.
