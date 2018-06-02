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


This module handles the functions related to manipulation of abstract syntax tree
data structure. For more information on ast data structure check abstract_syntax_tree.h.


@author Ashwin Jha<ajha.dev@gmail.com>

*****************************************************************************************************/

#include "interpreter.h"
#include "abstract_syntax_tree.h"
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ast   asts[MAX_NO_OF_FUNCTIONS];

ast new_ast(ast_node_tag t,char* l,data_type rt)
{
   ast   node  = (ast) safe_malloc(sizeof(ast_node));
   node->tag = t;
   node->ast_node_label = strdup(l);
   node->return_type = rt;
   node->left_most_child = NULL;
   node->left_most_sibling = NULL;
   return node;
}

ast copy_ast(ast node)
{
   ast   dup;
   ast   left_dup;
   ast   sibling;
   if (node == NULL)
   {
      return NULL;
   }
   dup = new_ast(node->tag,node->ast_node_label,node->return_type);
   left_dup = copy_ast(get_left_most_child(node));
   set_left_most_child(dup,left_dup);
   sibling = copy_ast(get_left_most_sibling(node));
   set_left_most_sibling(dup,sibling);
   return dup;
}

void set_left_most_child(ast node,ast lmc)
{
   node->left_most_child = lmc;
}

void set_left_most_sibling(ast node,ast lms)
{
   node->left_most_sibling = lms;
}

ast get_left_most_sibling(ast node)
{
   return node->left_most_sibling;
}

ast get_left_most_child(ast node)
{
   return node->left_most_child;
}

void purge_ast(ast node)
{
   ast   temp;
   while (node->left_most_child != NULL)
   {
      temp = node->left_most_child;
      node->left_most_child = get_left_most_sibling(temp);
      purge_ast(temp);
   }
   free(node->ast_node_label);
   free(node);
}

DWORD set_ast_root_reference(ast node)
{
   DWORD    h = Hash(node->ast_node_label,MAX_NO_OF_FUNCTIONS);

   for (DWORD i = 0; i < MAX_NO_OF_FUNCTIONS; i++)
   {
      DWORD    j = (h + i) % MAX_NO_OF_FUNCTIONS;

      if (!asts[j])
      {
         asts[j] = node;
         return j;
      }
   }

   err_msg = "RUNTIME EXCEPTION: Stack overflow.\n\n";
   
   err();

   return 0;
}

ast lookup_ast(char* label)
{
   DWORD    h = Hash(label,MAX_NO_OF_FUNCTIONS);

   for (DWORD i = 0; i < MAX_NO_OF_FUNCTIONS; i++)
   {
      DWORD    j = (h + i) % MAX_NO_OF_FUNCTIONS;

      if (asts[j] && !strcmp(asts[j]->ast_node_label,label))
      {
         return asts[j];
      }
   }

   return 0;
}

void purge_asts()
{
   int   i;
   ast   temp;
   for (i = 0; i < MAX_NO_OF_FUNCTIONS; i++)
   {
      temp = asts[i];
      if (temp != NULL)
      {
         purge_ast(temp);
         asts[i] = NULL;
      }
   }
}

char* toString(ast_node_tag tag)
{
   switch (tag)
   {
      case MULTIPLICATION:
         return "*";
      case DIVISION:
         return "/";
      case MODULO:
         return "%";
      case ADDITION:
         return "+";
      case SUBTRACTION:
         return "-";
      case BITWISE_AND:
         return "&";
      case BITWISE_OR:
         return "|";
      case BITWISE_XOR:
         return "^";
      case LOGICAL_AND:
         return "&&";
      case LOGICAL_OR:
         return "||";
      case LEFT_SHIFT:
         return "<<";
      case RIGHT_SHIFT:
         return ">>";
      case REL_LESS:
         return "<";
      case REL_GREATER:
         return ">";
      case REL_LESS_EQUAL:
         return "<=";
      case REL_GREATER_EQUAL:
         return ">=";
      case REL_EQUAL:
         return "==";
      case REL_NOT_EQUAL:
         return "!=";
      case PRE_INCREMENT:
         return "pre ++";
      case PRE_DECREMENT:
         return "pre --";
      case POST_INCREMENT:
         return "post ++";
      case POST_DECREMENT:
         return "post --";
         /* case PROGRAM, FUNCTION, BLOCK, VARIABLE, ARRAY, ARRAY_ID, ARRAY_OFFSET, CONSTANT, TYPE, DECLARATION,
         ASSIGNMENT, UNARY_SUBTRACTION,BITWISE_NOT, RELATIONAL_NOT, IF_STATEMENT,
         WHILE_STATEMENT, FOR_STATEMENT, TYPE_CAST */
      default:
         return "";
   }
}
