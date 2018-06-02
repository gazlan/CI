#include "stdafx.h"

#include "abstract_syntax_tree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void  print_prompt();
int   eval_global_var_decl(ast global_decl);

// d:\yacc\bin\yacc -o yy_parse.c -D yy_parse.h ci.y
#ifdef YYTRACE
#define YYDEBUG 1
#else
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#endif
/*
* Portable way of defining ANSI C prototypes
*/
#ifndef YY_ARGS
#if __STDC__
#define YY_ARGS(x) x
#else
#define YY_ARGS(x) ()
#endif
#endif

#if YYDEBUG
typedef struct yyNamedType_tag
{
   /* Tokens */
   char* name; /* printable name */
   short token; /* token # */
   short type; /* token type */
} yyNamedType;
typedef struct yyTypedRules_tag
{
   /* Typed rule table */
   char* name; /* compressed rule string */
   short type; /* rule result type */
} yyTypedRules;

#endif

#line 28 "ci.y"

#include <stdio.h>
#include "interpreter.h"
#include "abstract_syntax_tree.h"
#include "ast_builder.h"
#include "ast_evaluator.h"
#include "symbol_table.h"
#include "vm.h"

#define main_interact_env (_main_env_ && _interact_env_)
#define stmt_exec_env (main_interact_env && !_block_stmt)
#define ctrl_stmt_exec_env (main_interact_env && (_block_stmt == 1))

#define is_inc_block_count {if(main_interact_env) _block_stmt++;}
#define is_dec_block_count {if(main_interact_env) _block_stmt--;}

#define is_exec_return_stmt {if(stmt_exec_env) return 0;}
#define is_check_return_env {if(main_interact_env && CONTEXT_RETURN_VALUE != NULL) return 0;}

