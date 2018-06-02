#include "stdafx.h"

// d:\yacc\bin\lex -o yylex.c -D yylex.h ci.l
#define YYNEWLINE 10
#define INITIAL 0
#define yy_endst 163
#define yy_nxtmax 1267
#define YY_LA_SIZE 21

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static unsigned short   yy_la_act[]    =
{
   69, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 19, 77, 24, 77, 24, 77, 77, 62, 77, 77, 72, 77, 71, 77, 67, 77, 66, 77, 68, 77, 70, 77, 63, 77, 73, 77, 74, 77, 57, 77, 64, 77, 52, 77, 53, 77, 54, 77, 55, 77, 56, 77, 58, 77, 59, 77, 60, 77, 61, 77, 65, 77, 75, 77, 76, 77, 76, 77, 51, 50, 41, 47, 40, 39, 46, 38, 36, 35, 45, 34, 44, 43, 48, 33, 42, 49, 32, 31, 27, 28, 28, 26, 24, 25, 25, 29, 27, 29, 30, 30, 28, 30, 28, 30, 22, 24, 23, 25, 23, 25, 20, 21, 21, 19, 19, 19, 19, 19, 17, 19, 19, 19, 16, 19, 19, 19, 18, 19, 19, 19, 13, 19, 19, 19, 19, 19, 12, 19, 19, 19, 11, 19, 9, 19, 19, 10, 19, 19, 19, 8, 19, 19, 19, 7, 19, 19, 19, 6, 19, 19, 19, 19, 19, 5, 19, 19, 19, 19, 19, 19, 19, 19, 14, 19, 19, 4, 19, 19, 19, 19, 19, 15, 19, 19, 19, 3, 19, 19, 19, 19, 19, 2, 19, 19, 19, 1, 19, 0, 37, 
};

static unsigned char    yy_look[]      =
{
   0
};

static short            yy_final[]     =
{
   0, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 37, 39, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 107, 107, 108, 108, 109, 110, 111, 111, 111, 112, 112, 113, 114, 115, 116, 118, 119, 120, 122, 124, 124, 126, 128, 130, 131, 132, 133, 134, 135, 135, 135, 136, 137, 138, 140, 141, 142, 144, 145, 146, 148, 149, 150, 152, 153, 154, 155, 156, 158, 159, 160, 162, 164, 165, 167, 168, 169, 171, 172, 173, 175, 176, 177, 179, 180, 181, 182, 183, 185, 186, 187, 188, 189, 190, 191, 192, 194, 195, 197, 198, 199, 200, 201, 203, 204, 205, 207, 208, 209, 210, 211, 213, 214, 215, 217, 218, 219
};
#ifndef yy_state_t
#define yy_state_t unsigned char
#endif

static yy_state_t       yy_begin[]     =
{
   0, 0, 0
};

static yy_state_t       yy_next[]      =
{
   46, 46, 46, 46, 46, 46, 46, 46, 46, 44, 45, 44, 44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 44, 32, 21, 46, 46, 27, 28, 19, 38, 39, 26, 24, 36, 25, 20, 1, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 37, 33, 23, 31, 22, 43, 46, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 40, 46, 41, 29, 15, 46, 15, 12, 5, 6, 7, 8, 15, 15, 9, 15, 15, 10, 2, 15, 15, 3, 15, 11, 4, 15, 15, 13, 14, 15, 15, 15, 34, 30, 35, 42, 46, 47, 48, 49, 51, 53, 54, 55, 57, 59, 60, 61, 62, 64, 63, 65, 72, 85, 92, 163, 163, 163, 163, 163, 56, 163, 163, 58, 52, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 163, 163, 163, 163, 161, 163, 163, 163, 163, 71, 84, 91, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 162, 163, 163, 163, 50, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 163, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 163, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 163, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 80, 163, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 163, 163, 163, 163, 163, 163, 163, 163, 79, 163, 163, 163, 83, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 163, 80, 163, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 163, 163, 163, 163, 78, 163, 163, 163, 82, 163, 163, 163, 163, 163, 163, 163, 163, 86, 89, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 163, 163, 163, 100, 163, 97, 163, 90, 90, 90, 90, 90, 90, 99, 96, 163, 163, 104, 163, 95, 86, 88, 163, 163, 105, 163, 163, 163, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 103, 90, 90, 90, 90, 90, 90, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 163, 98, 163, 163, 93, 163, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 101, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 108, 163, 106, 107, 163, 102, 163, 163, 163, 163, 163, 109, 110, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 114, 163, 111, 113, 118, 112, 163, 115, 116, 117, 163, 163, 119, 121, 125, 120, 122, 163, 163, 163, 124, 163, 123, 163, 163, 163, 127, 129, 163, 163, 163, 126, 132, 163, 128, 163, 130, 134, 163, 135, 163, 133, 163, 163, 131, 163, 136, 163, 163, 163, 163, 163, 163, 137, 163, 139, 143, 163, 163, 142, 163, 163, 138, 163, 163, 163, 140, 163, 163, 141, 163, 145, 163, 147, 144, 163, 146, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 150, 163, 163, 163, 163, 163, 163, 163, 163, 163, 148, 163, 163, 149, 163, 152, 151, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 154, 163, 163, 163, 163, 163, 153, 163, 163, 155, 157, 163, 163, 163, 158, 163, 163, 163, 156, 163, 163, 163, 163, 163, 163, 159, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 160, 
};

