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
extern YYSTYPE    yylval;