void  is_eval_stmt(ast node);
void  is_hndlr(ast node);
//#define YYDEBUG 1
typedef union
{
   ast               node;
   char              unary_code;
   char*             string;
   assignment_code   assign_code;
} YYSTYPE;
#define MAIN_FUNCTION 257
#define LIB_PRINTF 258
#define LIB_SCANF 259
#define CHAR_CONSTANT 260
#define HEX_INT_CONSTANT 261
#define OCT_INT_CONSTANT 262
#define DEC_INT_CONSTANT 263
#define HEX_LONG_CONSTANT 264
#define OCT_LONG_CONSTANT 265
#define DEC_LONG_CONSTANT 266
#define FLOAT_CONSTANT 267
#define DOUBLE_CONSTANT 268
#define IDENTIFIER 269
#define STRING_LITERAL 270
#define INC_OP 271
#define DEC_OP 272
#define LEFT_SHIFT_OP 273
#define RIGHT_SHIFT_OP 274
#define LE_OP 275
#define GE_OP 276
#define EQ_OP 277
#define NE_OP 278
#define AND_OP 279
#define OR_OP 280
#define MUL_ASSIGN 281
#define DIV_ASSIGN 282
#define MOD_ASSIGN 283
#define ADD_ASSIGN 284
#define SUB_ASSIGN 285
#define LEFT_ASSIGN 286
#define RIGHT_ASSIGN 287
#define AND_ASSIGN 288
#define XOR_ASSIGN 289
#define OR_ASSIGN 290
#define CHAR_TYPE 291
#define SHORT_TYPE 292
#define INT_TYPE 293
#define LONG_TYPE 294
#define FLOAT_TYPE 295
#define DOUBLE_TYPE 296
#define VOID_TYPE 297
#define IF 298
#define ELSE 299
#define WHILE 300
#define FOR 301
#define CONTINUE 302
#define BREAK 303
#define RETURN 304
#define LOWER_THAN_ELSE 305
extern int        yychar, yyerrflag;
extern YYSTYPE    yylval;
#if YYDEBUG
enum YY_Types
{
   YY_t_NoneDefined,
   YY_t_string,
   YY_t_node,
   YY_t_unary_code,
   YY_t_assign_code
};
#endif
#if YYDEBUG
yyTypedRules   yyRules[]      =
{
   { "&00: %38 &00", 0}, { "%01: &05", 2}, { "%01: &06", 2}, { "%01: &07", 2}, { "%01: &08", 2}, { "%01: &12", 2}, { "%01: &13", 2}, { "%01: &09", 2}, { "%01: &10", 2}, { "%01: &11", 2}, { "%02: &42", 2}, { "%02: &36", 2}, { "%02: &37", 2}, { "%02: &38", 2}, { "%02: &40", 2}, { "%02: &41", 2}, { "%02: &39", 2}, { "%02: &42 &51", 2}, { "%02: &36 &51", 2}, { "%02: &37 &51", 2}, { "%02: &38 &51", 2}, { "%02: &40 &51", 2}, { "%02: &41 &51", 2}, { "%02: &39 &51", 2}, { "%02: &42 &51 &51", 2}, { "%02: &36 &51 &51", 2}, { "%02: &37 &51 &51", 2}, { "%02: &38 &51 &51", 2}, { "%02: &40 &51 &51", 2}, { "%02: &41 &51 &51", 2}, { "%02: &39 &51 &51", 2}, { "%03: &14", 2}, { "%03: %01", 2}, { "%03: &15", 2}, { "%03: &52 %19 &53", 2}, { "%04: %03", 2}, { "%04: &14 &54 %19 &55", 2}, { "%04: &14 &54 %19 &55 &54 %19 &55", 2}, { "%04: %33", 2}, { "%04: %46", 2}, { "%04: %47", 2}, { "%04: %04 &16", 2}, { "%04: %04 &17", 2}, { "%05: %04", 2}, { "%05: &16 %05", 2}, { "%05: &17 %05", 2}, { "%05: %50 %06", 2}, { "%50: &56", 3}, { "%50: &51", 3}, { "%50: &57", 3}, { "%50: &58", 3}, { "%50: &59", 3}, { "%06: %05", 2}, { "%06: &52 %02 &53 %06", 2}, { "%07: %06", 2}, { "%07: %07 &51 %06", 2}, { "%07: %07 &60 %06", 2}, { "%07: %07 &61 %06", 2}, { "%08: %07", 2}, { "%08: %08 &62 %07", 2}, { "%08: %08 &57 %07", 2}, { "%09: %08", 2}, { "%09: %09 &18 %08", 2}, { "%09: %09 &19 %08", 2}, { "%10: %09", 2}, { "%10: %10 &63 %09", 2}, { "%10: %10 &64 %09", 2}, { "%10: %10 &20 %09", 2}, { "%10: %10 &21 %09", 2}, { "%11: %10", 2}, { "%11: %11 &22 %10", 2}, { "%11: %11 &23 %10", 2}, { "%12: %11", 2}, { "%12: %12 &56 %11", 2}, { "%13: %12", 2}, { "%13: %13 &65 %12", 2}, { "%14: %13", 2}, { "%14: %14 &66 %13", 2}, { "%15: %14", 2}, { "%15: %15 &24 %14", 2}, { "%16: %15", 2}, { "%16: %16 &25 %15", 2}, { "%17: %16", 2}, { "%17: %16 &67 %19 &68 %17", 2}, { "%18: %17", 2}, { "%18: %05 %51 %18", 2}, { "%51: &69", 4}, { "%51: &26", 4}, { "%51: &27", 4}, { "%51: &28", 4}, { "%51: &29", 4}, { "%51: &30", 4}, { "%51: &31", 4}, { "%51: &32", 4}, { "%51: &33", 4}, { "
%51: &34", 4}, { "%51: &35", 4}, { "%19: %18", 2}, { "%19: %19 &70 %18", 2}, { "%20: %17", 2}, { "%21: %18", 2}, { "%21: &71 %39 &72", 2}, { "%39: %21", 2}, { "%39: %39 &70 %21", 2}, { "%22: &14", 2}, { "%22: &14 &54 %20 &55", 2}, { "%22: &14 &54 %20 &55 &54 %20 &55", 2}, { "%23: %22", 2}, { "%23: %22 &69 %21", 2}, { "%40: %23", 2}, { "%40: %40 &70 %23", 2}, { "%24: %02 %40 &73", 2}, { "%42: %24", 2}, { "%42: %42 %24", 2}, { "%25: %26", 2}, { "%25: %27", 2}, { "%25: %28", 2}, { "%25: %29", 2}, { "%25: %30", 2}, { "%43: %25", 2}, { "%43: %43 %25", 2}, { "%27: &73", 2}, { "%27: %19 &73", 2}, { "%41: &43", 2}, { "%28: %41 &52 %19 &53 %25", 2}, { "%28: %41 &52 %19 &53 %25 &44 %25", 2}, { "%48: &45", 2}, { "%49: &46", 2}, { "%29: %48 &52 %19 &53 %25", 2}, { "%29: %49 &52 %27 %27 &53 %25", 2}, { "%29: %49 &52 %27 %27 %19 &53 %25", 2}, { "%30: &49 &73", 2}, { "%30: &49 %19 &73", 2}, { "%30: &48 &73", 2}, { "%30: &47 &73", 2}, { "%26: &71 &72", 2}, { "%26: &71 %43 &72", 2}, { "%26: &71 %42 &72", 2}, { "%26: &71 %42 %43 &72", 2}, { "%44:", 2}, { "%44: %31", 2}, { "%44: %44 &70 %31", 2}, { "%31: %02 &14", 2}, { "%32: %02 &14 &52 %44 &53 %26", 2}, { "%33: &14 &52 %45 &53", 2}, { "%46: &03 &52 %45 &53", 2}, { "%47: &04 &52 %45 &53", 2}, { "%45:", 2}, { "%45: %18", 2}, { "%45: %45 &70 %18", 2}, { "%34: %32", 2}, { "%34: %24", 2}, { "%35: &38 &02 &52 &53", 2}, { "%36: %35 %26", 2}, { "%37: %34", 2}, { "%37: %37 %34", 2}, { "%38: %36", 2}, { "%38: %37 %36", 2}, { "$accept", 0}, { "error", 0}
};
yyNamedType    yyTokenTypes[] =
{
   { "$end", 0, 0}, { "error", 256, 0}, { "MAIN_FUNCTION", 257, 0}, { "LIB_PRINTF", 258, 0}, { "LIB_SCANF", 259, 0}, { "CHAR_CONSTANT", 260, 1}, { "HEX_INT_CONSTANT", 261, 1}, { "OCT_INT_CONSTANT", 262, 1}, { "DEC_INT_CONSTANT", 263, 1}, { "HEX_LONG_CONSTANT", 264, 1}, { "OCT_LONG_CONSTANT", 265, 1}, { "DEC_LONG_CONSTANT", 266, 1}, { "FLOAT_CONSTANT", 267, 1}, { "DOUBLE_CONSTANT", 268, 1}, { "IDENTIFIER", 269, 1}, { "STRING_LITERAL", 270, 1}, { "INC_OP", 271, 0}, { "DEC_OP", 272, 0}, { "LEFT_SHIFT_OP", 273, 0}, { "RIGHT_SHIFT_OP", 274, 0}, { "LE_OP", 275, 0}, { "GE_OP", 276, 0}, { "EQ_OP", 277, 0}, { "NE_OP", 278, 0}, { "AND_OP", 279, 0}, { "OR_OP", 280, 0}, { "MUL_ASSIGN", 281, 0}, { "DIV_ASSIGN", 282, 0}, { "MOD_ASSIGN", 283, 0}, { "ADD_ASSIGN", 284, 0}, { "SUB_ASSIGN", 285, 0}, { "LEFT_ASSIGN", 286, 0}, { "RIGHT_ASSIGN", 287, 0}, { "AND_ASSIGN", 288, 0}, { "XOR_ASSIGN", 289, 0}, { "OR_ASSIGN", 290, 0}, { "CHAR_TYPE", 291, 0}, { "SHORT_TYPE", 292, 0}, { "INT_TYPE", 293, 0}, { "LONG_TYPE", 294, 0}, { "FLOAT_TYPE", 295, 0}, { "DOUBLE_TYPE", 296, 0}, { "VOID_TYPE", 297, 0}, { "IF", 298, 0}, { "ELSE", 299, 0}, { "WHILE", 300, 0}, { "FOR", 301, 0}, { "CONTINUE", 302, 0}, { "BREAK", 303, 0}, { "RETURN", 304, 0}, { "LOWER_THAN_ELSE", 305, 0}, { "'*'", 42, 0}, { "'('", 40, 0}, { "')'", 41, 0}, { "'['", 91, 0}, { "']'", 93, 0}, { "'&'", 38, 0}, { "'-'", 45, 0}, { "'~'", 126, 0}, { "'!'", 33, 0}, { "'/'", 47, 0}, { "'%'", 37, 0}, { "'+'", 43, 0}, { "'<'", 60, 0}, { "'>'", 62, 0}, { "'^'", 94, 0}, { "'|'", 124, 0}, { "'?'", 63, 0}, { "':'", 58, 0}, { "'='", 61, 0}, { "','", 44, 0}, { "'{'", 123, 0}, { "'}'", 125, 0}, { "';'", 59, 0}
};
#endif
static short   yydef[]        =
{
   9, 8, 7, 6, 5, 4, 3, -1, 47, 45, 16, 15, 14, 13, 12, 11, 10, 44, 42, 40, 38, 36, 34, 31, 26, 23, 20, 125, 19, 17, 6, -5, -11, -17, 45, -23, 43, 41, 39, 37, 35, 33, 32, 30, 29, 28, 27, 25, 24, 22, 21, 46, 18, 48
};
static short   yyex[]         =
{
   0, 0, -1, 1, 41, 49, 44, 49, -1, 1, 41, 50, 44, 50, -1, 1, 41, 50, 44, 50, -1, 1, 41, 50, 44, 50, -1, 1
};
static short   yyact[]        =
{
   -6, -5, -4, -1, -3, -2, -7, 297, 296, 295, 294, 293, 292, 291, -137, 123, -10, 269, -11, 42, -12, 42, -13, 42, -14, -135, 257, 42, -15, 42, -16, 42, -17, 42, -217, -221, -119, -220, -219, -175, -137, -162, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, -6, -5, -31, -1, -3, -2, -7, -173, -171, -170, -132, -131, -130, 304, 303, 302, 301, 300, 298, 297, 296, 295, 294, 293, 292, 291, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 125, 123, 59, 45, 42, 40, 38, 33, -118, -185, 59, 44, -117, 61, -32, -116, 91, 40, -235, 42, -236, 42, -237, 42, -115, 40, -238, 42, -239, 42, -240, 42, -241, 42, -33, 40, -34, 40, -163, 59, -164, 59, -217, -221, -119, -220, -219, -166, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 59, 45, 42, 40, 38, 33, -113, 40, -112, 40, -111, 40, -217, -221, -119, -220, -219, -175, -137, -161, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, -173, -171, -170, -132, -131, -130, 304, 303, 302, 301, 300, 298, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 125, 123, 59, 45, 42, 40, 38, 33, -217, -221, -119, -220, -219, -175, -137, -160, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, -6, -5, -31, -1, -3, -2, -7, -173, -171, -170, -132, -131, -130, 304, 303, 302, 301, 300, 298, 297, 296, 295, 294, 293, 292, 291, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 125, 123, 59, 45, 42, 40, 38, 33, -35, 269, -109, -174, 59, 44, -108, -107, 280, 63, -106, 279, -105, 124, -104, 94, -103, 38, -101, -102, 278, 277, -97, -98, -99, -100, 276, 275, 62, 60, -95, -96, 274, 273, -93, -94, 45, 43, -92, -90, -91, 47, 42, 37, -207, -206, -205, -204, -203, -202, -201, -200, -199, -198, -197, 290, 289, 288, 287, 286, 285, 284, 283, 282, 281, 61, -217, -221, -119, -
220, -219, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 45, 42, 40, 38, 33, -217, -221, -88, -220, -219, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 45, 42, 40, 38, 33, -226, -225, 272, 271, -217, -221, -119, -220, -219, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, -6, -5, -31, -1, -3, -2, -7, 297, 296, 295, 294, 293, 292, 291, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 45, 42, 40, 38, 33, -36, -85, 91, 40, -14, 42, -217, -221, -119, -220, -219, -84, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 123, 45, 42, 40, 38, 33, -6, -5, -31, -1, -3, -2, -7, 297, 296, 295, 294, 293, 292, 291, -147, 41, -109, -165, 59, 44, -217, -221, -119, -220, -219, -175, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 59, 45, 42, 40, 38, 33, -217, -221, -119, -220, -219, -175, -137, -159, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, -173, -171, -170, -132, -131, -130, 304, 303, 302, 301, 300, 298, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 125, 123, 59, 45, 42, 40, 38, 33, -116, 91, -74, 41, -232, -109, 44, 41, -156, 269, -70, -69, 44, 41, -52, 93, -152, -68, 44, 41, -153, -68, 44, 41, -66, -109, 44, 41, -65, -109, 44, 41, -109, -64, 58, 44, -154, -68, 44, 41, -109, -53, 93, 44, -63, -192, 125, 44, -62, 91, -217, -221, -119, -61, -220, -219, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, 272, 271, 270, 269, 268,
 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 45, 42, 41, 40, 38, 33, -217, -221, -119, -220, -219, -175, -137, -218, -133, -134, -250, -249, -248, -247, -244, -243, -242, -246, -245, -30, -233, -120, -121, -173, -171, -170, -132, -131, -130, 304, 303, 302, 301, 300, 298, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 126, 123, 59, 45, 42, 40, 38, 33, -59, 91, -57, -109, 44, 41, -56, 299, -189, 93, -109, -230, 93, 44, -1
};
static short   yypact[]       =
{
   19, 21, 23, 26, 29, 31, 33, 34, 113, 116, 119, 121, 123, 127, 129, 131, 133, 334, 337, 339, 341, 343, 346, 352, 358, 362, 367, 381, 478, 538, 541, 593, 413, 413, 711, 413, 337, 339, 341, 343, 346, 352, 352, 358, 358, 358, 358, 362, 362, 367, 367, 759, 863, 869, 874, 833, 833, 871, 413, 866, 833, 413, 564, 413, 833, 833, 782, 413, 593, 15, 756, 752, 748, 413, 744, 740, 736, 628, 732, 728, 725, 722, 719, 564, 413, 716, 713, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 413, 680, 413, 413, 628, 604, 601, 413, 564, 327, 508, 455, 455, 413, 330, 327, 289, 222, 191, 189, 187, 164, 141, 139, 137, 135, 125, 110, 71, 17, 15, 7, 7
};
static short   yygo[]         =
{
   -234, -83, -83, -87, -124, -124, -138, 136, 124, 118, 68, 31, -231, -29, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -216, -224, -223, -216, -28, 121, 120, 119, 115, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 73, 63, 61, -215, -213, -212, -211, -222, -214, 121, 91, 90, 89, 73, -51, -50, -27, 93, 92, -49, -48, -26, 95, 94, -47, -46, -45, -44, -25, 99, 98, 97, 96, -43, -42, -24, 101, 100, -41, -23, 102, -40, -22, 103, -39, -21, 104, -38, -20, 105, -37, -19, 106, -18, -194, -210, -194, -209, 115, 63, 61, -151, -151, -151, -193, -150, -193, -208, -195, -193, -196, 116, 108, 88, 83, 67, 62, 35, 33, 32, -55, -60, -72, -86, -75, -76, -77, -86, -114, -123, 129, 118, 111, 110, 107, 87, 84, 66, 58, -58, -81, 61, -190, -191, -188, 83, 62, -9, -186, -187, 117, -183, -184, -148, 136, 124, -172, -167, -168, -54, -169, -176, -176, -177, 125, 109, 65, 64, 60, 56, 55, -155, -146, -182, 138, 69, -67, -78, -181, 112, 77, -180, -179, -178, -157, -158, 68, -149, -229, -144, -145, 139, -139, -142, -143, 139, -140, -8, -71, -136, -127, -125, -110, -126, 124, -82, -79, -73, -80, 35, 33, -228, -227, -128, -129, -122, -89, -1
};
static short   yypgo[]        =
{
   0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 12, 13, 39, 83, 83, 83, 90, 90, 90, 97, 97, 97, 97, 97, 101, 101, 101, 104, 104, 107, 107, 110, 110, 113, 113, 115, 115, 119, 169, 169, 171, 203, 227, 230, 219, 219, 218, 218, 216, 214, 212, 212, 230, 230, 234, 233, 210, 209, 207, 227, 227, 195, 195, 195, 195, 205, 205, 205, 205, 204, 204, 204, 236, 235, 203, 222, 200, 200, 225, 225, 185, 185, 185, 185, 185, 223, 223, 175, 221, 221, 171, 169, 220, 220, 166, 166, 162, 151, 151, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 132, 132, 119, 78, 78, 78, 78, 70, 70, 237, 237, 237, 237, 237, 39, 39, 39, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
static short   yyrlen[]       =
{
   0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 4, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 4, 1, 5, 0, 0, 2, 1, 2, 1, 2, 4, 1, 1, 3, 1, 4, 4, 4, 6, 2, 3, 1, 4, 3, 3, 2, 2, 2, 3, 2, 7, 6, 5, 1, 1, 7, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 3, 3, 1, 3, 7, 3, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 5, 3, 3, 3, 1, 4, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 7, 1, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2
};
#define YYS0 140
#define YYDELTA 90
#define YYNPACT 141
#define YYNDEF 54

#define YYr158 0
#define YYr159 1
#define YYr160 2
#define YYr10 3
#define YYr11 4
#define YYr12 5
#define YYr13 6
#define YYr14 7
#define YYr15 8
#define YYr16 9
#define YYr17 10
#define YYr18 11
#define YYr19 12
#define YYr20 13
#define YYr21 14
#define YYr22 15
#define YYr23 16
#define YYr31 17
#define YYr36 18
#define YYr43 19
#define YYr58 20
#define YYr59 21
#define YYr60 22
#define YYr61 23
#define YYr62 24
#define YYr63 25
#define YYr64 26
#define YYr65 27
#define YYr66 28
#define YYr67 29
#define YYr68 30
#define YYr69 31
#define YYr70 32
#define YYr71 33
#define YYr72 34
#define YYr73 35
#define YYr74 36
#define YYr75 37
#define YYr76 38
#define YYr77 39
#define YYr78 40
#define YYr79 41
#define YYr80 42
#define YYr81 43
#define YYr82 44
#define YYr104 45
#define YYr105 46
#define YYr107 47
#define YYr124 48
#define YYr139 49
#define YYr147 50
#define YYr157 51
#define YYr156 52
#define YYr155 53
#define YYr154 54
#define YYr153 55
#define YYr152 56
#define YYr151 57
#define YYr150 58
#define YYr149 59
#define YYr148 60
#define YYr146 61
#define YYr145 62
#define YYr144 63
#define YYr143 64
#define YYr142 65
#define YYr141 66
#define YYr140 67
#define YYr138 68
#define YYr137 69
#define YYr136 70
#define YYr135 71
#define YYr134 72
#define YYr133 73
#define YYr132 74
#define YYr131 75
#define YYr130 76
#define YYr129 77
#define YYr128 78
#define YYr127 79
#define YYr126 80
#define YYr125 81
#define YYr123 82
#define YYr122 83
#define YYr121 84
#define YYr120 85
#define YYr119 86
#define YYr118 87
#define YYr117 88
#define YYr116 89
#define YYr115 90
#define YYr114 91
#define YYr113 92
#define YYr112 93
#define YYr111 94
#define YYr110 95
#define YYr109 96
#define YYr108 97
#define YYr106 98
#define YYr103 99
#define YYr102 100
#define YYr101 101
#define YYr100 102
#define YYr99 103
#define YYr98 104
#define YYr97 105
#define YYr96 106
#define YYr95 107
#define YYr94 108
#define YYr93 109
#define YYr92 110
#define YYr91 111
#define YYr90 112
#define YYr89 113
#define YYr88 114
#define YYr87 115
#define YYr86 116
#define YYr85 117
#define YYr84 118
#define YYr83 119
#define YYr57 120
#define YYr56 121
#define YYr55 122
#define YYr54 123
#define YYr53 124
#define YYr52 125
#define YYr51 126
#define YYr50 127
#define YYr49 128
#define YYr48 129
#define YYr47 130
#define YYr46 131
#define YYr45 132
#define YYr44 133
#define YYr42 134
#define YYr41 135
#define YYr40 136
#define YYr39 137
#define YYr38 138
#define YYr37 139
#define YYr35 140
#define YYr34 141
#define YYr33 142
#define YYr32 143
#define YYr30 144
#define YYr29 145
#define YYr28 146
#define YYr27 147
#define YYr26 148
#define YYr25 149
#define YYr24 150
#define YYr9 151
#define YYr8 152
#define YYr7 153
#define YYr6 154
#define YYr5 155
#define YYr4 156
#define YYr3 157
#define YYr2 158
#define YYr1 159
#define YYrACCEPT YYr158
#define YYrERROR YYr159
#define YYrLR2 YYr160
#if YYDEBUG
char*          yysvar[]       =
{
   "$accept", "constant", "type", "primary_expression", "postfix_expression", "unary_expression", "cast_expression", "multiplicative_expression", "additive_expression", "shift_expression", "relational_expression", "equality_expression", "and_expression", "exclusive_or_expression", "inclusive_or_expression", "logical_and_expression", "logical_or_expression", "conditional_expression", "assignment_expression", "expression", "constant_expression", "initializer", "declarator", "variable_declarator", "variable_declaration", "statement", "compound_statement", "expression_statement", "selection_statement", "iteration_statement", "jump_statement", "parameter", "function_definition", "function_call", "global_declaration", "main_prototype", "main_definition", "translation_unit", "script", "initializer_list", "variable_declarator_list", "if_key", "variable_declaration_list", "statement_list", "parameter_list", "argument_expression_list", "printf_call", "scanf_call", "while_key", "for_key", "unary_operator", "assignment_operator", 0
};
short          yyrmap[]       =
{
   158, 159, 160, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 31, 36, 43, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 104, 105, 107, 124, 139, 147, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 146, 145, 144, 143, 142, 141, 140, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126, 125, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 106, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 42, 41, 40, 39, 38, 37, 35, 34, 33, 32, 30, 29, 28, 27, 26, 25, 24, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
};
short          yysmap[]       =
{
   8, 9, 10, 11, 12, 13, 14, 15, 22, 23, 24, 25, 26, 28, 29, 30, 31, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 69, 78, 86, 87, 100, 110, 111, 124, 167, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 217, 227, 237, 245, 244, 243, 241, 239, 235, 234, 232, 228, 224, 223, 222, 221, 218, 216, 215, 213, 211, 210, 208, 188, 185, 184, 183, 181, 180, 176, 174, 173, 171, 168, 166, 165, 161, 157, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126, 122, 118, 117, 116, 115, 105, 101, 99, 98, 83, 77, 76, 75, 55, 54, 52, 45, 42, 39, 38, 37, 36, 35, 33, 32, 27, 20, 19, 7, 4, 2, 0, 16, 1, 17, 3, 18, 178, 5, 6, 233, 179, 219, 220, 226, 230, 214, 231, 175, 186, 121, 119, 34, 112, 113, 182, 114, 247, 242, 236, 40, 41, 248, 43, 125, 44, 120, 46, 47, 48, 49, 50, 51, 123, 53, 97, 169, 21, 170, 246, 240, 212, 229, 172, 177, 187, 56, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 207, 57, 238, 204, 205, 206, 68, 225, 158, 70, 71, 72, 73, 74, 159, 160, 162, 163, 164, 79, 80, 81, 249, 82, 209, 84, 85, 102, 103, 104, 106, 107, 108, 109, 88, 89, 90, 91, 92, 93, 94, 95, 96
};
int            yyntoken       = 74;
int            yynvar         = 52;
int            yynstate       = 250;
int            yynrule        = 161;
#endif

#if YYDEBUG
/*
* Package up YACC context for tracing
*/
typedef struct yyTraceItems_tag
{
   int                           state, lookahead, errflag, done;
   int                           rule, npop;
   short*                        states;
   int                           nstates;
   YYSTYPE*                      values;
   int                           nvalues;
   short*                        types;
} yyTraceItems;
#endif

#line 2 "D:\YACC/etc/yyparse.c"

/*
* Copyright 1985, 1990 by Mortice Kern Systems Inc. All rights reserved.
*
* Automaton to interpret LALR(1) tables.
*
* Macros:
* yyclearin - clear the lookahead token.
* yyerrok - forgive a pending error
* YYERROR - simulate an error
* YYACCEPT - halt and return 0
* YYABORT - halt and return 1
* YYRETURN(value) - halt and return value. You should use this
* instead of return(value).
* YYREAD - ensure yychar contains a lookahead token by reading
* one if it does not. See also YYSYNC.
* YYRECOVERING - 1 if syntax error detected and not recovered
* yet; otherwise, 0.
*
* Preprocessor flags:
* YYDEBUG - includes debug code if 1. The parser will print
* a travelogue of the parse if this is defined as 1
* and yydebug is non-zero.
* yacc -t sets YYDEBUG to 1, but not yydebug.
* YYTRACE - turn on YYDEBUG, and undefine default trace functions
* so that the interactive functions in 'ytrack.c' will
* be used.
* YYSSIZE - size of state and value stacks (default 150).
* YYSTATIC - By default, the state stack is an automatic array.
* If this is defined, the stack will be static.
* In either case, the value stack is static.
* YYALLOC - Dynamically allocate both the state and value stacks
* by calling malloc() and free().
* YYSYNC - if defined, yacc guarantees to fetch a lookahead token
* before any action, even if it doesnt need it for a decision.
* If YYSYNC is defined, YYREAD will never be necessary unless
* the user explicitly sets yychar = -1
*
* Copyright (c) 1983, by the University of Waterloo
*/
/*
* Prototypes
*/

extern int yylex              YY_ARGS((void));

#if YYDEBUG

#include <stdlib.h> /* common prototypes */
#include <string.h>

extern char * yyValue         YY_ARGS((YYSTYPE, int)); /* print yylval */
extern void yyShowState       YY_ARGS((yyTraceItems *));
extern void yyShowReduce      YY_ARGS((yyTraceItems *));
extern void yyShowGoto        YY_ARGS((yyTraceItems *));
extern void yyShowShift       YY_ARGS((yyTraceItems *));
extern void yyShowErrRecovery YY_ARGS((yyTraceItems *));
extern void yyShowErrDiscard  YY_ARGS((yyTraceItems *));

extern void yyShowRead        YY_ARGS((int));
#endif

/*
* If YYDEBUG defined and yydebug set,
* tracing functions will be called at appropriate times in yyparse()
* Pass state of YACC parse, as filled into yyTraceItems yyx
* If yyx.done is set by the tracing function, yyparse() will terminate
* with a return value of -1
*/
#define YY_TRACE(fn) { \
yyx.state = yystate; yyx.lookahead = yychar; yyx.errflag =yyerrflag; \
yyx.states = yys+1; yyx.nstates = yyps-yys; \
yyx.values = yyv+1; yyx.nvalues = yypv-yyv; \
yyx.types = yytypev+1; yyx.done = 0; \
yyx.rule = yyi; yyx.npop = yyj; \
fn(&yyx); \
if (yyx.done) YYRETURN(-1); }

#ifndef I18N
#define gettext(x) x
#endif

#ifndef YYSSIZE
# define YYSSIZE 150
#endif

#define YYERROR goto yyerrlabel
#define yyerrok yyerrflag = 0
#if YYDEBUG
#define yyclearin { if (yydebug) yyShowRead(-1); yychar = -1; }
#else
#define yyclearin yychar = -1
#endif
#define YYACCEPT YYRETURN(0)
#define YYABORT YYRETURN(1)
#define YYRECOVERING() (yyerrflag != 0)
#ifdef YYALLOC
# define YYRETURN(val) { retval = (val); goto yyReturn; }
#else
# define YYRETURN(val) return(val)
#endif
#if YYDEBUG
/* The if..else makes this macro behave exactly like a statement */
# define YYREAD if (yychar < 0) { \
if ((yychar = yylex()) < 0) \
yychar = 0; \
if (yydebug) \
yyShowRead(yychar); \
} else
#else
# define YYREAD if (yychar < 0) { \
if ((yychar = yylex()) < 0) \
yychar = 0; \
} else
#endif

