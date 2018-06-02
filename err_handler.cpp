#include "stdafx.h"

/*
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


This module handles error handling. Currently, this module is in its very basic
structure. This will be improved subsequently.


@author Ashwin Jha<ajha.dev@gmail.com>
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

//err_t err_type;
char* err_msg;

void err()
{  
   purge_vmds();
   
   fprintf(stderr,"\n%sBye bye!!\n\n",err_msg);
   
   exit(1);
}
