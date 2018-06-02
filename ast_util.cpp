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


This is a helper module for ast_evaluator.c. It handles the type specific tasks and
other utility tasks. in general this file requires a lot of changes. we were in a
hurry to complete our project and so we gave preference to correct and stable
implementation over aesthetics.

TODO AND FIXME list:
1. a common function (with value as the common link maybe) for all conversion
functions.
2. comments...lots of them...definitely. ;)


@author Ashwin Jha<ajha.dev@gmail.com>
@contributor Durgesh Singh<durgesh.ccet@gmail.com>

*****************************************************************************************************/

#include "interpreter.h"
#include "abstract_syntax_tree.h"
#include "ast_util.h"
#include "symbol_table.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

data_type ptob(data_type type)
{
   switch (type)
   {
      case E_VOID_PTR:
         return E_VOID;
      case E_CHAR_PTR:
         return E_CHAR;
      case E_SHORT_PTR:
         return E_SHORT;
      case E_INT_PTR:
         return E_INT;
      case E_LONG_PTR:
         return E_LONG;
      case E_FLOAT_PTR:
         return E_FLOAT;
      case E_DOUBLE_PTR:
         return E_DOUBLE;
      case E_VOID_2PTR:
         return E_VOID_PTR;
      case E_CHAR_2PTR:
         return E_CHAR_PTR;
      case E_SHORT_2PTR:
         return E_SHORT_PTR;
      case E_INT_2PTR:
         return E_INT_PTR;
      case E_LONG_2PTR:
         return E_LONG_PTR;
      case E_FLOAT_2PTR:
         return E_FLOAT_PTR;
      case E_DOUBLE_2PTR:
         return E_DOUBLE_PTR;
      case E_VOID_3PTR:
         return E_VOID_2PTR;
      case E_CHAR_3PTR:
         return E_CHAR_2PTR;
      case E_SHORT_3PTR:
         return E_SHORT_2PTR;
      case E_INT_3PTR:
         return E_INT_2PTR;
      case E_LONG_3PTR:
         return E_LONG_2PTR;
      case E_FLOAT_3PTR:
         return E_FLOAT_2PTR;
      case E_DOUBLE_3PTR:
         return E_DOUBLE_2PTR;
   }

   return (data_type) 0;
}

data_type btop(data_type type)
{
   switch (type)
   {
      case E_VOID:
         return E_VOID_PTR;
      case E_CHAR:
         return E_CHAR_PTR;
      case E_SHORT:
         return E_SHORT_PTR;
      case E_INT:
         return E_INT_PTR;
      case E_LONG:
         return E_LONG_PTR;
      case E_FLOAT:
         return E_FLOAT_PTR;
      case E_DOUBLE:
         return E_DOUBLE_PTR;
      case E_VOID_PTR:
         return E_VOID_2PTR;
      case E_CHAR_PTR:
         return E_CHAR_2PTR;
      case E_SHORT_PTR:
         return E_SHORT_2PTR;
      case E_INT_PTR:
         return E_INT_2PTR;
      case E_LONG_PTR:
         return E_LONG_2PTR;
      case E_FLOAT_PTR:
         return E_FLOAT_2PTR;
      case E_DOUBLE_PTR:
         return E_DOUBLE_2PTR;
      case E_VOID_2PTR:
         return E_VOID_3PTR;
      case E_CHAR_2PTR:
         return E_CHAR_3PTR;
      case E_SHORT_2PTR:
         return E_SHORT_3PTR;
      case E_INT_2PTR:
         return E_INT_3PTR;
      case E_LONG_2PTR:
         return E_LONG_3PTR;
      case E_FLOAT_2PTR:
         return E_FLOAT_3PTR;
      case E_DOUBLE_2PTR:
         return E_DOUBLE_3PTR;
   }

   return (data_type) 0;
}

data_type get_effective_type(data_type left_type,data_type right_type)
{
   if (left_type >= right_type)
   {
      return left_type;
   }
   else
   {
      return right_type;
   }
}

value get_const(data_type type,char* str)
{
   char* dup;
   value val;

   memset(&val,0,sizeof(value));

   switch (type)
   {
      case E_CHAR:
         val._CHAR = get_char(str);
         return val;
      case E_SHORT:
         val._SHORT = (short) atoi(str);
         return val;
      case E_INT:
         val._INT = atoi(str);
         return val;
      case E_LONG:
         val._LONG = atol(str);
         return val;
      case E_FLOAT:
         val._FLOAT = (float) atof(str);
         return val;
      case E_DOUBLE:
         val._DOUBLE = atof(str);
         return val;
      case E_CHAR_PTR:
         dup = get_unquoted_string(str);
         val._CHAR_PTR = dup;
         return val;
   }

   return val;
}

returnable* get_type_cast_val(data_type type,returnable* right)
{
   returnable* ret   = new_returnable();
   ret->type = type;
   switch (type)
   {
      case E_CHAR:
         if (!is_basic_type(right->type))
         {
            err_msg = "RUNTIME EXCEPTION: Pointer type value not expected.\n\n";
            err();
         }
         else
         {
            ret->eval._CHAR = (char) DOUBLE_VALUE(right);
         }
         return ret;
      case E_SHORT:
         if (!is_basic_type(right->type))
         {
            err_msg = "RUNTIME EXCEPTION: Pointer type value not expected.\n\n";
            err();
         }
         else
         {
            ret->eval._SHORT = (short) DOUBLE_VALUE(right);
         }
         return ret;
      case E_INT:
         if (!is_basic_type(right->type))
         {
            err_msg = "RUNTIME EXCEPTION: Pointer type value not expected.\n\n";
            err();
         }
         else
         {
            ret->eval._INT = (int)DOUBLE_VALUE(right);
         }
         return ret;
      case E_LONG:
         if (is_basic_type(right->type))
         {
            ret->eval._LONG = (long)DOUBLE_VALUE(right);
         }
         else if (is_1pointer_type(right->type))
         {
            ret->eval._LONG = (long)DOUBLE_PTR_VALUE(right);
         }
         else if (is_2pointer_type(right->type))
         {
            ret->eval._LONG = (long)DOUBLE_2PTR_VALUE(right);
         }
         return ret;
      case E_FLOAT:
         if (!is_basic_type(right->type))
         {
            err_msg = "RUNTIME EXCEPTION: Pointer type value not expected.\n\n";
            err();
         }
         else
         {
            ret->eval._FLOAT = (float) DOUBLE_VALUE(right);
         }
         return ret;
      case E_DOUBLE:
         if (!is_basic_type(right->type))
         {
            err_msg = "RUNTIME EXCEPTION: Pointer type value not expected.\n\n";
            err();
         }
         else
         {
            ret->eval._DOUBLE = (double) DOUBLE_VALUE(right);
         }
         return ret;
      default:
         err_msg = "RUNTIME EXCEPTION: Type cast is available for basic types only.\n\n";
         err();
   }

   return 0;
}

returnable* get_lval_from_entry(st_entry* e,int offset,int is_arr)
{
   returnable* ret   = new_returnable();
   ret->eval = get_val_from_entry(e,LVAL,offset,is_arr);
   if (is_arr)
   {
      ret->type = e->symbol_entry_type;
   }
   else
   {
      ret->type = btop(e->symbol_entry_type);
   }
   return ret;
}

returnable* get_rval_from_entry(st_entry* e,int offset,int is_arr)
{
   returnable* ret   = new_returnable();
   ret->eval = get_val_from_entry(e,RVAL,offset,is_arr);
   if (is_arr)
   {
      ret->type = ptob(e->symbol_entry_type);
   }
   else
   {
      ret->type = e->symbol_entry_type;
   }
   return ret;
}