#define YYERRCODE 256 /* value of `error' */
#define YYQYYP yyq[yyq-yyp]

YYSTYPE                       yyval; /* $ */
YYSTYPE*                      yypvt; /* $n */
YYSTYPE                       yylval; /* yylex() sets this */

int                           yychar, /* current token */
yyerrflag, /* error flag */
yynerrs; /* error count */

#if YYDEBUG
int                           yydebug  = 0; /* debug if this flag is set */
extern char*                  yysvar[]; /* table of non-terminals (aka 'variables') */
extern yyNamedType            yyTokenTypes[]; /* table of terminals & their types */
extern short                  yyrmap[], yysmap[]; /* map internal rule/states */
extern int                    yynstate, yynvar, yyntoken, yynrule;

extern int yyGetType          YY_ARGS((int)); /* token type */
extern char *yyptok           YY_ARGS((int)); /* printable token string */
extern int yyExpandName       YY_ARGS((int, int, char *, int));
/* expand yyRules[] or yyStates[] */
static char * yygetState      YY_ARGS((int));

#define yyassert(condition, msg, arg) \
if (!(condition)) { \
printf(gettext("\nyacc bug: ")); \
printf(msg, arg); \
YYABORT; }
#else /* !YYDEBUG */
#define yyassert(condition, msg, arg)
#endif

