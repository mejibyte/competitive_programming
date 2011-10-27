{$r+,q+,o-}
{$apptype console}
uses
    TestLib, SysUtils;
const
    max_n = 1000;
    max_m = 1000;


type TLetters = array [0..25] of longint;

function letters(w: string): TLetters;
var
    i: longint;
begin
    fillchar(result, sizeof(result), 0);
    for i := 1 to length(w) do begin
        inc(result[ord(w[i]) - ord('A')]);
    end;
end;

var
    i: longint;
    n, m: integer;
    words: array [1..max_m] of string;
    letterss: array[1..max_m] of TLetters;
    ja, pa: longint;

function match(const letters, wordLetters: TLetters): boolean;
var
    i: longint;
begin
    for i := 0 to 25 do begin
        if (letters[i] > wordLetters[i]) then begin
            result := false;
            exit;
        end;
    end;
    result := true;
end;

function countLetters(const letters: TLetters): longint;
var
    i: longint;
begin
    result := 0;
    for i := 1 to m do begin
        if (match(letters, letterss[i])) then begin
            inc(result);
        end;
    end;
end;

var
    newWords: array [1..max_n] of string;

function count(var s: InStream): longint;
var
    i, j: longint;
begin
    result := 0;
    for i := 1 to n do begin
        newWords[i] := s.readWord(blanks, blanks);

        for j := 1 to length(newWords[i]) do begin
            if (not (newWords[i][j] in ['A'..'Z'])) then begin
                quit(_pe, 'Illegal character: "' + newWords[i][j] + '"');
            end;
        end;
    end;

    for i := 1 to n do begin
        for j := 1 to m do begin
            if (newWords[i] = words[j]) then begin
                quit(_wa, format('New word %d equals to old word %d', [i, j]));
            end;
        end;
        for j := i + 1 to n do begin
            if (newWords[i] = newWords[j]) then begin
                quit(_wa, format('New word %d equals to new word %d', [i, j]));
            end;
        end;
    end;

    for i := 1 to n do begin
        result := result + countLetters(letters(newWords[i]));
    end;
end;

begin
    n := inf.readLongint();
    m := inf.readLongint();

    for i := 1 to m do begin
        words[i] := inf.readWord(blanks, blanks);
    end;

    for i := 1 to m do begin
        letterss[i] := letters(words[i]);
    end;

    pa := count(ouf);
    ja := count(ans);

    if (ja < pa) then begin
        quit(_fail, format('Participant found %d entries, jury: %d', [pa, ja]));
    end;
    if (ja > pa) then begin
        quit(_wa, format('Participant found %d entries, jury: %d', [pa, ja]));
    end;
    quit(_ok, format('%d entries found', [pa]));
end.