static yy_state_t       yy_check[]     =
{
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 23, 60, 22, 22, 63, 70, 81, 90, ~0, 94, 93, ~0, ~0, 25, 94, 93, 24, 28, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 15, 100, 103, 106, 1, 15, 100, 103, 106, 70, 81, 90, 109, 114, 117, 120, 118, 109, 114, 117, 120, 118, ~0, 1, ~0, ~0, ~0, 30, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, ~0, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, ~0, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, ~0, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 18, ~0, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 14, 99, 12, ~0, 98, 14, 99, 12, 18, 98, ~0, ~0, 80, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, ~0, 87, ~0, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 123, 102, 126, ~0, 18, 123, 102, 126, 80, 129, 134, 142, ~0, ~0, 129, 134, 142, 17, 87, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, ~0, 97, ~0, 99, ~0, 14, 97, 86, 86, 86, 86, 86, 86, 98, 16, ~0, ~0, 12, 144, 16, 17, 87, 149, 144, 12, ~0, ~0, 149, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 102, 86, 86, 86, 86, 86, 86, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 13, 97, ~0, ~0, 16, 13, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 101, 105, 104, 107, 108, 101, 105, 104, 107, 108, 110, 11, 111, 112, 113, 110, 11, 111, 112, 113, 10, ~0, 115, 119, ~0, 10, 9, 115, 119, 8, 116, 9, 122, 121, 8, 116, ~0, 122, 121, 125, ~0, 124, 7, 127, 125, 13, 124, 7, 127, 6, 128, 130, ~0, ~0, 6, 128, 130, 132, 131, 5, 133, ~0, 132, 131, 5, 133, 107, 136, 105, 104, 137, 101, 136, ~0, 138, 137, 140, 108, 11, 138, 139, 140, 141, 135, 143, 139, 146, 141, 135, 143, 113, 146, 110, 112, 9, 111, 4, 10, 115, 116, ~0, 4, 9, 8, 124, 119, 8, ~0, 147, 148, 121, ~0, 122, 147, 148, 145, 7, 128, 150, ~0, 145, 125, 131, 150, 127, 151, 6, 133, 152, 5, 151, 132, 3, 152, 130, 153, 5, 3, ~0, 154, 153, ~0, 155, 136, 154, 138, 135, 155, 156, 141, 157, ~0, 137, 156, ~0, 157, 139, 2, ~0, 140, 158, 4, 2, 146, 143, 158, 4, 159, 160, ~0, ~0, ~0, 159, 160, ~0, ~0, ~0, ~0, 145, ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0, 147, ~0, ~0, 148, ~0, 151, 150, ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0, 153, ~0, ~0, ~0, ~0, ~0, 3, ~0, ~0, 154, 156, ~0, ~0, ~0, 2, ~0, ~0, ~0, 155, ~0, ~0, ~0, ~0, ~0, ~0, 158, ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0, 159, 
};