returnable* get_2arr_lval_from_entry(st_entry* e,int row,int col,int is_ptr)
{
   returnable* ret   = new_returnable();
   ret->eval = get_2arr_val_from_entry(e,LVAL,row,col,is_ptr);
   if (is_ptr)
   {
      if (is_2pointer_type(e->symbol_entry_type))
      {
         ret->type = ptob(e->symbol_entry_type);
      }
      else
      {
         ret->type = btop(e->symbol_entry_type);
      }
   }
   else
   {
      ret->type = btop(btop(e->symbol_entry_type));
   }
   return ret;
}

returnable* get_2arr_rval_from_entry(st_entry* e,int row,int col,int is_ptr)
{
   returnable* ret   = new_returnable();
   ret->eval = get_2arr_val_from_entry(e,RVAL,row,col,is_ptr);
   if (is_2pointer_type(e->symbol_entry_type))
   {
      ret->type = ptob(ptob(e->symbol_entry_type));
   }
   else
   {
      ret->type = e->symbol_entry_type;
   }
   return ret;
}

returnable* get_lval_from_returnable(returnable* r,int offset)
{
   returnable* ret   = new_returnable();
   ret->eval = get_val_from_returnable(r,LVAL,offset);
   ret->type = r->type;
   return ret;
}

returnable* get_rval_from_returnable(returnable* r,int offset)
{
   returnable* ret   = new_returnable();
   ret->eval = get_val_from_returnable(r,RVAL,offset);
   ret->type = ptob(r->type);
   return ret;
}

value get_val_from_entry(st_entry* entry,int mode,int offset,int is_arr)
{
   value val;

   memset(&val,0,sizeof(value));

   switch (entry->symbol_entry_type)
   {
      case E_VOID:
         if (mode)
         {
            val._VOID_PTR = NULL;
         }
         else
         {
            val._INT = 0;
         }
         return val;
      case E_CHAR:
         if (mode)
         {
            val._CHAR_PTR = entry->symbol_entry_value.var_val._CHAR_PTR + offset;
         }
         else
         {
            val._CHAR = *(entry->symbol_entry_value.var_val._CHAR_PTR + offset);
         }
         return val;
      case E_SHORT:
         if (mode)
         {
            val._SHORT_PTR = entry->symbol_entry_value.var_val._SHORT_PTR + offset;
         }
         else
         {
            val._SHORT = *(entry->symbol_entry_value.var_val._SHORT_PTR + offset);
         }
         return val;
      case E_INT:
         if (mode)
         {
            val._INT_PTR = entry->symbol_entry_value.var_val._INT_PTR + offset;
         }
         else
         {
            val._INT = *(entry->symbol_entry_value.var_val._INT_PTR + offset);
         }
         return val;
      case E_LONG:
         if (mode)
         {
            val._LONG_PTR = entry->symbol_entry_value.var_val._LONG_PTR + offset;
         }
         else
         {
            val._LONG = *(entry->symbol_entry_value.var_val._LONG_PTR + offset);
         }
         return val;
      case E_FLOAT:
         if (mode)
         {
            val._FLOAT_PTR = entry->symbol_entry_value.var_val._FLOAT_PTR + offset;
         }
         else
         {
            val._FLOAT = *(entry->symbol_entry_value.var_val._FLOAT_PTR + offset);
         }
         return val;
      case E_DOUBLE:
         if (mode)
         {
            val._DOUBLE_PTR = entry->symbol_entry_value.var_val._DOUBLE_PTR + offset;
         }
         else
         {
            val._DOUBLE = *(entry->symbol_entry_value.var_val._DOUBLE_PTR + offset);
         }
         return val;
      case E_VOID_PTR:
         if (mode)
         {
            val._VOID_2PTR = entry->symbol_entry_value.var_val._VOID_2PTR + offset;
         }
         else
         {
            val._VOID_PTR = (char *) (*entry->symbol_entry_value.var_val._VOID_2PTR) + offset;
         }
         return val;
      case E_CHAR_PTR:
         if (is_arr)
         {
            val._CHAR = *(*entry->symbol_entry_value.var_val._CHAR_2PTR + offset);
         }
         else if (mode)
         {
            val._CHAR_2PTR = entry->symbol_entry_value.var_val._CHAR_2PTR + offset;
         }
         else
         {
            val._CHAR_PTR = *entry->symbol_entry_value.var_val._CHAR_2PTR + offset;
         }
         return val;
      case E_SHORT_PTR:
         if (is_arr)
         {
            val._SHORT = *(*entry->symbol_entry_value.var_val._SHORT_2PTR + offset);
         }
         else if (mode)
         {
            val._SHORT_2PTR = entry->symbol_entry_value.var_val._SHORT_2PTR + offset;
         }
         else
         {
            val._SHORT_PTR = *entry->symbol_entry_value.var_val._SHORT_2PTR + offset;
         }
         return val;
      case E_INT_PTR:
         if (is_arr)
         {
            val._INT = *(*entry->symbol_entry_value.var_val._INT_2PTR + offset);
         }
         else if (mode)
         {
            val._INT_2PTR = entry->symbol_entry_value.var_val._INT_2PTR + offset;
         }
         else
         {
            val._INT_PTR = *entry->symbol_entry_value.var_val._INT_2PTR + offset;
         }
         return val;
      case E_LONG_PTR:
         if (is_arr)
         {
            val._LONG = *(*entry->symbol_entry_value.var_val._LONG_2PTR + offset);
         }
         else if (mode)
         {
            val._LONG_2PTR = entry->symbol_entry_value.var_val._LONG_2PTR + offset;
         }
         else
         {
            val._LONG_PTR = *entry->symbol_entry_value.var_val._LONG_2PTR + offset;
         }
         return val;
      case E_FLOAT_PTR:
         if (is_arr)
         {
            val._FLOAT = *(*entry->symbol_entry_value.var_val._FLOAT_2PTR + offset);
         }
         else if (mode)
         {
            val._FLOAT_2PTR = entry->symbol_entry_value.var_val._FLOAT_2PTR + offset;
         }
         else
         {
            val._FLOAT_PTR = *entry->symbol_entry_value.var_val._FLOAT_2PTR + offset;
         }
         return val;
      case E_DOUBLE_PTR:
         if (is_arr)
         {
            val._DOUBLE = *(*entry->symbol_entry_value.var_val._DOUBLE_2PTR + offset);
         }
         else if (mode)
         {
            val._DOUBLE_2PTR = entry->symbol_entry_value.var_val._DOUBLE_2PTR + offset;
         }
         else
         {
            val._DOUBLE_PTR = *entry->symbol_entry_value.var_val._DOUBLE_2PTR + offset;
         }
         return val;
      case E_VOID_2PTR:
         if (mode)
         {
            val._VOID_3PTR = entry->symbol_entry_value.var_val._VOID_3PTR + offset;
         }
         else
         {
            val._VOID_2PTR = *entry->symbol_entry_value.var_val._VOID_3PTR + offset;
         }
         return val;
      case E_CHAR_2PTR:
         if (is_arr)
         {
            val._CHAR_PTR = *(*entry->symbol_entry_value.var_val._CHAR_3PTR + offset);
         }
         else if (mode)
         {
            val._CHAR_3PTR = entry->symbol_entry_value.var_val._CHAR_3PTR + offset;
         }
         else
         {
            val._CHAR_2PTR = *entry->symbol_entry_value.var_val._CHAR_3PTR + offset;
         }
         return val;
      case E_SHORT_2PTR:
         if (is_arr)
         {
            val._SHORT_PTR = *(*entry->symbol_entry_value.var_val._SHORT_3PTR + offset);
         }
         else if (mode)
         {
            val._SHORT_3PTR = entry->symbol_entry_value.var_val._SHORT_3PTR + offset;
         }
         else
         {
            val._SHORT_2PTR = *entry->symbol_entry_value.var_val._SHORT_3PTR + offset;
         }
         return val;
      case E_INT_2PTR:
         if (is_arr)
         {
            val._INT_PTR = *(*entry->symbol_entry_value.var_val._INT_3PTR + offset);
         }
         else if (mode)
         {
            val._INT_3PTR = entry->symbol_entry_value.var_val._INT_3PTR + offset;
         }
         else
         {
            val._INT_2PTR = *entry->symbol_entry_value.var_val._INT_3PTR + offset;
         }
         return val;
      case E_LONG_2PTR:
         if (is_arr)
         {
            val._LONG_PTR = *(*entry->symbol_entry_value.var_val._LONG_3PTR + offset);
         }
         else if (mode)
         {
            val._LONG_3PTR = entry->symbol_entry_value.var_val._LONG_3PTR + offset;
         }
         else
         {
            val._LONG_2PTR = *entry->symbol_entry_value.var_val._LONG_3PTR + offset;
         }
         return val;
      case E_FLOAT_2PTR:
         if (is_arr)
         {
            val._FLOAT_PTR = *(*entry->symbol_entry_value.var_val._FLOAT_3PTR + offset);
         }
         else if (mode)
         {
            val._FLOAT_3PTR = entry->symbol_entry_value.var_val._FLOAT_3PTR + offset;
         }
         else
         {
            val._FLOAT_2PTR = *entry->symbol_entry_value.var_val._FLOAT_3PTR + offset;
         }
         return val;
      case E_DOUBLE_2PTR:
         if (is_arr)
         {
            val._DOUBLE_PTR = *(*entry->symbol_entry_value.var_val._DOUBLE_3PTR + offset);
         }
         else if (mode)
         {
            val._DOUBLE_3PTR = entry->symbol_entry_value.var_val._DOUBLE_3PTR + offset;
         }
         else
         {
            val._DOUBLE_2PTR = *entry->symbol_entry_value.var_val._DOUBLE_3PTR + offset;
         }
         return val;
      default:
         err_msg = "INTERNAL EXCEPTION: Invalid type operation.\n\n";
         err();
   }

   return val;
}

