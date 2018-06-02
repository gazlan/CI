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


Command line handler for ci. It uses vm.c as helper.

@author Ashwin Jha<ajha.dev@gmail.com>
*/

#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void  publish_masthead();
void  show_help();

int main(int argc,char** argv)
{
   FILE* in;

   int   a  = 0;

   if (argc == 1)
   {
      a = _start_();
   }
   else if (argc > 1)
   {
      if (argv[1][0] == '-')
      {
         switch (argv[1][1])
         {
            case 'v':
               publish_masthead();
            case 'h':
            default:
               show_help();
         }
      }
      else if (!strcmp(argv[1] + strlen(argv[1]) - 3,".ci"))
      {
         in = fopen(argv[1],"r");

         if (!in)
         {
            fprintf(stderr,"\nUnable to open script file.\n");
            exit(1);
         }
         else
         {
            a = _interpret_(in);
            fclose(in);
         }
      }
      else
      {
         show_help();
      }
   }

   return a;
}
