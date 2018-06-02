/****************************************************************************************************

   Copyright (C) 2015 Ashwin Jha and Durgesh Singh

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.


   Lexer generator file. This file is influenced from the grammar rules given in
   K&R book and various internet links.


   @contributor      Ashwin Jha<ajha.dev@gmail.com>
   @contributor      Durgesh Singh<durgesh.ccet@gmail.com>

*****************************************************************************************************/

D        [0-9]
L        [a-zA-Z_]
H        [a-fA-F0-9]
FS       (f|F)
IS       (l|L)

%{
#include <stdio.h>
#include "interpreter.h"
#include "abstract_syntax_tree.h"
#include "symbol_table.h"
#include "YY_PARSE.H"

void count();
static void comment();
%}

%%
"/*"        { comment(); }

"main"         { count(); return(MAIN_FUNCTION); }
"printf"    { count(); return(LIB_PRINTF); }
"scanf"        { count(); return(LIB_SCANF); }

"char"         { count(); return(CHAR_TYPE); }
"double"    { count(); return(DOUBLE_TYPE); }
"else"         { count(); return(ELSE); }
"float"        { count(); return(FLOAT_TYPE); }
"for"       { count(); return(FOR); }
"if"        { count(); return(IF); }
"int"       { count(); return(INT_TYPE); }
"long"         { count(); return(LONG_TYPE); }
"return"    { count(); return(RETURN); }
"break"        { count(); return(BREAK); }
"continue"     { count(); return(CONTINUE); }
"short"        { count(); return(SHORT_TYPE); }
"void"         { count(); return(VOID_TYPE); }
"while"        { count(); return(WHILE); }

"bye"       {err_msg="";err();}/*ci command to exit interactive session. This will be changed later. Usage in scripts should be avoided.*/

{L}({L}|{D})*     {count(); yylval.string = strdup(yytext); return(IDENTIFIER);}

0[xX]{H}+      { count(); yylval.string = strdup(yytext); return(HEX_INT_CONSTANT); }
0[xX]{H}+{IS}     { count(); yylval.string = strdup(yytext); return(HEX_LONG_CONSTANT); }
0{D}+       { count(); yylval.string = strdup(yytext); return(HEX_INT_CONSTANT); }
0{D}+{IS}      { count(); yylval.string = strdup(yytext); return(HEX_LONG_CONSTANT); }
{D}+        { count(); yylval.string = strdup(yytext); return(DEC_INT_CONSTANT); }
{D}+{IS}    { count(); yylval.string = strdup(yytext); return(DEC_LONG_CONSTANT); }
L?'(\\.|[^\\'])+' { count(); yylval.string = strdup(yytext); return(CHAR_CONSTANT); }

{D}*"."{D}+    { count(); yylval.string = strdup(yytext); return(DOUBLE_CONSTANT); }
{D}*"."{D}+{FS}      { count(); yylval.string = strdup(yytext); return(FLOAT_CONSTANT); }
{D}+"."{D}*    { count(); yylval.string = strdup(yytext); return(DOUBLE_CONSTANT); }
{D}+"."{D}*{FS}      { count(); yylval.string = strdup(yytext); return(FLOAT_CONSTANT); }

L?\"(\\.|[^\\"])*\"  { count();  yylval.string = strdup(yytext); return(STRING_LITERAL); }

">>="       { count(); return(RIGHT_ASSIGN); }
"<<="       { count(); return(LEFT_ASSIGN); }
"+="        { count(); return(ADD_ASSIGN); }
"-="        { count(); return(SUB_ASSIGN); }
"*="        { count(); return(MUL_ASSIGN); }
"/="        { count(); return(DIV_ASSIGN); }
"%="        { count(); return(MOD_ASSIGN); }
"&="        { count(); return(AND_ASSIGN); }
"^="        { count(); return(XOR_ASSIGN); }
"|="        { count(); return(OR_ASSIGN); }
">>"        { count(); return(RIGHT_SHIFT_OP); }
"<<"        { count(); return(LEFT_SHIFT_OP); }
"++"        { count(); return(INC_OP); }
"--"        { count(); return(DEC_OP); }
"&&"        { count(); return(AND_OP); }
"||"        { count(); return(OR_OP); }
"<="        { count(); return(LE_OP); }
">="        { count(); return(GE_OP); }
"=="        { count(); return(EQ_OP); }
"!="        { count(); return(NE_OP); }
";"         { count(); return(';'); }
"{"         { count(); return('{'); }
"}"         { count(); return('}'); }
","         { count(); return(','); }
":"         { count(); return(':'); }
"="         { count(); return('='); }
"("         { count(); return('('); }
")"         { count(); return(')'); }
"["         { count(); return('['); }
"]"         { count(); return(']'); }
"."         { count(); return('.'); }
"&"         { count(); return('&'); }
"!"         { count(); return('!'); }
"~"         { count(); return('~'); }
"-"         { count(); return('-'); }
"+"         { count(); return('+'); }
"*"         { count(); return('*'); }
"/"         { count(); return('/'); }
"%"         { count(); return('%'); }
"<"         { count(); return('<'); }
">"         { count(); return('>'); }
"^"         { count(); return('^'); }
"|"         { count(); return('|'); }
"?"         { count(); return('?'); }

[ \t\v\n\f]    { count(); }
.        { /* ignore bad characters */ }

%%

yywrap() {
   return(1);
}


static void comment(void) {
    int c;

    while ((c = input()) != 0)
        if (c == '*')
        {
            while ((c = input()) == '*')
                ;

            if (c == '/')
                return;

            if (c == 0)
                break;
        }
    yyerror("Unterminated comment");
}


int row = 1;
int column = 0;

void count() {
   int i;
   for (i = 0; yytext[i] != '\0'; i++) {
      if (yytext[i] == '\n') {
         row++;
         column = 0;
      } else if (yytext[i] == '\t') {
         column += 8 - (column % 8);
      } else {
         column++;
      }
   }
}
