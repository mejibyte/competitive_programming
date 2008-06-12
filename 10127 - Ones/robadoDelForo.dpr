program robadoDelForo;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var
  a, l, k, no : integer;
begin
  reset(input, 'input.txt');
  reset(output, 'output.txt');
  while not EOF do
    begin
    readLn(a);
    k := 1;
    no := 1;
    while true do
      begin
        l := k mod a;
        if (l = 0) then
          begin
            writeLn(no);
            break;
          end;
        k := l * 10 + 1;
        no := no + 1;
      end;
    end;
end.
