program aliens;

var
   n, x0, y0 : longint;
   left, right, up : longint;
   sideLength : longint;
   squaresLeft, squaresRight, squaresUp : longint;
   edgeLeft, edgeUp : longint;

function Rose( X, Y : longint ) : boolean;
var
   answer : string;
begin
   writeln( 'examine ', X, ' ', Y );
   flush( output );
   readln( answer );
   if answer = 'true' then Rose := true else Rose := false;
end;

function query( x, y : longint ) : boolean;
begin
   if (x < 1) or (x > n) or (y < 1) or (y > n) then query := false
   else query := Rose(x, y);
end;

function findFirstWhite( dx, dy : longint ) : longint;
var
   p, lo, hi, mid : longint;
begin
   p := 0;
   while query(x0+(dx shl p)-dx, y0+(dy shl p)-dy) do p := p + 1;

   lo := (1 shl (p-1))-1;
   hi := (1 shl p)-1;
   while lo+1 < hi do begin
      mid := (lo+hi) div 2;
      if query(x0+mid*dx, y0+mid*dy) then lo := mid else hi := mid;
   end;

   findFirstWhite := hi;
end;


begin;
   readln( n, x0, y0 );

   left := findFirstWhite(0, -1);
   right := findFirstWhite(0, 1);
   up := findFirstWhite(-1, 0);

   sideLength := right+left-1;
   squaresLeft := findFirstWhite(0, -2*sideLength);
   squaresRight := findFirstWhite(0, 2*sideLength);
   squaresUp := findFirstWhite(-2*sideLength, 0);

   edgeLeft := y0-left+1-(squaresLeft-1)*2*sideLength;
   edgeUp := x0-up+1-(squaresUp-1)*2*sideLength;

   if squaresLeft+squaresRight-1 <> 3 then begin;
      edgeLeft := edgeLeft - sideLength;
      edgeUp := edgeUp - sideLength;
   end;

   writeln( 'solution ', edgeUp+5*sideLength div 2, ' ', edgeLeft+5*sideLength div 2 );
   flush( output );
end.
