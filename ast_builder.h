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


AST builder functions declaration. For more information, check ast_builder.c.


@author Ashwin Jha<ajha.dev@gmail.com>
@contributor Durgesh Singh<durgesh.ccet@gmail.com>

*****************************************************************************************************/

#ifndef _AST_BUILDER_H_
#define _AST_BUILDER_H_

#include "abstract_syntax_tree.h"

ast   new_constant_node(char* l,data_type rt);
ast   new_type_node(char* l,data_type rt);
ast   new_variable_node(char* l,data_type rt);
ast   new_array_variable_node(char* id,ast offset1,ast offset2,data_type rt);
ast   new_inc_exp_node(ast_node_tag tag,ast exp);
ast   new_dec_exp_node(ast_node_tag tag,ast exp);
ast   new_unary_exp_node(char op,ast exp);
ast   new_ref_exp_node(ast exp);
ast   new_deref_exp_node(ast exp);
ast   new_unary_plus_exp_node(ast exp);
ast   new_unary_minus_exp_node(ast exp);
ast   new_complement_exp_node(ast exp);
ast   new_not_exp_node(ast exp);
ast   new_cast_node(ast type,ast expression);
ast   new_mul_exp_node(ast left,ast_node_tag tag,ast right);
ast   new_add_exp_node(ast left,ast_node_tag tag,ast right);
ast   new_shift_exp_node(ast left,ast_node_tag tag,ast right);
ast   new_rel_exp_node(ast left,ast_node_tag tag,ast right);
ast   new_logic_exp_node(ast left,ast_node_tag tag,ast right);
ast   new_bit_exp_node(ast left,ast_node_tag tag,ast right);
ast   new_cond_exp_node(ast condition,ast true_case,ast false_case);
ast   new_assign_exp_node(ast lval,assignment_code code,ast rval);
ast   new_exp_list_node(ast exp_node);
ast   append_exp_list_node(ast exp_list,ast exp_node);
ast   new_init_list_node(ast init_node);
ast   append_init_list_node(ast init_list,ast init_node);
ast   new_var_decl_list_node(ast var_node);
ast   append_var_decl_list_node(ast var_decl_list,ast var_node);
ast   new_decl_node(ast type,ast var_decl_list);
ast   new_var_type_decl_list_node(ast decl_node);
ast   append_var_type_decl_list_node(ast var_type_decl_list,ast decl_node);
ast   new_stmt_list_node(ast stmt_node);
ast   append_stmt_list_node(ast stmt_list,ast stmt_node);
ast   new_exp_stmt_node(ast exp_node);
ast   new_if_stmt_node(ast condition,ast if_case,ast else_case);
ast   new_while_stmt_node(ast condition,ast stmt);
ast   new_for_stmt_node(ast init_node,ast condition,ast inc_exp_node,ast stmt);
ast   new_return_stmt_node(ast return_value);
ast   new_break_stmt_node();
ast   new_continue_stmt_node();
ast   new_compound_stmt_node(ast var_type_decl_list_node,ast stmt_list_node);
ast   new_param_node(ast type,char* id);
ast   new_param_list_node(ast param_node);
ast   append_param_list_node(ast param_list,ast param_node);
ast   new_func_def_node(ast type,char* id,ast param_list,ast compound_stmt);
ast   new_func_call_node(char* id,ast arg_param_list);
ast   new_printf_call_node(ast arg_param_list);
ast   new_scanf_call_node(ast arg_param_list);
ast   new_arg_exp_list_node(ast arg_exp_node);
ast   append_arg_exp_list_node(ast arg_exp_list,ast arg_exp_node);
ast   new_trans_unit_list_node(ast global_decl);
ast   append_trans_unit_list_node(ast trans_unit_list,ast global_decl);
ast   new_main_def_node(ast compound_stmt);
ast   new_script_def_node(ast trans_unit,ast main_def);

# endif
