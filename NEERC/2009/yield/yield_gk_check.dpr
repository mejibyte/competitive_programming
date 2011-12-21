uses
    sysutils;
const
    max_a = 1000;
var
    a, b: longint;
begin
    assign(input, 'yield.in');  reset(input);
    assign(output, 'yield.out'); rewrite(output);

    read(a, b);
    assert((-max_a <= a) and (a <= max_a), 'A out of range');
    assert((-max_a <= b) and (b <= max_a), 'B out of range');
    writeln(a + b);

    close(input);
    close(output);
end.