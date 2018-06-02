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


   Parser generator file. This file is influenced from the grammar rules given in
   K&R book and various internet links.


   @contributor      Ashwin Jha<ajha.dev@gmail.com>
   @contributor      Durgesh Singh<durgesh.ccet@gmail.com>

*****************************************************************************************************/

%{
#include <stdio.h>
#include "interpreter.h"
#include "abstract_syntax_tree.h"
#include "ast_builder.h"
#include "ast_evaluator.h"
#include "symbol_table.h"
#include "vm.h"
   
#define main_interact_env                    (_main_env_ && _interact_env_)
#define stmt_exec_env                           (main_interact_env && !_block_stmt)
#define ctrl_stmt_exec_env          (main_interact_env && (_block_stmt == 1))

#define is_inc_block_count             {if(main_interact_env) _block_stmt++;}
#define is_dec_block_count                {if(main_interact_env) _block_stmt--;}

#define is_exec_return_stmt                      {if(stmt_exec_env) return 0;}
#define is_check_return_env   {if(main_interact_env && CONTEXT_RETURN_VALUE != NULL) return 0;}

void is_eval_stmt(ast node);
void is_hndlr(ast node);
//#define YYDEBUG 1
%}

%union {
   ast node;
   char unary_code;
   char* string;
   assignment_code assign_code;
}

%token MAIN_FUNCTION LIB_PRINTF LIB_SCANF

%token <string> CHAR_CONSTANT HEX_INT_CONSTANT OCT_INT_CONSTANT DEC_INT_CONSTANT
%token <string> HEX_LONG_CONSTANT OCT_LONG_CONSTANT DEC_LONG_CONSTANT FLOAT_CONSTANT
%token <string> DOUBLE_CONSTANT IDENTIFIER STRING_LITERAL

%token INC_OP DEC_OP LEFT_SHIFT_OP RIGHT_SHIFT_OP
%token LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP

%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN 
%token LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN

%token CHAR_TYPE SHORT_TYPE INT_TYPE LONG_TYPE FLOAT_TYPE DOUBLE_TYPE VOID_TYPE

%token IF ELSE WHILE FOR CONTINUE BREAK RETURN

%type <node> constant type primary_expression postfix_expression unary_expression cast_expression multiplicative_expression
%type <node> additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression
%type <node> inclusive_or_expression logical_and_expression logical_or_expression conditional_expression assignment_expression
%type <node> expression constant_expression initializer declarator variable_declarator variable_declaration statement compound_statement
%type <node> expression_statement selection_statement iteration_statement jump_statement parameter function_definition function_call
%type <node> global_declaration main_prototype main_definition translation_unit script initializer_list variable_declarator_list if_key
%type <node> variable_declaration_list statement_list parameter_list argument_expression_list printf_call scanf_call while_key for_key


%type <unary_code> unary_operator

%type <assign_code> assignment_operator

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start script

%%

constant
   : CHAR_CONSTANT            { $$ = new_constant_node($1, E_CHAR); free($1); }
   | HEX_INT_CONSTANT         { $$ = new_constant_node($1, E_INT); free($1); }
   | OCT_INT_CONSTANT         { $$ = new_constant_node($1, E_INT); free($1); }
   | DEC_INT_CONSTANT         { $$ = new_constant_node($1, E_INT); free($1); }
   | FLOAT_CONSTANT        { $$ = new_constant_node($1, E_FLOAT); free($1); }
   | DOUBLE_CONSTANT       { $$ = new_constant_node($1, E_DOUBLE); free($1); }
   | HEX_LONG_CONSTANT        { $$ = new_constant_node($1, E_LONG); free($1); }
   | OCT_LONG_CONSTANT        { $$ = new_constant_node($1, E_LONG); free($1); }
   | DEC_LONG_CONSTANT        { $$ = new_constant_node($1, E_LONG); free($1); }
   ;

