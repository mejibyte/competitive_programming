program robot;

var
   vis : array[-1000..1000, -1000..1000] of boolean;
   sol : longint;

procedure dfs(r, c : longint);
const
   command : array[0..3] of string  = ('up', 'down', 'left', 'right');
   dr      : array[0..3] of longint = (-1, 1, 0, 0);
   dc      : array[0..3] of longint = (0, 0, -1, 1);
var
   dir    : longint;
   reply  : string;
   nr, nc : longint;
begin
   sol := sol+1;
   for dir:=0 to 3 do begin
      nr := r+dr[dir]; nc := c+dc[dir];
      if vis[nr, nc] then continue;

      vis[nr, nc] := true;
      writeln(command[dir]);
      readln(reply);
      if reply = 'ok' then begin
         dfs(nr, nc);
         writeln(command[dir xor 1]);
         readln(reply);
      end;
   end;
end;

begin
   vis[0, 0] := true;
   dfs(0, 0);
   writeln(sol);
end.
