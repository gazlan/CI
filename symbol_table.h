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


Symbol table and activation record data structures. For more information, check
symbol_table.c.


@author Ashwin Jha<ajha.dev@gmail.com>

*****************************************************************************************************/

#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include "interpreter.h"

#define LOOP_ENV 1
#define BREAK_ENV 2
#define CONTINUE_ENV 4

#define CONTEXT_SYMBOL_TABLE ((peek_ar())->table)
#define CONTEXT_ENV ((peek_ar())->env)
#define CONTEXT_RETURN_VALUE ((peek_ar())->return_value)

typedef enum symbol_table_entry_token_tag
{
   _VARIABLE,
   _ARRAY,
   _2ARRAY,
   _FUNCTION
}   symbol_token_tag;

typedef union
{
   value var_val;
   int   ast_ref_index;
} symbol_value_type;

typedef struct symbol_table_entry
{
   symbol_token_tag           symbol_entry_tag;
   char*                      symbol_entry_label;
   data_type                  symbol_entry_type;
   symbol_value_type          symbol_entry_value;
   struct symbol_table_entry* next;
} st_entry;

typedef struct symbol_table
{
   char*          symbol_table_id;
   st_entry*      entry[SYMBOL_TABLE_HASH_SIZE];
} st;

typedef struct activation_record
{
   st*                        table;
   returnable*                return_value;
   char                       env;
   struct activation_record*  next;
} ar;

extern st*                 global_symbol_table;

extern st*                 context_symbol_table;

extern ar*                 activation_record_stack;

st_entry*                  new_st_entry(symbol_token_tag stt,char* l,data_type set,symbol_value_type sev);
void                       purge_st_entry(st_entry* te);
st*                        new_st(char* id);
void                       purge_st(st* t);
void                       purge_st_entries(st* t);
void                       insert_st_entry(st* table,st_entry* te);
st_entry*                  lookup_st_entry(st* table,char* id);
ar*                        new_ar(char* block_id);
void                       purge_ar(ar* a);
void                       push_ar(ar* a);
ar*                        pop_ar();
ar*                        peek_ar();
void                       clear_ar_stack();

#endif