value get_2arr_val_from_entry(st_entry* entry,int mode,int row,int col,int is_ptr)
{
   value val;

   memset(&val,0,sizeof(value));

   switch (entry->symbol_entry_type)
   {
      case E_VOID:
         if (mode)
         {
            val._VOID_PTR = NULL;
         }
         else
         {
            val._INT = 0;
         }
         return val;
      case E_CHAR:
         if (is_ptr)
         {
            val._CHAR_PTR = *(entry->symbol_entry_value.var_val._CHAR_2PTR + row) + col;
         }
         else if (mode)
         {
            val._CHAR_2PTR = entry->symbol_entry_value.var_val._CHAR_2PTR + row;
         }
         else
         {
            val._CHAR = *(*(entry->symbol_entry_value.var_val._CHAR_2PTR + row) + col);
         }
         return val;
      case E_SHORT:
         if (is_ptr)
         {
            val._SHORT_PTR = *(entry->symbol_entry_value.var_val._SHORT_2PTR + row) + col;
         }
         else if (mode)
         {
            val._SHORT_2PTR = entry->symbol_entry_value.var_val._SHORT_2PTR + row;
         }
         else
         {
            val._SHORT = *(*(entry->symbol_entry_value.var_val._SHORT_2PTR + row) + col);
         }
         return val;
      case E_INT:
         if (is_ptr)
         {
            val._INT_PTR = *(entry->symbol_entry_value.var_val._INT_2PTR + row) + col;
         }
         else if (mode)
         {
            val._INT_2PTR = entry->symbol_entry_value.var_val._INT_2PTR + row;
         }
         else
         {
            val._INT = *(*(entry->symbol_entry_value.var_val._INT_2PTR + row) + col);
         }
         return val;
      case E_LONG:
         if (is_ptr)
         {
            val._LONG_PTR = *(entry->symbol_entry_value.var_val._LONG_2PTR + row) + col;
         }
         else if (mode)
         {
            val._LONG_2PTR = entry->symbol_entry_value.var_val._LONG_2PTR + row;
         }
         else
         {
            val._LONG = *(*(entry->symbol_entry_value.var_val._LONG_2PTR + row) + col);
         }
         return val;
      case E_FLOAT:
         if (is_ptr)
         {
            val._FLOAT_PTR = *(entry->symbol_entry_value.var_val._FLOAT_2PTR + row) + col;
         }
         else if (mode)
         {
            val._FLOAT_2PTR = entry->symbol_entry_value.var_val._FLOAT_2PTR + row;
         }
         else
         {
            val._FLOAT = *(*(entry->symbol_entry_value.var_val._FLOAT_2PTR + row) + col);
         }
         return val;
      case E_DOUBLE:
         if (is_ptr)
         {
            val._DOUBLE_PTR = *(entry->symbol_entry_value.var_val._DOUBLE_2PTR + row) + col;
         }
         else if (mode)
         {
            val._DOUBLE_2PTR = entry->symbol_entry_value.var_val._DOUBLE_2PTR + row;
         }
         else
         {
            val._DOUBLE = *(*(entry->symbol_entry_value.var_val._DOUBLE_2PTR + row) + col);
         }
         return val;
      case E_CHAR_2PTR:
         if (is_ptr)
         {
            val._CHAR_PTR = *(*entry->symbol_entry_value.var_val._CHAR_3PTR + row) + col;
         }
         else if (mode)
         {
            val._CHAR_2PTR = *entry->symbol_entry_value.var_val._CHAR_3PTR + row;
         }
         else
         {
            val._CHAR = *(*(*entry->symbol_entry_value.var_val._CHAR_3PTR + row) + col);
         }
         return val;
      case E_SHORT_2PTR:
         if (is_ptr)
         {
            val._SHORT_PTR = *(*entry->symbol_entry_value.var_val._SHORT_3PTR + row) + col;
         }
         else if (mode)
         {
            val._SHORT_2PTR = *entry->symbol_entry_value.var_val._SHORT_3PTR + row;
         }
         else
         {
            val._SHORT = *(*(*entry->symbol_entry_value.var_val._SHORT_3PTR + row) + col);
         }
         return val;
      case E_INT_2PTR:
         if (is_ptr)
         {
            val._INT_PTR = *(*entry->symbol_entry_value.var_val._INT_3PTR + row) + col;
         }
         else if (mode)
         {
            val._INT_2PTR = *entry->symbol_entry_value.var_val._INT_3PTR + row;
         }
         else
         {
            val._INT = *(*(*entry->symbol_entry_value.var_val._INT_3PTR + row) + col);
         }
         return val;
      case E_LONG_2PTR:
         if (is_ptr)
         {
            val._LONG_PTR = *(*entry->symbol_entry_value.var_val._LONG_3PTR + row) + col;
         }
         else if (mode)
         {
            val._LONG_2PTR = *entry->symbol_entry_value.var_val._LONG_3PTR + row;
         }
         else
         {
            val._LONG = *(*(*entry->symbol_entry_value.var_val._LONG_3PTR + row) + col);
         }
         return val;
      case E_FLOAT_2PTR:
         if (is_ptr)
         {
            val._FLOAT_PTR = *(*entry->symbol_entry_value.var_val._FLOAT_3PTR + row) + col;
         }
         else if (mode)
         {
            val._FLOAT_2PTR = *entry->symbol_entry_value.var_val._FLOAT_3PTR + row;
         }
         else
         {
            val._FLOAT = *(*(*entry->symbol_entry_value.var_val._FLOAT_3PTR + row) + col);
         }
         return val;
      case E_DOUBLE_2PTR:
         if (is_ptr)
         {
            val._DOUBLE_PTR = *(*entry->symbol_entry_value.var_val._DOUBLE_3PTR + row) + col;
         }
         else if (mode)
         {
            val._DOUBLE_2PTR = *entry->symbol_entry_value.var_val._DOUBLE_3PTR + row;
         }
         else
         {
            val._DOUBLE = *(*(*entry->symbol_entry_value.var_val._DOUBLE_3PTR + row) + col);
         }
         return val;
      default:
         err_msg = "INTERNAL EXCEPTION: Invalid type operation.\n\n";
         err();
   }

   return val;
}