type
   : VOID_TYPE          { $$ = new_type_node("void", E_VOID); }
   | CHAR_TYPE          { $$ = new_type_node("char", E_CHAR); }
   | SHORT_TYPE            { $$ = new_type_node("short", E_SHORT); }
   | INT_TYPE           { $$ = new_type_node("int", E_INT); }
   | FLOAT_TYPE            { $$ = new_type_node("float", E_FLOAT); }
   | DOUBLE_TYPE           { $$ = new_type_node("double", E_DOUBLE); }
   | LONG_TYPE          { $$ = new_type_node("long", E_LONG); }
   | VOID_TYPE '*'            { $$ = new_type_node("void pointer", VOID_PTR); }
   | CHAR_TYPE '*'            { $$ = new_type_node("char pointer", CHAR_PTR); }
   | SHORT_TYPE '*'        { $$ = new_type_node("short pointer", SHORT_PTR); }
   | INT_TYPE '*'          { $$ = new_type_node("int pointer", E_INT_PTR); }
   | FLOAT_TYPE '*'        { $$ = new_type_node("float pointer", FLOAT_PTR); }
   | DOUBLE_TYPE '*'       { $$ = new_type_node("double pointer", DOUBLE_PTR); }
   | LONG_TYPE '*'            { $$ = new_type_node("long pointer", E_LONG_PTR); }
   | VOID_TYPE '*' '*'        { $$ = new_type_node("void 2 pointer", VOID_2PTR); }
   | CHAR_TYPE '*'   '*'         { $$ = new_type_node("char 2 pointer", CHAR_2PTR); }
   | SHORT_TYPE '*' '*'       { $$ = new_type_node("short 2 pointer", SHORT_2PTR); }
   | INT_TYPE '*' '*'         { $$ = new_type_node("int 2 pointer", INT_2PTR); }
   | FLOAT_TYPE '*' '*'       { $$ = new_type_node("float 2 pointer", FLOAT_2PTR); }
   | DOUBLE_TYPE '*' '*'         { $$ = new_type_node("double 2 pointer", DOUBLE_2PTR); }
   | LONG_TYPE '*' '*'        { $$ = new_type_node("long 2 pointer", LONG_2PTR); }
   ;

primary_expression
   : IDENTIFIER            { $$ = new_variable_node($1, UNDEFINED); free($1); }
   | constant           { $$ = $1; }
   | STRING_LITERAL        { $$ = new_constant_node($1, CHAR_PTR); free($1); }
   | '(' expression ')'       { $$ = $2; }
   ;

postfix_expression
   : primary_expression                   { $$ = $1; }
   | IDENTIFIER '[' expression ']'                 { $$ = new_array_variable_node($1, $3, NULL, UNDEFINED); free($1); }
   | IDENTIFIER '[' expression ']' '[' expression ']'       { $$ = new_array_variable_node($1, $3, $6, UNDEFINED); free($1); }
   | function_call                        { $$ = $1; }
   | printf_call                       { $$ = $1; }   
   | scanf_call                        { $$ = $1; }
   | postfix_expression INC_OP                  { $$ = new_inc_exp_node(POST_INCREMENT, $1); }
   | postfix_expression DEC_OP                  { $$ = new_dec_exp_node(POST_DECREMENT, $1); }
   ;

unary_expression
   : postfix_expression                   { $$ = $1; }
   | INC_OP unary_expression                 { $$ = new_inc_exp_node(PRE_INCREMENT, $2); }
   | DEC_OP unary_expression                 { $$ = new_dec_exp_node(PRE_DECREMENT, $2); }
   | unary_operator cast_expression             { $$ = new_unary_exp_node($1, $2); }
   ;

unary_operator
   : '&'                         { $$ = '&'; }
   | '*'                         { $$ = '*'; }
   | '-'                         { $$ = '-'; }
   | '~'                         { $$ = '~'; }
   | '!'                         { $$ = '!'; }
   ;

cast_expression
   : unary_expression                     { $$ = $1; }
   | '(' type ')' cast_expression                  { $$ = new_cast_node($2, $4); }
   ;

multiplicative_expression
   : cast_expression                   { $$ = $1; }
   | multiplicative_expression '*' cast_expression          { $$ = new_mul_exp_node($1, MULTIPLICATION, $3); }
   | multiplicative_expression '/' cast_expression          { $$ = new_mul_exp_node($1, DIVISION, $3); }
   | multiplicative_expression '%' cast_expression          { $$ = new_mul_exp_node($1, MODULO, $3); }
   ;

