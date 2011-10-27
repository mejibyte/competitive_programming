{$r+,q+,o-}
{$apptype console}
uses
	TestLib, SysUtils;

var
	ja, pa: integer;
	n, m: integer;

begin
	ja := ans.readlongint();
	pa := ouf.readlongint();
	if (ja <> pa) then
		quit(_wa, format('Expected: %d, found: %d', [ja, pa]));

	n := inf.readlongint();
	m := inf.readlongint();
	quit(_ok, format('n = %d, m = %d, ans = %d', [n, m, ja]));
end.
