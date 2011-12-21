{$r+,q+,o-}
{$apptype console}
uses
	testlib, SysUtils;

var
	ja, pa : string;
	line : integer;

begin
	line := 1;
	while not ans.seekeof do begin
		ja := ans.readString();
		pa := ouf.readString();
		if (ja <> pa) then
			quit(_wa, format('Line %d, expected: %s, found: %s', [line, ja, pa]));
		inc(line);
	end;
	quit(_ok, inttostr (line) + ' lines');
end.
