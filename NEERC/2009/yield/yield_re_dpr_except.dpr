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
  try 
    s := a div s;
  except
    on EDivByZero do s := a + b;
  end;

  WriteLn(s);

  Close(input);
  Close(output);
end.