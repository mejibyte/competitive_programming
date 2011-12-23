program igra3d;

var
   loga : array[0..225*225*225] of longint;
   XX, YY, ZZ : longint;

function loga_query( x0, y0, z0 : longint ) : longint;
var
   ret : longint;
   x, y, z : longint;
begin
   ret := 0;
   x := x0; while x > 0 do begin
      y := y0; while y > 0 do begin
         z := z0; while z > 0 do begin
            ret := ret + loga[ ((x-1)*YY + y-1)*ZZ + z-1 ];
         z := z - (z and -z) end;
      y := y - (y and -y) end;
   x := x - (x and -x) end;
   loga_query := ret;
end;

function query( x1, x2, y1, y2, z1, z2 : longint ) : longint;
begin
   x1 := x1-1; if x1 < 0 then x1 := 0; if x2 > XX then x2 := XX;
   y1 := y1-1; if y1 < 0 then y1 := 0; if y2 > YY then y2 := YY;
   z1 := z1-1; if z1 < 0 then z1 := 0; if z2 > ZZ then z2 := ZZ;

   query := loga_query( x2, y2, z2 )
          - loga_query( x1, y2, z2 ) - loga_query( x2, y1, z2 ) - loga_query( x2, y2, z1 )
          + loga_query( x1, y1, z2 ) + loga_query( x1, y2, z1 ) + loga_query( x2, y1, z1 )
          - loga_query( x1, y1, z1 );
end;

procedure update( x0, y0, z0, val : longint );
var
   x, y, z : longint;
begin
   x := x0; while x <= XX do begin
      y := y0; while y <= YY do begin
         z := z0; while z <= ZZ do begin
            loga[ ((x-1)*YY + y-1)*ZZ + z-1 ] := loga[ ((x-1)*YY + y-1)*ZZ + z-1 ] + val;
         z := z + (z and -z) end;
      y := y + (y and -y) end;
   x := x + (x and -x) end;
end;

type
   point = record
      x, y, z : longint;
      a, b, c, d : longint;
   end;

var
   B, N, K, M : longint;
   tocke, tmp : array[1..100000] of point;
   T : point;
   ret : int64;
   i, head, tail : longint;

procedure merge_sort( lo, hi : longint );
var
   mid, i, j, k : longint;
begin
   if hi <> lo then begin
      mid := (lo+hi) div 2;

      merge_sort( lo, mid );
      merge_sort( mid+1, hi );

      i := lo;
      j := mid+1;

      for k := lo to hi do begin
         if j > hi then begin tmp[k] := tocke[i]; i := i + 1; end
         else if i > mid then begin tmp[k] := tocke[j]; j := j + 1; end
         else if tocke[i].a < tocke[j].a then begin tmp[k] := tocke[i]; i := i + 1; end
         else begin tmp[k] := tocke[j]; j := j + 1; end;
      end;

      for k := lo to hi do tocke[k] := tmp[k];
   end;
end;

begin
   readln( B, N, K, M );

   if B = 1 then begin XX := 1;   YY := 1;   ZZ := 1;   end;
   if B = 2 then begin XX := 2*M; YY := 1;   ZZ := 1;   end;
   if B = 3 then begin XX := 3*M; YY := 3*M; ZZ := 3*M; end;

   for i := 1 to N do begin
      if B = 1 then begin
         readln( T.x );
         T.a := T.x;
         T.b := 1;
         T.c := 1;
         T.d := 1;
      end;
      if B = 2 then begin
         readln( T.x, T.y );
         T.a := T.x+T.y - 1;
         T.b := T.x-T.y + M;
         T.c := 1;
         T.d := 1;
      end;
      if B = 3 then begin
         readln( T.x, T.y, T.z );
         T.a := T.x+T.y+T.z - 2;
         T.b := T.x+T.y-T.z + M-1;
         T.c := T.x-T.y+T.z + M-1;
         T.d := T.x-T.y-T.z + M+M;
      end;
      tocke[i] := T;
   end;

   merge_sort( 1, N );

   ret := 0;
   head := 1; tail := 1;
   while head <= N do begin
      while tocke[head].a - tocke[tail].a > K do begin
         update( tocke[tail].b, tocke[tail].c, tocke[tail].d, -1 );
         tail := tail + 1;
      end;

      ret := ret + query( tocke[head].b-K, tocke[head].b+K,
                          tocke[head].c-K, tocke[head].c+K,
                          tocke[head].d-K, tocke[head].d+K );

      update( tocke[head].b, tocke[head].c, tocke[head].d, 1 );
      head := head + 1;
   end;

   writeln( ret );

end.