value get_val_from_returnable(returnable* ret,int mode,int offset)
{
   value val;

   memset(&val,0,sizeof(value));

   switch (ret->type)
   {
      case E_VOID_PTR:
         if (mode)
         {
            val._VOID_PTR = NULL;
         }
         else
         {
            val._INT = 0;
         }
         return val;
      case E_CHAR_PTR:
         if (mode)
         {
            val._CHAR_PTR = ret->eval._CHAR_PTR + offset;
         }
         else
         {
            val._CHAR = *(ret->eval._CHAR_PTR + offset);
         }
         return val;
      case E_SHORT_PTR:
         if (mode)
         {
            val._SHORT_PTR = ret->eval._SHORT_PTR + offset;
         }
         else
         {
            val._SHORT = *(ret->eval._SHORT_PTR + offset);
         }
         return val;
      case E_INT_PTR:
         if (mode)
         {
            val._INT_PTR = ret->eval._INT_PTR + offset;
         }
         else
         {
            val._INT = *(ret->eval._INT_PTR + offset);
         }
         return val;
      case E_LONG_PTR:
         if (mode)
         {
            val._LONG_PTR = ret->eval._LONG_PTR + offset;
         }
         else
         {
            val._LONG = *(ret->eval._LONG_PTR + offset);
         }
         return val;
      case E_FLOAT_PTR:
         if (mode)
         {
            val._FLOAT_PTR = ret->eval._FLOAT_PTR + offset;
         }
         else
         {
            val._FLOAT = *(ret->eval._FLOAT_PTR + offset);
         }
         return val;
      case E_DOUBLE_PTR:
         if (mode)
         {
            val._DOUBLE_PTR = ret->eval._DOUBLE_PTR + offset;
         }
         else
         {
            val._DOUBLE = *(ret->eval._DOUBLE_PTR + offset);
         }
         return val;
      case E_VOID_2PTR:
         if (mode)
         {
            val._VOID_2PTR = ret->eval._VOID_2PTR + offset;
         }
         else
         {
            val._VOID_PTR = (char *) (*ret->eval._VOID_2PTR) + offset;
         }
         return val;
      case E_CHAR_2PTR:
         if (mode)
         {
            val._CHAR_2PTR = ret->eval._CHAR_2PTR + offset;
         }
         else
         {
            val._CHAR_PTR = *ret->eval._CHAR_2PTR + offset;
         }
         return val;
      case E_SHORT_2PTR:
         if (mode)
         {
            val._SHORT_2PTR = ret->eval._SHORT_2PTR + offset;
         }
         else
         {
            val._SHORT_PTR = *ret->eval._SHORT_2PTR + offset;
         }
         return val;
      case E_INT_2PTR:
         if (mode)
         {
            val._INT_2PTR = ret->eval._INT_2PTR + offset;
         }
         else
         {
            val._INT_PTR = *ret->eval._INT_2PTR + offset;
         }
         return val;
      case E_LONG_2PTR:
         if (mode)
         {
            val._LONG_2PTR = ret->eval._LONG_2PTR + offset;
         }
         else
         {
            val._LONG_PTR = *ret->eval._LONG_2PTR + offset;
         }
         return val;
      case E_FLOAT_2PTR:
         if (mode)
         {
            val._FLOAT_2PTR = ret->eval._FLOAT_2PTR + offset;
         }
         else
         {
            val._FLOAT_PTR = *ret->eval._FLOAT_2PTR + offset;
         }
         return val;
      case E_DOUBLE_2PTR:
         if (mode)
         {
            val._DOUBLE_2PTR = ret->eval._DOUBLE_2PTR + offset;
         }
         else
         {
            val._DOUBLE_PTR = *ret->eval._DOUBLE_2PTR + offset;
         }
         return val;
      default:
         err_msg = "INTERNAL EXCEPTION: Invalid type operation.\n\n";
         err();
   }

   return val;
}

returnable* get_assign_value(returnable* left,returnable* right)
{
   returnable* ret   = new_returnable();
   ret->type = ptob(left->type);
   switch (left->type)
   {
      case E_CHAR_PTR:
         *(left->eval._CHAR_PTR) = (char) DOUBLE_VALUE(right);
         ret->eval._CHAR = *(left->eval._CHAR_PTR);
         return ret;
      case E_SHORT_PTR:
         *(left->eval._SHORT_PTR) = (short) DOUBLE_VALUE(right);
         ret->eval._SHORT = *(left->eval._SHORT_PTR);
         return ret;
      case E_INT_PTR:
         *(left->eval._INT_PTR) = (int) DOUBLE_VALUE(right);
         ret->eval._INT = *(left->eval._INT_PTR);
         return ret;
      case E_LONG_PTR:
         *(left->eval._LONG_PTR) = (long) DOUBLE_VALUE(right);
         ret->eval._LONG = *(left->eval._LONG_PTR);
         return ret;
      case E_FLOAT_PTR:
         *(left->eval._FLOAT_PTR) = (float) DOUBLE_VALUE(right);
         ret->eval._FLOAT = *(left->eval._FLOAT_PTR);
         return ret;
      case E_DOUBLE_PTR:
         *(left->eval._DOUBLE_PTR) = (double) DOUBLE_VALUE(right);
         ret->eval._DOUBLE = *(left->eval._DOUBLE_PTR);
         return ret;
      case E_VOID_2PTR:
         *(left->eval._VOID_2PTR) = VOID_PTR_VALUE(right);
         ret->eval._VOID_PTR = *(left->eval._VOID_2PTR);
         return ret;
      case E_CHAR_2PTR:
         *(left->eval._CHAR_2PTR) = (char *) CHAR_PTR_VALUE(right);
         ret->eval._CHAR_PTR = *(left->eval._CHAR_2PTR);
         return ret;
      case E_SHORT_2PTR:
         *(left->eval._SHORT_2PTR) = (short *) SHORT_PTR_VALUE(right);
         ret->eval._SHORT_PTR = *(left->eval._SHORT_2PTR);
         return ret;
      case E_INT_2PTR:
         *(left->eval._INT_2PTR) = (int *) INT_PTR_VALUE(right);
         ret->eval._INT_PTR = *(left->eval._INT_2PTR);
         return ret;
      case E_LONG_2PTR:
         *(left->eval._LONG_2PTR) = (long *) LONG_PTR_VALUE(right);
         ret->eval._LONG_PTR = *(left->eval._LONG_2PTR);
         return ret;
      case E_FLOAT_2PTR:
         *(left->eval._FLOAT_2PTR) = (float *) FLOAT_PTR_VALUE(right);
         ret->eval._FLOAT_PTR = *(left->eval._FLOAT_2PTR);
         return ret;
      case E_DOUBLE_2PTR:
         *(left->eval._DOUBLE_2PTR) = (double *) DOUBLE_PTR_VALUE(right);
         ret->eval._DOUBLE_PTR = *(left->eval._DOUBLE_2PTR);
         return ret;
      case E_VOID_3PTR:
         *(left->eval._VOID_3PTR) = VOID_2PTR_VALUE(right);
         ret->eval._VOID_2PTR = *(left->eval._VOID_3PTR);
         return ret;
      case E_CHAR_3PTR:
         *(left->eval._CHAR_3PTR) = CHAR_2PTR_VALUE(right);
         ret->eval._CHAR_2PTR = *(left->eval._CHAR_3PTR);
         return ret;
      case E_SHORT_3PTR:
         *(left->eval._SHORT_3PTR) = SHORT_2PTR_VALUE(right);
         ret->eval._SHORT_2PTR = *(left->eval._SHORT_3PTR);
         return ret;
      case E_INT_3PTR:
         *(left->eval._INT_3PTR) = INT_2PTR_VALUE(right);
         ret->eval._INT_2PTR = *(left->eval._INT_3PTR);
         return ret;
      case E_LONG_3PTR:
         *(left->eval._LONG_3PTR) = LONG_2PTR_VALUE(right);
         ret->eval._LONG_2PTR = *(left->eval._LONG_3PTR);
         return ret;
      case E_FLOAT_3PTR:
         *(left->eval._FLOAT_3PTR) = FLOAT_2PTR_VALUE(right);
         ret->eval._FLOAT_2PTR = *(left->eval._FLOAT_3PTR);
         return ret;
      case E_DOUBLE_3PTR:
         *(left->eval._DOUBLE_3PTR) = DOUBLE_2PTR_VALUE(right);
         ret->eval._DOUBLE_2PTR = *(left->eval._DOUBLE_3PTR);
         return ret;
   }

   return 0;
}

