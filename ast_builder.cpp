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


This module handles bulk of the ast building code. These functions are used in the
parser (from the yacc file).

TODO AND FIXME list:
1. Nodes for script, translation-unit are not required. So, the corresponding
functions can be removed.


@author Ashwin Jha<ajha.dev@gmail.com>
@contributor Durgesh Singh<durgesh.ccet@gmail.com>

*****************************************************************************************************/

#include "interpreter.h"
#include "abstract_syntax_tree.h"
#include "ast_builder.h"
#include "ast_util.h"
#include "symbol_table.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ast new_constant_node(char* l,data_type rt)
{
   return new_ast(CONSTANT,l,rt);
}

ast new_type_node(char* l,data_type rt)
{
   return new_ast(TYPE,l,rt);
}

ast new_variable_node(char* l,data_type rt)
{
   return new_ast(VARIABLE,l,rt);
}

ast new_array_variable_node(char* id,ast offset1,ast offset2,data_type rt)
{
   ast   arr_node;
   if (offset2 != NULL)
   {
      set_left_most_sibling(offset1,offset2);
      arr_node = new_ast(ARRAY2,id,rt);
   }
   else
   {
      arr_node = new_ast(ARRAY,id,rt);
   }
   set_left_most_child(arr_node,offset1);
   return arr_node;
}

ast new_inc_exp_node(ast_node_tag t,ast exp)
{
   ast   new_node    = new_ast(t,toString(t),E_INT);
   ast   unit_node   = new_constant_node("1",E_INT);
   ast   dup_exp     = copy_ast(exp);
   ast   add_node    = new_add_exp_node(dup_exp,ADDITION,unit_node);
   set_left_most_child(new_node,exp);
   set_left_most_sibling(exp,add_node);
   return new_node;
}

ast new_dec_exp_node(ast_node_tag t,ast exp)
{
   ast   new_node    = new_ast(t,toString(t),E_INT);
   ast   unit_node   = new_constant_node("1",E_INT);
   ast   dup_exp     = copy_ast(exp);
   ast   sub_node    = new_add_exp_node(dup_exp,SUBTRACTION,unit_node);
   set_left_most_child(new_node,exp);
   set_left_most_sibling(exp,sub_node);
   return new_node;
}

ast new_unary_exp_node(char op,ast exp)
{
   ast   unary_exp_node = NULL;
   switch (op)
   {
      case '&':
         unary_exp_node = new_ref_exp_node(exp);
         break;
      case '*':
         unary_exp_node = new_deref_exp_node(exp);
         break;
      case '+':
         unary_exp_node = new_unary_plus_exp_node(exp);
         break;
      case '-':
         unary_exp_node = new_unary_minus_exp_node(exp);
         break;
      case '~':
         unary_exp_node = new_complement_exp_node(exp);
         break;
      case '!':
         unary_exp_node = new_not_exp_node(exp);
         break;
   }
   return unary_exp_node;
}

ast new_ref_exp_node(ast exp)
{
   char* label    = concat_str(2,"ref_",exp->ast_node_label);
   ast   ref_node = new_ast(REFERENCE,label,E_UNDEFINED);
   set_left_most_child(ref_node,exp);
   free(label);
   return ref_node;
}

ast new_deref_exp_node(ast exp)
{
   char* label       = concat_str(2,"deref_",exp->ast_node_label);
   ast   deref_node  = new_ast(DEREFERENCE,label,E_UNDEFINED);
   set_left_most_child(deref_node,exp);
   free(label);
   return deref_node;
}

ast new_unary_plus_exp_node(ast exp)
{
   char* label             = concat_str(2,"uplus_",exp->ast_node_label);
   ast   unary_plus_node   = new_ast(UNARY_PLUS,label,E_UNDEFINED);
   set_left_most_child(unary_plus_node,exp);
   free(label);
   return unary_plus_node;
}

ast new_unary_minus_exp_node(ast exp)
{
   char* label             = concat_str(2,"uminus_",exp->ast_node_label);
   ast   unary_minus_node  = new_ast(UNARY_MINUS,label,E_UNDEFINED);
   set_left_most_child(unary_minus_node,exp);
   free(label);
   return unary_minus_node;
}

ast new_complement_exp_node(ast exp)
{
   char* label             = concat_str(2,"~_",exp->ast_node_label);
   ast   complement_node   = new_ast(BITWISE_NOT,label,E_UNDEFINED);
   set_left_most_child(complement_node,exp);
   free(label);
   return complement_node;
}

