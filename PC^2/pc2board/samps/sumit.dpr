{ Sample problem proba.dpr }

{$APPTYPE CONSOLE}

{ $Id: sumit.dpr,v 1.1 2005/03/06 05:13:57 laned Exp $ }

uses SysUtils;  { for StrToInt }

procedure processfile (filename : string);
var
  s : string;
  sum : longint;
  v : longint;
  tf : text;
begin

 sum := 0;
 AssignFile (tf, filename);
  {$i-} reset (tf); {$i+}
  if ioresult = 0 then
  begin
    while not eof (tf) do
    begin
      readln (tf, s);
      v := strtoInt (s);
      if (v > 0) then
         sum := sum + v;
    end;
    close (tf);
    writeln('The sum of the positive integers is ',sum);
  end

  else
     writeln ('Could not open file '+filename+' for read ');
end;


begin
     processfile ('sumit.dat');
end.