void set_init_value(st_entry* entry,int offset,returnable* _init_)
{
   switch (entry->symbol_entry_type)
   {
      case E_CHAR:
         *(entry->symbol_entry_value.var_val._CHAR_PTR + offset) = (char) DOUBLE_VALUE(_init_);
         return;
      case E_SHORT:
         *(entry->symbol_entry_value.var_val._SHORT_PTR + offset) = (short) DOUBLE_VALUE(_init_);
         return;
      case E_INT:
         *(entry->symbol_entry_value.var_val._INT_PTR + offset) = (int) DOUBLE_VALUE(_init_);
         return;
      case E_LONG:
         *(entry->symbol_entry_value.var_val._LONG_PTR + offset) = (long) DOUBLE_VALUE(_init_);
         return;
      case E_FLOAT:
         *(entry->symbol_entry_value.var_val._FLOAT_PTR + offset) = (float) DOUBLE_VALUE(_init_);
         return;
      case E_DOUBLE:
         *(entry->symbol_entry_value.var_val._DOUBLE_PTR + offset) = (double) DOUBLE_VALUE(_init_);
         return;
      case E_VOID_PTR:
         *(entry->symbol_entry_value.var_val._VOID_2PTR + offset) = VOID_PTR_VALUE(_init_);
         return;
      case E_CHAR_PTR:
         *(entry->symbol_entry_value.var_val._CHAR_2PTR + offset) = (char *) CHAR_PTR_VALUE(_init_);
         return;
      case E_SHORT_PTR:
         *(entry->symbol_entry_value.var_val._SHORT_2PTR + offset) = (short *) SHORT_PTR_VALUE(_init_);
         return;
      case E_INT_PTR:
         *(entry->symbol_entry_value.var_val._INT_2PTR + offset) = (int *) INT_PTR_VALUE(_init_);
         return;
      case E_LONG_PTR:
         *(entry->symbol_entry_value.var_val._LONG_2PTR + offset) = (long *) LONG_PTR_VALUE(_init_);
         return;
      case E_FLOAT_PTR:
         *(entry->symbol_entry_value.var_val._FLOAT_2PTR + offset) = (float *) FLOAT_PTR_VALUE(_init_);
         return;
      case E_DOUBLE_PTR:
         *(entry->symbol_entry_value.var_val._DOUBLE_2PTR + offset) = (double *) DOUBLE_PTR_VALUE(_init_);
         return;
      case E_VOID_2PTR:
         *(entry->symbol_entry_value.var_val._VOID_3PTR + offset) = VOID_2PTR_VALUE(_init_);
         return;
      case E_CHAR_2PTR:
         *(entry->symbol_entry_value.var_val._CHAR_3PTR + offset) = CHAR_2PTR_VALUE(_init_);
         return;
      case E_SHORT_2PTR:
         *(entry->symbol_entry_value.var_val._SHORT_3PTR + offset) = SHORT_2PTR_VALUE(_init_);
         return;
      case E_INT_2PTR:
         *(entry->symbol_entry_value.var_val._INT_3PTR + offset) = INT_2PTR_VALUE(_init_);
         return;
      case E_LONG_2PTR:
         *(entry->symbol_entry_value.var_val._LONG_3PTR + offset) = LONG_2PTR_VALUE(_init_);
         return;
      case E_FLOAT_2PTR:
         *(entry->symbol_entry_value.var_val._FLOAT_3PTR + offset) = FLOAT_2PTR_VALUE(_init_);
         return;
      case E_DOUBLE_2PTR:
         *(entry->symbol_entry_value.var_val._DOUBLE_3PTR + offset) = DOUBLE_2PTR_VALUE(_init_);
         return;
      default:
         err_msg = "INTERNAL EXCEPTION: Invalid type operation.\n\n";
         err();
   }
}

void set_2arr_init_value(st_entry* entry,int row,int col,returnable* _init_)
{
   switch (entry->symbol_entry_type)
   {
      case E_CHAR:
         *(*(entry->symbol_entry_value.var_val._CHAR_2PTR + row) + col) = (char) DOUBLE_VALUE(_init_);
         return;
      case E_SHORT:
         *(*(entry->symbol_entry_value.var_val._SHORT_2PTR + row) + col) = (short) DOUBLE_VALUE(_init_);
         return;
      case E_INT:
         *(*(entry->symbol_entry_value.var_val._INT_2PTR + row) + col) = (int) DOUBLE_VALUE(_init_);
         return;
      case E_LONG:
         *(*(entry->symbol_entry_value.var_val._LONG_2PTR + row) + col) = (long) DOUBLE_VALUE(_init_);
         return;
      case E_FLOAT:
         *(*(entry->symbol_entry_value.var_val._FLOAT_2PTR + row) + col) = (float) DOUBLE_VALUE(_init_);
         return;
      case E_DOUBLE:
         *(*(entry->symbol_entry_value.var_val._DOUBLE_2PTR + row) + col) = (double) DOUBLE_VALUE(_init_);
         return;
      default:
         err_msg = "INTERNAL EXCEPTION: Invalid type operation.\n\n";
         err();
   }
}

