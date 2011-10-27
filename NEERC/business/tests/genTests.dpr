{$r+,q+,o-}
{$apptype console}
uses
    SysUtils, Math;

type
    int = longint;

var
    n, m: int;
    u, d: array [1..2000] of int;
    currentTestNumber: int;

procedure writeTest();
var
    i: int;
    fp: TEXT;

begin
    inc(currentTestNumber);
    writeln('Writing test ', currentTestNumber, '... (n = ', n, ' m = ', m, ')');
    rewrite(fp, chr(ord('0') + (currentTestNumber div 10)) + '' + chr(ord('0') + (currentTestNumber mod 10)));

    writeln(fp, n, ' ', m);
    for i := 1 to m do
        writeln(fp, u[i], ' ', d[i]);

    close(fp);
end;

function calcAnswer(n, m, u, d: int): int;
var
    a, b: int;

begin
    a := (n * d) div (u + d) + 1;
    b := n - a;
    result := a * u - b * d;
end;

{ Generates random test with n = nn, m = mm and with answer = answer }
procedure genRandomTest(nn, mm: int; answer: int);
var
    i, cur, curAnswer: int;

begin
    n := nn;
    m := mm;
    while (true) do begin
        curAnswer := 2000000000;
        for i := 1 to m do begin
            cur := 0;
            while (true) do begin
                u[i] := 1 + random(1000);
                d[i] := 1 + random(1000);
                cur := calcAnswer(n, m, u[i], d[i]);
                if (cur >= answer) then
                    break;
            end;
            curAnswer := min(curAnswer, cur);
        end;
        if (curAnswer = answer) then
            break;
    end;
end;

procedure genMaxTest(nn, mm: int);
var
    i: int;

begin
    n := nn;
    m := mm;
    for i := 1 to m do begin
        u[i] := 1000;
        d[i] := 1000;
    end;
end;

var
    i: int;

begin
    currentTestNumber := 1;
    randseed := 238578235;

    // Small tests
    genRandomTest(1, 1, 239);
    writeTest();
    genRandomTest(1, 1, 1000);
    writeTest();
    genRandomTest(7, 2, 718);
    writeTest();
    genRandomTest(13, 5, 999);
    writeTest();
    genRandomTest(239, 15, 1);
    writeTest();
    genRandomTest(1, 100, 566);
    writeTest();

    // Tests with small answers
    for i := 1 to 5 do begin
        genRandomTest(1 + random(100), 1 + random(2000), i);
        writeTest();
    end;

    // Tests with (100 <= answer <= 500)
    for i := 1 to 5 do begin
        genRandomTest(1 + random(100000), 1 + random(2000), 100 + random(401));
        writeTest();
        genRandomTest(1 + random(100), 1 + random(2000), 100 + random(401));
        writeTest();
    end;

    // Tests with (500 <= answer <= 1000)
    for i := 1 to 5 do begin
        genRandomTest(1000000 - random(10000), 2000 - random(100), 500 + random(501));
        writeTest();                                          
        genRandomTest(1 + random(1000), 2000 - random(100), 500 + random(501));
        writeTest();
    end;

    // Tests with big n, m and (1000 <= answer <= 1500)
    for i := 1 to 5 do begin
        genRandomTest(1000000 - random(10000), 2000 - random(100), 1000 + random(501));
        writeTest();
    end;

    // Tests with big n, m and answer > 1600
    for i := 1 to 5 do begin
        genRandomTest(1000000 - random(1000), 2000 - random(100), 1600 + random(301));
        writeTest();
    end;

    // Tests with big n, m and answer
    genRandomTest(1000000, 2000, 1952);
    writeTest();
    genRandomTest(1000000, 2000, 1963);
    writeTest();
    genRandomTest(1000000, 2000, 1974);
    writeTest();
    genRandomTest(1000000, 2000, 1982);
    writeTest();
    genRandomTest(1000000, 2000, 1990);
    writeTest();
    genMaxTest(1000000, 2000);
    writeTest();
end.
