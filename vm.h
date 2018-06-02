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


VM functions declarations. For more information, check vm.c.

@author Ashwin Jha<ajha.dev@gmail.com>

*****************************************************************************************************/

#ifndef _VM_H_
#define _VM_H_

#include "abstract_syntax_tree.h"

#define INTERPRETER_VERSION "1.0"

int   _start_();
int   _interpret_(FILE* in);
void  set_main_ref(ast node);

#endif