#line 407 "ci.y"
extern char                   yytext[];
extern int                    column;
extern int                    row;
//int yydebug=1;

void yyerror(char* s)
{
   fflush(stdout);
   printf("\nSYNTACTICAL EXCEPTION: Syntax error at line %d, column %d\n",row,column);
}

void is_eval_stmt(ast node)
{
   if (ctrl_stmt_exec_env)
   {
      if (node->tag == IF_STATEMENT || node->tag == WHILE_STATEMENT || node->tag == FOR_STATEMENT)
      {
         eval_stmt(node);
         purge_ast(node);
         print_prompt();
      }
   }
   else if (stmt_exec_env)
   {
      if (node->tag == EXPRESSION_STATEMENT)
      {
         eval_exp_stmt(node);
      }
      else if (node->tag == RETURN_STATEMENT)
      {
         eval_return_stmt(node);
      }
      else if (node->tag == DECLARATION)
      {
         eval_var_decl(CONTEXT_SYMBOL_TABLE,node);
      }
      purge_ast(node);
      print_prompt();
   }
}

void is_hndlr(ast node)
{
   is_eval_stmt(node);
   is_dec_block_count
}

yyparse()
{
   register short yyi, * yyp; /* for table lookup */
   register short * yyps; /* top of state stack */
   register short yystate; /* current state */
   register YYSTYPE * yypv; /* top of value stack */
   register short * yyq;
   register int yyj;
   #if YYDEBUG
   yyTraceItems   yyx; /* trace block */
   short*         yytp;
   int            yyruletype  = 0;
   #endif
   #ifdef YYSTATIC
   static short   yys[YYSSIZE + 1];
   static YYSTYPE yyv[YYSSIZE + 1];
   #if YYDEBUG
   static short   yytypev[YYSSIZE + 1]; /* type assignments */
   #endif
   #else /* ! YYSTATIC */
   #ifdef YYALLOC
   YYSTYPE*       yyv;
   short*         yys;
   #if YYDEBUG
   short*         yytypev;
   #endif
   YYSTYPE        save_yylval;
   YYSTYPE        save_yyval;
   YYSTYPE*       save_yypvt;
   int            save_yychar, save_yyerrflag, save_yynerrs;
   int            retval;
   #else
   short          yys[YYSSIZE + 1];
   static YYSTYPE yyv[YYSSIZE + 1]; /* historically static */
   #if YYDEBUG
   short          yytypev[YYSSIZE + 1]; /* mirror type table */
   #endif
   #endif /* ! YYALLOC */
   #endif /* ! YYSTATIC */


   #ifdef YYALLOC
   yys = (short *) malloc((YYSSIZE + 1) * sizeof(short));
   yyv = (YYSTYPE *) malloc((YYSSIZE + 1) * sizeof(YYSTYPE));
   #if YYDEBUG
   yytypev = (short *) malloc((YYSSIZE + 1) * sizeof(short));
   #endif
   if (yys == (short *) 0 || yyv == (YYSTYPE *) 0
       #if YYDEBUG
       || yytypev == (short *) 0
       #endif
      )
   {
      yyerror("Not enough space for parser stacks");
      return 1;
   }
   save_yylval = yylval;
   save_yyval = yyval;
   save_yypvt = yypvt;
   save_yychar = yychar;
   save_yyerrflag = yyerrflag;
   save_yynerrs = yynerrs;
   #endif

   yynerrs = 0;
   yyerrflag = 0;    
   yyclearin;
   yyps = yys;
   yypv = yyv;
   *yyps = yystate = YYS0; /* start state */
   #if YYDEBUG
   yytp = yytypev;
   yyi = yyj = 0; /* silence compiler warnings */
   #endif

   yyStack:
   yyassert((unsigned) yystate < yynstate, gettext("state %d\n"), yystate);
   if (++yyps > &yys[YYSSIZE])
   {
      yyerror("Parser stack overflow");      
      YYABORT;
   }
   *yyps = yystate; /* stack current state */
   *++yypv = yyval; /* ... and value */
   #if YYDEBUG
   *++yytp = yyruletype; /* ... and type */

   if (yydebug)
   {
      YY_TRACE(yyShowState)
   }
   #endif

   /*
   * Look up next action in action table.
   */
   yyEncore:
   #ifdef YYSYNC
   YYREAD;
   #endif
   if (yystate >= sizeof yypact / sizeof yypact[0]) /* simple state */
   {
      yyi = yystate - YYDELTA;
   } /* reduce in any case */
   else
   {
      if (*(yyp = &yyact[yypact[yystate]]) >= 0)
      {
         /* Look for a shift on yychar */
         #ifndef YYSYNC
         YYREAD;
         #endif
         yyq = yyp;
         yyi = yychar;
         while (yyi < *yyp++)
         ;
         if (yyi == yyp[-1])
         {
            yystate = ~YYQYYP;
            #if YYDEBUG
            if (yydebug)
            {
               yyruletype = yyGetType(yychar);
               YY_TRACE(yyShowShift)
            }
            #endif
            yyval = yylval; /* stack what yylex() set */             
            yyclearin; /* clear token */
            if (yyerrflag)
            {
               yyerrflag--;
            } /* successful shift */
            goto yyStack;
         }
      }

      /*
      * Fell through - take default action
      */

      if (yystate >= sizeof yydef / sizeof yydef[0])
      {
         goto yyError;
      }
      if ((yyi = yydef[yystate]) < 0)
      {
         /* default == reduce? */
         /* Search exception table */
         yyassert((unsigned) ~yyi < sizeof yyex / sizeof yyex[0],
gettext("exception %d\n"), yystate);
         yyp = &yyex[~yyi];
         #ifndef YYSYNC
         YYREAD;
         #endif
         while ((yyi = *yyp) >= 0 && yyi != yychar)
         {
            yyp += 2;
         }
         yyi = yyp[1];
         yyassert(yyi >= 0,gettext("Ex table not reduce %d\n"),yyi);
      }
   }

   yyassert((unsigned) yyi < yynrule, gettext("reduce %d\n"), yyi);
   yyj = yyrlen[yyi];
   #if YYDEBUG
   if (yydebug)
   {
      YY_TRACE(yyShowReduce)
      yytp -= yyj;
   }
   #endif
   yyps -= yyj; /* pop stacks */
   yypvt = yypv; /* save top */
   yypv -= yyj;
   yyval = yypv[1]; /* default action $ = $1 */
   #if YYDEBUG
   yyruletype = yyRules[yyrmap[yyi]].type;
   #endif

   switch (yyi)
   {
         /* perform semantic action */

      case YYr1:
         {
            /* constant : CHAR_CONSTANT */
            #line 96 "ci.y"
            yyval.node = new_constant_node(yypvt[0].string,E_CHAR); free(yypvt[0].string);
         } break;

      case YYr2:
         {
            /* constant : HEX_INT_CONSTANT */
            #line 97 "ci.y"
            yyval.node = new_constant_node(yypvt[0].string,E_INT); free(yypvt[0].string);
         } break;

      case YYr3:
         {
            /* constant : OCT_INT_CONSTANT */
            #line 98 "ci.y"
            yyval.node = new_constant_node(yypvt[0].string,E_INT); free(yypvt[0].string);
         } break;

      case YYr4:
         {
            /* constant : DEC_INT_CONSTANT */
            #line 99 "ci.y"
            yyval.node = new_constant_node(yypvt[0].string,E_INT); free(yypvt[0].string);
         } break;

      case YYr5:
         {
            /* constant : FLOAT_CONSTANT */
            #line 100 "ci.y"
            yyval.node = new_constant_node(yypvt[0].string,E_FLOAT); free(yypvt[0].string);
         } break;

      case YYr6:
         {
            /* constant : DOUBLE_CONSTANT */
            #line 101 "ci.y"
            yyval.node = new_constant_node(yypvt[0].string,E_DOUBLE); free(yypvt[0].string);
         } break;

      case YYr7:
         {
            /* constant : HEX_LONG_CONSTANT */
            #line 102 "ci.y"
            yyval.node = new_constant_node(yypvt[0].string,E_LONG); free(yypvt[0].string);
         } break;

      case YYr8:
         {
            /* constant : OCT_LONG_CONSTANT */
            #line 103 "ci.y"
            yyval.node = new_constant_node(yypvt[0].string,E_LONG); free(yypvt[0].string);
         } break;

      case YYr9:
         {
            /* constant : DEC_LONG_CONSTANT */
            #line 104 "ci.y"
            yyval.node = new_constant_node(yypvt[0].string,E_LONG); free(yypvt[0].string);
         } break;

      case YYr10:
         {
            /* type : VOID_TYPE */
            #line 108 "ci.y"
            yyval.node = new_type_node("void",E_VOID);
         } break;

      case YYr11:
         {
            /* type : CHAR_TYPE */
            #line 109 "ci.y"
            yyval.node = new_type_node("char",E_CHAR);
         } break;

      case YYr12:
         {
            /* type : SHORT_TYPE */
            #line 110 "ci.y"
            yyval.node = new_type_node("short",E_SHORT);
         } break;

      case YYr13:
         {
            /* type : INT_TYPE */
            #line 111 "ci.y"
            yyval.node = new_type_node("int",E_INT);
         } break;

      case YYr14:
         {
            /* type : FLOAT_TYPE */
            #line 112 "ci.y"
            yyval.node = new_type_node("float",E_FLOAT);
         } break;

      case YYr15:
         {
            /* type : DOUBLE_TYPE */
            #line 113 "ci.y"
            yyval.node = new_type_node("double",E_DOUBLE);
         } break;

      case YYr16:
         {
            /* type : LONG_TYPE */
            #line 114 "ci.y"
            yyval.node = new_type_node("long",E_LONG);
         } break;

      case YYr17:
         {
            /* type : VOID_TYPE '*' */
            #line 115 "ci.y"
            yyval.node = new_type_node("void pointer",E_VOID_PTR);
         } break;

      case YYr18:
         {
            /* type : CHAR_TYPE '*' */
            #line 116 "ci.y"
            yyval.node = new_type_node("char pointer",E_CHAR_PTR);
         } break;

      case YYr19:
         {
            /* type : SHORT_TYPE '*' */
            #line 117 "ci.y"
            yyval.node = new_type_node("short pointer",E_SHORT_PTR);
         } break;

      case YYr20:
         {
            /* type : INT_TYPE '*' */
            #line 118 "ci.y"
            yyval.node = new_type_node("int pointer",E_INT_PTR);
         } break;

      case YYr21:
         {
            /* type : FLOAT_TYPE '*' */
            #line 119 "ci.y"
            yyval.node = new_type_node("float pointer",E_FLOAT_PTR);
         } break;

      case YYr22:
         {
            /* type : DOUBLE_TYPE '*' */
            #line 120 "ci.y"
            yyval.node = new_type_node("double pointer",E_DOUBLE_PTR);
         } break;

      case YYr23:
         {
            /* type : LONG_TYPE '*' */
            #line 121 "ci.y"
            yyval.node = new_type_node("long pointer",E_LONG_PTR);
         } break;

      case YYr24:
         {
            /* type : VOID_TYPE '*' '*' */
            #line 122 "ci.y"
            yyval.node = new_type_node("void 2 pointer",E_VOID_2PTR);
         } break;

      case YYr25:
         {
            /* type : CHAR_TYPE '*' '*' */
            #line 123 "ci.y"
            yyval.node = new_type_node("char 2 pointer",E_CHAR_2PTR);
         } break;

      case YYr26:
         {
            /* type : SHORT_TYPE '*' '*' */
            #line 124 "ci.y"
            yyval.node = new_type_node("short 2 pointer",E_SHORT_2PTR);
         } break;

      case YYr27:
         {
            /* type : INT_TYPE '*' '*' */
            #line 125 "ci.y"
            yyval.node = new_type_node("int 2 pointer",E_INT_2PTR);
         } break;

      case YYr28:
         {
            /* type : FLOAT_TYPE '*' '*' */
            #line 126 "ci.y"
            yyval.node = new_type_node("float 2 pointer",E_FLOAT_2PTR);
         } break;

      case YYr29:
         {
            /* type : DOUBLE_TYPE '*' '*' */
            #line 127 "ci.y"
            yyval.node = new_type_node("double 2 pointer",E_DOUBLE_2PTR);
         } break;

      case YYr30:
         {
            /* type : LONG_TYPE '*' '*' */
            #line 128 "ci.y"
            yyval.node = new_type_node("long 2 pointer",E_LONG_2PTR);
         } break;

      case YYr31:
         {
            /* primary_expression : IDENTIFIER */
            #line 132 "ci.y"
            yyval.node = new_variable_node(yypvt[0].string,E_UNDEFINED); free(yypvt[0].string);
         } break;

      case YYr32:
         {
            /* primary_expression : constant */
            #line 133 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr33:
         {
            /* primary_expression : STRING_LITERAL */
            #line 134 "ci.y"
            yyval.node = new_constant_node(yypvt[0].string,E_CHAR_PTR); free(yypvt[0].string);
         } break;

      case YYr34:
         {
            /* primary_expression : '(' expression ')' */
            #line 135 "ci.y"
            yyval.node = yypvt[-1].node;
         } break;

      case YYr35:
         {
            /* postfix_expression : primary_expression */
            #line 139 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr36:
         {
            /* postfix_expression : IDENTIFIER '[' expression ']' */
            #line 140 "ci.y"
            yyval.node = new_array_variable_node(yypvt[-3].string,yypvt[-1].node,NULL,E_UNDEFINED); free(yypvt[-3].string);
         } break;

      case YYr37:
         {
            /* postfix_expression : IDENTIFIER '[' expression ']' '[' expression ']' */
            #line 141 "ci.y"
            yyval.node = new_array_variable_node(yypvt[-6].string,yypvt[-4].node,yypvt[-1].node,E_UNDEFINED); free(yypvt[-6].string);
         } break;

      case YYr38:
         {
            /* postfix_expression : function_call */
            #line 142 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr39:
         {
            /* postfix_expression : printf_call */
            #line 143 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr40:
         {
            /* postfix_expression : scanf_call */
            #line 144 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr41:
         {
            /* postfix_expression : postfix_expression INC_OP */
            #line 145 "ci.y"
            yyval.node = new_inc_exp_node(POST_INCREMENT,yypvt[-1].node);
         } break;

      case YYr42:
         {
            /* postfix_expression : postfix_expression DEC_OP */
            #line 146 "ci.y"
            yyval.node = new_dec_exp_node(POST_DECREMENT,yypvt[-1].node);
         } break;

      case YYr43:
         {
            /* unary_expression : postfix_expression */
            #line 150 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr44:
         {
            /* unary_expression : INC_OP unary_expression */
            #line 151 "ci.y"
            yyval.node = new_inc_exp_node(PRE_INCREMENT,yypvt[0].node);
         } break;

      case YYr45:
         {
            /* unary_expression : DEC_OP unary_expression */
            #line 152 "ci.y"
            yyval.node = new_dec_exp_node(PRE_DECREMENT,yypvt[0].node);
         } break;

      case YYr46:
         {
            /* unary_expression : unary_operator cast_expression */
            #line 153 "ci.y"
            yyval.node = new_unary_exp_node(yypvt[-1].unary_code,yypvt[0].node);
         } break;

      case YYr47:
         {
            /* unary_operator : '&' */
            #line 157 "ci.y"
            yyval.unary_code = '&';
         } break;

      case YYr48:
         {
            /* unary_operator : '*' */
            #line 158 "ci.y"
            yyval.unary_code = '*';
         } break;

      case YYr49:
         {
            /* unary_operator : '-' */
            #line 159 "ci.y"
            yyval.unary_code = '-';
         } break;

      case YYr50:
         {
            /* unary_operator : '~' */
            #line 160 "ci.y"
            yyval.unary_code = '~';
         } break;

      case YYr51:
         {
            /* unary_operator : '!' */
            #line 161 "ci.y"
            yyval.unary_code = '!';
         } break;

      case YYr52:
         {
            /* cast_expression : unary_expression */
            #line 165 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr53:
         {
            /* cast_expression : '(' type ')' cast_expression */
            #line 166 "ci.y"
            yyval.node = new_cast_node(yypvt[-2].node,yypvt[0].node);
         } break;

      case YYr54:
         {
            /* multiplicative_expression : cast_expression */
            #line 170 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr55:
         {
            /* multiplicative_expression : multiplicative_expression '*' cast_expression */
            #line 171 "ci.y"
            yyval.node = new_mul_exp_node(yypvt[-2].node,MULTIPLICATION,yypvt[0].node);
         } break;

      case YYr56:
         {
            /* multiplicative_expression : multiplicative_expression '/' cast_expression */
            #line 172 "ci.y"
            yyval.node = new_mul_exp_node(yypvt[-2].node,DIVISION,yypvt[0].node);
         } break;

      case YYr57:
         {
            /* multiplicative_expression : multiplicative_expression '%' cast_expression */
            #line 173 "ci.y"
            yyval.node = new_mul_exp_node(yypvt[-2].node,MODULO,yypvt[0].node);
         } break;

      case YYr58:
         {
            /* additive_expression : multiplicative_expression */
            #line 177 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr59:
         {
            /* additive_expression : additive_expression '+' multiplicative_expression */
            #line 178 "ci.y"
            yyval.node = new_add_exp_node(yypvt[-2].node,ADDITION,yypvt[0].node);
         } break;

      case YYr60:
         {
            /* additive_expression : additive_expression '-' multiplicative_expression */
            #line 179 "ci.y"
            yyval.node = new_add_exp_node(yypvt[-2].node,SUBTRACTION,yypvt[0].node);
         } break;

      case YYr61:
         {
            /* shift_expression : additive_expression */
            #line 183 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr62:
         {
            /* shift_expression : shift_expression LEFT_SHIFT_OP additive_expression */
            #line 184 "ci.y"
            yyval.node = new_shift_exp_node(yypvt[-2].node,LEFT_SHIFT,yypvt[0].node);
         } break;

      case YYr63:
         {
            /* shift_expression : shift_expression RIGHT_SHIFT_OP additive_expression */
            #line 185 "ci.y"
            yyval.node = new_shift_exp_node(yypvt[-2].node,RIGHT_SHIFT,yypvt[0].node);
         } break;

      case YYr64:
         {
            /* relational_expression : shift_expression */
            #line 189 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr65:
         {
            /* relational_expression : relational_expression '<' shift_expression */
            #line 190 "ci.y"
            yyval.node = new_rel_exp_node(yypvt[-2].node,REL_LESS,yypvt[0].node);
         } break;

      case YYr66:
         {
            /* relational_expression : relational_expression '>' shift_expression */
            #line 191 "ci.y"
            yyval.node = new_rel_exp_node(yypvt[-2].node,REL_GREATER,yypvt[0].node);
         } break;

      case YYr67:
         {
            /* relational_expression : relational_expression LE_OP shift_expression */
            #line 192 "ci.y"
            yyval.node = new_rel_exp_node(yypvt[-2].node,REL_LESS_EQUAL,yypvt[0].node);
         } break;

      case YYr68:
         {
            /* relational_expression : relational_expression GE_OP shift_expression */
            #line 193 "ci.y"
            yyval.node = new_rel_exp_node(yypvt[-2].node,REL_GREATER_EQUAL,yypvt[0].node);
         } break;

      case YYr69:
         {
            /* equality_expression : relational_expression */
            #line 197 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr70:
         {
            /* equality_expression : equality_expression EQ_OP relational_expression */
            #line 198 "ci.y"
            yyval.node = new_rel_exp_node(yypvt[-2].node,REL_EQUAL,yypvt[0].node);
         } break;

      case YYr71:
         {
            /* equality_expression : equality_expression NE_OP relational_expression */
            #line 199 "ci.y"
            yyval.node = new_rel_exp_node(yypvt[-2].node,REL_NOT_EQUAL,yypvt[0].node);
         } break;

      case YYr72:
         {
            /* and_expression : equality_expression */
            #line 203 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr73:
         {
            /* and_expression : and_expression '&' equality_expression */
            #line 204 "ci.y"
            yyval.node = new_bit_exp_node(yypvt[-2].node,BITWISE_AND,yypvt[0].node);
         } break;

      case YYr74:
         {
            /* exclusive_or_expression : and_expression */
            #line 208 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr75:
         {
            /* exclusive_or_expression : exclusive_or_expression '^' and_expression */
            #line 209 "ci.y"
            yyval.node = new_bit_exp_node(yypvt[-2].node,BITWISE_XOR,yypvt[0].node);
         } break;

      case YYr76:
         {
            /* inclusive_or_expression : exclusive_or_expression */
            #line 213 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr77:
         {
            /* inclusive_or_expression : inclusive_or_expression '|' exclusive_or_expression */
            #line 214 "ci.y"
            yyval.node = new_bit_exp_node(yypvt[-2].node,BITWISE_OR,yypvt[0].node);
         } break;

      case YYr78:
         {
            /* logical_and_expression : inclusive_or_expression */
            #line 218 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr79:
         {
            /* logical_and_expression : logical_and_expression AND_OP inclusive_or_expression */
            #line 219 "ci.y"
            yyval.node = new_logic_exp_node(yypvt[-2].node,LOGICAL_AND,yypvt[0].node);
         } break;

      case YYr80:
         {
            /* logical_or_expression : logical_and_expression */
            #line 223 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr81:
         {
            /* logical_or_expression : logical_or_expression OR_OP logical_and_expression */
            #line 224 "ci.y"
            yyval.node = new_logic_exp_node(yypvt[-2].node,LOGICAL_OR,yypvt[0].node);
         } break;

      case YYr82:
         {
            /* conditional_expression : logical_or_expression */
            #line 228 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr83:
         {
            /* conditional_expression : logical_or_expression '?' expression ':' conditional_expression */
            #line 229 "ci.y"
            yyval.node = new_cond_exp_node(yypvt[-4].node,yypvt[-2].node,yypvt[0].node);
         } break;

      case YYr84:
         {
            /* assignment_expression : conditional_expression */
            #line 233 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr85:
         {
            /* assignment_expression : unary_expression assignment_operator assignment_expression */
            #line 234 "ci.y"
            yyval.node = new_assign_exp_node(yypvt[-2].node,yypvt[-1].assign_code,yypvt[0].node);
         } break;

      case YYr86:
         {
            /* assignment_operator : '=' */
            #line 238 "ci.y"
            yyval.assign_code = EQ_ASSIGN_CODE;
         } break;

      case YYr87:
         {
            /* assignment_operator : MUL_ASSIGN */
            #line 239 "ci.y"
            yyval.assign_code = MUL_ASSIGN_CODE;
         } break;

      case YYr88:
         {
            /* assignment_operator : DIV_ASSIGN */
            #line 240 "ci.y"
            yyval.assign_code = DIV_ASSIGN_CODE;
         } break;

      case YYr89:
         {
            /* assignment_operator : MOD_ASSIGN */
            #line 241 "ci.y"
            yyval.assign_code = MOD_ASSIGN_CODE;
         } break;

      case YYr90:
         {
            /* assignment_operator : ADD_ASSIGN */
            #line 242 "ci.y"
            yyval.assign_code = ADD_ASSIGN_CODE;
         } break;

      case YYr91:
         {
            /* assignment_operator : SUB_ASSIGN */
            #line 243 "ci.y"
            yyval.assign_code = SUB_ASSIGN_CODE;
         } break;

      case YYr92:
         {
            /* assignment_operator : LEFT_ASSIGN */
            #line 244 "ci.y"
            yyval.assign_code = LEFT_ASSIGN_CODE;
         } break;

      case YYr93:
         {
            /* assignment_operator : RIGHT_ASSIGN */
            #line 245 "ci.y"
            yyval.assign_code = RIGHT_ASSIGN_CODE;
         } break;

      case YYr94:
         {
            /* assignment_operator : AND_ASSIGN */
            #line 246 "ci.y"
            yyval.assign_code = AND_ASSIGN_CODE;
         } break;

      case YYr95:
         {
            /* assignment_operator : XOR_ASSIGN */
            #line 247 "ci.y"
            yyval.assign_code = XOR_ASSIGN_CODE;
         } break;

      case YYr96:
         {
            /* assignment_operator : OR_ASSIGN */
            #line 248 "ci.y"
            yyval.assign_code = OR_ASSIGN_CODE;
         } break;

      case YYr97:
         {
            /* expression : assignment_expression */
            #line 252 "ci.y"
            yyval.node = new_exp_list_node(yypvt[0].node);
         } break;

      case YYr98:
         {
            /* expression : expression ',' assignment_expression */
            #line 253 "ci.y"
            yyval.node = append_exp_list_node(yypvt[-2].node,yypvt[0].node);
         } break;

      case YYr99:
         {
            /* constant_expression : conditional_expression */
            #line 257 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr100:
         {
            /* initializer : assignment_expression */
            #line 261 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr101:
         {
            /* initializer : '{' initializer_list '}' */
            #line 262 "ci.y"
            yyval.node = yypvt[-1].node;
         } break;

      case YYr102:
         {
            /* initializer_list : initializer */
            #line 266 "ci.y"
            yyval.node = new_init_list_node(yypvt[0].node);
         } break;

      case YYr103:
         {
            /* initializer_list : initializer_list ',' initializer */
            #line 267 "ci.y"
            yyval.node = append_init_list_node(yypvt[-2].node,yypvt[0].node);
         } break;

      case YYr104:
         {
            /* declarator : IDENTIFIER */
            #line 271 "ci.y"
            yyval.node = new_variable_node(yypvt[0].string,E_UNDEFINED); free(yypvt[0].string);
         } break;

      case YYr105:
         {
            /* declarator : IDENTIFIER '[' constant_expression ']' */
            #line 272 "ci.y"
            yyval.node = new_array_variable_node(yypvt[-3].string,yypvt[-1].node,NULL,E_UNDEFINED); free(yypvt[-3].string);
         } break;

      case YYr106:
         {
            /* declarator : IDENTIFIER '[' constant_expression ']' '[' constant_expression ']' */
            #line 273 "ci.y"
            yyval.node = new_array_variable_node(yypvt[-6].string,yypvt[-4].node,yypvt[-1].node,E_UNDEFINED); free(yypvt[-6].string);
         } break;

      case YYr107:
         {
            /* variable_declarator : declarator */
            #line 277 "ci.y"
            yyval.node = yypvt[0].node;
         } break;

      case YYr108:
         {
            /* variable_declarator : declarator '=' initializer */
            #line 278 "ci.y"
            yyval.node = new_assign_exp_node(yypvt[-2].node,EQ_ASSIGN_CODE,yypvt[0].node);
         } break;

      case YYr109:
         {
            /* variable_declarator_list : variable_declarator */
            #line 282 "ci.y"
            yyval.node = new_var_decl_list_node(yypvt[0].node);
         } break;

      case YYr110:
         {
            /* variable_declarator_list : variable_declarator_list ',' variable_declarator */
            #line 283 "ci.y"
            yyval.node = append_var_decl_list_node(yypvt[-2].node,yypvt[0].node);
         } break;

      case YYr111:
         {
            /* variable_declaration : type variable_declarator_list ';' */
            #line 287 "ci.y"
            yyval.node = new_decl_node(yypvt[-2].node,yypvt[-1].node); is_eval_stmt(yyval.node);
         } break;

      case YYr112:
         {
            /* variable_declaration_list : variable_declaration */
            #line 291 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = new_var_type_decl_list_node(yypvt[0].node);
            }
         } break;

      case YYr113:
         {
            /* variable_declaration_list : variable_declaration_list variable_declaration */
            #line 292 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = append_var_type_decl_list_node(yypvt[-1].node,yypvt[0].node);
            }
         } break;

      case YYr114:
         {
            /* statement : compound_statement */
            #line 296 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = yypvt[0].node;
            }
         } break;

      case YYr115:
         {
            /* statement : expression_statement */
            #line 297 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = yypvt[0].node;
            }
         } break;

      case YYr116:
         {
            /* statement : selection_statement */
            #line 298 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = yypvt[0].node;
            }
         } break;

      case YYr117:
         {
            /* statement : iteration_statement */
            #line 299 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = yypvt[0].node;
            }
         } break;

      case YYr118:
         {
            /* statement : jump_statement */
            #line 300 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = yypvt[0].node;
            }
         } break;

      case YYr119:
         {
            /* statement_list : statement */
            #line 304 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = new_stmt_list_node(yypvt[0].node);
            }
         } break;

      case YYr120:
         {
            /* statement_list : statement_list statement */
            #line 305 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = append_stmt_list_node(yypvt[-1].node,yypvt[0].node);
            }
         } break;

      case YYr121:
         {
            /* expression_statement : ';' */
            #line 309 "ci.y"
            yyval.node = new_exp_stmt_node(NULL);
         } break;

      case YYr122:
         {
            /* expression_statement : expression ';' */
            #line 310 "ci.y"
            yyval.node = new_exp_stmt_node(yypvt[-1].node); is_eval_stmt(yyval.node);
         } break;

      case YYr123:
         {
            /* if_key : IF */
            #line 314 "ci.y"
            yyval.node = NULL; is_inc_block_count
         } break;

      case YYr124:
         {
            /* selection_statement : if_key '(' expression ')' statement */
            #line 318 "ci.y"
            yyval.node = new_if_stmt_node(yypvt[-2].node,yypvt[0].node,NULL); is_hndlr(yyval.node); is_check_return_env
         } break;

      case YYr125:
         {
            /* selection_statement : if_key '(' expression ')' statement ELSE statement */
            #line 319 "ci.y"
            yyval.node = new_if_stmt_node(yypvt[-4].node,yypvt[-2].node,yypvt[0].node); is_hndlr(yyval.node); is_check_return_env
         } break;

      case YYr126:
         {
            /* while_key : WHILE */
            #line 323 "ci.y"
            yyval.node = NULL; is_inc_block_count
         } break;

      case YYr127:
         {
            /* for_key : FOR */
            #line 327 "ci.y"
            yyval.node = NULL; is_inc_block_count
         } break;

      case YYr128:
         {
            /* iteration_statement : while_key '(' expression ')' statement */
            #line 331 "ci.y"
            yyval.node = new_while_stmt_node(yypvt[-2].node,yypvt[0].node); is_hndlr(yyval.node); is_check_return_env
         } break;

      case YYr129:
         {
            /* iteration_statement : for_key '(' expression_statement expression_statement ')' statement */
            #line 332 "ci.y"
            yyval.node = new_for_stmt_node(yypvt[-3].node,yypvt[-2].node,NULL,yypvt[0].node); is_hndlr(yyval.node); is_check_return_env
         } break;

      case YYr130:
         {
            /* iteration_statement : for_key '(' expression_statement expression_statement expression ')' statement */
            #line 333 "ci.y"
            yyval.node = new_for_stmt_node(yypvt[-4].node,yypvt[-3].node,yypvt[-2].node,yypvt[0].node); is_hndlr(yyval.node); is_check_return_env
         } break;

      case YYr131:
         {
            /* jump_statement : RETURN ';' */
            #line 337 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = new_return_stmt_node(NULL);
            } is_exec_return_stmt
         } break;

      case YYr132:
         {
            /* jump_statement : RETURN expression ';' */
            #line 338 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL; purge_ast(yypvt[-1].node);
            }
            else
            {
               yyval.node = new_return_stmt_node(yypvt[-1].node);
            } is_exec_return_stmt
         } break;

      case YYr133:
         {
            /* jump_statement : BREAK ';' */
            #line 339 "ci.y"
            yyval.node = new_break_stmt_node();
         } break;

      case YYr134:
         {
            /* jump_statement : CONTINUE ';' */
            #line 340 "ci.y"
            yyval.node = new_continue_stmt_node();
         } break;

      case YYr135:
         {
            /* compound_statement : '{' '}' */
            #line 344 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = new_compound_stmt_node(NULL,NULL);
            }
         } break;

      case YYr136:
         {
            /* compound_statement : '{' statement_list '}' */
            #line 345 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = yypvt[-1].node;
            }
         } break;

      case YYr137:
         {
            /* compound_statement : '{' variable_declaration_list '}' */
            #line 346 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = yypvt[-1].node;
            }
         } break;

      case YYr138:
         {
            /* compound_statement : '{' variable_declaration_list statement_list '}' */
            #line 347 "ci.y"
            if (stmt_exec_env)
            {
               yyval.node = NULL;
            }
            else
            {
               yyval.node = new_compound_stmt_node(yypvt[-2].node,yypvt[-1].node);
            }
         } break;

      case YYr139:
         {
            /* parameter_list : */
            #line 351 "ci.y"
            yyval.node = NULL;
         } break;

      case YYr140:
         {
            /* parameter_list : parameter */
            #line 352 "ci.y"
            yyval.node = new_param_list_node(yypvt[0].node);
         } break;

      case YYr141:
         {
            /* parameter_list : parameter_list ',' parameter */
            #line 353 "ci.y"
            yyval.node = append_param_list_node(yypvt[-2].node,yypvt[0].node);
         } break;

      case YYr142:
         {
            /* parameter : type IDENTIFIER */
            #line 357 "ci.y"
            yyval.node = new_param_node(yypvt[-1].node,yypvt[0].string); free(yypvt[0].string);
         } break;

      case YYr143:
         {
            /* function_definition : type IDENTIFIER '(' parameter_list ')' compound_statement */
            #line 361 "ci.y"
            yyval.node = new_func_def_node(yypvt[-5].node,yypvt[-4].string,yypvt[-2].node,yypvt[0].node); free(yypvt[-4].string);
         } break;

      case YYr144:
         {
            /* function_call : IDENTIFIER '(' argument_expression_list ')' */
            #line 365 "ci.y"
            yyval.node = new_func_call_node(yypvt[-3].string,yypvt[-1].node); free(yypvt[-3].string);
         } break;

      case YYr145:
         {
            /* printf_call : LIB_PRINTF '(' argument_expression_list ')' */
            #line 369 "ci.y"
            yyval.node = new_printf_call_node(yypvt[-1].node);
         } break;

      case YYr146:
         {
            /* scanf_call : LIB_SCANF '(' argument_expression_list ')' */
            #line 373 "ci.y"
            yyval.node = new_scanf_call_node(yypvt[-1].node);
         } break;

      case YYr147:
         {
            /* argument_expression_list : */
            #line 377 "ci.y"
            yyval.node = NULL;
         } break;

      case YYr148:
         {
            /* argument_expression_list : assignment_expression */
            #line 378 "ci.y"
            yyval.node = new_arg_exp_list_node(yypvt[0].node);
         } break;

      case YYr149:
         {
            /* argument_expression_list : argument_expression_list ',' assignment_expression */
            #line 379 "ci.y"
            yyval.node = append_arg_exp_list_node(yypvt[-2].node,yypvt[0].node);
         } break;

      case YYr150:
         {
            /* global_declaration : function_definition */
            #line 383 "ci.y"
            yyval.node = yypvt[0].node; eval_func_def(yyval.node); if (_interact_env_)
            {
                                                                      print_prompt();
            }
         } break;

      case YYr151:
         {
            /* global_declaration : variable_declaration */
            #line 384 "ci.y"
            yyval.node = yypvt[0].node; eval_global_var_decl(yyval.node); if (_interact_env_)
            {
                                                                             print_prompt();
            }
         } break;

      case YYr152:
         {
            /* main_prototype : INT_TYPE MAIN_FUNCTION '(' ')' */
            #line 388 "ci.y"
            yyval.node = NULL; _main_env_ = TRUE; if (_interact_env_)
            {
                                                     print_prompt();
            } ar*                record   = new_ar(MAIN_FUNCTION_LABEL); push_ar(record);
         } break;

      case YYr153:
         {
            /* main_definition : main_prototype compound_statement */
            #line 392 "ci.y"
            if (!_interact_env_)
            {
               yyval.node = new_main_def_node(yypvt[0].node); eval_main_def(yyval.node);
            }
            else
            {
               yyval.node = NULL; is_exec_return_stmt
            }
         } break;

      case YYr154:
         {
            /* translation_unit : global_declaration */
            #line 396 "ci.y"
            yyval.node = NULL;
         } break;

      case YYr155:
         {
            /* translation_unit : translation_unit global_declaration */
            #line 397 "ci.y"
            yyval.node = NULL;
         } break;

      case YYr156:
         {
            /* script : main_definition */
            #line 401 "ci.y"
            yyval.node = new_func_call_node(MAIN_FUNCTION_LABEL,NULL); set_main_ref(yyval.node); return 0;
         } break;

      case YYr157:
         {
            /* script : translation_unit main_definition */
            #line 402 "ci.y"
            yyval.node = new_func_call_node(MAIN_FUNCTION_LABEL,NULL); set_main_ref(yyval.node); return 0;
         } break;
         #line 314 "D:\YACC/etc/yyparse.c"
      case YYrACCEPT:
         YYACCEPT;
      case YYrERROR:
         goto yyError;
   }

   /*
   * Look up next state in goto table.
   */

   yyp = &yygo[yypgo[yyi]];
   yyq = yyp++;
   yyi = *yyps;
   while (yyi < *yyp++)
   ;

   yystate = ~(yyi == *--yyp ? YYQYYP : *yyq);
   #if YYDEBUG
   if (yydebug)
   {
      YY_TRACE(yyShowGoto)
   }
   #endif
   goto yyStack;

   yyerrlabel: ; /* come here from YYERROR */
   /*
   #pragma used yyerrlabel
   */
   yyerrflag = 1;
   if (yyi == YYrERROR)
   {
      yyps--;
      yypv--;
      #if YYDEBUG
      yytp--;
      #endif
   }

   yyError:
   switch (yyerrflag)
   {
      case 0:
         /* new error */
         yynerrs++;
         yyi = yychar;
         yyerror("Syntax error");
         if (yyi != yychar)
         {
            /* user has changed the current token */
            /* try again */
            yyerrflag++; /* avoid loops */
            goto yyEncore;
         }

      case 1:
         /* partially recovered */
      case 2:
         yyerrflag = 3; /* need 3 valid shifts to recover */

         /*
         * Pop states, looking for a
         * shift on `error'.
         */

         for (; yyps > yys; yyps--, yypv--
                            #if YYDEBUG
                            , yytp--
                            #endif
             )
         {
            if (*yyps >= sizeof yypact / sizeof yypact[0])
            {
               continue;
            }
            yyp = &yyact[yypact[*yyps]];
            yyq = yyp;
            do
               ;
            while (YYERRCODE < *yyp++);

            if (YYERRCODE == yyp[-1])
            {
               yystate = ~YYQYYP;
               goto yyStack;
            }

            /* no shift in this state */
            #if YYDEBUG
            if (yydebug && yyps > yys + 1)
            {
               YY_TRACE(yyShowErrRecovery)
            }
            #endif
            /* pop stacks; try again */
         }
         /* no shift on error - abort */
         break;

      case 3:
         /*
         * Erroneous token after
         * an error - discard it.
         */

         if (yychar == 0) /* but not EOF */
         {
            break;
         }
         #if YYDEBUG
         if (yydebug)
         {
            YY_TRACE(yyShowErrDiscard)
         }
         #endif
         yyclearin;
         goto yyEncore; /* try again in same state */
   }     
   YYABORT;

   #ifdef YYALLOC
   yyReturn:
   yylval = save_yylval;
   yyval = save_yyval;
   yypvt = save_yypvt;
   yychar = save_yychar;
   yyerrflag = save_yyerrflag;
   yynerrs = save_yynerrs;
   free((char *) yys);
   free((char *) yyv);
   return(retval);
   #endif
}


#if YYDEBUG
/*
* Return type of token
*/
int   yyGetType(tok)
int   tok;
{
   yyNamedType*   tp;
   for (tp = &yyTokenTypes[yyntoken - 1]; tp > yyTokenTypes; tp--)
   {
      if (tp->token == tok)
      {
         return tp->type;
      }
   }
   return 0;
}
/*
* Print a token legibly.
*/
char* yyptok(tok)
int   tok;
{
   yyNamedType*   tp;
   for (tp = &yyTokenTypes[yyntoken - 1]; tp > yyTokenTypes; tp--)
   {
      if (tp->token == tok)
      {
         return tp->name;
      }
   }
   return "";
}

/*
* Read state 'num' from YYStatesFile
*/
#ifdef YYTRACE
static FILE*   yyStatesFile   = (FILE*) 0;
static char    yyReadBuf[YYMAX_READ + 1];

static char*   yygetState(num)
int            num;
{
   int   size;

   if (yyStatesFile == (FILE *) 0 && (yyStatesFile = fopen(YYStatesFile,"r")) == (FILE *) 0)
   {
      return "yyExpandName: cannot open states file";
   }

   if (num < yynstate - 1)
   {
      size = (int) (yyStates[num + 1] - yyStates[num]);
   }
   else
   {
      /* length of last item is length of file - ptr(last-1) */
      if (fseek(yyStatesFile,0L,2) < 0)
      {
         goto cannot_seek;
      }
      size = (int) (ftell(yyStatesFile) - yyStates[num]);
   }
   if (size <0 || size> YYMAX_READ)
   {
      return "yyExpandName: bad read size";
   }
   if (fseek(yyStatesFile,yyStates[num],0) < 0)
   {
      cannot_seek:
      return "yyExpandName: cannot seek in states file";
   }

   (void) fread(yyReadBuf,1,size,yyStatesFile);
   yyReadBuf[size] = '\0';
   return yyReadBuf;
}
#endif /* YYTRACE */
/*
* Expand encoded string into printable representation
* Used to decode yyStates and yyRules strings.
* If the expansion of 's' fits in 'buf', return 1; otherwise, 0.
*/
int   yyExpandName(num,isrule,buf,len)
int   num, isrule;
char* buf;
int   len;
{
   int   i, n, cnt, type;
   char* endp, * cp;
   char* s;

   if (isrule)
   {
      s = yyRules[num].name;
   }
   else
   #ifdef YYTRACE
   {
      s = yygetState(num);
   }
   #else
   s = "*no states*";
   #endif

   for (endp = buf + len - 8; *s; s++)
   {
      if (buf >= endp)
      {
         /* too large: return 0 */
         full: (void) strcpy(buf," ...\n");
         return 0;
      }
      else if (*s == '%')
      {
         /* nonterminal */
         type = 0;
         cnt = yynvar;
         goto getN;
      }
      else if (*s == '&')
      {
         /* terminal */
         type = 1;
         cnt = yyntoken;
         getN:
         if (cnt < 100)
         {
            i = 2;
         }
         else if (cnt < 1000)
         {
            i = 3;
         }
         else
         {
            i = 4;
         }
         for (n = 0; i-- > 0;)
         {
            n = (n * 10) + *++s - '0';
         }
         if (type == 0)
         {
            if (n >= yynvar)
            {
               goto too_big;
            }
            cp = yysvar[n];
         }
         else if (n >= yyntoken)
         {
            too_big:
            cp = "<range err>";
         }
         else
         {
            cp = yyTokenTypes[n].name;
         }

         if ((i = strlen(cp)) + buf > endp)
         {
            goto full;
         }
         (void) strcpy(buf,cp);
         buf += i;
      }
      else
      {
         *buf++ = *s;
      }
   }
   *buf = '\0';
   return 1;
}
#ifndef YYTRACE
/*
* Show current state of yyparse
*/
void  yyShowState(tp)
yyTraceItems*  tp;
{
   short*   p;
   YYSTYPE* q;

   printf(gettext("state %d (%d), char %s (%d)\n"),yysmap[tp->state],tp->state,yyptok(tp->lookahead),tp->lookahead);
}
/*
* show results of reduction
*/
void  yyShowReduce(tp)
yyTraceItems*  tp;
{
   printf("reduce %d (%d), pops %d (%d)\n",yyrmap[tp->rule],tp->rule,tp->states[tp->nstates - tp->npop],yysmap[tp->states[tp->nstates - tp->npop]]);
}
void  yyShowRead(val)
int   val;
{
   printf(gettext("read %s (%d)\n"),yyptok(val),val);
}
void  yyShowGoto(tp)
yyTraceItems*  tp;
{
   printf(gettext("goto %d (%d)\n"),yysmap[tp->state],tp->state);
}
void  yyShowShift(tp)
yyTraceItems*  tp;
{
   printf(gettext("shift %d (%d)\n"),yysmap[tp->state],tp->state);
}
void  yyShowErrRecovery(tp)
yyTraceItems*  tp;
{
   short*   top   = tp->states + tp->nstates - 1;

   printf(gettext("Error recovery pops state %d (%d), uncovers %d (%d)\n"),yysmap[*top],*top,yysmap[*(top - 1)],*(top - 1));
}
void  yyShowErrDiscard(tp)
yyTraceItems*  tp;
{
   printf(gettext("Error recovery discards %s (%d), "),yyptok(tp->lookahead),tp->lookahead);
}
#endif /* ! YYTRACE */
#endif /* YYDEBUG */