static yy_state_t       yy_default[]   =
{
   163, 163, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 163, 18, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 21, 163, 21, 20, 163, 163, 163, 163, 163, 74, 18, 163, 163, 163, 80, 163, 163, 163, 163, 163, 163, 163, 163, 86, 163, 163, 16, 16, 19, 21, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 163, 163, 
};

static short            yy_base[]      =
{
   0, 128, 1147, 1122, 1086, 1049, 1039, 1032, 1019, 1016, 1010, 1001, 824, 958, 822, 132, 901, 821, 788, 450, 108, 194, 79, 77, 93, 90, 73, 72, 94, 70, 69, 68, 67, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 1268, 78, 1268, 1268, 81, 1268, 1268, 322, 1268, 1268, 1268, 73, 1268, 1268, 706, 578, 1268, 1268, 1268, 1268, 1268, 798, 74, 1268, 1268, 1268, 1268, 863, 834, 1268, 1268, 69, 1268, 1268, 114, 113, 1268, 1268, 888, 826, 823, 133, 990, 859, 134, 992, 991, 135, 993, 994, 144, 1000, 1002, 1003, 1004, 145, 1012, 1020, 146, 148, 1013, 147, 1023, 1022, 858, 1031, 1029, 860, 1033, 1040, 867, 1041, 1048, 1047, 1050, 868, 1073, 1057, 1060, 1064, 1070, 1066, 1072, 869, 1074, 905, 1105, 1076, 1098, 1099, 909, 1108, 1115, 1118, 1125, 1129, 1132, 1138, 1140, 1150, 1157, 1158, 1268, 1268, 1268
};


#line 1 // "D:\YACC/etc/yylex.c"
/*
* Copyright 1988, 1990 by Mortice Kern Systems Inc. All rights reserved.
* All rights reserved.
*/
#include <stdlib.h>
#include <stdio.h>
/*
* Define gettext() to an appropriate function for internationalized messages
* or custom processing.
*/
#if __STDC__
#define YY_ARGS(args) args
#else
#define YY_ARGS(args) ()
#endif

#ifndef I18N
#define gettext(s) (s)
#endif
/*
* Include string.h to get definition of memmove() and size_t.
* If you do not have string.h or it does not declare memmove
* or size_t, you will have to declare them here.
*/
#include <string.h>
/* Uncomment next line if memmove() is not declared in string.h */
/*extern char * memmove();*/
/* Uncomment next line if size_t is not available in stdio.h or string.h */
/*typedef unsigned size_t;*/
/* Drop this when LATTICE provides memmove */
#ifdef LATTICE
#define memmove memcopy
#endif

/*
* YY_STATIC determines the scope of variables and functions
* declared by the lex scanner. It must be set with a -DYY_STATIC
* option to the compiler (it cannot be defined in the lex program).
*/
#ifdef YY_STATIC
/* define all variables as static to allow more than one lex scanner */
#define YY_DECL static
#else
/* define all variables as global to allow other modules to access them */
#define YY_DECL
#endif

/*
* You can redefine yygetc. For YACC Tracing, compile this code
* with -DYYTRACE to get input from yt_getc
*/
#ifdef YYTRACE
extern int yt_getc      YY_ARGS((void));
#define yygetc() yt_getc()
#else
#define yygetc() getc(yyin) /* yylex input source */
#endif

/*
* the following can be redefined by the user.
*/
#define ECHO fputs(yytext, yyout)
#define output(c) putc((c), yyout) /* yylex sink for unmatched chars */
#define YY_FATAL(msg) { fprintf(stderr, "yylex: %s\n", msg); exit(1); }
#define YY_INTERACTIVE 1 /* save micro-seconds if 0 */
#define YYLMAX 100 /* token and pushback buffer size */

/*
* the following must not be redefined.
*/
#define yy_tbuf yytext /* token string */

#define BEGIN yy_start =
#define REJECT goto yy_reject
#define NLSTATE (yy_lastc = YYNEWLINE)
#define YY_INIT \
(yy_start = yyleng = yy_end = 0, yy_lastc = YYNEWLINE)
#define yymore() goto yy_more
#define yyless(n) if ((n) < 0 || (n) > yy_end) ; \
else { YY_SCANNER; yyleng = (n); YY_USER; }