additive_expression
   : multiplicative_expression                  { $$ = $1; }
   | additive_expression '+' multiplicative_expression         { $$ = new_add_exp_node($1, ADDITION, $3); }
   | additive_expression '-' multiplicative_expression         { $$ = new_add_exp_node($1, SUBTRACTION, $3); }    
   ;

shift_expression
   : additive_expression                     { $$ = $1; }
   | shift_expression LEFT_SHIFT_OP additive_expression        { $$ = new_shift_exp_node($1, LEFT_SHIFT, $3); }
   | shift_expression RIGHT_SHIFT_OP additive_expression       { $$ = new_shift_exp_node($1, RIGHT_SHIFT, $3); }
   ;

relational_expression
   : shift_expression                     {$$ = $1; }
   | relational_expression '<' shift_expression          { $$ = new_rel_exp_node($1, REL_LESS, $3); }
   | relational_expression '>' shift_expression          { $$ = new_rel_exp_node($1, REL_GREATER, $3); }
   | relational_expression LE_OP shift_expression           { $$ = new_rel_exp_node($1, REL_LESS_EQUAL, $3); }
   | relational_expression GE_OP shift_expression           { $$ = new_rel_exp_node($1, REL_GREATER_EQUAL, $3); }
   ;

equality_expression
   : relational_expression                   { $$ = $1; }
   | equality_expression EQ_OP relational_expression        { $$ = new_rel_exp_node($1, REL_EQUAL, $3); }
   | equality_expression NE_OP relational_expression        { $$ = new_rel_exp_node($1, REL_NOT_EQUAL, $3); }
   ;

and_expression
   : equality_expression                     { $$ = $1; }
   | and_expression '&' equality_expression           { $$ = new_bit_exp_node($1, BITWISE_AND, $3); }
   ;

exclusive_or_expression
   : and_expression                    { $$ = $1; }
   | exclusive_or_expression '^' and_expression          { $$ = new_bit_exp_node($1, BITWISE_XOR, $3); }
   ;

inclusive_or_expression
   : exclusive_or_expression                 { $$ = $1; }
   | inclusive_or_expression '|' exclusive_or_expression       { $$ = new_bit_exp_node($1, BITWISE_OR, $3); }
   ;

logical_and_expression
   : inclusive_or_expression                 { $$ = $1; }
   | logical_and_expression AND_OP inclusive_or_expression        { $$ = new_logic_exp_node($1, LOGICAL_AND, $3); }
   ;

logical_or_expression
   : logical_and_expression                  { $$ = $1; }
   | logical_or_expression OR_OP logical_and_expression        { $$ = new_logic_exp_node($1, LOGICAL_OR, $3); }
   ;

conditional_expression
   : logical_or_expression                   { $$ = $1; }
   | logical_or_expression '?' expression ':' conditional_expression { $$ = new_cond_exp_node($1, $3, $5); }
   ;

assignment_expression
   : conditional_expression                  { $$ = $1; }
   | unary_expression assignment_operator assignment_expression      { $$ = new_assign_exp_node($1, $2, $3); }
   ;

assignment_operator
   : '='                         { $$ = EQ_ASSIGN_CODE; }
   | MUL_ASSIGN                        { $$ = MUL_ASSIGN_CODE; }
   | DIV_ASSIGN                        { $$ = DIV_ASSIGN_CODE; }
   | MOD_ASSIGN                        { $$ = MOD_ASSIGN_CODE; }
   | ADD_ASSIGN                        { $$ = ADD_ASSIGN_CODE; }
   | SUB_ASSIGN                        { $$ = SUB_ASSIGN_CODE; }
   | LEFT_ASSIGN                       { $$ = LEFT_ASSIGN_CODE; }
   | RIGHT_ASSIGN                      { $$ = RIGHT_ASSIGN_CODE; }
   | AND_ASSIGN                        { $$ = AND_ASSIGN_CODE; }
   | XOR_ASSIGN                        { $$ = XOR_ASSIGN_CODE; }
   | OR_ASSIGN                      { $$ = OR_ASSIGN_CODE; }
   ;

expression
   : assignment_expression                   { $$ = new_exp_list_node($1); }
   | expression ',' assignment_expression             { $$ = append_exp_list_node($1, $3); }
   ;

constant_expression
   : conditional_expression                  { $$ = $1; }
   ;

