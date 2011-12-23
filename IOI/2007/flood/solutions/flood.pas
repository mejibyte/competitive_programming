const MAXN = 100000;

type tocka = record
	x, y, tag : longint;
	s, indeks_brida : array[0..3] of longint;
end;

type brid = record
	a, b, indeks : longint;
end;


var n, id, i : longint;
	t : array[0..MAXN] of tocka;
	rjesenje : array[0..MAXN] of brid;
	rj_num : longint;
	sortirano : array[0..MAXN] of longint;
	temp : array[0..MAXN] of longint;


function make_tocka : tocka;
var t : tocka;
	i : longint;
begin
    for i:=0 to 3 do t.s[i]:=-1;
    t.tag := -1;
    make_tocka := t;
end;

function make_brid(a, b, indeks : longint) : brid;
var br : brid;
begin
	br.indeks := indeks;
	if A>B then begin
		br.a:=B;
		br.b:=A;
	end else begin
		br.a:=A;
		br.b:=B;
	end;
	make_brid := br;
end;


procedure dodaj(a, b, indeks : longint);
var k : longint;
begin
	if (t[a].x>t[b].x) then k := 0 else
    if (t[a].y<t[b].y) then k := 1 else
    if (t[a].x<t[b].x) then k := 2 else k := 3;
    t[a].s[k] := b;
    t[a].indeks_brida[k] := indeks;
end;

procedure brisi(a, b : longint);
var i : longint;
begin
	for i:=0 to 3 do if t[a].s[i] = b then
	begin
		t[a].s[i]:=-1;
		break;
	end;
end;

procedure ucitaj;
var m, a, b, i : longint;
begin
	readln(n);
    for i:=0 to n-1 do
    begin
    	t[i] := make_tocka;
    	readln(t[i].x, t[i].y);
    end;
    readln(m);
    for i:=1 to m do
    begin
    	readln(a, b);
    	dec(a);
    	dec(b);
        dodaj(a, b, i);
        dodaj(b, a, i);
    end;
end;

procedure ispisi;
var i : longint;
begin
	writeln(rj_num);
    for i:=0 to rj_num-1 do writeln(rjesenje[i].indeks);
end;

function dfs(a, d : longint) : longint;
var i, b, indeks, ret : longint;
begin
	if (t[a].tag<>-1) then
	begin
		dfs := t[a].tag;
		exit;
	end;
    t[a].tag := id;
    inc(id);
    for i:=0 to 3 do
    begin
        b := t[a].s[(d+i)mod 4];
        indeks := t[a].indeks_brida[(d+i)mod 4];
        if (b=-1) then continue;
        brisi(a, b);
        brisi(b, a);
        ret := dfs(b, (d+i+3) mod 4);
        if (ret<=t[a].tag) then
        begin
        	if (ret < t[a].tag) then
        	begin
            	t[a].tag := -1;
            	dec(id);
            	dfs := ret;
            	exit;
            end;
        end else
        begin
            rjesenje[rj_num] := make_brid(a, b, indeks);
            inc(rj_num);
        end;
    end;
    t[a].tag := -1;
    dec(id);
    dfs := id;
end;

procedure sort(l, r : longint);
var m, i : longint;
	t1, t2 : tocka;
begin
	if (l >= r) then exit;
	m := (l+r) div 2;
	sort(l, m);
	sort(m+1, r);
	for i:=l to m do temp[i] := sortirano[i];
	for i:=m+1 to r do temp[i] := sortirano[r - i + m + 1];
	i := l;
	while (l<=r) do
	begin
		t1 := t[temp[l]];
		t2 := t[temp[r]];
		if (t1.y < t2.y) or ((t1.y = t2.y) and (t1.x < t2.x)) then
		begin
			sortirano[i] := temp[l];
			inc(l);
		end else begin
			sortirano[i] := temp[r];
			dec(r);
		end;
		inc(i);
	end;
end;

begin
	id := 0;
	rj_num := 0;

	ucitaj;

    for i:=1 to n-1 do sortirano[i] := i;
    sort(0, n-1);

    for i:=0 to n-1 do dfs(sortirano[i], 0);

    ispisi;
end.