YY_DECL void yy_reset   YY_ARGS((void));
YY_DECL int input       YY_ARGS((void));
YY_DECL int unput       YY_ARGS((int c));

/* functions defined in libl.lib */
extern int yywrap       YY_ARGS((void));
// extern void yyerror YY_ARGS((char *fmt, ...));
extern void             yyerror(char* s);
extern void yycomment   YY_ARGS((char* term));
extern int yymapch      YY_ARGS((int delim, int escape));

#line 34 // "ci.l"

#include <stdio.h>
#include "interpreter.h"
#include "abstract_syntax_tree.h"
#include "symbol_table.h"
#include "YY_PARSE.H"

void                    count();
static void             comment();

#line 92 // "D:\YACC/etc/yylex.c"


#ifdef YY_DEBUG
#undef YY_DEBUG
#define YY_DEBUG(fmt, a1, a2) fprintf(stderr, fmt, a1, a2)
#else
#define YY_DEBUG(fmt, a1, a2)
#endif

/*
* The declaration for the lex scanner can be changed by
* redefining YYLEX or YYDECL. This must be done if you have
* more than one scanner in a program.
*/
#ifndef YYLEX
#define YYLEX yylex /* name of lex scanner */
#endif

#ifndef YYDECL
#define YYDECL int YYLEX YY_ARGS((void)) /* declaration for lex scanner */
#endif

/* stdin and stdout may not neccessarily be constants */
YY_DECL FILE*           yyin     = stdin;
YY_DECL FILE*           yyout    = stdout;
YY_DECL int             yylineno = 1; /* line number */

/*
* yy_tbuf is an alias for yytext.
* yy_sbuf[0:yyleng-1] contains the states corresponding to yy_tbuf.
* yy_tbuf[0:yyleng-1] contains the current token.
* yy_tbuf[yyleng:yy_end-1] contains pushed-back characters.
* When the user action routine is active,
* yy_save contains yy_tbuf[yyleng], which is set to '\0'.
* Things are different when YY_PRESERVE is defined.
*/

YY_DECL char            yy_tbuf[YYLMAX + 1]; /* text buffer (really yytext) */
static yy_state_t       yy_sbuf[YYLMAX + 1]; /* state buffer */

static int              yy_end   = 0; /* end of pushback */
static int              yy_start = 0; /* start state */
static int              yy_lastc = YYNEWLINE; /* previous char */
YY_DECL int             yyleng   = 0; /* yytext token length */

#ifndef YY_PRESERVE /* the efficient default push-back scheme */

static char             yy_save; /* saved yytext[yyleng] */

#define YY_USER { /* set up yytext for user */ \
yy_save = yytext[yyleng]; \
yytext[yyleng] = 0; \
}
#define YY_SCANNER { /* set up yytext for scanner */ \
yytext[yyleng] = yy_save; \
}

#else /* not-so efficient push-back for yytext mungers */

static char             yy_save[YYLMAX];
static char*            yy_push  = yy_save + YYLMAX;

#define YY_USER { \
size_t n = yy_end - yyleng; \
yy_push = yy_save+YYLMAX - n; \
if (n > 0) \
memmove(yy_push, yytext+yyleng, n); \
yytext[yyleng] = 0; \
}
#define YY_SCANNER { \
size_t n = yy_save+YYLMAX - yy_push; \
if (n > 0) \
memmove(yytext+yyleng, yy_push, n); \
yy_end = yyleng + n; \
}

#endif