initializer
   : assignment_expression                   { $$ = $1; }
   | '{' initializer_list '}'                { $$ = $2; }
   ;

initializer_list
   : initializer                       { $$ = new_init_list_node($1); }
   | initializer_list ',' initializer              { $$ = append_init_list_node($1, $3); }
   ;

declarator
   : IDENTIFIER                        { $$ = new_variable_node($1,E_UNDEFINED); free($1); }
   | IDENTIFIER '[' constant_expression ']'           { $$ = new_array_variable_node($1, $3, NULL,E_UNDEFINED); free($1); }
   | IDENTIFIER '[' constant_expression ']' '[' constant_expression ']' { $$ = new_array_variable_node($1, $3, $6,E_UNDEFINED); free($1); }
   ;

variable_declarator
   : declarator                        { $$ = $1; }
   | declarator '=' initializer                 { $$ = new_assign_exp_node($1, EQ_ASSIGN_CODE, $3); }
   ;

variable_declarator_list
   : variable_declarator                     { $$ = new_var_decl_list_node($1); }
   | variable_declarator_list ',' variable_declarator       { $$ = append_var_decl_list_node($1, $3); }
   ;

variable_declaration
   : type variable_declarator_list ';'             { $$ = new_decl_node($1, $2); is_eval_stmt($$); }
   ;

variable_declaration_list
   : variable_declaration                    { if(stmt_exec_env) { $$ = NULL; } else { $$ = new_var_type_decl_list_node($1); } }
   | variable_declaration_list variable_declaration         { if(stmt_exec_env) { $$ = NULL; } else { $$ = append_var_type_decl_list_node($1, $2); } }
   ;

statement
   : compound_statement                   { if(stmt_exec_env) { $$ = NULL; } else { $$ = $1; } }
   | expression_statement                    { if(stmt_exec_env) { $$ = NULL; } else { $$ = $1; } }
   | selection_statement                     { if(stmt_exec_env) { $$ = NULL; } else { $$ = $1; } }
   | iteration_statement                     { if(stmt_exec_env) { $$ = NULL; } else { $$ = $1; } }
   | jump_statement                    { if(stmt_exec_env) { $$ = NULL; } else { $$ = $1; } }
   ;

statement_list
   : statement                      { if(stmt_exec_env) { $$ = NULL; } else { $$ = new_stmt_list_node($1); } }
   | statement_list statement                { if(stmt_exec_env) { $$ = NULL; } else { $$ = append_stmt_list_node($1, $2); } }
   ;

expression_statement
   : ';'                         { $$ = new_exp_stmt_node(NULL); }
   | expression ';'                    { $$ = new_exp_stmt_node($1); is_eval_stmt($$); }
   ;

if_key
   : IF                          { $$ = NULL; is_inc_block_count }
   ;

selection_statement
   : if_key '(' expression ')' statement %prec LOWER_THAN_ELSE       { $$ = new_if_stmt_node($3, $5, NULL); is_hndlr($$); is_check_return_env }
   | if_key '(' expression ')' statement ELSE statement        { $$ = new_if_stmt_node($3, $5, $7); is_hndlr($$); is_check_return_env }
   ;

while_key
   : WHILE                          { $$ = NULL; is_inc_block_count }
   ;

for_key
   : FOR                         { $$ = NULL; is_inc_block_count }
   ;

iteration_statement
   : while_key '(' expression ')' statement                 { $$ = new_while_stmt_node($3, $5); is_hndlr($$); is_check_return_env }
   | for_key '(' expression_statement expression_statement ')' statement         { $$ = new_for_stmt_node($3,$4,NULL,$6);  is_hndlr($$); is_check_return_env }
   | for_key '(' expression_statement expression_statement expression ')' statement    { $$ = new_for_stmt_node($3,$4,$5,$7); is_hndlr($$); is_check_return_env }
   ;

jump_statement
   : RETURN ';'                     { if(stmt_exec_env) { $$ = NULL; } else { $$ = new_return_stmt_node(NULL); } is_exec_return_stmt }
   | RETURN expression ';'                { if(stmt_exec_env) { $$ = NULL; purge_ast($2); } else { $$ = new_return_stmt_node($2); } is_exec_return_stmt }
   | BREAK ';'                   { $$ = new_break_stmt_node(); }
   | CONTINUE ';'                   { $$ = new_continue_stmt_node(); }
   ;

