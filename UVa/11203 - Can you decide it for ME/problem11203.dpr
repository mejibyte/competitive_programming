program problem11203 (input, output);

{$APPTYPE CONSOLE}


Function StrToInt(Const S: String): Integer;
Var
  E: Integer;
Begin
  Val(S, Result, E);
End;


function allCharsEqual(s : string; c : char) : boolean;
//Returns true if all chars from s equal c
var
  i : integer;
begin
result := true;
for i := 1 to length(s) do
  if s[i] <> c then
    result := false;
end;

function extract(s : string; var x : string; var y: string; var z : string) : boolean;
//returns true if it can extract x, y and z with the correct format, false otherwise.
var
  i : integer;
begin
result := true;
i := 1;
x := '';
//Extract x
while ((s[i] <> 'M') and (i <= length(s))) do
  begin
  x := x + s[i];
  inc(i);
  end;

if (x = '') or (not allCharsEqual(x, '?')) then
  begin
  result := false;
  exit;
  end;


//delete from S from the beggining until the last character of x
s := copy(s, i, length(s));
if (s[1] <> 'M') then //if next char is not an M
  begin
  result := false;
  exit;
  end;

s := copy(s, 2, length(s)); //delete the M
i := 1;
y := '';
//Extract y
while ((s[i] <> 'E') and (i <= length(s))) do
  begin
  y := y + s[i];
  inc(i);
  end;

if (y = '') or (not allCharsEqual(y, '?')) then
  begin
  result := false;
  exit;
  end;

//delete from S from the beggining until the last character of y
s := copy(s, i, length(s));
if s[1] <> 'E' then
  begin
  result := false;
  exit;
  end;

z := copy(s, 2, length(s)); //delete the E
if (z = '') or (not allCharsEqual(z, '?')) then
  begin
  result := false;
  exit;
  end;
end;

function isTheorem(s : string) : boolean;
var
  x, y, z : string;
  i : integer;
begin
result := false;
if extract(s, x, y, z) then
  result := (x + y = z);
end;


var
  howMany : integer;
  i, principalLoop : integer;
  line : String;
  correctChars : Set of char;
  invalid : boolean;

//Main:
begin
//reset(input, 'input.txt');
//reset(output, 'out.txt');
correctChars := ['M', 'E', '?'];
readLn(line);
howMany := strToInt(line);

for principalLoop := 1 to howMany do
  begin
  invalid := false;
  readLn(line);
  for i := 1 to length(line) do
      if not (line[i] in correctChars) then
        invalid := true;
  if invalid then
    writeLn('no-theorem')
  else
    begin
    if isTheorem(line) then
      writeLn('theorem')
    else
      writeLn('no-theorem');
    end;
  end;
end.
