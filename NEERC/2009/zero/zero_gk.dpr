{$q-,r-,o+}

uses
    sysutils;

const
    max_n = 100000;
    max_a = 1000000000000000;
    radix = 1000000000;
var
    i, n: longint;
    a: array [1..max_n] of int64;
begin
    assign(input, 'zero.in'); reset(input);
    assign(output, 'zero.out'); rewrite(output);

    read(n);

    for i := 1 to n do begin
        read(a[i]);
    end;

    for i := n downto 1 do begin
        write(a[i], ' ');
    end;
    writeln;

    close(input);
    close(output);
end.