compound_statement
   : '{' '}'                     { if(stmt_exec_env) { $$ = NULL; } else { $$ = new_compound_stmt_node(NULL, NULL); } }
   | '{' statement_list '}'               { if(stmt_exec_env) { $$ = NULL; } else { $$ = $2; } }
   | '{' variable_declaration_list '}'          { if(stmt_exec_env) { $$ = NULL; } else { $$ = $2; } }
   | '{' variable_declaration_list statement_list '}'    { if(stmt_exec_env) { $$ = NULL; } else { $$ = new_compound_stmt_node($2, $3); } }
   ;

parameter_list
   :                       { $$ = NULL; }
   | parameter                   { $$ = new_param_list_node($1); }
   | parameter_list ',' parameter               { $$ = append_param_list_node($1, $3); }
   ;

parameter
   : type IDENTIFIER                { $$ = new_param_node($1, $2); free($2); }
   ;

function_definition
   : type IDENTIFIER '(' parameter_list ')' compound_statement { $$ = new_func_def_node($1,$2,$4,$6); free($2); }
   ;

function_call
   : IDENTIFIER '(' argument_expression_list ')'         { $$ = new_func_call_node($1,$3); free($1); }
   ;

printf_call
   : LIB_PRINTF '(' argument_expression_list ')'         { $$ = new_printf_call_node($3); }
   ;

scanf_call
   : LIB_SCANF '(' argument_expression_list ')'       { $$ = new_scanf_call_node($3); }
   ;

argument_expression_list
   :                       { $$ = NULL; }
   | assignment_expression                { $$ = new_arg_exp_list_node($1); }
   | argument_expression_list ',' assignment_expression     { $$ = append_arg_exp_list_node($1, $3); }
   ;

global_declaration
   : function_definition                  { $$ = $1; eval_func_def($$); if(_interact_env_) print_prompt(); }
   | variable_declaration                 { $$ = $1; eval_global_var_decl($$); if(_interact_env_) print_prompt(); }
   ;

main_prototype
   : INT_TYPE MAIN_FUNCTION '(' ')'          { $$ = NULL; _main_env_ = TRUE; if(_interact_env_) print_prompt(); ar* record = new_ar(MAIN_FUNCTION_LABEL); push_ar(record); /*set IN_MAIN flag here*/ }
   ;

main_definition
   : main_prototype compound_statement          { if(!_interact_env_) {$$ = new_main_def_node($2); eval_main_def($$);} else { $$ = NULL; is_exec_return_stmt } }
   ;

translation_unit
   : global_declaration                   { $$ = NULL; /* are these nodes required? */ }
   | translation_unit global_declaration           { $$ = NULL; /* are these nodes required? */ }
   ;

script
   : main_definition                   { $$ = new_func_call_node(MAIN_FUNCTION_LABEL, NULL); set_main_ref($$); return 0; /* are these nodes required? */ }
   | translation_unit main_definition           { $$ = new_func_call_node(MAIN_FUNCTION_LABEL, NULL); set_main_ref($$); return 0; /* are these nodes required? */ }
   ;
%%

extern char yytext[];
extern int column;
extern int row;
//int yydebug=1;

yyerror(char* s) {
   fflush(stdout);
   printf("\nSYNTACTICAL EXCEPTION: Syntax error at line %d, column %d\n", row, column);
}

void is_eval_stmt(ast node) {
   if(ctrl_stmt_exec_env) {
      if(node->tag == IF_STATEMENT || node->tag == WHILE_STATEMENT || node->tag == FOR_STATEMENT) {
         eval_stmt(node);        
         purge_ast(node);  
         print_prompt();
      }
   } else if(stmt_exec_env) {
      if(node->tag == EXPRESSION_STATEMENT) eval_exp_stmt(node);
      else if(node->tag == RETURN_STATEMENT) eval_return_stmt(node);
      else if(node->tag == DECLARATION) eval_var_decl(CONTEXT_SYMBOL_TABLE, node);
      purge_ast(node);
      print_prompt();
   }
}

void is_hndlr(ast node) {
   is_eval_stmt(node);
   is_dec_block_count
}