ast new_not_exp_node(ast exp)
{
   char* label    = concat_str(2,"!_",exp->ast_node_label);
   ast   not_node = new_ast(LOGICAL_NOT,label,E_UNDEFINED);
   set_left_most_child(not_node,exp);
   free(label);
   return not_node;
}

ast new_cast_node(ast type,ast expression)
{
   char* label       = concat_str(4,"tp_",type->ast_node_label,"_on_",expression->ast_node_label);
   ast   cast_node   = new_ast(TYPE_CAST,label,type->return_type);
   set_left_most_sibling(type,expression);
   set_left_most_child(cast_node,type);
   free(label);
   return cast_node;
}

ast new_mul_exp_node(ast left,ast_node_tag t,ast right)
{
   char* label          = concat_str(5,left->ast_node_label,"_",toString(t),"_",right->ast_node_label);
   ast   mul_exp_node   = new_ast(t,label,E_UNDEFINED);
   set_left_most_sibling(left,right);
   set_left_most_child(mul_exp_node,left);
   free(label);
   return mul_exp_node;
}

ast new_add_exp_node(ast left,ast_node_tag t,ast right)
{
   char* label          = concat_str(5,left->ast_node_label,"_",toString(t),"_",right->ast_node_label);
   ast   add_exp_node   = new_ast(t,label,E_UNDEFINED);
   set_left_most_sibling(left,right);
   set_left_most_child(add_exp_node,left);
   free(label);
   return add_exp_node;
}

ast new_shift_exp_node(ast left,ast_node_tag t,ast right)
{
   char* label          = concat_str(5,left->ast_node_label,"_",toString(t),"_",right->ast_node_label);
   ast   shift_exp_node = new_ast(t,label,left->return_type);
   set_left_most_sibling(left,right);
   set_left_most_child(shift_exp_node,left);
   free(label);
   return shift_exp_node;
}

ast new_rel_exp_node(ast left,ast_node_tag t,ast right)
{
   char* label          = concat_str(5,left->ast_node_label,"_",toString(t),"_",right->ast_node_label);
   ast   rel_exp_node   = new_ast(t,label,E_INT);
   set_left_most_sibling(left,right);
   set_left_most_child(rel_exp_node,left);
   free(label);
   return rel_exp_node;
}

ast new_logic_exp_node(ast left,ast_node_tag t,ast right)
{
   char* label          = concat_str(5,left->ast_node_label,"_",toString(t),"_",right->ast_node_label);
   ast   logic_exp_node = new_ast(t,label,E_INT);
   set_left_most_sibling(left,right);
   set_left_most_child(logic_exp_node,left);
   free(label);
   return logic_exp_node;
}

ast new_bit_exp_node(ast left,ast_node_tag t,ast right)
{
   char* label          = concat_str(5,left->ast_node_label,"_",toString(t),"_",right->ast_node_label);
   ast   bit_exp_node   = new_ast(t,label,E_UNDEFINED);
   set_left_most_sibling(left,right);
   set_left_most_child(bit_exp_node,left);
   free(label);
   return bit_exp_node;
}

ast new_cond_exp_node(ast condition,ast true_case,ast false_case)
{
   char* label          = concat_str(5,condition->ast_node_label,"?",true_case->ast_node_label,":",false_case->ast_node_label);
   ast   cond_exp_node  = new_ast(CONDITIONAL,label,E_UNDEFINED);
   set_left_most_sibling(true_case,false_case);
   set_left_most_sibling(condition,true_case);
   set_left_most_child(cond_exp_node,condition);
   free(label);
   return cond_exp_node;
}

