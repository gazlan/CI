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


This module handles bulk of the ast evaluation code. A helper module ast_util.c is used
to hanlde specific data type operations and other utility tasks. There is a shortage of
inline comments in this project (we don't believes in commenting).

TODO AND FIXME list:
1. handle type casting statement.
2. implement pre/post increment/decrement operations.


@author Ashwin Jha<ajha.dev@gmail.com>
@contributor Durgesh Singh<durgesh.ccet@gmail.com>

*****************************************************************************************************/

#include "interpreter.h"
#include "symbol_table.h"
#include "abstract_syntax_tree.h"
#include "ast_evaluator.h"
#include "ast_util.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

returnable* eval_constant(ast const_node)
{
   value       val;
   returnable* ret;
   if (const_node->tag != CONSTANT)
   {
      err_msg = "INTERNAL EXCEPTION: CONSTANT node expected.\n\n";
      err();
   }
   else
   {
      val = get_const(const_node->return_type,const_node->ast_node_label);
      ret = new_returnable();
      ret->type = const_node->return_type;
      ret->eval = val;
      return ret;
   }

   return 0;
}

data_type eval_type(ast type_node)
{
   if (type_node->tag != TYPE)
   {
      err_msg = "INTERNAL EXCEPTION: TYPE node expected.\n\n";
      err();
   }
   else
   {
      return type_node->return_type;
   }

   return (data_type) 0;
}

returnable* eval_var_rval(ast var_node)
{
   st_entry*entry = lookup_st_entry(CONTEXT_SYMBOL_TABLE,var_node->ast_node_label);
   if (entry == NULL)
   {
      entry = lookup_st_entry(global_symbol_table,var_node->ast_node_label);
      if (entry == NULL)
      {
         err_msg = "RUNTIME EXCEPTION: Variable not defined in this context.\n\n";
         err();
      }
   }
   if (entry->symbol_entry_tag == _ARRAY)
   {
      return get_lval_from_entry(entry,0,0);
   }
   else if (entry->symbol_entry_tag == _2ARRAY)
   {
      return get_2arr_lval_from_entry(entry,0,0,0);
   }
   else
   {
      return get_rval_from_entry(entry,0,0);
   }
}

returnable* eval_var_lval(ast var_node)
{
   st_entry*entry = lookup_st_entry(CONTEXT_SYMBOL_TABLE,var_node->ast_node_label);
   if (entry == NULL)
   {
      entry = lookup_st_entry(global_symbol_table,var_node->ast_node_label);
      if (entry == NULL)
      {
         err_msg = "RUNTIME EXCEPTION: Variable not defined in this context.\n\n";
         err();
      }
   }
   if (entry->symbol_entry_tag == _2ARRAY)
   {
      return get_2arr_lval_from_entry(entry,0,0,0);
   }
   else
   {
      return get_lval_from_entry(entry,0,0);
   }
}

returnable* eval_arr_rval(ast arr_node)
{
   ast         left_;
   returnable* left;
   returnable* ret   = NULL;
   st_entry*   entry;
   if (arr_node->tag != ARRAY)
   {
      err_msg = "INTERNAL EXCEPTION: ARRAY node expected.\n\n";
      err();
   }
   left_ = get_left_most_child(arr_node);
   entry = lookup_st_entry(CONTEXT_SYMBOL_TABLE,arr_node->ast_node_label);
   if (entry == NULL)
   {
      entry = lookup_st_entry(global_symbol_table,arr_node->ast_node_label);
      if (entry == NULL)
      {
         err_msg = "RUNTIME EXCEPTION: Variable not defined in this context.\n\n";
         err();
      }
   }
   if (left_ == NULL)
   {
      err_msg = "INTERNAL EXCEPTION: Offset node expected.\n\n";
      err();
   }
   left = eval_exp(left_,RVAL);
   if (!is_int_type(left->type))
   {
      err_msg = "RUNTIME EXCEPTION: Offset can't be a non int type.\n\n";
      err();
   }
   if (entry->symbol_entry_tag == _VARIABLE)
   {
      if (is_1pointer_type(entry->symbol_entry_type))
      {
         ret = get_rval_from_entry(entry,left->eval._INT,1);
      }
      else if (is_2pointer_type(entry->symbol_entry_type))
      {
         ret = get_rval_from_entry(entry,left->eval._INT,1);
      }
      else
      {
         err_msg = "RUNTIME EXCEPTION: Basic type variables can't be used as array variables.\n\n";
         err();
      }
   }
   else if (entry->symbol_entry_tag == _2ARRAY)
   {
      ret = get_2arr_lval_from_entry(entry,left->eval._INT,0,1);
   }
   else
   {
      ret = get_rval_from_entry(entry,left->eval._INT,0);
   }
   purge_returnable(left);
   return ret;
}

returnable* eval_arr_lval(ast arr_node)
{
   ast         left_;
   returnable* left;
   returnable* ret   = NULL;
   st_entry*   entry;
   if (arr_node->tag != ARRAY)
   {
      err_msg = "INTERNAL EXCEPTION: ARRAY node expected.\n\n";
      err();
   }
   left_ = get_left_most_child(arr_node);
   entry = lookup_st_entry(CONTEXT_SYMBOL_TABLE,arr_node->ast_node_label);
   if (entry == NULL)
   {
      entry = lookup_st_entry(global_symbol_table,arr_node->ast_node_label);
      if (entry == NULL)
      {
         err_msg = "RUNTIME EXCEPTION: Variable not defined in this context.\n\n";
         err();
      }
   }
   if (left_ == NULL)
   {
      err_msg = "INTERNAL EXCEPTION: Offset node expected.\n\n";
      err();
   }
   left = eval_exp(left_,RVAL);
   if (!is_int_type(left->type))
   {
      err_msg = "RUNTIME EXCEPTION: Offset can't be a non int type.\n\n";
      err();
   }
   if (entry->symbol_entry_tag == _VARIABLE)
   {
      if (is_pointer_type(entry->symbol_entry_type))
      {
         ret = get_rval_from_entry(entry,left->eval._INT,0);
      }
      else if (is_2pointer_type(entry->symbol_entry_type))
      {
         ret = get_rval_from_entry(entry,left->eval._INT,0);
      }
      else
      {
         err_msg = "RUNTIME EXCEPTION: Basic type variables can't be used as array variables.\n\n";
         err();
      }
   }
   else if (entry->symbol_entry_tag == _2ARRAY)
   {
      ret = get_2arr_lval_from_entry(entry,left->eval._INT,0,0);
   }
   else
   {
      ret = get_lval_from_entry(entry,left->eval._INT,0);
   }
   purge_returnable(left);
   return ret;
}

returnable* eval_2arr_rval(ast arr_node)
{
   ast         left_;
   ast         right_;
   returnable* left  = NULL;
   returnable* right = NULL;
   returnable* ret   = NULL;
   st_entry*   entry;
   if (arr_node->tag != ARRAY2)
   {
      err_msg = "INTERNAL EXCEPTION: ARRAY node expected.\n\n";
      err();
   }
   left_ = get_left_most_child(arr_node);
   if (left_ == NULL)
   {
      err_msg = "INTERNAL EXCEPTION: Row offset node expected.\n\n";
      err();
   }
   right_ = get_left_most_sibling(left_);
   if (right_ == NULL)
   {
      err_msg = "INTERNAL EXCEPTION: Column offset node expected.\n\n";
      err();
   }
   entry = lookup_st_entry(CONTEXT_SYMBOL_TABLE,arr_node->ast_node_label);
   if (entry == NULL)
   {
      entry = lookup_st_entry(global_symbol_table,arr_node->ast_node_label);
      if (entry == NULL)
      {
         err_msg = "RUNTIME EXCEPTION: Variable not defined in this context.\n\n";
         err();
      }
   }
   left = eval_exp(left_,RVAL);
   right = eval_exp(right_,RVAL);
   if (!is_int_type(left->type) || !is_int_type(right->type))
   {
      err_msg = "RUNTIME EXCEPTION: Offset can't be a non int type.\n\n";
      err();
   }
   if (entry->symbol_entry_tag == _VARIABLE)
   {
      if (is_2pointer_type(entry->symbol_entry_type))
      {
         ret = get_2arr_rval_from_entry(entry,left->eval._INT,right->eval._INT,0);
      }
      else
      {
         err_msg = "RUNTIME EXCEPTION: Only double pointer type variables can be used as 2d array variables.\n\n";
         err();
      }
   }
   else if (entry->symbol_entry_tag == _ARRAY)
   {
      err_msg = "RUNTIME EXCEPTION: Only double pointer type variables can be used as 2d array variables.\n\n";
      err();
   }
   else
   {
      ret = get_2arr_rval_from_entry(entry,left->eval._INT,right->eval._INT,0);
   }
   purge_returnable(left);
   purge_returnable(right);
   return ret;
}

returnable* eval_2arr_lval(ast arr_node)
{
   ast         left_;
   ast         right_;
   returnable* left  = NULL;
   returnable* right = NULL;
   returnable* ret   = NULL;
   st_entry*   entry;
   if (arr_node->tag != ARRAY2)
   {
      err_msg = "INTERNAL EXCEPTION: ARRAY node expected.\n\n";
      err();
   }
   left_ = get_left_most_child(arr_node);
   if (left_ == NULL)
   {
      err_msg = "INTERNAL EXCEPTION: Row offset node expected.\n\n";
      err();
   }
   right_ = get_left_most_sibling(left_);
   if (right_ == NULL)
   {
      err_msg = "INTERNAL EXCEPTION: Row offset node expected.\n\n";
      err();
   }
   entry = lookup_st_entry(CONTEXT_SYMBOL_TABLE,arr_node->ast_node_label);
   if (entry == NULL)
   {
      entry = lookup_st_entry(global_symbol_table,arr_node->ast_node_label);
      if (entry == NULL)
      {
         err_msg = "RUNTIME EXCEPTION: Variable not defined in this context.\n\n";
         err();
      }
   }
   left = eval_exp(left_,RVAL);
   right = eval_exp(right_,RVAL);
   if (!is_int_type(left->type) || !is_int_type(right->type))
   {
      err_msg = "RUNTIME EXCEPTION: Offset can't be a non int type.\n\n";
      err();
   }
   if (entry->symbol_entry_tag == _VARIABLE)
   {
      if (is_2pointer_type(entry->symbol_entry_type))
      {
         ret = get_2arr_lval_from_entry(entry,left->eval._INT,right->eval._INT,1);
      }
      else
      {
         err_msg = "RUNTIME EXCEPTION: Only double pointer type variables can be used as 2d array variables.\n\n";
         err();
      }
   }
   else if (entry->symbol_entry_tag == _VARIABLE)
   {
      err_msg = "RUNTIME EXCEPTION: Only double pointer type variables can be used as 2d array variables.\n\n";
      err();
   }
   else
   {
      ret = get_2arr_lval_from_entry(entry,left->eval._INT,right->eval._INT,1);
   }
   purge_returnable(left);
   purge_returnable(right);
   return ret;
}

returnable* eval_func_call(ast node)
{
   st_entry*   entry;
   ast         left;
   ast         func_def;
   returnable* ret;
   returnable* param_list;
   ar*         record;

   left = get_left_most_child(node);

   if (left)
   {
      param_list = eval_param_list(left);
   }
   else
   {
      param_list = NULL;
   }

   if (is_lib_func(node->ast_node_label))
   {
      ret = exec_lib_func(node->ast_node_label,param_list);
   }
   else
   {
      entry = lookup_st_entry(global_symbol_table,node->ast_node_label);

      if (!entry)
      {
         err_msg = "RUNTIME EXCEPTION: Function not defined in this context.\n\n";
         err();
      }
      else if (entry->symbol_entry_tag != _FUNCTION)
      {
         err_msg = "RUNTIME EXCEPTION: Not defined as a function.\n\n";
         err();
      }

      func_def = asts[entry->symbol_entry_value.ast_ref_index];
      
      record = new_ar(entry->symbol_entry_label);
      
      push_ar(record);
      
      exec_func(func_def,param_list);
      
      if (CONTEXT_RETURN_VALUE == NULL)
      {
         CONTEXT_RETURN_VALUE = new_returnable();
         CONTEXT_RETURN_VALUE->type = E_VOID;
         CONTEXT_RETURN_VALUE->eval._INT = 0;
      }
      
      ret = copy_returnable(CONTEXT_RETURN_VALUE);
      purge_ar(pop_ar());
   }

   if (param_list)
   {
      purge_returnable(param_list);
   }

   return ret;
}

int exec_func(ast func_def,returnable* param_list)
{
   ast         temp;
   ast         var;
   ast         param;
   st_entry*   entry;
   returnable* p           = param_list;
   returnable* param_num   = eval_constant(get_left_most_child(func_def));
   int         x           = param_num->eval._INT;
   purge_returnable(param_num);
   if ((!x && p != NULL) || (x && p == NULL) || (x && p != NULL && x != get_param_list_size(p)))
   {
      err_msg = "RUNTIME EXCEPTION: Invalid number of parameters to function.\n\n";
      err();
   }
   temp = get_left_most_sibling(get_left_most_child(func_def));
   param = get_left_most_child(temp);
   while (x && p != NULL)
   {
      eval_var_decl(CONTEXT_SYMBOL_TABLE,param);
      var = get_left_most_child(get_left_most_sibling(get_left_most_child(param)));
      entry = lookup_st_entry(CONTEXT_SYMBOL_TABLE,var->ast_node_label);
      if (!is_compatible(entry->symbol_entry_type,p->type))
      {
         err_msg = "RUNTIME EXCEPTION: Incompatible parameter type in function call.\n\n";
         err();
      }
      else
      {
         set_init_value(entry,0,p);
      }
      p = p->next;
      param = get_left_most_sibling(param);
      x--;
   }
   if (param_list != NULL)
   {
      temp = get_left_most_sibling(temp);
   }
   if (temp->tag == VAR_TYPE_DECL_LIST)
   {
      return eval_context_var_decl_list(temp);
   }
   else if (temp->tag == STATEMENT_LIST)
   {
      return eval_stmt_list(temp);
   }
   else
   {
      return eval_block_stmt(temp);
   }
}

returnable* exec_lib_func(char* func,returnable* param_list)
{
   if (!strcmp(func,PRINTF_LABEL))
   {
      return lib_printf(param_list);
   }
   else if (!strcmp(func,SCANF_LABEL))
   {
      return lib_scanf(param_list);
   }
   else
   {
      // this won't get called!!
      err_msg = "INTERNAL EXCEPTION: Boolean function is not working dude.";
      err();
   }

   return NULL;
}

returnable* eval_param_list(ast param_list)
{
   ast         temp  = get_left_most_child(param_list);
   returnable* ret   = NULL;
   returnable* count = NULL;
   while (temp != NULL)
   {
      if (ret == NULL)
      {
         ret = eval_exp(temp,RVAL);
         count = ret;
      }
      else
      {
         count->next = eval_exp(temp,RVAL);
         count = count->next;
      }
      temp = get_left_most_sibling(temp);
   }
   return ret;
}

returnable* eval_exp(ast exp_node,int mode)
{
   switch (exp_node->tag)
   {
      case VARIABLE:
         if (mode)
         {
            return eval_var_lval(exp_node);
         }
         else
         {
            return eval_var_rval(exp_node);
         }
      case ARRAY:
         if (mode)
         {
            return eval_arr_lval(exp_node);
         }
         else
         {
            return eval_arr_rval(exp_node);
         }
      case ARRAY2:
         if (mode)
         {
            return eval_2arr_lval(exp_node);
         }
         else
         {
            return eval_2arr_rval(exp_node);
         }
      case CONSTANT:
         return eval_constant(exp_node);
      case EXP_LIST:
         return eval_exp_list(exp_node);
      case ASSIGNMENT:
         return eval_assign_exp(exp_node);
      case MULTIPLICATION:
         return eval_arithmetic_exp(exp_node);
      case DIVISION:
         return eval_arithmetic_exp(exp_node);
      case MODULO:
         return eval_arithmetic_exp(exp_node);
      case ADDITION:
         return eval_arithmetic_exp(exp_node);
      case SUBTRACTION:
         return eval_arithmetic_exp(exp_node);
      case LEFT_SHIFT:
         return eval_shift_exp(exp_node);
      case RIGHT_SHIFT:
         return eval_shift_exp(exp_node);
      case REL_LESS:
         return eval_rel_exp(exp_node);
      case REL_GREATER:
         return eval_rel_exp(exp_node);
      case REL_LESS_EQUAL:
         return eval_rel_exp(exp_node);
      case REL_GREATER_EQUAL:
         return eval_rel_exp(exp_node);
      case REL_EQUAL:
         return eval_rel_exp(exp_node);
      case REL_NOT_EQUAL:
         return eval_rel_exp(exp_node);
      case BITWISE_AND:
         return eval_bitwise_exp(exp_node);
      case BITWISE_OR:
         return eval_bitwise_exp(exp_node);
      case BITWISE_XOR:
         return eval_bitwise_exp(exp_node);
      case BITWISE_NOT:
         return eval_bitwise_exp(exp_node);
      case LOGICAL_AND:
         return eval_logical_exp(exp_node);
      case LOGICAL_OR:
         return eval_logical_exp(exp_node);
      case LOGICAL_NOT:
         return eval_logical_exp(exp_node);
      case CONDITIONAL:
         return eval_conditional_exp(exp_node);
      case REFERENCE:
         return eval_ref_exp(exp_node);
      case DEREFERENCE:
         return eval_deref_exp(exp_node,mode);
      case UNARY_MINUS:
         return eval_unary_minus_exp(exp_node);
      case PRE_INCREMENT:
      case PRE_DECREMENT:
         return eval_pre_inc_dec_exp(exp_node);
      case POST_INCREMENT:
      case POST_DECREMENT:
         return eval_post_inc_dec_exp(exp_node);
      case TYPE_CAST:
         return eval_cast_exp(exp_node);
      case CALL:
         return eval_func_call(exp_node);
      default:
         err_msg = "INTERNAL EXCEPTION: I wonder why this statement got filtered out.\n\n";
         err();
   }

   return NULL;
}

returnable* eval_exp_list(ast node)
{
   ast         left_;
   returnable* ret;
   returnable* temp;
   left_ = get_left_most_child(node);
   if (left_ == NULL)
   {
      ret = new_returnable();
      ret->type = E_INT;
      ret->eval._INT = 1;
      return ret;
   }
   else if (get_left_most_sibling(left_) == NULL)
   {
      return eval_exp(left_,RVAL);
   }
   else
   {
      do
      {
         temp = eval_exp(left_,RVAL);
         left_ = get_left_most_sibling(left_);
         purge_returnable(temp);
      }
      while (left_ != NULL);
      ret = new_returnable();
      ret->type = E_INT;
      ret->eval._INT = 1;
      return ret;
   }
}

returnable* eval_assign_exp(ast node)
{
   ast         left_;
   ast         right_;
   returnable* left  = NULL;
   returnable* right = NULL;
   returnable* ret;
   left_ = get_left_most_child(node);
   if (!is_lval_type(left_))
   {
      err_msg = "RUNTIME EXCEPTION: Not a valid LVALUE.\n\n";
      err();
   }
   right_ = get_left_most_sibling(left_);
   left = eval_exp(left_,LVAL);
   right = eval_exp(right_,RVAL);
   if (!is_compatible(ptob(left->type),right->type))
   {
      err_msg = "RUNTIME EXCEPTION: Types incompatible for assignment opeartion.\n\n";
      err();
   }
   ret = get_assign_value(left,right);
   purge_returnable(left);
   purge_returnable(right);
   return ret;
}

returnable* eval_post_inc_dec_exp(ast node)
{
   ast         left_;
   ast         right_;
   returnable* left  = NULL;
   returnable* right = NULL;
   returnable* ret;
   left_ = get_left_most_child(node);
   right_ = get_left_most_sibling(left_);
   if (!is_lval_type(left_))
   {
      err_msg = "RUNTIME EXCEPTION: Not a valid LVALUE.\n\n";
      err();
   }
   ret = eval_exp(left_,RVAL);
   if (!is_int_type(ret->type))
   {
      err_msg = "RUNTIME EXCEPTION: Pre/Post Increment/Decrement operators operate on integers only.\n\n";
      err();
   }
   left = eval_exp(left_,LVAL);
   right = eval_exp(right_,RVAL);
   if (!is_compatible(ptob(left->type),right->type))
   {
      err_msg = "RUNTIME EXCEPTION: Types incompatible for assignment opeartion.\n\n";
      err();
   }
   purge_returnable(get_assign_value(left,right));
   purge_returnable(left);
   purge_returnable(right);
   return ret;
}

returnable* eval_pre_inc_dec_exp(ast node)
{
   ast         left_;
   ast         right_;
   returnable* left  = NULL;
   returnable* right = NULL;
   returnable* ret;
   left_ = get_left_most_child(node);
   if (!is_lval_type(left_))
   {
      err_msg = "RUNTIME EXCEPTION: Not a valid LVALUE.\n\n";
      err();
   }
   right_ = get_left_most_sibling(left_);
   left = eval_exp(left_,LVAL);
   right = eval_exp(right_,RVAL);
   if (!is_int_type(ptob(left->type)))
   {
      err_msg = "RUNTIME EXCEPTION: Pre/Post Increment/Decrement operators operate on integers only.\n\n";
      err();
   }
   if (!is_compatible(ptob(left->type),right->type))
   {
      err_msg = "RUNTIME EXCEPTION: Types incompatible for assignment opeartion.\n\n";
      err();
   }
   ret = get_assign_value(left,right);
   purge_returnable(left);
   purge_returnable(right);
   return ret;
}

returnable* eval_cast_exp(ast node)
{
   ast         left_;
   ast         right_;
   data_type   left;
   returnable* right = NULL;
   returnable* ret;
   left_ = get_left_most_child(node);
   right_ = get_left_most_sibling(left_);
   left = eval_type(left_);
   right = eval_exp(right_,RVAL);
   if (is_basic_type(left))
   {
      ret = get_type_cast_val(left,right);
      purge_returnable(right);
      return ret;
   }
   else
   {
      err_msg = "RUNTIME EXCEPTION: Invalid typecast operation.\n\n";
      err();
   }

   return NULL;
}

returnable* eval_arithmetic_exp(ast node)
{
   ast         left_;
   ast         right_;
   returnable* left  = NULL;
   returnable* right = NULL;
   returnable* ret;
   left_ = get_left_most_child(node);
   right_ = get_left_most_sibling(left_);
   left = eval_exp(left_,RVAL);
   right = eval_exp(right_,RVAL);
   if (is_arithmetic_types(left->type,right->type))
   {
      ret = get_arithmetic_value(left,right,node->tag);
      purge_returnable(left);
      purge_returnable(right);
      return ret;
   }
   else
   {
      err_msg = "RUNTIME EXCEPTION: Incompatible types for arithmetic operations.\n\n";
      err();
   }

   return NULL;
}

returnable* eval_shift_exp(ast node)
{
   ast         left_;
   ast         right_;
   returnable* left  = NULL;
   returnable* right = NULL;
   returnable* ret;
   left_ = get_left_most_child(node);
   right_ = get_left_most_sibling(left_);
   left = eval_exp(left_,RVAL);
   right = eval_exp(right_,RVAL);
   if (is_int_type(left->type) && is_int_type(right->type))
   {
      ret = get_arithmetic_value(left,right,node->tag);
      purge_returnable(left);
      purge_returnable(right);
      return ret;
   }
   else
   {
      err_msg = "RUNTIME EXCEPTION: Incompatible types for shift operations.\n\n";
      err();
   }

   return NULL;
}

returnable* eval_rel_exp(ast node)
{
   ast         left_;
   ast         right_;
   returnable* left  = NULL;
   returnable* right = NULL;
   returnable* ret;
   left_ = get_left_most_child(node);
   right_ = get_left_most_sibling(left_);
   left = eval_exp(left_,RVAL);
   right = eval_exp(right_,RVAL);
   if (is_compatible(left->type,right->type))
   {
      ret = get_relational_value(left,right,node->tag);
      purge_returnable(left);
      purge_returnable(right);
      return ret;
   }
   else
   {
      err_msg = "RUNTIME EXCEPTION: Incompatible types for relational operations.\n\n";
      err();
   }

   return NULL;
}

returnable* eval_bitwise_exp(ast node)
{
   ast         left_;
   ast         right_;
   returnable* left  = NULL;
   returnable* right = NULL;
   returnable* ret;
   left_ = get_left_most_child(node);
   right_ = get_left_most_sibling(left_);
   left = eval_exp(left_,RVAL);
   if (right_ != NULL)
   {
      right = eval_exp(right_,RVAL);
   }
   if (is_int_type(left->type) && (right == NULL || is_int_type(right->type)))
   {
      ret = get_bitwise_value(left,right,node->tag);
      purge_returnable(left);
      purge_returnable(right);
      return ret;
   }
   else
   {
      err_msg = "RUNTIME EXCEPTION: Incompatible types for bitwise operations.\n\n";
      err();
   }

   return NULL;
}

returnable* eval_logical_exp(ast node)
{
   ast         left_;
   ast         right_;
   returnable* left  = NULL;
   returnable* right = NULL;
   returnable* ret;
   left_ = get_left_most_child(node);
   right_ = get_left_most_sibling(left_);
   left = eval_exp(left_,RVAL);
   if (right_ != NULL)
   {
      right = eval_exp(right_,RVAL);
   }
   ret = get_logical_value(left,right,node->tag);
   purge_returnable(left);
   purge_returnable(right);
   return ret;
}

returnable* eval_conditional_exp(ast node)
{
   ast         condition_;
   ast         true_case_;
   ast         false_case_;
   returnable* condition;
   returnable* ret;
   condition_ = get_left_most_child(node);
   true_case_ = get_left_most_sibling(condition_);
   false_case_ = get_left_most_sibling(true_case_);
   condition = eval_exp(condition_,RVAL);
   if (condition->type != E_INT)
   {
      err_msg = "RUNTIME EXCEPTION: Condition should evaluate to int.\n\n";
      err();
   }
   if (condition->eval._INT)
   {
      ret = eval_exp(true_case_,RVAL);
   }
   else
   {
      ret = eval_exp(false_case_,RVAL);
   }
   purge_returnable(condition);
   return ret;
}

returnable* eval_unary_minus_exp(ast node)
{
   returnable* exp   = NULL;
   returnable* ret   = NULL;
   exp = eval_exp(get_left_most_child(node),RVAL);
   if (!is_basic_type(exp->type))
   {
      err_msg = "RUNTIME EXCEPTION: Incompatible type for unary minus operation.\n\n";
      err();
   }
   ret = get_arithmetic_value(exp,NULL,node->tag);
   purge_returnable(exp);
   return ret;
}

returnable* eval_deref_exp(ast node,int mode)
{
   ast         left_;
   returnable* left  = NULL;
   returnable* ret;
   left_ = get_left_most_child(node);
   left = eval_exp(left_,RVAL);
   if (!is_pointer_type(left->type))
   {
      err_msg = "RUNTIME EXCEPTION: Pointer value expected.\n\n";
      err();
   }

   if (mode == RVAL)
   {
      ret = get_rval_from_returnable(left,0);
   }
   else
   {
      ret = get_lval_from_returnable(left,0);
   }

   purge_returnable(left);
   
   return ret;
}

returnable* eval_ref_exp(ast node)
{
   ast         left_;
   returnable* left;
   left_ = get_left_most_child(node);
   left = eval_exp(left_,LVAL);
   if (!is_pointer_type(left->type))
   {
      err_msg = "RUNTIME EXCEPTION: Pointer value expected.\n\n";
      err();
   }
   return left;
}

int eval_stmt(ast stmt_node)
{
   if (stmt_node == NULL)
   {
      return 1;
   }
   switch (stmt_node->tag)
   {
      case FOR_STATEMENT:
         return eval_for_stmt(stmt_node);
      case WHILE_STATEMENT:
         return eval_while_stmt(stmt_node);
      case IF_STATEMENT:
         return eval_if_stmt(stmt_node);
      case BLOCK:
         return eval_block_stmt(stmt_node);
      case RETURN_STATEMENT:
         return eval_return_stmt(stmt_node);
      case BREAK_STATEMENT:
         return eval_break_stmt(stmt_node);
      case CONTINUE_STATEMENT:
         return eval_continue_stmt(stmt_node);
      case STATEMENT_LIST:
         return eval_stmt_list(stmt_node);
      case EXPRESSION_STATEMENT:
         return eval_exp_stmt(stmt_node);
      default:
         err_msg = "INTERNAL EXCEPTION: I wonder why this statement got filtered out.\n\n";
         err();
   }

   return 0;
}

int eval_for_stmt(ast node)
{
   int   loop_flag      = 0;
   int   condition;
   ast   init_node_     = get_left_most_child(node);
   ast   condition_     = get_left_most_sibling(init_node_);
   ast   stmt_          = get_left_most_sibling(condition_);
   ast   inc_exp_node_  = get_left_most_sibling(stmt_);
   eval_stmt(init_node_);
   condition = eval_stmt(condition_);
   if (!is_loop_env)
   {
      CONTEXT_ENV |= LOOP_ENV;
      loop_flag = 1;
   }
   while (condition)
   {
      eval_stmt(stmt_);
      if (CONTEXT_RETURN_VALUE != NULL)
      {
         return 1;
      }
      else if (is_break_condition)
      {
         CONTEXT_ENV ^= BREAK_ENV;
         break;
      }
      else if (is_continue_condition)
      {
         CONTEXT_ENV ^= CONTINUE_ENV;
      }
      if (inc_exp_node_ != NULL)
      {
         purge_returnable(eval_exp(inc_exp_node_,RVAL));
      }
      condition = eval_stmt(condition_);
   }
   if (loop_flag)
   {
      CONTEXT_ENV ^= LOOP_ENV;
   }
   return 1;
}

int eval_while_stmt(ast node)
{
   int         loop_flag   = 0;
   ast         condition_  = get_left_most_child(node);
   ast         stmt_       = get_left_most_sibling(condition_);
   returnable* temp;
   returnable* condition   = eval_exp(condition_,RVAL);
   if (!is_loop_env)
   {
      CONTEXT_ENV |= LOOP_ENV;
      loop_flag = 1;
   }
   while (condition->eval._INT)
   {
      eval_stmt(stmt_);
      if (CONTEXT_RETURN_VALUE != NULL)
      {
         return 1;
      }
      else if (is_break_condition)
      {
         CONTEXT_ENV ^= BREAK_ENV;
         break;
      }
      else if (is_continue_condition)
      {
         CONTEXT_ENV ^= CONTINUE_ENV;
      }
      temp = condition;
      condition = eval_exp(condition_,RVAL);
      purge_returnable(temp);
   }
   if (loop_flag)
   {
      CONTEXT_ENV ^= LOOP_ENV;
   }
   return 1;
}

int eval_if_stmt(ast node)
{
   ast         condition_;
   ast         true_case_;
   ast         false_case_;
   returnable* condition;

   condition_ = get_left_most_child(node);
   true_case_ = get_left_most_sibling(condition_);
   false_case_ = get_left_most_sibling(true_case_);
   condition = eval_exp(condition_,RVAL);

   if (condition->type != E_INT)
   {
      err_msg = "RUNTIME EXCEPTION: Condition should evaluate to int.\n\n";
      err();
   }

   if (condition->eval._INT)
   {
      purge_returnable(condition);
      eval_stmt(true_case_);
   }
   else
   {
      purge_returnable(condition);
      eval_stmt(false_case_);
   }

   return 1;
}

int eval_exp_stmt(ast node)
{
   int   i  = 1;
  
   ast      exp_;

   returnable*    exp = NULL;

   exp_ = get_left_most_child(node);
   
   if (exp_)
   {
      exp = eval_exp(exp_,RVAL);
      
      i = exp->eval._INT;
      
      purge_returnable(exp);
   }

   return i;
}

int eval_block_stmt(ast node)
{
   ast   left_;
   ast   right_;

   left_ = get_left_most_child(node);

   if (left_)
   {
      eval_context_var_decl_list(left_);

      right_ = get_left_most_sibling(left_);
      
      if (right_)
      {
         eval_stmt_list(right_);
      }
   }

   return 1;
}

void eval_func_def(ast function)
{
   int   x = set_ast_root_reference(function);

   symbol_value_type    val;

   memset(&val,0,sizeof(symbol_value_type));
   
   st_entry*   entry = NULL;
   
   val.ast_ref_index = x;
   
   entry = new_st_entry(_FUNCTION,function->ast_node_label,function->return_type,val);
   
   insert_st_entry(global_symbol_table,entry);
}

void eval_main_def(ast _main_)
{
   int   x = set_ast_root_reference(_main_);

   symbol_value_type val;
   
   st_entry*   entry = NULL;
   
   val.ast_ref_index = x;

   entry = new_st_entry(_FUNCTION,_main_->ast_node_label,_main_->return_type,val);
   
   insert_st_entry(global_symbol_table,entry);
}

int eval_return_stmt(ast stmt)
{
   ast   left_;

   returnable*    ret = NULL;

   // ar* cur_rec;
   left_ = get_left_most_child(stmt);
   
   if (left_)
   {
      ret = eval_exp(left_,RVAL);
   }
   else
   {
      ret->type = E_VOID;
      ret->eval._INT = 0;
   }

   CONTEXT_RETURN_VALUE = copy_returnable(ret);
   
   purge_returnable(ret);
   
   return 1;
}

int eval_break_stmt(ast stmt)
{
   if (CONTEXT_ENV & LOOP_ENV)
   {
      CONTEXT_ENV |= BREAK_ENV;
   }

   return 1;
}

int eval_continue_stmt(ast stmt)
{
   if (CONTEXT_ENV & LOOP_ENV)
   {
      CONTEXT_ENV |= CONTINUE_ENV;
   }

   return 1;
}

int eval_stmt_list(ast node)
{
   ast   left_;
   
   left_ = get_left_most_child(node);
 
   if (!left_)
   {
      return 1;
   }
   else
   {
      do
      {
         eval_stmt(left_);

         if (is_jmp_condition)
         {
            return 1;
         }

         left_ = get_left_most_sibling(left_);
      }

      while (left_);

      return 1;
   }
}

int eval_global_var_decl(ast global_decl)
{
   ast   temp;
   eval_var_decl(global_symbol_table,global_decl);
   temp = global_decl;
   purge_ast(temp);
   global_decl = NULL;
   return 1;
}

int eval_context_var_decl_list(ast context_decl)
{
   eval_var_decl_list(CONTEXT_SYMBOL_TABLE,context_decl);
   return 1;
}

int eval_var_decl_list(st* table,ast vtdl)
{
   ast   temp;

   if (!vtdl->tag == VAR_TYPE_DECL_LIST)
   {
      err_msg = "INTERNAL EXCEPTION: Variable declaration list expected.\n\n";
      err();
   }
   else
   {
      temp = get_left_most_child(vtdl);
      while (temp != NULL)
      {
         eval_var_decl(table,temp);
         temp = get_left_most_sibling(temp);
      }
   }
   return 1;
}

int eval_var_decl(st* table,ast variable)
{
   ast         var;
   ast         init;
   ast         type        = get_left_most_child(variable);
   data_type   t           = eval_type(type);
   ast         decl_list   = get_left_most_sibling(type);
   ast         temp        = get_left_most_child(decl_list);
   while (temp != NULL)
   {
      if (temp->tag == ASSIGNMENT)
      {
         var = get_left_most_child(temp);
         init = get_left_most_sibling(var);
      }
      else
      {
         var = temp;
         init = NULL;
      }
      decl_var(table,t,var);
      if (init != NULL)
      {
         init_var(table,var,init);
      }
      temp = get_left_most_sibling(temp);
   }
   return 1;
}

int decl_var(st* table,data_type type,ast var)
{
   st_entry*         entry;
   symbol_value_type sev;
   if (lookup_st_entry(table,var->ast_node_label) != NULL)
   {
      err_msg = "RUNTIME EXCEPTION: Variable already declared in this context.\n\n";
      err();
   }
   if (var->tag == ARRAY)
   {
      decl_arr(table,type,var);
   }
   else if (var->tag == ARRAY2)
   {
      decl_2arr(table,type,var);
   }
   else
   {
      sev.var_val = alloc_mem(type,1);
      entry = new_st_entry(_VARIABLE,var->ast_node_label,type,sev);
      insert_st_entry(table,entry);
   }
   return 1;
}

int decl_arr(st* table,data_type type,ast var)
{
   ast               offset;
   returnable*       ret;
   st_entry*         entry;
   symbol_value_type sev;
   if (!is_basic_type(type))
   {
      err_msg = "RUNTIME EXCEPTION: Arrays can only be of basic types.\n\n";
      err();
   }
   offset = get_left_most_child(var);
   if (offset == NULL)
   {
      err_msg = "RUNTIME EXCEPTION: Array size required.\n\n";
      err();
   }
   ret = eval_exp(offset,RVAL);
   if (!is_int_type(ret->type))
   {
      err_msg = "RUNTIME EXCEPTION: Array size should be an int.\n\n";
      err();
   }
   if (ret->eval._INT == 0)
   {
      err_msg = "RUNTIME EXCEPTION: Arrays can't have size less than 1.\n\n";
      err();
   }
   sev.var_val = alloc_mem(type,ret->eval._INT);
   entry = new_st_entry(_ARRAY,var->ast_node_label,type,sev);
   insert_st_entry(table,entry);
   purge_returnable(ret);
   return 1;
}

int decl_2arr(st* table,data_type type,ast var)
{
   // int i;
   ast               offset1;
   ast               offset2;
   returnable*       ret1;
   returnable*       ret2;
   st_entry*         entry;
   symbol_value_type sev;
   if (!is_basic_type(type))
   {
      err_msg = "RUNTIME EXCEPTION: Arrays can only be of basic types.\n\n";
      err();
   }
   offset1 = get_left_most_child(var);
   if (offset1 == NULL)
   {
      err_msg = "RUNTIME EXCEPTION: Array row size required.\n\n";
      err();
   }
   offset2 = get_left_most_sibling(offset1);
   if (offset2 == NULL)
   {
      err_msg = "RUNTIME EXCEPTION: Array column size required.\n\n";
      err();
   }
   ret1 = eval_exp(offset1,RVAL);
   ret2 = eval_exp(offset2,RVAL);
   if (!is_int_type(ret1->type) || !is_int_type(ret2->type))
   {
      err_msg = "RUNTIME EXCEPTION: Array row and column sizes should be an int.\n\n";
      err();
   }
   if (ret1->eval._INT == 0 || ret2->eval._INT == 0)
   {
      err_msg = "RUNTIME EXCEPTION: Arrays can't have row and column sizes less than 1.\n\n";
      err();
   }
   sev.var_val = alloc_mem_for_2arr(type,ret1->eval._INT,ret2->eval._INT);
   entry = new_st_entry(_2ARRAY,var->ast_node_label,type,sev);
   insert_st_entry(table,entry);
   purge_returnable(ret1);
   purge_returnable(ret2);
   return 1;
}

int init_var(st* table,ast var,ast init_exp)
{
   st_entry*   entry;
   returnable* ret;
   entry = lookup_st_entry(table,var->ast_node_label);
   if (entry == NULL)
   {
      err_msg = "INTERNAL EXCEPTION: Grave problem with symbol table.\n\n";
      err();
   }
   if (entry->symbol_entry_tag == _ARRAY)
   {
      init_arr(entry,var,init_exp);
   }
   else if (entry->symbol_entry_tag == _2ARRAY)
   {
      init_2arr(entry,var,init_exp);
   }
   else
   {
      if (init_exp->tag == INIT_LIST)
      {
         err_msg = "RUNTIME EXCEPTION: Initializing value can't be a list.\n\n";
         err();
      }
      ret = eval_exp(init_exp,RVAL);
      if (!is_compatible(entry->symbol_entry_type,ret->type))
      {
         err_msg = "RUNTIME EXCEPTION: Incompatible type used for initialization.\n\n";
         err();
      }
      set_init_value(entry,0,ret);
      purge_returnable(ret);
   }
   return 1;
}

int init_arr(st_entry* entry,ast var,ast init_list)
{
   int         i;
   ast         temp;
   ast         offset;
   returnable* ret;
   returnable* ret1;
   if (init_list->tag != INIT_LIST)
   {
      err_msg = "RUNTIME EXCEPTION: Initializing value needs to be a list.\n\n";
      err();
   }
   temp = get_left_most_child(init_list);
   offset = get_left_most_child(var);
   ret1 = eval_exp(offset,RVAL);
   for (i = 0; i < ret1->eval._INT && temp != NULL; i++)
   {
      if (temp->tag == INIT_LIST)
      {
         err_msg = "RUNTIME EXCEPTION: Initializing value for individual array element can't be a list.\n\n";
         err();
      }
      ret = eval_exp(temp,RVAL);
      if (!is_compatible(entry->symbol_entry_type,ret->type))
      {
         err_msg = "RUNTIME EXCEPTION: Incompatible type used for initialization.\n\n";
         err();
      }
      set_init_value(entry,i,ret);
      purge_returnable(ret);
      temp = get_left_most_sibling(temp);
   }
   /*if(i < ret1->eval._INT || temp != NULL) {
   err_msg = "RUNTIME EXCEPTION: Invalid number of initialization values.\n\n";
   err();
   }*/
   purge_returnable(ret1);
   return 1;
}

int init_2arr(st_entry* entry,ast var,ast init_init_list)
{
   int         i, j;
   ast         outer;
   ast         inner;
   ast         offset1;
   ast         offset2;
   // ast init_list;
   returnable* ret;
   returnable* ret1;
   returnable* ret2;
   if (init_init_list->tag != INIT_LIST)
   {
      err_msg = "RUNTIME EXCEPTION: Initializing value needs to be a list.\n\n";
      err();
   }
   offset1 = get_left_most_child(var);
   offset2 = get_left_most_sibling(offset1);
   ret1 = eval_exp(offset1,RVAL);
   ret2 = eval_exp(offset2,RVAL);
   outer = get_left_most_child(init_init_list);
   for (i = 0; i < ret1->eval._INT || outer != NULL; i++)
   {
      if (outer->tag != INIT_LIST)
      {
         err_msg = "RUNTIME EXCEPTION: Initializing value for each row of a 2d array needs to be a list.\n\n";
         err();
      }
      inner = get_left_most_child(outer);
      for (j = 0; j < ret2->eval._INT && inner != NULL; j++)
      {
         if (inner->tag == INIT_LIST)
         {
            err_msg = "RUNTIME EXCEPTION: Initializing value for individual elements of a 2d array can't be a list.\n\n";
            err();
         }
         ret = eval_exp(inner,RVAL);
         if (!is_compatible(entry->symbol_entry_type,ret->type))
         {
            err_msg = "RUNTIME EXCEPTION: Incompatible type used for initialization.\n\n";
            err();
         }
         set_2arr_init_value(entry,i,j,ret);
         purge_returnable(ret);
         inner = get_left_most_sibling(inner);
      }
      /*if(j < ret2->eval._INT || inner != NULL) {
      err_msg = "RUNTIME EXCEPTION: Invalid number of initialization values.\n\n";
      err();
      }*/
      outer = get_left_most_sibling(outer);
   }
   /*if(i < ret1->eval._INT || outer != NULL) {
   err_msg = "RUNTIME EXCEPTION: Invalid number of initialization values.\n\n";
   err();
   }*/
   purge_returnable(ret1);
   purge_returnable(ret2);
   return 1;
}

