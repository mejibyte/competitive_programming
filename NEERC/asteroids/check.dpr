uses
    testlib, sysutils;

const
    eps = 1.1e-5;

var
    ja, pa: extended;

begin
    ja := ans.readreal;
    pa := ouf.readreal;

    if abs(ja - pa) > eps then
        quit(_wa, 'Expected: ' + floattostr(ja) + ', found: ' + floattostr(pa));

    quit(_ok, floattostr(ja));
end.