ast new_assign_exp_node(ast lval,assignment_code code,ast rval)
{
   char* label;
   ast   assign_exp_node;
   ast   temp_op_node   = 0;
   ast   temp_exp_node;
   switch (code)
   {
      case EQ_ASSIGN_CODE:
         temp_op_node = rval;
         break;
      case MUL_ASSIGN_CODE:
         temp_exp_node = copy_ast(lval);
         set_left_most_sibling(temp_exp_node,rval);
         temp_op_node = new_mul_exp_node(lval,MULTIPLICATION,temp_exp_node);
         set_left_most_child(temp_op_node,temp_exp_node);
         break;
      case DIV_ASSIGN_CODE:
         temp_exp_node = copy_ast(lval);
         set_left_most_sibling(temp_exp_node,rval);
         temp_op_node = new_mul_exp_node(lval,DIVISION,temp_exp_node);
         set_left_most_child(temp_op_node,temp_exp_node);
         break;
      case MOD_ASSIGN_CODE:
         temp_exp_node = copy_ast(lval);
         set_left_most_sibling(temp_exp_node,rval);
         temp_op_node = new_mul_exp_node(lval,MODULO,temp_exp_node);
         set_left_most_child(temp_op_node,temp_exp_node);
         break;
      case ADD_ASSIGN_CODE:
         temp_exp_node = copy_ast(lval);
         set_left_most_sibling(temp_exp_node,rval);
         temp_op_node = new_add_exp_node(lval,ADDITION,temp_exp_node);
         set_left_most_child(temp_op_node,temp_exp_node);
         break;
      case SUB_ASSIGN_CODE:
         temp_exp_node = copy_ast(lval);
         set_left_most_sibling(temp_exp_node,rval);
         temp_op_node = new_add_exp_node(lval,SUBTRACTION,temp_exp_node);
         set_left_most_child(temp_op_node,temp_exp_node);
         break;
      case LEFT_ASSIGN_CODE:
         temp_exp_node = copy_ast(lval);
         set_left_most_sibling(temp_exp_node,rval);
         temp_op_node = new_shift_exp_node(lval,LEFT_SHIFT,temp_exp_node);
         set_left_most_child(temp_op_node,temp_exp_node);
         break;
      case RIGHT_ASSIGN_CODE:
         temp_exp_node = copy_ast(lval);
         set_left_most_sibling(temp_exp_node,rval);
         temp_op_node = new_shift_exp_node(lval,RIGHT_SHIFT,temp_exp_node);
         set_left_most_child(temp_op_node,temp_exp_node);
         break;
      case AND_ASSIGN_CODE:
         temp_exp_node = copy_ast(lval);
         set_left_most_sibling(temp_exp_node,rval);
         temp_op_node = new_bit_exp_node(lval,BITWISE_AND,temp_exp_node);
         set_left_most_child(temp_op_node,temp_exp_node);
         break;
      case XOR_ASSIGN_CODE:
         temp_exp_node = copy_ast(lval);
         set_left_most_sibling(temp_exp_node,rval);
         temp_op_node = new_bit_exp_node(lval,BITWISE_XOR,temp_exp_node);
         set_left_most_child(temp_op_node,temp_exp_node);
         break;
      case OR_ASSIGN_CODE:
         temp_exp_node = copy_ast(lval);
         set_left_most_sibling(temp_exp_node,rval);
         temp_op_node = new_bit_exp_node(lval,BITWISE_OR,temp_exp_node);
         set_left_most_child(temp_op_node,temp_exp_node);
         break;
   }
   label = concat_str(3,lval->ast_node_label,"=",temp_op_node->ast_node_label);
   assign_exp_node = new_ast(ASSIGNMENT,label,E_UNDEFINED);
   set_left_most_sibling(lval,temp_op_node);
   set_left_most_child(assign_exp_node,lval);
   free(label);
   return assign_exp_node;
}

ast new_exp_list_node(ast exp_node)
{
   ast   exp_list = new_ast(EXP_LIST,"exp_list",E_UNDEFINED);
   if (exp_node != NULL)
   {
      set_left_most_child(exp_list,exp_node);
   }
   return exp_list;
}

ast append_exp_list_node(ast exp_list,ast exp_node)
{
   ast   temp  = get_left_most_child(exp_list);
   if (temp == NULL)
   {
      set_left_most_child(exp_list,exp_node);
   }
   else
   {
      while (temp->left_most_sibling)
      {
         temp = get_left_most_sibling(temp);
      }
      set_left_most_sibling(temp,exp_node);
   }
   return exp_list;
}

ast new_init_list_node(ast init_node)
{
   ast   init_list   = new_ast(INIT_LIST,"init_list",E_UNDEFINED);
   set_left_most_child(init_list,init_node);
   return init_list;
}

ast append_init_list_node(ast init_list,ast init_node)
{
   ast   temp  = get_left_most_child(init_list);
   while (temp->left_most_sibling != NULL)
   {
      temp = get_left_most_sibling(temp);
   }
   set_left_most_sibling(temp,init_node);
   return init_list;
}

ast new_var_decl_list_node(ast var_node)
{
   ast   var_decl_list  = new_ast(VAR_DECL_LIST,"var_decl_list",E_UNDEFINED);
   set_left_most_child(var_decl_list,var_node);
   return var_decl_list;
}

