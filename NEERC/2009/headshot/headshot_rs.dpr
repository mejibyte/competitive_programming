{$r+,q+,o-}
{$apptype console}
uses
    SysUtils, Math;

type
    int = longint;

procedure check(expr: boolean; msg: string);
begin
    if (not expr) then begin
        writeln(erroutput, 'Error: ', msg);
        assert(false);
    end;
end;

var
    n, i, ii, u, v: int;
    p: array [1..100] of char;

begin
    reset(input, 'headshot.in');
    rewrite(output, 'headshot.out');

    n := 0;
    while (not seekeoln) do begin
        inc(n);
        check(n <= 100, 'n is greater than 100');
        read(p[n]);
        check((p[n] = '0') or (p[n] = '1'), 'some of chambers != 0 and != 1');
    end;

    u := 0;
    v := 0;
    for i := 1 to n do begin
        ii := (i mod n) + 1;
        if (p[i] = '0') then begin
            if (p[ii] = '0') then
                inc(u);

            inc(v);
        end;
    end;

    if (u * n = v * v) then
        writeln('EQUAL')
    else if (u * n > v * v) then
        writeln('SHOOT')
    else
        writeln('ROTATE');

    close(input);
    close(output);
end.
