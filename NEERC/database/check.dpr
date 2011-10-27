{$r+,q+,o-}
{$apptype console}
uses
    TestLib, SysUtils;
const
    max_n = 10000;
    max_m = 100;

procedure checkRange(v: string; value, a, b: integer);
begin
    if (value < a) or (value > b) then begin
        quit(_wa, format('%s not in range %d..%d: %d', [v, value, a, b]));
    end;
end;

function get(line: string; field: longint): string;
var
    pos: longint;
begin
    line := line + ',';
    pos := 1;
    while (field > 0) do begin
        result := '';
        while (line[pos] <> ',') do begin
            result := result + line[pos];
            inc(pos);
        end;
        dec(field);
        inc(pos);
    end;
end;

var
    ja, pa: string;
    i: longint;
    r1, r2, c1, c2: integer;
    n, m: integer;
    data: array [1..max_n] of string;

begin
    n := inf.readLongint();
    m := inf.readLongint();
    inf.readString();
    for i := 1 to n do begin
        data[i] := inf.readString();
    end;

    ja := ans.readWord(blanks, blanks);
    pa := ouf.readWord(blanks, blanks);

    if (pa = 'NO') then begin
        r1 := ouf.readLongint();
        r2 := ouf.readLongint();
        c1 := ouf.readLongint();
        c2 := ouf.readLongint();

        checkRange('r1', r1, 1, n);
        checkRange('r2', r2, 1, n);
        checkRange('c1', c1, 1, m);
        checkRange('c2', c2, 1, m);

        if (r1 = r2) then begin
            quit(_wa, format('r1 = r2 = %d', [r1]));
        end;
        if (c1 = c2) then begin
            quit(_wa, format('c1 = c2 = %d', [c1]));
        end;

        if (get(data[r1], c1) <> get(data[r2], c1)) then begin
            quit(_wa, format('Values in first column %d in rows %d and %d does not match', [c1, r1, r2]));
        end;
        if (get(data[r1], c2) <> get(data[r2], c2)) then begin
            quit(_wa, format('Values in second column %d in rows %d and %d does not match', [c2, r1, r2]));
        end;
        if (ja = 'YES') then begin
            quit(_fail, format('Solution r1 = %d, r2 = %d, c1 = %d, c2 = %d missed by the Jury', [r1, r2, c1, c2]));
        end;
        quit(_ok, format('r1 = %d, r2 = %d, c1 = %d, c2 = %d', [r1, r2, c1, c2]));
    end;
    
    if (pa = 'YES') then begin
        if (ja = 'NO') then begin
            r1 := ans.readLongint();
            r2 := ans.readLongint();
            c1 := ans.readLongint();
            c2 := ans.readLongint();
            quit(_wa, format('Solution r1 = %d, r2 = %d, c1 = %d, c2 = %d missed', [r1, r2, c1, c2]));
        end;
        quit(_ok, 'YES');
    end;
    quit(_wa, format('YES or NO expected, %s found', [pa]));
end.
