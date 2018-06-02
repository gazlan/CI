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


AST evaluator functions declaration. For more information, check ast_evaluator.c.


@author Ashwin Jha<ajha.dev@gmail.com>
@contributor Durgesh Singh<durgesh.ccet@gmail.com>

*****************************************************************************************************/

#ifndef _AST_EVALUATOR_H_
#define _AST_EVALUATOR_H_

#include "interpreter.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>

returnable* eval_constant(ast const_node);
data_type   eval_type(ast type_node);
returnable* eval_var_rval(ast var_node);
returnable* eval_arr_rval(ast arr_node);
returnable* eval_var_lval(ast var_node);
returnable* eval_arr_lval(ast arr_node);
returnable* eval_func_call(ast node);
returnable* exec_lib_func(char* func,returnable* param_list);
returnable* eval_param_list(ast param_list);
returnable* eval_exp(ast exp_node,int mode);
returnable* eval_exp_list(ast node);
returnable* eval_assign_exp(ast node);
returnable* eval_pre_inc_dec_exp(ast pre_node);
returnable* eval_post_inc_dec_exp(ast post_node);
returnable* eval_cast_exp(ast node);
returnable* eval_arithmetic_exp(ast node);
returnable* eval_shift_exp(ast node);
returnable* eval_rel_exp(ast node);
returnable* eval_bitwise_exp(ast node);
returnable* eval_logical_exp(ast node);
returnable* eval_conditional_exp(ast node);
returnable* eval_unary_minus_exp(ast node);
returnable* eval_deref_exp(ast node,int mode);
returnable* eval_ref_exp(ast node);
int         eval_stmt(ast stmt_node);
int         eval_exp_stmt(ast stmt_node);
int         eval_for_stmt(ast node);
int         eval_while_stmt(ast node);
int         eval_if_stmt(ast node);
int         eval_block_stmt(ast node);
void        eval_func_def(ast function);
void        eval_main_def(ast _main_);
int         eval_return_stmt(ast stmt);
int         eval_break_stmt(ast stmt);
int         eval_continue_stmt(ast stmt);
int         eval_stmt_list(ast node);
int         exec_func(ast node,returnable* params);
int         eval_global_var_decl_list(ast global_decl);
int         eval_context_var_decl_list(ast context_decl);
int         eval_var_decl_list(st* table,ast vtdl);
int         eval_var_decl(st* table,ast variable);
int         decl_var(st* table,data_type type,ast var);
int         decl_arr(st* table,data_type type,ast var);
int         decl_2arr(st* table,data_type type,ast var);
int         init_var(st* table,ast var,ast init_exp);
int         init_arr(st_entry* entry,ast var,ast init_list);
int         init_2arr(st_entry* entry,ast var,ast init_init_list);

#endif
