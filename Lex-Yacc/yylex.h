#ifndef yy_state_t
#define yy_state_t unsigned char
#endif
#define YYNEWLINE 10

#line 1 // "D:\\YACC/etc/yylex.cpp"
// MKS LEX prototype scanner header
// Copyright 1991 by Mortice Kern Systems Inc.
// All rights reserved.

// You can define YY_PRESERVE to get System V UNIX lex compatibility,
// if you need to change yytext[] in your user actions
// This is quite a bit slower, though, so the default is without

class yy_scan
{
protected:

yy_state_t* state; // state buffer
int size; // length of state buffer
int mustfree; // set if space is allocated
int yy_end; // end of pushback
int yy_start; // start state
int yy_lastc; // previous char
#ifndef YY_PRESERVE // efficient default push-back scheme
char save; // saved yytext[yyleng]
#else // slower push-back for yytext mungers
char* save; // saved yytext[]
char* push;
#endif

public:

char* yytext; // yytext text buffer
FILE* yyin; // input stream
FILE* yyout; // output stream
int yylineno; // line number
int yyleng; // yytext token length

yy_scan(int sz = 100); // Constructor for this scanner. Default token & pushback size is 100 bytes
yy_scan(int sz,char* buf,char* sv,yy_state_t* states); // Constructor when tables are given
virtual ~yy_scan(); // Destructor

int yylex(); // begin a scan

virtual int yygetc()
{
// Scanner source of input characters
return getc(yyin);
}

virtual int yywrap()
{
return 1; // EOF processing
}

// virtual void yyerror(char*,...); // print error message
virtual void yyerror(char*); // print error message

virtual void output(int c)
{
putc(c, yyout);
}

virtual void output(const char* const pszStr) { }

virtual void YY_FATAL(char* msg)
{
// print message and stop
yyerror(msg);
exit(1);
}

virtual void ECHO()
{
// Print matched input
fputs((const char*)yytext,yyout);
}

int input(); // user-callable get-input
int unput(int c); // user-callable unput character
void yy_reset(); // reset scanner

void setinput(FILE* in)
{
// Switch input streams
yyin = in;
}

void setoutput(FILE* out)
{
// Switch output
yyout = out;
}

void NLSTATE()
{
yy_lastc = YYNEWLINE;
}

void YY_INIT()
{
yy_start = 0;
yy_end = 0;
yyleng = 0;
yy_lastc = YYNEWLINE;
}

void YY_USER()
{
// Set up yytext for user
#ifndef YY_PRESERVE
save = yytext[yyleng];
#else
size_t n = yy_end - yyleng;
push = save+size - n;

if (n > 0)
{
memmove(push, yytext+yyleng, n);
}
#endif
yytext[yyleng] = 0;
}

void YY_SCANNER()
{
// Set up yytext for scanner
#ifndef YY_PRESERVE
yytext[yyleng] = save;
#else
size_t n = save+size - push;

if (n > 0)
{
memmove(yytext+yyleng, push, n);
}

yy_end = yyleng + n;
#endif
}

void yyless(int n)
{
// trim input to 'n' bytes
if (n >= 0 && n <= yy_end)
{
YY_SCANNER();
yyleng = n;
YY_USER();
}
}

void yycomment(char* const mat); // skip comment input
int yymapch(int delim,int escape); // map C escapes
};

// #include "stdafx.h"

