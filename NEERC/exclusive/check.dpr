{$apptype console}
{$r+,o-,q-}
{$minstacksize 30000000}
uses
  SysUtils, Math, testlib;

const
  PCOUNT = ord('Z') - ord('L') + 1;

var
  n : integer;
  pa, ja : integer;
  processes : array[1..100, 1..2] of integer;
  i : integer;
  r1, r2 : string;
  desc : array[1..100, 1..2] of integer; 
  r1n, r2n : integer;
  actualLength : integer;
  edge : array[0..PCOUNT - 1, 0..PCOUNT - 1] of boolean;

function computeWaitingChain : integer;
var
  a : array[0..65536, 0..15] of integer;
  i, j, k : integer;
  s : string;
  l : integer;
begin
  for i := 0 to (1 shl PCOUNT) - 1 do begin
    for j := 0 to PCOUNT - 1 do begin
      a[i][j] := -1;
  	end;
  end;

  for i := 0 to PCOUNT - 1 do begin
    a[1 shl i][i] := 0;
  end;  
  for i := 0 to (1 shl PCOUNT) - 1 do begin
    for j := 0 to PCOUNT - 1 do begin
      if (a[i][j] = -1) then begin
        continue;
      end;
      for k := 0 to PCOUNT - 1 do begin
        if (edge[j][k]) then begin
          if ((i or (1 shl k)) = i) then begin
            s := '';
            for l := 0 to PCOUNT - 1 do begin
              if ((i or (1 shl l)) = i) then begin
                s := s + ' ' + chr(ord('L') + l);
              end;
            end; 
            quit(_wa, 'System deadlocks while trying to work with resources' + s);
          end else begin
            a[i or (1 shl k)][k] := max(a[i][j] + 1, a[i or (1 shl k)][k]);
          end;
        end;
      end;
    end;
  end;
  result := -1;
  for i := 0 to (1 shl PCOUNT) - 1 do begin
    for j := 0 to PCOUNT - 1 do begin
      result := max(result, a[i][j]);
  	end;
  end;
  dec(result);
end;

begin
  n := inf.readInteger();
  for i := 1 to n do begin
    r1 := inf.readWord(BLANKS, BLANKS);  
    r2 := inf.readWord(BLANKS, BLANKS);  
    processes[i][1] := ord(r1[1]) - ord('L');
    processes[i][2] := ord(r2[1]) - ord('L');
  end; 
  ja := ans.readInteger();
  pa := ouf.readInteger();
  if (pa > ja) then begin
    quit(_wa, format('Participant has longer waiting chain: jury has %d, participant has %d', [ja, pa]));
  end;
  for i := 1 to n do begin
    r1 := ouf.readWord(BLANKS, BLANKS);  
    if (length(r1) > 1) then begin
      quit(_wa, format('Invalid resource for process %d: %s', [i, r1]));
    end;
    if (r1[1] < 'L') or (r1[1] > 'Z') then begin
      quit(_wa, format('Invalid resource for process %d: %s', [i, r1]));
    end;
    r2 := ouf.readWord(BLANKS, BLANKS);  
    if (length(r2) > 1) then begin
      quit(_wa, format('Invalid resource for process %d: %s', [i, r1]));
    end;
    if (r2[1] < 'L') or (r2[1] > 'Z') then begin
      quit(_wa, format('Invalid resource for process %d: %s', [i, r1]));
    end;
    r1n := ord(r1[1]) - ord('L');
    r2n := ord(r2[1]) - ord('L');
    if ((r1n = processes[i][1]) and (r2n <> processes[i][2])) or
       ((r1n = processes[i][2]) and (r2n <> processes[i][1])) then begin
      quit(_wa, format('Invalid set of resources for process %d: (%s, %s) instead of (%s, %s)', [i, r1, r2, '' + chr(ord('L') + processes[i][1]), '' + chr(ord('L') + processes[i][1])]));   
    end; 
    desc[i][1] := r1n;
    desc[i][2] := r2n;
  end;
  for i := 1 to n do begin
    edge[desc[i][1]][desc[i][2]] := true;
  end;
  actualLength := computeWaitingChain();
  if (actualLength <> pa) then begin
    quit(_wa, format('Participant reported wrong wainting chain length: %d, but actual is %d', [pa, actualLength]));
  end;
  if (pa < ja) then begin
    quit(_fail, format('Participant has better answer: pa = %d, ja = %d', [pa, ja]));
  end;
  quit(_ok, format('%d processes, length of waiting chain = %d', [n, ja]));
end.
