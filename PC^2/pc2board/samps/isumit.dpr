{
*
* File:    isumit.dpr
* Purpose: prints the sum of the positive integers, read from stdin
* Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
*
* $Id: isumit.dpr,v 1.1 2005/03/06 05:34:39 laned Exp $
*
}

{$APPTYPE CONSOLE}

uses SysUtils;  { for StrToInt }

var
  s : string;
  sum : longint;
  v : longint;
begin

 sum := 0;
 
  readln (s);
  v := strtoInt (s);

 while (v <> 0) do
 begin
  if (v > 0) then
     sum := sum + v;
  readln (s);
  v := strtoInt (s);
 end;
 writeln('The sum of the positive integers is ',sum);

end.