/*
* The actual lex scanner (usually yylex(void)).
* NOTE: you should invoke yy_init() if you are calling yylex()
* with new input; otherwise old lookaside will get in your way
* and yylex() will die horribly.
*/
YYDECL
{
   register int c, i, yyst, yybase;
   int   yyfmin, yyfmax; /* yy_la_act indices of final states */
   int   yyoldi, yyoleng; /* base i, yyleng before look-ahead */
   int   yyeof; /* 1 if eof has already been read */

   #line 181 // "D:\YACC/etc/yylex.c"

   yyeof = 0;
   i = yyleng;    
   YY_SCANNER;

   yy_again:
   yyleng = i;
   /* determine previous char. */
   if (i > 0)
   {
      yy_lastc = yytext[i - 1];
   }
   /* scan previously accepted token adjusting yylineno */
   while (i > 0)
   {
      if (yytext[--i] == YYNEWLINE)
      {
         yylineno++;
      }
   }
   /* adjust pushback */
   yy_end -= yyleng;
   memmove(yytext,yytext + yyleng,(size_t) yy_end);
   i = 0;

   yy_contin:
   yyoldi = i;

   /* run the state machine until it jams */
   yy_sbuf[i] = yyst = yy_begin[yy_start + (yy_lastc == YYNEWLINE)];
   do
   {
      YY_DEBUG(gettext("<state %d, i = %d>\n"),yyst,i);
      if (i >= YYLMAX)
      {
         YY_FATAL(gettext("Token buffer overflow"));
      }

      /* get input char */
      if (i < yy_end)
      {
         c = yy_tbuf[i];
      } /* get pushback char */
      else if (!yyeof && (c = yygetc()) != EOF)
      {
         yy_end = i + 1;
         yy_tbuf[i] = c;
      }
      else /* c == EOF */
      {
         c = EOF; /* just to make sure... */
         if (i == yyoldi)
         {
            /* no token */
            yyeof = 0;
            if (yywrap())
            {
               return 0;
            }
            else
            {
               goto yy_again;
            }
         }
         else
         {
            yyeof = 1; /* don't re-read EOF */
            break;
         }
      }
      YY_DEBUG(gettext("<input %d = 0x%02x>\n"),c,c);

      /* look up next state */
      while ((yybase = yy_base[yyst] + c) > yy_nxtmax || yy_check[yybase] != yyst)
      {
         if (yyst == yy_endst)
         {
            goto yy_jammed;
         }
         yyst = yy_default[yyst];
      }
      yyst = yy_next[yybase];
      yy_jammed: ;
      yy_sbuf[++i] = yyst;
   }
   while (!(yyst == yy_endst || YY_INTERACTIVE && yy_base[yyst] > yy_nxtmax && yy_default[yyst] == yy_endst));
   YY_DEBUG(gettext("<stopped %d, i = %d>\n"),yyst,i);
   if (yyst != yy_endst)
   {
      ++i;
   }

   yy_search:
   /* search backward for a final state */
   while (--i > yyoldi)
   {
      yyst = yy_sbuf[i];
      if ((yyfmin = yy_final[yyst]) < (yyfmax = yy_final[yyst + 1]))
      {
         goto yy_found;
      } /* found final state(s) */
   }
   /* no match, default action */
   i = yyoldi + 1;
   output(yy_tbuf[yyoldi]);
   goto yy_again;

   yy_found:
   YY_DEBUG(gettext("<final state %d, i = %d>\n"),yyst,i);
   yyoleng = i; /* save length for REJECT */

   /* pushback look-ahead RHS */
   if ((c = (int) (yy_la_act[yyfmin] >> 9) - 1) >= 0)
   {
      /* trailing context? */
      unsigned char * bv = yy_look + c * YY_LA_SIZE;
      static unsigned char bits[8]  =
      {
         1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7
      };
      while (1)
      {
         if (--i < yyoldi)
         {
            /* no / */
            i = yyoleng;
            break;
         }
         yyst = yy_sbuf[i];
         if (bv[(unsigned) yyst / 8] & bits[(unsigned) yyst % 8])
         {
            break;
         }
      }
   }

   /* perform action */
   yyleng = i;    
   YY_USER;
   switch (yy_la_act[yyfmin] & 0777)
   {
      case 0:
         #line 46 // "ci.l"
         {
            comment();
         }
         break;
      case 1:
         #line 48 // "ci.l"
         {
            count(); return(MAIN_FUNCTION);
         }
         break;
      case 2:
         #line 49 // "ci.l"
         {
            count(); return(LIB_PRINTF);
         }
         break;
      case 3:
         #line 50 // "ci.l"
         {
            count(); return(LIB_SCANF);
         }
         break;
      case 4:
         #line 52 // "ci.l"
         {
            count(); return(CHAR_TYPE);
         }
         break;
      case 5:
         #line 53 // "ci.l"
         {
            count(); return(DOUBLE_TYPE);
         }
         break;
      case 6:
         #line 54 // "ci.l"
         {
            count(); return(ELSE);
         }
         break;
      case 7:
         #line 55 // "ci.l"
         {
            count(); return(FLOAT_TYPE);
         }
         break;
      case 8:
         #line 56 // "ci.l"
         {
            count(); return(FOR);
         }
         break;
      case 9:
         #line 57 // "ci.l"
         {
            count(); return(IF);
         }
         break;
      case 10:
         #line 58 // "ci.l"
         {
            count(); return(INT_TYPE);
         }
         break;
      case 11:
         #line 59 // "ci.l"
         {
            count(); return(LONG_TYPE);
         }
         break;
      case 12:
         #line 60 // "ci.l"
         {
            count(); return(RETURN);
         }
         break;
      case 13:
         #line 61 // "ci.l"
         {
            count(); return(BREAK);
         }
         break;
      case 14:
         #line 62 // "ci.l"
         {
            count(); return(CONTINUE);
         }
         break;
      case 15:
         #line 63 // "ci.l"
         {
            count(); return(SHORT_TYPE);
         }
         break;
      case 16:
         #line 64 // "ci.l"
         {
            count(); return(VOID_TYPE);
         }
         break;
      case 17:
         #line 65 "ci.l"
         {
            count(); return(WHILE);
         }
         break;
      case 18:
         #line 67 "ci.l"
         {
            err_msg = "";err();
         }/*ci command to exit interactive session. This will be changed later. Usage in scripts should be avoided.*/
         break;
      case 19:
         #line 69 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(IDENTIFIER);
         }
         break;
      case 20:
         #line 71 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(HEX_INT_CONSTANT);
         }
         break;
      case 21:
         #line 72 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(HEX_LONG_CONSTANT);
         }
         break;
      case 22:
         #line 73 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(HEX_INT_CONSTANT);
         }
         break;
      case 23:
         #line 74 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(HEX_LONG_CONSTANT);
         }
         break;
      case 24:
         #line 75 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(DEC_INT_CONSTANT);
         }
         break;
      case 25:
         #line 76 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(DEC_LONG_CONSTANT);
         }
         break;
      case 26:
         #line 77 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(CHAR_CONSTANT);
         }
         break;
      case 27:
         #line 79 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(DOUBLE_CONSTANT);
         }
         break;
      case 28:
         #line 80 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(FLOAT_CONSTANT);
         }
         break;
      case 29:
         #line 81 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(DOUBLE_CONSTANT);
         }
         break;
      case 30:
         #line 82 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(FLOAT_CONSTANT);
         }
         break;
      case 31:
         #line 84 "ci.l"
         {
            count(); yylval.string = strdup(yytext); return(STRING_LITERAL);
         }
         break;
      case 32:
         #line 86 "ci.l"
         {
            count(); return(RIGHT_ASSIGN);
         }
         break;
      case 33:
         #line 87 "ci.l"
         {
            count(); return(LEFT_ASSIGN);
         }
         break;
      case 34:
         #line 88 "ci.l"
         {
            count(); return(ADD_ASSIGN);
         }
         break;
      case 35:
         #line 89 "ci.l"
         {
            count(); return(SUB_ASSIGN);
         }
         break;
      case 36:
         #line 90 "ci.l"
         {
            count(); return(MUL_ASSIGN);
         }
         break;
      case 37:
         #line 91 "ci.l"
         {
            count(); return(DIV_ASSIGN);
         }
         break;
      case 38:
         #line 92 "ci.l"
         {
            count(); return(MOD_ASSIGN);
         }
         break;
      case 39:
         #line 93 "ci.l"
         {
            count(); return(AND_ASSIGN);
         }
         break;
      case 40:
         #line 94 "ci.l"
         {
            count(); return(XOR_ASSIGN);
         }
         break;
      case 41:
         #line 95 "ci.l"
         {
            count(); return(OR_ASSIGN);
         }
         break;
      case 42:
         #line 96 "ci.l"
         {
            count(); return(RIGHT_SHIFT_OP);
         }
         break;
      case 43:
         #line 97 "ci.l"
         {
            count(); return(LEFT_SHIFT_OP);
         }
         break;
      case 44:
         #line 98 "ci.l"
         {
            count(); return(INC_OP);
         }
         break;
      case 45:
         #line 99 "ci.l"
         {
            count(); return(DEC_OP);
         }
         break;
      case 46:
         #line 100 "ci.l"
         {
            count(); return(AND_OP);
         }
         break;
      case 47:
         #line 101 "ci.l"
         {
            count(); return(OR_OP);
         }
         break;
      case 48:
         #line 102 "ci.l"
         {
            count(); return(LE_OP);
         }
         break;
      case 49:
         #line 103 "ci.l"
         {
            count(); return(GE_OP);
         }
         break;
      case 50:
         #line 104 "ci.l"
         {
            count(); return(EQ_OP);
         }
         break;
      case 51:
         #line 105 "ci.l"
         {
            count(); return(NE_OP);
         }
         break;
      case 52:
         #line 106 "ci.l"
         {
            count(); return(';');
         }
         break;
      case 53:
         #line 107 "ci.l"
         {
            count(); return('{');
         }
         break;
      case 54:
         #line 108 "ci.l"
         {
            count(); return('}');
         }
         break;
      case 55:
         #line 109 "ci.l"
         {
            count(); return(',');
         }
         break;
      case 56:
         #line 110 "ci.l"
         {
            count(); return(':');
         }
         break;
      case 57:
         #line 111 "ci.l"
         {
            count(); return('=');
         }
         break;
      case 58:
         #line 112 "ci.l"
         {
            count(); return('(');
         }
         break;
      case 59:
         #line 113 "ci.l"
         {
            count(); return(')');
         }
         break;
      case 60:
         #line 114 "ci.l"
         {
            count(); return('[');
         }
         break;
      case 61:
         #line 115 "ci.l"
         {
            count(); return(']');
         }
         break;
      case 62:
         #line 116 "ci.l"
         {
            count(); return('.');
         }
         break;
      case 63:
         #line 117 "ci.l"
         {
            count(); return('&');
         }
         break;
      case 64:
         #line 118 "ci.l"
         {
            count(); return('!');
         }
         break;
      case 65:
         #line 119 "ci.l"
         {
            count(); return('~');
         }
         break;
      case 66:
         #line 120 "ci.l"
         {
            count(); return('-');
         }
         break;
      case 67:
         #line 121 "ci.l"
         {
            count(); return('+');
         }
         break;
      case 68:
         #line 122 "ci.l"
         {
            count(); return('*');
         }
         break;
      case 69:
         #line 123 "ci.l"
         {
            count(); return('/');
         }
         break;
      case 70:
         #line 124 "ci.l"
         {
            count(); return('%');
         }
         break;
      case 71:
         #line 125 "ci.l"
         {
            count(); return('<');
         }
         break;
      case 72:
         #line 126 "ci.l"
         {
            count(); return('>');
         }
         break;
      case 73:
         #line 127 "ci.l"
         {
            count(); return('^');
         }
         break;
      case 74:
         #line 128 "ci.l"
         {
            count(); return('|');
         }
         break;
      case 75:
         #line 129 "ci.l"
         {
            count(); return('?');
         }
         break;
      case 76:
         #line 131 "ci.l"
         {
            count();
         }
         break;
      case 77:
         #line 132 "ci.l"
         {
            /* ignore bad characters */
         }
         break;

         #line 283 "D:\YACC/etc/yylex.c"
   }     
   YY_SCANNER;
   i = yyleng;
   goto yy_again; /* action fell though */

   yy_reject:     
   YY_SCANNER;
   i = yyoleng; /* restore original yytext */
   if (++yyfmin < yyfmax)
   {
      goto yy_found;
   } /* another final state, same length */
   else
   {
      goto yy_search;
   } /* try shorter yytext */

   yy_more:    
   YY_SCANNER;
   i = yyleng;
   if (i > 0)
   {
      yy_lastc = yytext[i - 1];
   }
   goto yy_contin;
}
/*
* Safely switch input stream underneath LEX
*/
typedef struct yy_save_block_tag
{
   FILE*       oldfp;
   int         oldline;
   int         oldend;
   int         oldstart;
   int         oldlastc;
   int         oldleng;
   char        savetext[YYLMAX + 1];
   yy_state_t  savestate[YYLMAX + 1];
} YY_SAVED;

