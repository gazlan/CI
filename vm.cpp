#include "stdafx.h"

/****************************************************************************************************

Copyright (C) 2015 Ashwin Jha and Durgesh Singh

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.


Virtual machine for ci. It manages all the modules of the interpreter to
parse-->build ast-->evaluate ast.
For more information on specific modules, check following:
1. Lexer + Parser ci.l, ci.y
2. AST builder ast_builder.h
3. AST evaluation ast_evaluator.h
For data structures:
1. Abstract syntax tree abstract_syntax_tree.h
1. Symbol table symbol_table.h
2. Activation record symbol_table.h


@author Ashwin Jha<ajha.dev@gmail.com>

*****************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "vm.h"
#include "interpreter.h"
#include "abstract_syntax_tree.h"
#include "ast_evaluator.h"
#include "symbol_table.h"
#include "yy_parse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

yyparse();

extern FILE*   yyin, * yyout;
ast            _main_ref_;

/**
* one of these days I will
* define this init boilerplate
*
* int __init__();
*/

void publish_masthead()
{
   fprintf(stdout,"\nci interpreter v"INTERPRETER_VERSION"\n"
"Copyright (C) 2015 Ashwin Jha and Durgesh Singh\n"
"This program comes with ABSOLUTELY NO WARRANTY; for details type \'ci -h\'.\n"
"This is free software, and you are welcome to redistribute it under certain\n"
"conditions; type \'ci -h\' for details.\n\n\t"
"@author Ashwin Jha<ajha.dev@gmail.com>\n\t"
"@contributor Durgesh Singh<durgesh.ccet@gmail.com>\n\n");
}

void show_help()
{
   fprintf(stdout,"\nci interpreter v"INTERPRETER_VERSION"\n"
"Usage:\n"
"Virtual Machine:\tci <ci script file with \".ci\" extension>\n"
"Interactive Session:\tci\n"
"Help:\t\t\tci -h\n"
"Version:\t\tci -v\n\n");
}

void set_main_ref(ast node)
{
   if (_main_ref_ == NULL)
   {
      _main_ref_ = node;
   }
   else
   {
      err_msg = "No main declaration block.\n\n";
      err();
   }
}

void print_prompt()
{
   fprintf(stdout,"ci>> ");
}

int _start_()
{
   publish_masthead();
   print_prompt();
   yyin = stdin;
   while (1)
   {
      init(TRUE);
      yyparse();
      purge_vmds();
      _main_ref_ = NULL;
      fprintf(stdout,"\nBye bye!!\n\n");
      break;
   }
   return 0;
}

int _interpret_(FILE* in)
{
   // go on interpreting
   int   i = -1;

   returnable*    ret = NULL;
   
   init(FALSE);
   
   yyin = in;
   yyparse();
   
   ret = eval_func_call(_main_ref_);
   
   i = ret->eval._INT;
   
   purge_returnable(ret);
   
   purge_vmds();
   
   purge_ast(_main_ref_);
   
   _main_ref_ = NULL;
   
   return i;
}