returnable* get_arithmetic_value(returnable* left,returnable* right,ast_node_tag op)
{
   // void* l;
   // int i;
   returnable* ret   = new_returnable();
   if (op == UNARY_MINUS)
   {
      ret->type = left->type;
   }
   else
   {
      ret->type = get_effective_type(left->type,right->type);
   }
   if (op == SUBTRACTION && is_pointer_type(ret->type) && ret->type == right->type)
   {
      err_msg = "RUNTIME EXCEPTION: Invalid opeartion over pointer.\n\n";
      err();
   }
   switch (ret->type)
   {
      case E_CHAR:
         ret->eval._CHAR = char_arithmetic_value(CHAR_VALUE(left),right != NULL ? CHAR_VALUE(right) : (char) 0,op);
         return ret;
      case E_SHORT:
         ret->eval._SHORT = short_arithmetic_value(SHORT_VALUE(left),right != NULL ? SHORT_VALUE(right) : (short) 0,op);
         return ret;
      case E_INT:
         ret->eval._INT = int_arithmetic_value(INT_VALUE(left),right != NULL ? INT_VALUE(right) : 0,op);
         return ret;
      case E_LONG:
         ret->eval._LONG = long_arithmetic_value(LONG_VALUE(left),right != NULL ? LONG_VALUE(right) : 0,op);
         return ret;
      case E_FLOAT:
         ret->eval._FLOAT = float_arithmetic_value(FLOAT_VALUE(left),right != NULL ? FLOAT_VALUE(right) : 0,op);
         return ret;
      case E_DOUBLE:
         ret->eval._DOUBLE = double_arithmetic_value(DOUBLE_VALUE(left),right != NULL ? DOUBLE_VALUE(right) : 0,op);
         return ret;
      case E_CHAR_PTR:
         ret->eval._CHAR_PTR = (char *) ptr_arithmetic_value((is_pointer_type(left->type) ? VOID_PTR_VALUE(left) : VOID_PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_SHORT_PTR:
         ret->eval._SHORT_PTR = (short *) ptr_arithmetic_value((is_pointer_type(left->type) ? VOID_PTR_VALUE(left) : VOID_PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_INT_PTR:
         ret->eval._INT_PTR = (int *) ptr_arithmetic_value((is_pointer_type(left->type) ? VOID_PTR_VALUE(left) : VOID_PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_LONG_PTR:
         ret->eval._LONG_PTR = (long *) ptr_arithmetic_value((is_pointer_type(left->type) ? VOID_PTR_VALUE(left) : VOID_PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_FLOAT_PTR:
         ret->eval._FLOAT_PTR = (float *) ptr_arithmetic_value((is_pointer_type(left->type) ? VOID_PTR_VALUE(left) : VOID_PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_DOUBLE_PTR:
         ret->eval._DOUBLE_PTR = (double *) ptr_arithmetic_value((is_pointer_type(left->type) ? VOID_PTR_VALUE(left) : VOID_PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_CHAR_2PTR:
         ret->eval._CHAR_2PTR = (char * *) ptr2_arithmetic_value((is_2pointer_type(left->type) ? VOID_2PTR_VALUE(left) : VOID_2PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_SHORT_2PTR:
         ret->eval._SHORT_2PTR = (short * *) ptr2_arithmetic_value((is_2pointer_type(left->type) ? VOID_2PTR_VALUE(left) : VOID_2PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_INT_2PTR:
         ret->eval._INT_2PTR = (int * *) ptr2_arithmetic_value((is_2pointer_type(left->type) ? VOID_2PTR_VALUE(left) : VOID_2PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_LONG_2PTR:
         ret->eval._LONG_2PTR = (long * *) ptr2_arithmetic_value((is_2pointer_type(left->type) ? VOID_2PTR_VALUE(left) : VOID_2PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_FLOAT_2PTR:
         ret->eval._FLOAT_2PTR = (float * *) ptr2_arithmetic_value((is_2pointer_type(left->type) ? VOID_2PTR_VALUE(left) : VOID_2PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      case E_DOUBLE_2PTR:
         ret->eval._DOUBLE_2PTR = (double * *) ptr2_arithmetic_value((is_2pointer_type(left->type) ? VOID_2PTR_VALUE(left) : VOID_2PTR_VALUE(right)),(is_int_type(left->type) ? INT_VALUE(left) : INT_VALUE(right)),op);
         return ret;
      default:
         err_msg = "INTERNAL EXCEPTION: Invalid type operation.\n\n";
         err();
   }

   return 0;
}

char char_arithmetic_value(char left,char right,ast_node_tag op)
{
   switch (op)
   {
      case MULTIPLICATION:
         return (char) (left * right);
      case DIVISION:
         if (right == 0)
         {
            err_msg = "RUNTIME EXCEPTION: Divide by 0.\n\n";
            err();
         }
         return (char) (left / right);
      case MODULO:
         if (right == 0)
         {
            err_msg = "RUNTIME EXCEPTION: Divide by 0.\n\n";
            err();
         }
         return (char) (left % right);
      case ADDITION:
         return (char) (left + right);
      case SUBTRACTION:
         return (char) (left - right);
      case LEFT_SHIFT:
         return (char) (left << right);
      case RIGHT_SHIFT:
         return (char) (left >> right);
      case UNARY_MINUS:
         return (char) (-left);
   }

   return 0;
}

char short_arithmetic_value(short left,short right,ast_node_tag op)
{
   switch (op)
   {
      case MULTIPLICATION:
         return (char) (left * right);
      case DIVISION:
         if (right == 0)
         {
            err_msg = "RUNTIME EXCEPTION: Divide by 0.\n\n";
            err();
         }
         return (char) (left / right);
      case MODULO:
         if (right == 0)
         {
            err_msg = "RUNTIME EXCEPTION: Divide by 0.\n\n";
            err();
         }
         return (char) (left % right);
      case ADDITION:
         return (char) (left + right);
      case SUBTRACTION:
         return (char) (left - right);
      case LEFT_SHIFT:
         return (char) (left << right);
      case RIGHT_SHIFT:
         return (char) (left >> right);
      case UNARY_MINUS:
         return (char) (-left);
   }

   return 0;
}

int int_arithmetic_value(int left,int right,ast_node_tag op)
{
   switch (op)
   {
      case MULTIPLICATION:
         return (left * right);
      case DIVISION:
         if (right == 0)
         {
            err_msg = "RUNTIME EXCEPTION: Divide by 0.\n\n";
            err();
         }
         return left / right;
      case MODULO:
         if (right == 0)
         {
            err_msg = "RUNTIME EXCEPTION: Divide by 0.\n\n";
            err();
         }
         return (left % right);
      case ADDITION:
         return (left + right);
      case SUBTRACTION:
         return (left - right);
      case LEFT_SHIFT:
         return (left << right);
      case RIGHT_SHIFT:
         return (left >> right);
      case UNARY_MINUS:
         return (-left);
   }

   return 0;
}

long long_arithmetic_value(long left,long right,ast_node_tag op)
{
   switch (op)
   {
      case MULTIPLICATION:
         return (left * right);
      case DIVISION:
         if (right == 0)
         {
            err_msg = "RUNTIME EXCEPTION: Divide by 0.\n\n";
            err();
         }
         return left / right;
      case MODULO:
         if (right == 0)
         {
            err_msg = "RUNTIME EXCEPTION: Divide by 0.\n\n";
            err();
         }
         return (left % right);
      case ADDITION:
         return (left + right);
      case SUBTRACTION:
         return (left - right);
      case LEFT_SHIFT:
         return (left << right);
      case RIGHT_SHIFT:
         return (left >> right);
      case UNARY_MINUS:
         return (-left);
   }

   return 0;
}

float float_arithmetic_value(float left,float right,ast_node_tag op)
{
   switch (op)
   {
      case MULTIPLICATION:
         return (left * right);
      case DIVISION:
         if (right == 0)
         {
            err_msg = "RUNTIME EXCEPTION: Divide by 0.\n\n";
            err();
         }
         return left / right;
      case ADDITION:
         return (left + right);
      case SUBTRACTION:
         return (left - right);
      case UNARY_MINUS:
         return (-left);
   }

   return 0;
}

double double_arithmetic_value(double left,double right,ast_node_tag op)
{
   switch (op)
   {
      case MULTIPLICATION:
         return (left * right);
      case DIVISION:
         if (right == 0)
         {
            err_msg = "RUNTIME EXCEPTION: Divide by 0.\n\n";
            err();
         }
         return left / right;
      case ADDITION:
         return (left + right);
      case SUBTRACTION:
         return (left - right);
      case UNARY_MINUS:
         return (-left);
   }

   return 0;
}

void* ptr_arithmetic_value(void* left,int right,ast_node_tag op)
{
   switch (op)
   {
      case ADDITION:
         return (char *) left + right;
      case SUBTRACTION:
         return (char *) left - right;
      default:
         err_msg = "Invalid arithmetic operation over pointer types.\n\n";
         err();
   }

   return 0;
}

void** ptr2_arithmetic_value(void** left,int right,ast_node_tag op)
{
   switch (op)
   {
      case ADDITION:
         return (left + right);
      case SUBTRACTION:
         return (left - right);
      default:
         err_msg = "Invalid arithmetic operation over pointer types.\n\n";
         err();
   }

   return 0;
}

returnable* get_relational_value(returnable* left,returnable* right,ast_node_tag op)
{
   returnable* ret   = new_returnable();
   ret->type = E_INT;
   switch (op)
   {
      case REL_LESS:
         ret->eval._INT = is_pointer_type(left->type) ? (DOUBLE_PTR_VALUE(left) < DOUBLE_PTR_VALUE(right)) : (DOUBLE_VALUE(left) < DOUBLE_VALUE(right));
         return ret;
      case REL_GREATER:
         ret->eval._INT = is_pointer_type(left->type) ? (DOUBLE_PTR_VALUE(left) > DOUBLE_PTR_VALUE(right)) : (DOUBLE_VALUE(left) > DOUBLE_VALUE(right));
         return ret;
      case REL_LESS_EQUAL:
         ret->eval._INT = is_pointer_type(left->type) ? (DOUBLE_PTR_VALUE(left) <= DOUBLE_PTR_VALUE(right)) : (DOUBLE_VALUE(left) <= DOUBLE_VALUE(right));
         return ret;
      case REL_GREATER_EQUAL:
         ret->eval._INT = is_pointer_type(left->type) ? (DOUBLE_PTR_VALUE(left) >= DOUBLE_PTR_VALUE(right)) : (DOUBLE_VALUE(left) >= DOUBLE_VALUE(right));
         return ret;
      case REL_EQUAL:
         ret->eval._INT = is_pointer_type(left->type) ? (DOUBLE_PTR_VALUE(left) == DOUBLE_PTR_VALUE(right)) : (DOUBLE_VALUE(left) == DOUBLE_VALUE(right));
         return ret;
      case REL_NOT_EQUAL:
         ret->eval._INT = is_pointer_type(left->type) ? (DOUBLE_PTR_VALUE(left) != DOUBLE_PTR_VALUE(right)) : (DOUBLE_VALUE(left) != DOUBLE_VALUE(right));
         return ret;
   }

   return 0;
}

returnable* get_logical_value(returnable* left,returnable* right,ast_node_tag op)
{
   returnable* ret   = new_returnable();
   ret->type = E_INT;
   if (op == LOGICAL_AND)
   {
      ret->eval._INT = is_pointer_type(left->type) ? (DOUBLE_PTR_VALUE(left) && DOUBLE_PTR_VALUE(right)) : (DOUBLE_VALUE(left) && DOUBLE_VALUE(right));
   }
   else if (op == LOGICAL_OR)
   {
      ret->eval._INT = is_pointer_type(left->type) ? (DOUBLE_PTR_VALUE(left) || DOUBLE_PTR_VALUE(right)) : (DOUBLE_VALUE(left) || DOUBLE_VALUE(right));
   }
   else
   {
      ret->eval._INT = is_pointer_type(left->type) ? (!DOUBLE_PTR_VALUE(left)) : (!DOUBLE_VALUE(left));
   }
   return ret;
}

returnable* get_bitwise_value(returnable* left,returnable* right,ast_node_tag op)
{
   returnable* ret   = new_returnable();
   ret->type = E_INT;
   switch (op)
   {
      case BITWISE_AND:
         ret->eval._INT = (INT_VALUE(left) & INT_VALUE(right));
         return ret;
      case BITWISE_OR:
         ret->eval._INT = (INT_VALUE(left) | INT_VALUE(right));
         return ret;
      case BITWISE_XOR:
         ret->eval._INT = (INT_VALUE(left) ^ INT_VALUE(right));
         return ret;
      case BITWISE_NOT:
         ret->eval._INT = (~INT_VALUE(left));
         return ret;
   }

   return 0;
}

returnable* lib_printf(returnable* param_list)
{
   int         len, i = 0, count = 0;
   char*       str;
   char        flag  = 1;
   returnable* ret;
   returnable* param = param_list;
   if (param == NULL || param->type != E_CHAR_PTR)
   {
      err_msg = "RUNTIME EXCEPTION: Invalid parameters to printf. First parameter must be a format string.\n\n";
      err();
   }
   str = param->eval._CHAR_PTR;
   param = param->next;
   len = strlen(str) - 1;
   while (len >= i)
   {
      if (str[i] == '%')
      {
         switch (str[i + 1])
         {
            case 'c':
               if (param == NULL || !is_compatible(param->type,E_CHAR))
               {
                  err_msg = "RUNTIME EXCEPTION: Char type parameter expected.\n\n";
                  err();
               }
               else
               {
                  count += printf("%c",(char) DOUBLE_VALUE(param));
                  i += 2;
                  break;
               }
            case 'd':
               if (param == NULL || !is_compatible(param->type,E_INT))
               {
                  err_msg = "RUNTIME EXCEPTION: Int type parameter expected.\n\n";
                  err();
               }
               else
               {
                  count += printf("%d",(int) DOUBLE_VALUE(param));
                  i += 2;
                  break;
               }
            case 'f':
               if (param == NULL || !is_compatible(param->type,E_FLOAT))
               {
                  err_msg = "RUNTIME EXCEPTION: Float type parameter expected.\n\n";
                  err();
               }
               else
               {
                  count += printf("%f",(float) DOUBLE_VALUE(param));
                  i += 2;
                  break;
               }
            case 'l':
               if (str[i + 2] == 'd')
               {
                  if (param == NULL || !is_compatible(param->type,E_LONG))
                  {
                     err_msg = "RUNTIME EXCEPTION: Long type parameter expected.\n\n";
                     err();
                  }
                  else
                  {
                     count += printf("%ld",(long) DOUBLE_VALUE(param));
                     i += 3;
                     break;
                  }
               }
               else if (str[i + 2] == 'f')
               {
                  if (param == NULL || !is_compatible(param->type,E_DOUBLE))
                  {
                     err_msg = "RUNTIME EXCEPTION: Double type parameter expected.\n\n";
                     err();
                  }
                  else
                  {
                     count += printf("%lf",(double) DOUBLE_VALUE(param));
                     i += 3;
                     break;
                  }
               }
               else
               {
                  err_msg = "RUNTIME EXCEPTION: Invalid use of %%l.\n\n";
                  err();
               }
            case 's':
               if (param == NULL || param->type != E_CHAR_PTR)
               {
                  err_msg = "RUNTIME EXCEPTION: Char pointer type parameter expected.\n\n";
                  err();
               }
               else
               {
                  count += printf("%s",param->eval._CHAR_PTR);
                  i += 2;
                  break;
               }
            case '%':
               count += printf("%%");
               flag = 0;
               i += 2;
               break;
            default:
               err_msg = "RUNTIME EXCEPTION: Invalid use of %%.\n\n";
               err();
         }
         if (flag && param != NULL)
         {
            param = param->next;
         }
         else
         {
            flag = 1;
         }
      }
      else if (str[i] == '\\')
      {
         switch (str[i + 1])
         {
            case 't':
               count += printf("\t");
               i += 2;
               break;
            case 'n':
               count += printf("\n");
               i += 2;
               break;
            case '\\':
               count += printf("\\");
               i += 2;
               break;
            case '\'':
               count += printf("\'");
               i += 2;
               break;
            case '\"':
               count += printf("\"");
               i += 2;
               break;
            case 'v':
               count += printf("\v");
               i += 2;
               break;
            case 'b':
               count += printf("\b");
               i += 2;
               break;
            case 'a':
               count += printf("\a");
               i += 2;
               break;
            case 'f':
               count += printf("\f");
               i += 2;
               break;
            case 'r':
               count += printf("\r");
               i += 2;
               break;
            case '?':
               count += printf("\?");
               i += 2;
               break;
            default:
               err_msg = "RUNTIME EXCEPTION: Invalid use of \\.\n\n";
               err();
         }
      }
      else
      {
         count += printf("%c",str[i]);
         i += 1;
      }
   }
   free(str);
   if (param != NULL)
   {
      err_msg = "RUNTIME EXCEPTION: No format for next print.\n\n";
      err();
   }
   ret = new_returnable();
   ret->type = E_INT;
   ret->eval._INT = count;
   return ret;
}

returnable* lib_scanf(returnable* param_list)
{
   int         len, i = 0, count = 0;
   char*       str;
   returnable* ret;
   returnable* param = param_list;
   if (param == NULL || param->type != E_CHAR_PTR)
   {
      err_msg = "RUNTIME EXCEPTION: Invalid parameters to scanf. First parameter must be a format string.\n\n";
      err();
   }
   str = param->eval._CHAR_PTR;
   param = param->next;
   len = strlen(str);
   while (len > i)
   {
      if (str[i] != '%')
      {
         err_msg = "RUNTIME EXCEPTION: %% expected.\n\n";
         err();
      }
      else
      {
         switch (str[i + 1])
         {
            case 'c':
               if (param == NULL || param->type != E_CHAR_PTR)
               {
                  err_msg = "RUNTIME EXCEPTION: Char pointer type parameter expected.\n\n";
                  err();
               }
               else
               {
                  count += scanf("%c",param->eval._CHAR_PTR);
                  i += 2;
                  break;
               }
            case 'd':
               if (param == NULL || param->type != E_INT_PTR)
               {
                  err_msg = "RUNTIME EXCEPTION: Int pointer type parameter expected.\n\n";
                  err();
               }
               else
               {
                  count += scanf("%d",param->eval._INT_PTR);
                  i += 2;
                  break;
               }
            case 'h':
               if (param == NULL || param->type != E_SHORT_PTR)
               {
                  err_msg = "RUNTIME EXCEPTION: Short pointer type parameter expected.\n\n";
                  err();
               }
               else
               {
                  count += scanf("%hd",param->eval._SHORT_PTR);
                  i += 2;
                  break;
               }
            case 'f':
               if (param == NULL || param->type != E_FLOAT_PTR)
               {
                  err_msg = "RUNTIME EXCEPTION: Float pointer type parameter expected.\n\n";
                  err();
               }
               else
               {
                  count += scanf("%f",param->eval._FLOAT_PTR);
                  i += 2;
                  break;
               }
            case 'l':
               if (str[i + 2] == 'd')
               {
                  if (param == NULL || param->type != E_LONG_PTR)
                  {
                     err_msg = "RUNTIME EXCEPTION: Long pointer type parameter expected.\n\n";
                     err();
                  }
                  else
                  {
                     count += scanf("%ld",param->eval._LONG_PTR);
                     i += 3;
                     break;
                  }
               }
               else if (str[i + 2] == 'f')
               {
                  if (param == NULL || param->type != E_DOUBLE_PTR)
                  {
                     err_msg = "RUNTIME EXCEPTION: Double pointer type parameter expected.\n\n";
                     err();
                  }
                  else
                  {
                     count += scanf("%lf",param->eval._DOUBLE_PTR);
                     i += 3;
                     break;
                  }
               }
               else
               {
                  err_msg = "RUNTIME EXCEPTION: Invalid use of %%l.\n\n";
                  err();
               }
            case 's':
               if (param == NULL || !is_compatible(param->type,E_CHAR_PTR))
               {
                  err_msg = "RUNTIME EXCEPTION: Char pointer type parameter expected.\n\n";
                  err();
               }
               else
               {
                  count += scanf("%s",param->eval._CHAR_PTR);
                  i += 2;
                  break;
               }
            default:
               err_msg = "RUNTIME EXCEPTION: Invalid use of %%.\n\n";
               err();
         }
         if (param != NULL)
         {
            param = param->next;
         }
      }
   }
   free(str);
   if (param != NULL)
   {
      err_msg = "RUNTIME EXCEPTION: No format for next scan.\n\n";
      err();
   }
   ret = new_returnable();
   ret->type = E_INT;
   ret->eval._INT = count;
   return ret;
}

char* get_param_num(ast node)
{
   int   i  = 0;
   ast   temp;
   if (node == NULL)
   {
      return strdup("0");
   }
   else
   {
      temp = get_left_most_child(node);
      while (temp != NULL)
      {
         i++;
         temp = get_left_most_sibling(temp);
      }
      return itostr(i);
   }
}

char* itostr(int i)
{
   char* str   = (char*) safe_malloc(2 * sizeof(int));
   sprintf(str,"%d",i);
   return str;
}

int is_lib_func(char* str)
{
   if (!strcmp(str,PRINTF_LABEL))
   {
      return 1;
   }
   else if (!strcmp(str,SCANF_LABEL))
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

char* get_unquoted_string(char* s)
{
   int   i = 0, j = strlen(s) - 1;
   char* str   = (char*) safe_malloc(sizeof(char) * j);
   for (i = 0; i < j - 1; i++)
   {
      str[i] = s[i + 1];
   }
   str[j - 1] = '\0';
   return str;
}

char get_char(char* s)
{
   int   x  = strlen(s);
   if (x <= 2)
   {
      err_msg = "RUNTIME EXCEPTION: Invalid char \'\'.\n\n";
      err();
   }
   if (s[1] == '\\' && x >= 3)
   {
      switch (s[2])
      {
         case '0':
            return '\0';
         case '\\':
            if (x >= 4 && s[3] == '\'')
            {
               return s[3];
            }
            else if (x >= 4 && s[3] == '\"')
            {
               return s[3];
            }
            else
            {
               return s[2];
            }
         default:
            err_msg = "RUNTIME EXCEPTION: Invalid escape sequence.\n\n";
            err();
      }
   }
   else
   {
      return s[1];
   }

   return 0;
}


int get_param_list_size(returnable* ret)
{
   int         i     = 0;
   returnable* temp  = ret;
   while (temp != NULL)
   {
      i++;
      temp = temp->next;
   }
   return i;
}
