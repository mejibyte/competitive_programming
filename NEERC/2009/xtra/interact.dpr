(*
    Interaction for NEERC'2008 Problem X: Xtrapolation
    (C) Andrew Stankevich
*)

{$O+,Q+,R+}
{$APPTYPE CONSOLE}

program interact;
var
  fin, fout: text;
  x: int64;
  s: string;

begin
  reset(fin, 'xtra.in');
  rewrite(fout, 'xtra.out');

  while true do begin
    readln(fin, x);
    writeln(x);
    flush(output);

    if x = 0 then 
      break;

    readln(s);
    writeln(fout, s);
    flush(fout);
  end;

  close(fin);
  close(fout);
end.
