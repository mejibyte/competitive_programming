program problem11203 (input, output);

{$APPTYPE CONSOLE}


Function StrToInt(Const S: String): Integer;
Var
  E: Integer;
Begin
  Val(S, Result, E);
End;


function formadaPor(s : string; c : char) : boolean;
var
  i : integer;
begin
result := true;
for i := 1 to length(s) do
  begin
  if s[i] <> c then
    begin
    result := false;
    exit;
    end;
  end;
end;

{function isAxiom(s : String): boolean; overload;
var
  x1, x2 : String;
  i : integer;
begin
result := true;
x1 := '';
i:=1;
while ((s[i] <> 'M') and (i <= length(s))) do
  begin
  x1 := x1 + s[i];
  inc(i);
  end;

if (x1 = '') or (not formadaPor(x1, '?')) then
  begin
  result := false;
  exit;
  end;

s := copy(s, i, length(s));
if (s[1] <> 'M') or (s[2] <> '?') or (s[3] <> 'E') then
  begin
  result := false;
  exit;
  end;

x2 := copy(s, 4, length(s));
if (not formadaPor(x2, '?')) or ((length(x1) + 1) <> length(x2)) then
  begin
  result := false;
  exit;
  end;
end; }


function isAxiom(x, y, z : string) : boolean; overload;
begin
result := true;
if (length(x) + 1) <> (length(z)) then
  result := false;

end;

function isTheorem(s : string) : boolean;
var
  x, y, z : string;
  i : integer;
begin
i := 1;
x := '';
while ((s[i] <> 'M') and (i <= length(s))) do
  begin
  x := x + s[i];
  inc(i);
  end;

if (x = '') or (not formadaPor(x, '?')) then
  begin
  result := false;
  exit;
  end;

s := copy(s, i, length(s)); //delete from the beggining until the character before the first M
if s[1] <> 'M' then
  begin
  result := false;
  exit;
  end;

s := copy(s, 2, length(s)); //delete the M
i := 1;
y := '';
while ((s[i] <> 'E') and (i <= length(s))) do
  begin
  y := y + s[i];
  inc(i);
  end;

if (y = '') or (not formadaPor(y, '?')) then
  begin
  result := false;
  exit;
  end;

s := copy(s, i, length(s)); //delete from the beggining until the character before the first E
if s[1] <> 'E' then
  begin
  result := false;
  exit;
  end;

z := copy(s, 2, length(s)); //delete the E
if not formadaPor(z, '?') then
  begin
  result := false;
  exit;
  end;


if length(y) = 1 then
  result := isAxiom(x, y, z)
else
  begin
  y := copy(y, 1, length(y) - 1); //borra el ultimo
  z := copy(z, 1, length(z) - 1);
  result := isTheorem(x+'M'+y+'E'+z);
  end;
end;

var
  cuantos : integer;
  i, j, principalLoop : integer;
  entrada : String;
  letrasCorrectas : Set of char;
  invalid : boolean;

begin

//reset(input, 'input.txt');
//reset(output, 'out.txt');


letrasCorrectas := ['M', 'E', '?'];
readLn(entrada);
cuantos := strToInt(entrada);

{if isAxiom('?E??') then writeLn('si') else writeLn('no');
if isAxiom('??M?E???') then writeLn('si') else writeLn('no');
if isAxiom('??M?E??') then writeLn('si') else writeLn('no');
if isAxiom('?M??E??') then writeLn('si') else writeLn('no');
if isAxiom('?M?E??') then writeLn('si') else writeLn('no');
if isAxiom('???M?E????') then writeLn('si') else writeLn('no');
if isAxiom('?E?M??') then writeLn('si') else writeLn('no');  }

{if isTheorem('?E??') then writeLn('si') else writeLn('no');
if isTheorem('??M?E???') then writeLn('si') else writeLn('no');
if isTheorem('??M?E??') then writeLn('si') else writeLn('no');
if isTheorem('?M??E??') then writeLn('si') else writeLn('no');
if isTheorem('?M?E??') then writeLn('si') else writeLn('no');
if isTheorem('???M?E????') then writeLn('si') else writeLn('no');
if isTheorem('?E?M??') then writeLn('si') else writeLn('no');
if isTheorem('?M???E????') then writeLn('si') else writeLn('no');}

for principalLoop := 1 to cuantos do
  begin
  invalid := false;
  readLn(entrada);
  j := length(entrada);
  for i := 1 to j do
      if not (entrada[i] in letrasCorrectas) then
      begin
        invalid := true;
        break;
      end;
  if invalid then
    writeLn('no-theorem')
  else
    begin
    if isTheorem(entrada) then
      writeLn('theorem')
    else
      writeLn('no-theorem');
    end;
  end;

end.
