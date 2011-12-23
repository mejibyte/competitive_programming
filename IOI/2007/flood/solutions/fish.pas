program ribari;

const MAXN = 100000;

var
   position, food : array[0..MAXN-1] of int64;
   n, i           : longint;
   low, high, mid : int64;

function ok(K : int64) : boolean;
var carry, x : int64;
   i : longint;
begin
   carry:=0;
   for i:=0 to n-2 do
   begin
      x := food[i] + carry;

      if x<K then
      begin
         carry := x - K - (position[i+1] - position[i]);
      end
      else if x>= K then
      begin
         carry := x - K - (position[i + 1] - position[i]);
         if carry<0 then carry := 0;
      end;
   end;
   ok := (food[n-1]+carry)>=K;
end;

begin
   low := 0;
   high := 1;

   readln(n);

   for i:=0 to n-1 do
   begin
      readln(position[i], food[i]);
      if food[i]>high then high := food[i];
   end;

   while low < high do
   begin
      mid := (low + high + 1) div 2;
      if ok(mid) then
         low := mid
      else
         high := mid - 1;
   end;

   writeln(low);
end.