YY_SAVED* yySaveScan(FILE* fp)
{
   YY_SAVED*   p;

   if ((p = (YY_SAVED *) malloc(sizeof(*p))) == NULL)
   {
      return p;
   }

   p->oldfp = yyin;
   p->oldline = yylineno;
   p->oldend = yy_end;
   p->oldstart = yy_start;
   p->oldlastc = yy_lastc;
   p->oldleng = yyleng;
   (void) memcpy(p->savetext,yytext,sizeof yytext);
   (void) memcpy((char *) p->savestate,(char *) yy_sbuf,sizeof yy_sbuf);

   yyin = fp;
   yylineno = 1;     
   YY_INIT;

   return p;
}
/*f
* Restore previous LEX state
*/
void yyRestoreScan(YY_SAVED* p)
{
   if (p == NULL)
   {
      return;
   }
   yyin = p->oldfp;
   yylineno = p->oldline;
   yy_end = p->oldend;
   yy_start = p->oldstart;
   yy_lastc = p->oldlastc;
   yyleng = p->oldleng;

   (void) memcpy(yytext,p->savetext,sizeof yytext);
   (void) memcpy((char *) yy_sbuf,(char *) p->savestate,sizeof yy_sbuf);
   free(p);
}
/*
* User-callable re-initialization of yylex()
*/
void yy_reset()
{
   YY_INIT;
   yylineno = 1; /* line number */
}
/* get input char with pushback */
YY_DECL int input()
{
   int   c;
   #ifndef YY_PRESERVE
   if (yy_end > yyleng)
   {
      yy_end--;
      memmove(yytext + yyleng,yytext + yyleng + 1,(size_t) (yy_end - yyleng));
      c = yy_save;      
      YY_USER;
      #else
      if (yy_push < yy_save + YYLMAX)
      {
         c = *yy_push++;
         #endif
      }
      else
      {
         c = yygetc();
      }
      yy_lastc = c;
      if (c == YYNEWLINE)
      {
         yylineno++;
      }
      return c;
   }

   /*f
   * pushback char
   */
   YY_DECL int unput(int c)
   {
      #ifndef YY_PRESERVE
      if (yy_end >= YYLMAX)
      {
         YY_FATAL(gettext("Push-back buffer overflow"));
      }
      if (yy_end > yyleng)
      {
         yytext[yyleng] = yy_save;
         memmove(yytext + yyleng + 1,yytext + yyleng,(size_t) (yy_end - yyleng));
         yytext[yyleng] = 0;
      }
      yy_end++;
      yy_save = c;
      #else
      if (yy_push <= yy_save)
      {
         YY_FATAL(gettext("Push-back buffer overflow"));
      }
      *--yy_push = c;
      #endif
      if (c == YYNEWLINE)
      {
         yylineno--;
      }
      return c;
   }

   #line 135 // "ci.l"

   yywrap()
   {
      return(1);
   }


   static void comment(void)
   {
      int   c;

      while ((c = input()) != 0)
      {
         if (c == '*')
         {
            while ((c = input()) == '*')
            ;

            if (c == '/')
            {
               return;
            }

            if (c == 0)
            {
               break;
            }
         }
      }
      yyerror("Unterminated comment");
   }


   int   row      = 1;
   int   column   = 0;

   void  count    () {
   int i;
   for (i = 0; yytext[i] != '\0'; i++)
   {
      if (yytext[i] == '\n')
      {
         row++;
         column = 0;
      }
      else if (yytext[i] == '\t')
      {
         column += 8 - (column % 8);
      }
      else
      {
         column++;
      }
   }
}
