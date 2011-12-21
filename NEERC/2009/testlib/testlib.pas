{ Copyright(c) SPb-IFMO CTD Developers, 2000 }
{ Copyright(c) Anton Sukhanov, 1996 }

{ $Id: testlib.pas,v 1.9 2004/06/30 08:55:35 jury Exp $ }

{ Evaluating programs support stuff }

{$ifdef VER70}
{$A-,B-,D+,E+,F+,G+,I-,L+,N+,O-,P+,Q-,R+,S+,T-,V+,X+,Y+}
{$M 65520, 0, 0}
{$endif}

(*
   Program, using testlib running format:
     CHECK <Input_File> <Output_File> <Answer_File> [<Result_File> [-xml]],

   If result file is specified it will contain results.
*)

  { Modifications log:
      dd.mm.yyyy  modified by          modification log
      17.09.2000  Andrew Stankevich    XML correct comments
      01.08.2000  Andrew Stankevich    Messages translated to English
                                       APPES support added   
                                       FAIL name changed
      07.02.1998  Roman Elizarov       Correct EOF processing
      12.02.1998  Roman Elizarov       SeekEoln corrected
                                       eoln added
                                       nextLine added
                                       nextChar is now function
  }

unit TESTLIB;

(* ================================================================= *)
                              interface
(* ================================================================= *)

