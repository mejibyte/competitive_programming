var
    a, b: longint;
begin
    assign(input, 'yield.in');  reset(input);
    assign(output, 'yield.out'); rewrite(output);

    read(a, b);
    writeln(a + b);

    close(input);
    close(output);
end.