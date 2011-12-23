program miners;

const MAX=100005;

var
   n                       : longint;
   shipment                : array[1..MAX] of longint;
   now, prev               : longint;
   dp                      : array[0..1, 0..3, 0..3, 0..3] of longint;
   k, a, b, c, left, right : longint;

procedure read_input;
var
   i  : longint;
   ch : char;
begin
   readln(n);
   for i:=1 to n do begin
      read(ch);
      case ch of
        'F' : shipment[i] := 1;
        'M' : shipment[i] := 2;
        'B' : shipment[i] := 3;
      end;
   end;
end;

function ore(a, b, c : longint) : longint;
var ret : longint;
begin
   ret := 0;
   if (a = 1) or (b = 1) or (c = 1) then ret := ret+1;
   if (a = 2) or (b = 2) or (c = 2) then ret := ret+1;
   if (a = 3) or (b = 3) or (c = 3) then ret := ret+1;
   ore := ret;
end;

function max2(a, b : longint) : longint;
begin
   if a > b then max2 := a else max2 := b;
end;

begin
   read_input;
   now := 0; prev := 1;

   for k:=n downto 1 do begin
      for a:=0 to 3 do begin
         for b:=0 to 3 do begin
            for c:=0 to 3 do begin
               left := ore(shipment[k], shipment[k-1], a) + dp[prev, shipment[k-1], b, c];
               right := ore(shipment[k], b, c) + dp[prev, b, shipment[k-1], a];
               dp[now, a, b, c] := max2(left, right);
            end;
         end;
      end;

      now := now xor 1;
      prev := prev xor 1;
   end;
   writeln(dp[prev, 0, 0, 0]);
end.
