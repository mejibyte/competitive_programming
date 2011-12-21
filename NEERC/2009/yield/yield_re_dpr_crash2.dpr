{$apptype console}
{$r+,o+}

uses
  SysUtils;

var
  a, b, s: integer;

begin
  AssignFile(input, 'yield.in');
  Reset(input);
  AssignFile(output, 'yield.out');
  Rewrite(output);

  ReadLn(a, b);
  s := 0;
  s := a div s; // crash here

  WriteLn(s);

  Close(input);
  Close(output);
end.