ast append_var_decl_list_node(ast var_decl_list,ast var_node)
{
   ast   temp  = get_left_most_child(var_decl_list);
   while (temp->left_most_sibling != NULL)
   {
      temp = get_left_most_sibling(temp);
   }
   set_left_most_sibling(temp,var_node);
   return var_decl_list;
}

ast new_decl_node(ast type,ast var_decl_list)
{
   char* label       = concat_str(3,type->ast_node_label,"_",var_decl_list->ast_node_label);
   ast   decl_node   = new_ast(DECLARATION,label,E_UNDEFINED);
   set_left_most_sibling(type,var_decl_list);
   set_left_most_child(decl_node,type);
   free(label);
   return decl_node;
}

ast new_var_type_decl_list_node(ast decl_node)
{
   ast   var_type_decl_list   = new_ast(VAR_TYPE_DECL_LIST,"var_type_decl_list",E_UNDEFINED);
   set_left_most_child(var_type_decl_list,decl_node);
   return var_type_decl_list;
}

ast append_var_type_decl_list_node(ast var_type_decl_list,ast decl_node)
{
   ast   temp  = get_left_most_child(var_type_decl_list);
   while (temp->left_most_sibling != NULL)
   {
      temp = get_left_most_sibling(temp);
   }
   set_left_most_sibling(temp,decl_node);
   return var_type_decl_list;
}

ast new_stmt_list_node(ast stmt_node)
{
   ast   stmt_list   = new_ast(STATEMENT_LIST,"stmt_list",E_UNDEFINED);
   set_left_most_child(stmt_list,stmt_node);
   return stmt_list;
}

ast append_stmt_list_node(ast stmt_list,ast stmt_node)
{
   ast   temp  = get_left_most_child(stmt_list);
   while (temp->left_most_sibling != NULL)
   {
      temp = get_left_most_sibling(temp);
   }
   set_left_most_sibling(temp,stmt_node);
   return stmt_list;
}

ast new_exp_stmt_node(ast exp_node)
{
   ast   exp_stmt_node  = new_ast(EXPRESSION_STATEMENT,"exp_stmt",E_UNDEFINED);
   if (exp_node != NULL)
   {
      set_left_most_child(exp_stmt_node,exp_node);
   }
   return exp_stmt_node;
}

ast new_if_stmt_node(ast condition,ast if_case,ast else_case)
{
   char* label          = concat_str(5,"if","_",condition->ast_node_label,"_",if_case->ast_node_label);
   ast   if_stmt_node   = new_ast(IF_STATEMENT,label,E_UNDEFINED);
   set_left_most_sibling(condition,if_case);
   if (else_case != NULL)
   {
      set_left_most_sibling(if_case,else_case);
   }
   set_left_most_child(if_stmt_node,condition);
   free(label);
   return if_stmt_node;
}

ast new_while_stmt_node(ast condition,ast stmt)
{
   char* label             = concat_str(5,"while","_",condition->ast_node_label,"_",stmt->ast_node_label);
   ast   while_stmt_node   = new_ast(WHILE_STATEMENT,label,E_UNDEFINED);
   set_left_most_sibling(condition,stmt);
   set_left_most_child(while_stmt_node,condition);
   free(label);
   return while_stmt_node;
}

ast new_for_stmt_node(ast init_node,ast condition,ast inc_exp_node,ast stmt)
{
   char* label          = concat_str(7,"for","_",init_node->ast_node_label,"_",condition->ast_node_label,"_",stmt->ast_node_label);
   ast   for_stmt_node  = new_ast(FOR_STATEMENT,label,E_UNDEFINED);
   set_left_most_sibling(init_node,condition);
   set_left_most_sibling(condition,stmt);
   if (inc_exp_node != NULL)
   {
      set_left_most_sibling(stmt,inc_exp_node);
   }
   set_left_most_child(for_stmt_node,init_node);
   free(label);
   return for_stmt_node;
}

ast new_return_stmt_node(ast return_value)
{
   ast   return_stmt_node  = new_ast(RETURN_STATEMENT,"return",E_UNDEFINED);
   if (return_value != NULL)
   {
      set_left_most_child(return_stmt_node,return_value);
   }
   return return_stmt_node;
}

ast new_break_stmt_node()
{
   return new_ast(BREAK_STATEMENT,"break",E_UNDEFINED);
}

ast new_continue_stmt_node()
{
   return new_ast(CONTINUE_STATEMENT,"continue",E_UNDEFINED);
}

