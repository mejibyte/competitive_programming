uses
	testlib;
var
	n: longint;
	s: string;
begin
	n := ouf.readlongint;
	ouf.nextline;
	s := ouf.readstring;
	if (n = 0) then
		quit(_ok, s);
	if (n = 1) then
		quit(_wa, s);
	if (n = 2) then
		quit(_pe, s);

	quit(_fail, s);
end.