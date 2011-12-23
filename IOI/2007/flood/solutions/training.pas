program training;

const MAXN = 1000;
const MAXK = 10;

type
   Edge = record
      u, v : longint;
      cost : longint;
      LCA : longint; // lowest common ancestor of u and v
   end;
   Pair = record
      first, second : longint;
   end;

var
   E : array[1..MAXN*MAXK div 2] of Edge;
   n, m : longint;
   costSum : longint;
   traversalTime : longint;
   discover : array[1..MAXN] of longint;
   finish   : array[1..MAXN] of longint;
   depth    : array[1..MAXN] of longint;
   degree   : array[1..MAXN] of longint;
   color    : array[1..MAXN] of longint;
   parent   : array[1..MAXN] of Pair;

   treeDegree : array[1..MAXN] of longint;
   treeLinks  : array[1..MAXN,1..MAXN] of longint;

   DP : array[1..MAXN, 0..1 shl MAXK] of longint;

procedure load;
var
   i : longint;
begin
   costSum := 0;

   readln( n, m );

   for i := 1 to n do begin
      treeDegree[i] := 0;
   end;

   for i := 1 to m do begin
      readln( E[i].u, E[i].v, E[i].cost );

      costSum := costSum + E[i].cost;
      if E[i].cost = 0 then begin;
         treeDegree[E[i].u] := treeDegree[E[i].u] + 1;
         treeDegree[E[i].v] := treeDegree[E[i].v] + 1;

         treeLinks[E[i].u, treeDegree[E[i].u]] := E[i].v;
         treeLinks[E[i].v, treeDegree[E[i].v]] := E[i].u;
      end;
   end;
end;

procedure treeInit( a : longint );
var
   i, b : longint;
begin
   traversalTime := traversalTime + 1;
   discover[a] := traversalTime;

   for i := 1 to treeDegree[a] do begin
      b := treeLinks[a, i];
      if b = parent[a].first then continue;

      color[b] := 1 - color[a];
      depth[b] := 1 + depth[a];
      parent[b].first := a;
      parent[b].second := 1 shl degree[a];
      degree[a] := degree[a] + 1;

      treeInit( b );
   end;

   traversalTime := traversalTime + 1;
   finish[a] := traversalTime;
end;

procedure init;
var
   i, j : longint;
begin;
   for i := 1 to n do
      for j := 0 to (1 shl MAXK) do
         DP[i, j] := 0;

   traversalTime := 0;
   color[1] := 0;
   depth[1] := 0;
   parent[1].first := -1;
   parent[1].second := 1;
   treeInit( 1 );
end;

procedure calcLCA;
var
   i, u, v : longint;
begin
   for i := 1 to m do begin;
      u := E[i].u;
      v := E[i].v;
      while depth[u] > depth[v] do u := parent[u].first;
      while depth[v] > depth[u] do v := parent[v].first;
      while u <> v do begin;
         u := parent[u].first;
         v := parent[v].first;
      end;
      E[i].LCA := u;
   end;
end;

procedure swap( var a, b : Edge );
var
   tmp : Edge;
begin
   tmp := a;
   a := b;
   b := tmp;
end;

procedure sortByLCAFinishTime;
var
   i, j : longint;
begin
   for i := 1 to m do
      for j := i+1 to m do
         if finish[E[j].LCA] < finish[E[i].LCA] then
            swap( E[i], E[j] );
end;

procedure solve;
var
   i, L, sum, mask : longint;
   U, V : Pair;
begin
   for i := 1 to m do begin
      if (E[i].cost <> 0) and (color[E[i].u] <> color[E[i].v]) then continue;

      L := E[i].LCA;
      sum := E[i].cost;

      U.first := E[i].u; U.second := 0;
      while U.first <> L do begin
         sum := sum + DP[U.first, U.second];
         U := parent[U.first];
      end;

      V.first := E[i].v; V.second := 0;
      while V.first <> L do begin
         sum := sum + DP[V.first, V.second];
         V := parent[V.first];
      end;

      for mask := (1 shl degree[L])-1 downto 0 do
         if (mask and U.second = 0) and (mask and V.second = 0) then
            if DP[L, mask] < sum + DP[L, mask or U.second or V.second] then
               DP[L, mask] := sum + DP[L, mask or U.second or V.second];
   end;
end;

begin
   load;
   init;
   calcLCA;
   sortByLCAFinishTime;
   solve;
   writeln( costSum - DP[1, 0] );
end.
