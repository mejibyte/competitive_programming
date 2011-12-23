program sails;

const MAXN = 100000;
const MAXH = 100000;
const MAXH_POW2 = 262144;

type jedro = record
   h, x : longint;
end;

var
   n                     : longint;
   A, B                  : array[1..MAXN] of jedro;
   sortcnt               : array[0..MAXH] of longint;
   delta                 : array[0..MAXH] of longint;
   tree_first, tree_last : array[0..MAXH_POW2] of longint;

procedure input;
var i : longint;
begin
   readln(n);
   for i:=1 to n do
      readln( A[i].h, A[i].x );
end;

procedure sort;
(* Sort the sails in ascending order of height. Uses counting sort. *)
var i : longint;
begin
   for i:=0 to MAXH do sortcnt[i] := 0;
   for i:=1 to n do sortcnt[A[i].h] := sortcnt[A[i].h] + 1;
   for i:=1 to MAXH do sortcnt[i] := sortcnt[i] + sortcnt[i-1];

   for i:=n downto 1 do begin
      B[sortcnt[A[i].h]] := A[i];
      sortcnt[A[i].h] := sortcnt[A[i].h] - 1;
   end;

   for i:=1 to n do A[i] := B[i];
end;

function First(a, b, i, lo, hi : longint) : longint;
var
   mid, L, R : longint;
begin
   if (lo >= b) or (hi <= a) then begin
      First := -1;
      exit;
   end;
   if (lo >= a) and (hi <= b) then begin
      First := tree_first[i];
      exit;
   end;

   mid := (lo+hi) div 2;
   L := First(a, b, 2*i, lo, mid);
   R := First(a, b, 2*i+1, mid, hi);
   if L <> -1 then First := L else First := R;
end;

function Last(a, b, i, lo, hi : longint) : longint;
var
   mid, L, R : longint;
begin
   if (lo >= b) or (hi <= a) then begin
      Last := -1;
      exit;
   end;
   if (lo >= a) and (hi <= b) then begin
      Last := tree_last[i];
      exit;
   end;

   mid := (lo+hi) div 2;
   L := Last(a, b, 2*i, lo, mid);
   R := Last(a, b, 2*i+1, mid, hi);
   if R <> -1 then Last := R else Last := L;
end;

procedure Update(x, val, i, lo, hi : longint);
var
   mid : longint;
begin
   if (lo > x) or (hi <= x) then exit;

   if (lo+1 = hi) then begin
      delta[x] := delta[x] + val;
      if delta[x] <> 0 then begin
         tree_first[i] := x;
         tree_last[i] := x;
      end else begin
         tree_first[i] := -1;
         tree_last[i] := -1;
      end;
   end else begin
      mid := (lo+hi) div 2;
      Update( x, val, 2*i, lo, mid );
      Update( x, val, 2*i+1, mid, hi );
      if tree_first[2*i] <> -1 then tree_first[i] := tree_first[2*i] else tree_first[i] := tree_first[2*i+1];
      if tree_last[2*i+1] <> -1 then tree_last[i] := tree_last[2*i+1] else tree_last[i] := tree_last[2*i];
   end;
end;

procedure init;
var
   i : longint;
begin
   for i:=0 to MAXH_POW2 do begin
      tree_first[i] := -1;
      tree_last[i] := -1;
   end;
   Update(0, MAXH+1, 1, 0, MAXH+1);
end;

procedure solve;
var
   i, h, h0, h_up, h_down : longint;
   ret, val               : int64;
begin
   init;
   for i:=1 to n do begin
      h0 := A[i].h - A[i].x;
      h_up := First(h0, MAXH+1, 1, 0, MAXH+1);
      if h_up = -1 then h_up := A[i].h;

      h_down := Last(0, h0+1, 1, 0, MAXH+1);

      Update( A[i].h, 1, 1, 0, MAXH+1 );
      Update( h_up, -1, 1, 0, MAXH+1 );
      Update( h_down + h_up - h0, 1, 1, 0, MAXH+1 );
      Update( h_down, -1, 1, 0, MAXH+1 );
   end;

   ret := 0; val := 0;
   for h:=MAXH downto 1 do begin
      val := val + delta[h];
      ret := ret + ((val * (val-1)) div 2);
   end;
   writeln(ret);
end;

begin
   input;
   sort;
   solve;
end.