const eofChar  = #$1A;
      eofRemap = ' ';
      NumberBefore = [#10,#13,' ',#09];
      NumberAfter  = [#10,#13,' ',#09,eofChar];
      lineAfter    = [#10,#13,eofChar];
      Blanks       = [#10,#13,' ',#09];
      eolnChar     = [#10,#13,eofChar];

type REAL = EXTENDED; {!!!!!!!!}

type CharSet = set of char;
     TMode   = (_Input, _Output, _Answer);
     TResult = (_OK, _WA, _PE,  _Fail, _PC, _Dirt);
               {_OK - accepted, _WA - wrong answer, _PE - output format mismatch,
                _Fail - when everything fucks up }
               { _Dirt - for inner using}

     InStream = object
                    cur: char; { current char, =EofChar, if eof }
                    f: TEXT; { file }
                    name: string; { file name }
                    mode: TMode;
                    opened: boolean;

                    { for internal usage }
                    constructor init (fname: string; m: TMode);

                    function CurChar: char; { returns cur }
                    function nextChar: char;  { moves to next char }

                    function seekeof: boolean;

                    function eof : boolean;  { == cur = EofChar }

                    function eoln: boolean;
                    function seekEoln: boolean;
                    procedure nextLine; { skips current line }

                    { Skips chars from given set }
                    { Does not generate errors }
                    procedure skip (setof: CharSet);

                    { Read word. Skip before all chars from `before`
                      and after all chars from `after`. If eof or word is
                      empty or it contains more than 255 chars, generates _pe }
                    function ReadWord (Before, After: CharSet): string;

                    { reads integer }
                    { _pe if error }
                    { USE readlongint! }
                    function ReadInteger: integer;
                   
                    { reads longint }
                    { _pe if error }
                    function ReadLongint: longint;

                    { reads real }
                    { _pe if error }
                    function ReadReal: real;

                    procedure Reset;

                    { same as readword([], [#13 #10]) }
                    function ReadString: string;

                    { for internal usage }
                    procedure QUIT (res: TResult; msg: string);
                    procedure close;

                end;


procedure Quit(res: TResult; msg: string); overload;
procedure QuitWithPC(msg : string; pctype : integer);
procedure SetCustomAttribute(name : string; value : string); overload;
procedure SetCustomAttribute(name : string; value : integer); overload;
procedure SetCustomAttribute(name : string; value : real); overload;

var inf, ouf, ans: InStream;
    ResultName: string; { result file name }
    AppesMode: boolean;

(* ================================================================= *)
                              implementation
(* ================================================================= *)

{$ifdef VER70}
uses crt;
{$else}
uses sysutils;
{$endif}

{$ifndef VER70}
const
    LightGray = $07;    
    LightRed  = $0c;    
    LightCyan = $0b;    
    LightGreen = $0a;
    Yellow = $0e;
    
    MAX_CUSTOM_ATTR = 256;
    
type
    TCustomAttr = record
        name, value : string;
    end;    

var
    nCustomAttr : integer = 0;
    customAttr : array[1..MAX_CUSTOM_ATTR] of TCustomAttr;
    
procedure SetCustomAttribute(name : string; value : string); overload;
var
    i : integer;
    
begin
    for i := 1 to nCustomAttr do
        if customAttr[i].name = name then begin
            customAttr[i].value := value;
            exit;
        end;

    inc(nCustomAttr);
    assert(nCustomAttr <= MAX_CUSTOM_ATTR);
    customAttr[nCustomAttr].name := name;
    customAttr[nCustomAttr].value := value;
end;

procedure SetCustomAttribute(name : string; value : integer); overload;
begin
    SetCustomAttribute(name, inttostr(value));
end;

procedure SetCustomAttribute(name : string; value : real); overload;
begin
    SetCustomAttribute(name, floattostr(value));
end;

procedure textcolor(x: word);
var
    h: thandle;
begin
(*    h := getstdhandle(std_output_handle);
    setconsoletextattribute(h, x); *)
end;
{$endif}

{$ifdef ver70}
procedure beep(freq, duration: integer);
begin
    sound(freq);
    delay(duration);
    nosound;
end;
{$endif}

const outcomes: array[0..8] of string = (
    'accepted',
    'wrong-answer',
    'presentation-error',
    'fail',
    'partially-correct',
    'run-time-error',
    'time-limit-exceeded',
    'compilation-error',
    'security-violation' );

procedure safewrite(var t: text; s: string);
var
  i: longint;
begin
  for i := 1 to length(s) do
  begin
    case s[i] of
      '&': write(t, '&amp;');
      '<': write(t, '&lt;');
      '"': write(t, '&quot;');
      else
        if s[i] < ' ' then
          write(t, '?')
        else
          write(t, s[i]);
    end; { case }
  end;
end;

procedure quit (res: TResult; msg: string; pctype : integer); overload; forward;

procedure quit (res: TResult; msg: string); overload;
begin
    assert(res <> _PC);
    quit(res, msg, 0);
end;

procedure quitwithpc(msg : string; pctype : integer);
begin
    quit(_PC, msg, pctype);
end;

procedure quit (res: TResult; msg: string; pctype : integer);
var ResFile: text;
    ErrorName: string;
    i : integer;

    procedure scr (color: word; msg: string);
    begin
       if ResultName = '' then { if no result file }
       begin
              TextColor (color); write (msg); TextColor (LightGray);
       end;
    end;

begin
   if (res = _OK) then
   begin
      ouf.skip (Blanks);
      if not ouf.eof then QUIT (_Dirt, 'Extra information in Output');
   end;

   case res of
      _Fail: begin
                   ErrorName := 'FAIL ';
                   Scr (LightRed, ErrorName);
             end;

      _Dirt: begin
                   ErrorName := 'wrong output format ';
                   Scr (LightCyan, ErrorName);
                   res := _PE;
                   msg := 'Extra information in output file';
             end;

      _PE: begin
              ErrorName := 'wrong output format ';
              Scr (LightRed, ErrorName);
           end;

      _OK: begin
              ErrorName := 'ok ';
              Scr (LightGreen, ErrorName);
           end;

      _PC: begin
              ErrorName := 'pc' + inttostr(pctype) + ' ';
              Scr (Yellow, ErrorName);
           end;

      _WA: begin
              ErrorName := 'wrong answer ';
              TextColor (LightRed); scr (LightRed, ErrorName);
           end;

      else QUIT (_Fail, 'What is the code ??? ');
   end;

   if ResultName <> '' then
   begin
      assign (RESFILE, ResultName); { Create file with result of evaluation }
      rewrite (ResFile);
      if IORESULT <> 0 then QUIT (_Fail, 'Can not write to Result file');
      if AppesMode then
      begin
        writeln(ResFile, '<?xml version = "1.0" encoding = "cp866"?>');
        writeln(ResFile, '<result');
        writeln(ResFile, '  outcome = "', outcomes[ord(res)], '"');
        write(ResFile, '  comment = "');
        SafeWrite(ResFile, msg);
        writeln(ResFile, '" ');
        if res = _PC then
            writeln(ResFile, '  pc-type = "', pctype, '"');
        for i := 1 to nCustomAttr do begin
            write(ResFile, '  ', customAttr[i].name, ' = "');
            SafeWrite(ResFile, customAttr[i].value);
            writeln(ResFile, '"');
        end;
        writeln(ResFile, '>');
        SafeWrite(ResFile, msg);
        writeln(ResFile, '</result>');
      end
      else
      begin
      	writeln(resfile, msg);
      end;
      close (ResFile);
      if IORESULT <> 0 then QUIT (_Fail, 'Can not write to Result file');
   end;

   Scr (LightGray, msg + ' ');
   writeln;

   if Res = _Fail then HALT (ord (res));

   {$i-}close (inf.f); close (ouf.f); close (ans.f);{$i+}
   if ioresult<>0 then;

   TextColor (LightGray);

   if (res = _OK) or (appesmode) then HALT (0)
                                 else HALT (ord (res));
end;

constructor Instream.init (fname: string; m: TMode);
begin
   name := fname;
   mode := m;
   assign (f, fname);
   {$I-} system.reset (f);
   if IORESULT <> 0 then
   begin
      if mode = _Output then QUIT (_PE, 'File not found ' + fname);
       cur := EofChar; 
   end
   else
      if system.eof (f) then cur := EofChar
                        else begin cur := ' '; nextchar end;
   opened := true;

end;

function InStream.curchar: char;
begin
   curchar := cur
end;

function InStream.nextChar: char;
begin
   nextChar:= curChar;
   if cur = EofChar then { do nothing }
   else if system.eof (f) then cur := EofChar
   else begin
      {$I-} read (f, cur);
      if IORESULT <> 0 then Quit (_Fail, 'Read error' + name);
      if cur = eofChar then cur:= eofRemap;
   end;
end;

procedure InStream.QUIT (res: TResult; msg: string);
begin
   if mode = _Output then TESTLIB.QUIT (res, msg)
   { if can't read input or answer - fail }
   else TESTLIB.QUIT (_Fail, msg + ' (' + name + ')');
end;

function InStream.ReadWord (Before, After: CharSet): string;
var 
   {$ifdef ver70}
    i: integer;
   {$endif}
    res: string;
begin
   while cur in Before do nextchar;

   if (cur = EofChar) and not (cur in after) then
     QUIT (_PE, 'Unexpected end-of-file');

   {$ifdef ver70}
   i := 0;
   {$endif}
   res := '';
   while not ((cur IN AFTER) or (cur = EofChar))  do
   begin
      {$ifdef ver70}
      inc (i);
      if i > 255 then QUIT (_PE, 'Line too long');
      {$endif}
      res := res + cur;
      nextchar;
   end;
   
   ReadWord := res;
end;


function InStream.ReadInteger: integer;
begin
	readinteger := readlongint;
end;


function InStream.ReadReal: real;
var help: string;
    res: real;
    code: integer;
begin
   help := ReadWord (NumberBefore, NumberAfter);
   val (help, res, code);
   if code <> 0 then QUIT (_PE, 'Expected real instead of "' + help + '"');
   ReadReal := res
end;

function InStream.ReadLongint: longint;
var help: string;
    res: longint;
    code: integer;
begin
   help := ReadWord (NumberBefore, NumberAfter);
   val (help, res, code);
   if code <> 0 then QUIT (_PE, 'Expected longint instead of "' + help + '"');
   ReadLongint := res
end;

procedure InStream.skip (setof: CharSet);
begin
   while (cur in setof) and (cur <> eofchar) do nextchar;
end;

function InStream.eof: boolean;
begin
   eof := cur = eofChar;
end;

function InStream.seekEof: boolean;
begin
   while (cur in Blanks) do nextchar;
   seekeof := cur = EofChar;
end;

function InStream.eoln: boolean;
begin
  eoln:= cur in eolnChar;
end;

function InStream.seekEoln: boolean;
begin
  skip ( [' ', #9] );
  seekEoln:= eoln;
end;

procedure InStream.nextLine;
begin
  while not (cur in eolnChar) do nextchar;
  if cur = #13 then nextchar; 
  if cur = #10 then nextchar; 
end;

function InStream.ReadString: string;
begin
  readstring:= ReadWord ([], lineAfter);
  nextLine;
end;

procedure InStream.Reset;
begin
   {$I-} system.reset (f);
   if IORESULT <> 0 then
   begin
      cur := EofChar; { allow for other files }
   end
   else
      if system.eof (f) then cur := EofChar
                        else begin cur := ' '; nextchar end;
   opened := true;

end;

procedure InStream.close;
begin
  if opened then system.close(f);
  opened := false;
end;

function upper(s: string): string;
var
  i: longint;
begin
  for i := 1 to length(s) do
    s[i] := upcase(s[i]);
  upper := s;
end;

BEGIN { a.k.a. initialization }
   if (ParamCount < 3) or  (ParamCount > 5) then
      quit(_fail, 'Program must be run with the following arguments: ' +
        '<INPUT-FILE> <OUTPUT-FILE> <ANSWER-FILE> [<Result_File> [-xml]]');

   case ParamCount of
     3: begin
          ResultName := '';
          AppesMode := false;
        end;
     4: begin
          ResultName := ParamStr(4);
          AppesMode := false;
        end;
     5: begin
          if (upper(ParamStr(5)) <> '-XML') and (upper(paramstr(5)) <> '-APPES') then
            quit(_fail, 'Program must be run with the following arguments: ' +
              '<INPUT-FILE> <OUTPUT-FILE> <ANSWER-FILE> [<Result_File> [-xml]]');
          ResultName := ParamStr(4);
          AppesMode := true;
        end;
   end; { case }

   inf.opened := false;
   ouf.opened := false;
   ans.opened := false;

   inf.init (ParamStr (1), _Input);
   ouf.init (ParamStr (2), _Output);
   ans.init (ParamStr (3), _Answer);
END.