ast new_compound_stmt_node(ast var_type_decl_list_node,ast stmt_list_node)
{
   ast   compound_stmt_node   = new_ast(BLOCK,"compound",E_UNDEFINED);
   if (var_type_decl_list_node != NULL)
   {
      set_left_most_sibling(var_type_decl_list_node,stmt_list_node);
      set_left_most_child(compound_stmt_node,var_type_decl_list_node);
   }
   else
   {
      if (stmt_list_node != NULL)
      {
         set_left_most_child(compound_stmt_node,stmt_list_node);
      }
   }
   return compound_stmt_node;
}

ast new_param_node(ast type,char* id)
{
   ast   var_node             = new_variable_node(id,E_UNDEFINED);
   ast   var_decl_list_node   = new_var_decl_list_node(var_node);
   return new_decl_node(type,var_decl_list_node);
}

ast new_param_list_node(ast param_node)
{
   return new_var_type_decl_list_node(param_node);
}

ast append_param_list_node(ast param_list,ast param_node)
{
   return append_var_type_decl_list_node(param_list,param_node);
}

ast new_func_def_node(ast type,char* id,ast param_list,ast compound_stmt)
{
   ast   temp;
   char* param_num      = get_param_num(param_list);
   ast   param_num_node = new_constant_node(param_num,E_INT);
   ast   func_def_node  = new_ast(FUNCTION,id,type->return_type);
   if (param_list != NULL)
   {
      set_left_most_sibling(param_num_node,param_list);
      set_left_most_sibling(param_list,compound_stmt);
   }
   else
   {
      set_left_most_sibling(param_num_node,compound_stmt);
   }
   set_left_most_child(func_def_node,param_num_node);
   temp = type;
   purge_ast(temp);
   type = NULL;
   free(param_num);
   return func_def_node;
}

ast new_func_call_node(char* id,ast arg_param_list)
{
   ast   func_call_node = new_ast(CALL,id,E_UNDEFINED);
   set_left_most_child(func_call_node,arg_param_list);
   return func_call_node;
}

ast new_arg_exp_list_node(ast arg_exp_node)
{
   ast   arg_exp_list   = new_ast(ARGUMENT_EXPRESSION_LIST,"arg_exp_list",E_UNDEFINED);
   set_left_most_child(arg_exp_list,arg_exp_node);
   return arg_exp_list;
}

ast append_arg_exp_list_node(ast arg_exp_list,ast arg_exp_node)
{
   ast   temp  = get_left_most_child(arg_exp_list);
   while (temp->left_most_sibling != NULL)
   {
      temp = get_left_most_sibling(temp);
   }
   set_left_most_sibling(temp,arg_exp_node);
   return arg_exp_list;
}

ast new_printf_call_node(ast arg_param_list)
{
   ast   func_call_node = new_ast(CALL,PRINTF_LABEL,E_UNDEFINED);
   set_left_most_child(func_call_node,arg_param_list);
   return func_call_node;
}

ast new_scanf_call_node(ast arg_param_list)
{
   ast   func_call_node = new_ast(CALL,SCANF_LABEL,E_UNDEFINED);
   set_left_most_child(func_call_node,arg_param_list);
   return func_call_node;
}

ast new_trans_unit_list_node(ast global_decl)
{
   ast   trans_unit_list   = new_ast(TRANSLATION_UNIT_LIST,"trans_unit_list",E_UNDEFINED);
   set_left_most_child(trans_unit_list,global_decl);
   return trans_unit_list;
}

ast append_trans_unit_list_node(ast trans_unit_list,ast global_decl)
{
   ast   temp  = get_left_most_child(trans_unit_list);
   while (temp->left_most_sibling != NULL)
   {
      temp = get_left_most_sibling(temp);
   }
   set_left_most_sibling(temp,global_decl);
   return trans_unit_list;
}

ast new_main_def_node(ast compound_stmt)
{
   char*    param_num = get_param_num(NULL);
   
   ast   param_num_node = new_constant_node(param_num,E_INT);
   ast   main_node      = new_ast(FUNCTION,MAIN_FUNCTION_LABEL,E_INT);
   
   set_left_most_child(main_node,param_num_node);
   set_left_most_sibling(param_num_node,compound_stmt);
   
   free(param_num);

   return main_node;
}

ast new_script_def_node(ast trans_unit,ast main_def)
{
   ast   script_node = new_ast(SCRIPT,"script",E_UNDEFINED);
   
   set_left_most_child(script_node,main_def);
  
   if (trans_unit)
   {
      set_left_most_sibling(main_def,trans_unit);
   }

   return script_node;
}
