/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "Yacc.y"

#include <stdio.h>
#include "SymbolTable.h"

#define oprintf(s, ...)	\
	do{	\
		char format[2048];	\
		sprintf(format, "{%s}\r\n", s);	\
		fprintf(stdout, format, ##__VA_ARGS__);	\
	}while(0)
#define grammar(s)	"\033[38;5;12m"s"\033[0;0m"
#define gmr(s)			grammar(s)
#define grammarP(s)	"\033[38;5;69m"s"\033[0;0m"
#define terminal(s)	"\033[38;5;190m"s"\033[0;0m"
#define derive(s, f, ...)	oprintf(grammarP(s)" -> "f, ##__VA_ARGS__)
#define constant(s)	"\033[38;5;196m"s"\033[0;0m"
#define id(s)	"\033[38;5;190m"s"\033[0;0m"

extern FILE *yyin;
symbolTable *global, *current;

void yyerror(char *msg)
{
    fprintf(stderr, "%s\r\n", msg);
}

/*void oprintf(const char *s){
	char format[4096];
	sprintf(buff, "{%s}\r\n", s);
	fprintf(stdout, format, s);
}

char *grammar(const char *s){
	char buff[256];
	sprintf(buff, "\033[38;5;69m%s\033[0;0m", s);
	return buff;
}*/



/* Line 268 of yacc.c  */
#line 112 "Yacc.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 288 of yacc.c  */
#line 41 "Yacc.y"

	#include "SymbolTable.h"
	typedef struct _NODE *nodeP;



/* Line 288 of yacc.c  */
#line 143 "Yacc.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DEL_COMMA = 258,
     DEL_COLON = 259,
     DEL_DUAL_COLON = 260,
     DEL_SEMICOLON = 261,
     DEL_L_PARENTHESIS = 262,
     DEL_R_PARENTHESIS = 263,
     DEL_L_SQUARE_BRACKET = 264,
     DEL_R_SQUARE_BRACKET = 265,
     DEL_L_BRACKET = 266,
     DEL_R_BRACKET = 267,
     DEL_COMPONENT_REF = 268,
     OP_ADD = 269,
     OP_SUB = 270,
     OP_MULTIPLY = 271,
     OP_DIVIDE = 272,
     OP_EXPONENT = 273,
     OP_CONCAT = 274,
     OP_LT = 275,
     OP_LE = 276,
     OP_GT = 277,
     OP_GE = 278,
     OP_EQ = 279,
     OP_NE = 280,
     OP_AND = 281,
     OP_OR = 282,
     OP_NOT = 283,
     OP_EQV = 284,
     OP_NEQV = 285,
     OP_ASSIGN = 286,
     OP_POINTER_ASSIGN = 287,
     KW_CALL = 288,
     KW_CASE = 289,
     KW_CHAR = 290,
     KW_CLOSE = 291,
     KW_COMMON = 292,
     KW_CONT = 293,
     KW_CYCLE = 294,
     KW_DATA = 295,
     KW_DIM = 296,
     KW_DO = 297,
     KW_ELSE = 298,
     KW_END = 299,
     KW_EXIT = 300,
     KW_FUNC = 301,
     KW_GOTO = 302,
     KW_IF = 303,
     KW_INT = 304,
     KW_INTERFACE = 305,
     KW_LOGIC = 306,
     KW_PROCEDURE = 307,
     KW_PARAMETER = 308,
     KW_PRINT = 309,
     KW_PRINTLN = 310,
     KW_POINTER = 311,
     KW_PROGRAM = 312,
     KW_READ = 313,
     KW_REAL = 314,
     KW_RECURSIVE = 315,
     KW_RETURN = 316,
     KW_SELECT = 317,
     KW_STOP = 318,
     KW_SUB = 319,
     KW_TYPE = 320,
     KW_THEN = 321,
     CONST_BOOL = 322,
     CONST_INT = 323,
     CONST_REAL = 324,
     CONST_STRING = 325,
     IDENTIFIER = 326,
     C_EOF = 327,
     C_LF = 328,
     UMINUS = 329
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 66 "Yacc.y"

	struct _CONST{
		int type;	// 0x01 for int, 0x02 for double, 0x03 for string, 0x04 for boolean.
		union _DATA{
			int Zval;
			double Rval;
			char Str[2048];
		} data;
	} constant;
	struct _NODE{
		element *ep;
		nodeP next;
	} node;



/* Line 293 of yacc.c  */
#line 251 "Yacc.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 263 "Yacc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   196

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNRULES -- Number of states.  */
#define YYNSTATES  180

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   329

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    12,    13,    23,    27,    31,
      32,    37,    39,    44,    46,    48,    50,    52,    56,    57,
      62,    64,    66,    68,    69,    72,    76,    77,    80,    81,
      88,    91,    92,    93,   105,   106,   118,   119,   130,   131,
     142,   146,   147,   149,   150,   154,   158,   159,   162,   165,
     170,   172,   174,   176,   180,   181,   183,   185,   187,   191,
     195,   198,   202,   206,   210,   214,   218,   222,   226,   230,
     234,   238,   242,   246,   250,   253,   255,   257,   259,   261,
     263,   267,   269,   271,   273,   275,   278,   281
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      76,     0,    -1,    78,    77,    72,    -1,    96,   113,    77,
      -1,    -1,    -1,    57,    71,   113,    79,    80,    44,    57,
      71,   113,    -1,    81,    90,   101,    -1,    82,   113,    81,
      -1,    -1,    84,    85,    87,    88,    -1,    83,    -1,    37,
      17,    71,    17,    -1,    35,    -1,    49,    -1,    59,    -1,
      51,    -1,     3,    86,    85,    -1,    -1,    41,     7,    68,
       8,    -1,    56,    -1,    53,    -1,     5,    -1,    -1,    71,
      89,    -1,     3,    71,    89,    -1,    -1,    91,    90,    -1,
      -1,    50,   113,    92,    44,    50,   113,    -1,    93,    92,
      -1,    -1,    -1,   100,    64,    71,    99,   113,    94,    81,
      44,    64,    71,   113,    -1,    -1,   100,    46,    71,    99,
     113,    95,    81,    44,    46,    71,   113,    -1,    -1,   100,
      64,    71,    99,   113,    97,    80,    44,    64,    71,    -1,
      -1,   100,    46,    71,    99,   113,    98,    80,    44,    46,
      71,    -1,     7,    88,     8,    -1,    -1,    60,    -1,    -1,
     103,   113,   102,    -1,   103,   113,   102,    -1,    -1,    58,
      71,    -1,   104,   110,    -1,    71,   105,   112,   110,    -1,
     110,    -1,    54,    -1,    55,    -1,     9,   111,    10,    -1,
      -1,   109,    -1,   108,    -1,   107,    -1,   110,    26,   110,
      -1,   110,    27,   110,    -1,    28,   110,    -1,   110,    29,
     110,    -1,   110,    30,   110,    -1,   110,    20,   110,    -1,
     110,    21,   110,    -1,   110,    22,   110,    -1,   110,    23,
     110,    -1,   110,    24,   110,    -1,   110,    25,   110,    -1,
     110,    14,   110,    -1,   110,    15,   110,    -1,   110,    16,
     110,    -1,   110,    17,   110,    -1,   110,    18,   110,    -1,
      15,   110,    -1,    68,    -1,    69,    -1,    67,    -1,    71,
      -1,   106,    -1,     7,   106,     8,    -1,    68,    -1,    71,
      -1,    31,    -1,    32,    -1,    73,   114,    -1,    73,   114,
      -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    99,   100,   103,   102,   115,   117,   121,
     123,   128,   130,   132,   133,   134,   135,   137,   138,   140,
     141,   142,   144,   145,   147,   154,   159,   161,   162,   164,
     166,   167,   170,   169,   183,   182,   197,   196,   210,   209,
     223,   224,   226,   227,   229,   231,   232,   234,   235,   236,
     237,   239,   240,   242,   243,   245,   246,   247,   249,   250,
     251,   252,   253,   255,   256,   257,   258,   259,   260,   262,
     263,   264,   265,   266,   267,   269,   270,   271,   272,   273,
     274,   276,   277,   279,   280,   282,   284,   285
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEL_COMMA", "DEL_COLON",
  "DEL_DUAL_COLON", "DEL_SEMICOLON", "DEL_L_PARENTHESIS",
  "DEL_R_PARENTHESIS", "DEL_L_SQUARE_BRACKET", "DEL_R_SQUARE_BRACKET",
  "DEL_L_BRACKET", "DEL_R_BRACKET", "DEL_COMPONENT_REF", "OP_ADD",
  "OP_SUB", "OP_MULTIPLY", "OP_DIVIDE", "OP_EXPONENT", "OP_CONCAT",
  "OP_LT", "OP_LE", "OP_GT", "OP_GE", "OP_EQ", "OP_NE", "OP_AND", "OP_OR",
  "OP_NOT", "OP_EQV", "OP_NEQV", "OP_ASSIGN", "OP_POINTER_ASSIGN",
  "KW_CALL", "KW_CASE", "KW_CHAR", "KW_CLOSE", "KW_COMMON", "KW_CONT",
  "KW_CYCLE", "KW_DATA", "KW_DIM", "KW_DO", "KW_ELSE", "KW_END", "KW_EXIT",
  "KW_FUNC", "KW_GOTO", "KW_IF", "KW_INT", "KW_INTERFACE", "KW_LOGIC",
  "KW_PROCEDURE", "KW_PARAMETER", "KW_PRINT", "KW_PRINTLN", "KW_POINTER",
  "KW_PROGRAM", "KW_READ", "KW_REAL", "KW_RECURSIVE", "KW_RETURN",
  "KW_SELECT", "KW_STOP", "KW_SUB", "KW_TYPE", "KW_THEN", "CONST_BOOL",
  "CONST_INT", "CONST_REAL", "CONST_STRING", "IDENTIFIER", "C_EOF", "C_LF",
  "UMINUS", "$accept", "file_p", "file", "program", "$@1",
  "program_description", "var_const_declare_p", "var_const_declare",
  "global_declare", "type", "attr_list", "attrs", "dual_colon",
  "id_list_p", "id_list", "interface_declare_p", "interface_declare",
  "procedure_declaration_p", "procedure_declaration", "$@2", "$@3",
  "procedure_description", "$@4", "$@5", "arguments", "recursive_p",
  "stmts", "stmt_p", "stmt", "print_p", "array_indexing", "expr",
  "boolean_operation", "relational_operation", "mathematical_operation",
  "computable", "integer_expr", "assign", "linebreak_p", "linebreak", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    77,    77,    79,    78,    80,    81,    81,
      82,    82,    83,    84,    84,    84,    84,    85,    85,    86,
      86,    86,    87,    87,    88,    89,    89,    90,    90,    91,
      92,    92,    94,    93,    95,    93,    97,    96,    98,    96,
      99,    99,   100,   100,   101,   102,   102,   103,   103,   103,
     103,   104,   104,   105,   105,   106,   106,   106,   107,   107,
     107,   107,   107,   108,   108,   108,   108,   108,   108,   109,
     109,   109,   109,   109,   109,   110,   110,   110,   110,   110,
     110,   111,   111,   112,   112,   113,   114,   114
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     0,     0,     9,     3,     3,     0,
       4,     1,     4,     1,     1,     1,     1,     3,     0,     4,
       1,     1,     1,     0,     2,     3,     0,     2,     0,     6,
       2,     0,     0,    11,     0,    11,     0,    10,     0,    10,
       3,     0,     1,     0,     3,     3,     0,     2,     2,     4,
       1,     1,     1,     3,     0,     1,     1,     1,     3,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     2,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    43,     0,     1,    42,     0,     0,     0,
      87,     5,     2,    43,     0,     0,    87,    85,     9,     3,
      41,    41,    86,    13,     0,    14,    16,    15,     0,    28,
       0,    11,    18,     0,     0,     0,     0,     0,     0,     0,
      28,     9,     0,    23,    26,     0,    38,    36,     0,     0,
      43,     0,     0,     0,    51,    52,     0,    77,    75,    76,
      78,     7,     0,     0,    79,    57,    56,    55,    50,    27,
       8,     0,    21,    20,    18,    22,     0,     0,    24,    40,
       9,     9,    12,     0,     0,    43,     0,    78,    79,     0,
      74,    60,    47,     0,     0,    46,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,    10,    26,     0,     0,     6,     0,
      30,     0,     0,    80,    81,    82,     0,    83,    84,     0,
      44,     0,    69,    70,    71,    72,    73,    63,    64,    65,
      66,    67,    68,    58,    59,    61,    62,     0,    25,     0,
       0,     0,    41,    41,    53,    49,    46,    19,     0,     0,
      29,     0,     0,    45,    39,    37,    34,    32,     9,     9,
       0,     0,     0,     0,     0,     0,     0,     0,    35,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,     3,    18,    28,    29,    30,    31,    32,
      43,    74,    76,    45,    78,    39,    40,    84,    85,   169,
     168,     8,    81,    80,    34,     9,    61,   130,   131,    63,
      94,    64,    65,    66,    67,    68,   126,   129,    11,    17
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -54
static const yytype_int16 yypact[] =
{
     -49,   -46,    46,   -53,    -1,   -54,   -54,   -23,    -1,   -41,
       0,   -54,   -54,   -53,     7,     8,     0,   -54,   -31,   -54,
      67,    67,   -54,   -54,    64,   -54,   -54,   -54,    38,    33,
      -1,   -54,    89,    28,    -1,    -1,    37,    59,    -1,    22,
      33,   -31,    -5,   119,   122,   118,   -54,   -54,   110,    57,
     -27,    17,    17,    17,   -54,   -54,    60,   -54,   -54,   -54,
       3,   -54,    -1,    17,   -54,   -54,   -54,   -54,    80,   -54,
     -54,   127,   -54,   -54,    89,   -54,    28,    65,   -54,   -54,
     -31,   -31,   -54,    -1,    91,   -27,   -33,   -54,   129,    80,
     -54,    97,   -54,   -24,    21,    22,    80,    17,    17,    17,
      17,    17,    17,    17,    17,    17,    17,    17,    17,    17,
      17,    17,    84,   -54,   -54,   122,   116,   126,   -54,   121,
     -54,   101,   102,   -54,   -54,   -54,   164,   -54,   -54,    17,
     -54,    -1,    -2,    -2,   157,   157,   157,    25,    25,    25,
      25,    25,    25,    97,   141,   124,   124,   168,   -54,   131,
     114,    -1,    67,    67,   -54,    80,    22,   -54,   108,   109,
     -54,    -1,    -1,   -54,   -54,   -54,   -54,   -54,   -31,   -31,
     137,   138,   139,   120,   112,   115,    -1,    -1,   -54,   -54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   174,   -54,   -54,   -10,   -39,   -54,   -54,   -54,
     117,   -54,   -54,   113,    73,   150,   -54,   107,   -54,   -54,
     -54,   -54,   -54,   -54,   -20,   -47,   -54,    39,   154,   -54,
     -54,   143,   -54,   -54,   -54,   -42,   -54,   -54,    -8,   180
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -55
static const yytype_int16 yytable[] =
{
      13,    35,    70,    86,    23,    14,    24,     6,     1,    89,
      90,    91,    93,   121,    99,   100,   101,   -31,    25,    -4,
      26,    96,    41,    15,    51,     4,    46,    47,    27,    51,
      50,   122,    52,     6,   -54,   -54,    71,    52,    86,    97,
      98,    99,   100,   101,   124,    53,     5,   125,    72,    12,
      53,    73,   127,   128,    95,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     116,   117,    10,    16,    33,   118,    54,    55,    20,    21,
      56,    36,    37,    38,    57,    58,    59,   155,    87,    57,
      58,    59,    42,    60,    97,    98,    99,   100,   101,    44,
     102,   103,   104,   105,   106,   107,   108,   109,    48,   110,
     111,    97,    98,    99,   100,   101,    49,   102,   103,   104,
     105,   106,   107,   156,    75,    77,    79,    82,    83,   170,
     171,    92,   161,   162,   112,   119,   115,   123,    97,    98,
      99,   100,   101,   160,   102,   103,   104,   105,   106,   107,
     108,   109,   147,   166,   167,    97,    98,    99,   100,   101,
     149,   102,   103,   104,   105,   106,   107,   108,   178,   179,
     150,   151,   152,   153,   154,   101,   157,   158,   159,   164,
     165,   172,   173,   176,   175,   174,   177,    19,   148,   114,
      69,   113,   120,    62,    88,   163,    22
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-54))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
       8,    21,    41,    50,    35,    46,    37,    60,    57,    51,
      52,    53,     9,    46,    16,    17,    18,    44,    49,    72,
      51,    63,    30,    64,     7,    71,    34,    35,    59,     7,
      38,    64,    15,    60,    31,    32,    41,    15,    85,    14,
      15,    16,    17,    18,    68,    28,     0,    71,    53,    72,
      28,    56,    31,    32,    62,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
      80,    81,    73,    73,     7,    83,    54,    55,    71,    71,
      58,    17,    44,    50,    67,    68,    69,   129,    71,    67,
      68,    69,     3,    71,    14,    15,    16,    17,    18,    71,
      20,    21,    22,    23,    24,    25,    26,    27,    71,    29,
      30,    14,    15,    16,    17,    18,    57,    20,    21,    22,
      23,    24,    25,   131,     5,     3,     8,    17,    71,   168,
     169,    71,   152,   153,     7,    44,    71,     8,    14,    15,
      16,    17,    18,   151,    20,    21,    22,    23,    24,    25,
      26,    27,    68,   161,   162,    14,    15,    16,    17,    18,
      44,    20,    21,    22,    23,    24,    25,    26,   176,   177,
      44,    50,    71,    71,    10,    18,     8,    46,    64,    71,
      71,    44,    44,    71,    64,    46,    71,    13,   115,    76,
      40,    74,    85,    39,    51,   156,    16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,    76,    78,    71,     0,    60,    77,    96,   100,
      73,   113,    72,   113,    46,    64,    73,   114,    79,    77,
      71,    71,   114,    35,    37,    49,    51,    59,    80,    81,
      82,    83,    84,     7,    99,    99,    17,    44,    50,    90,
      91,   113,     3,    85,    71,    88,   113,   113,    71,    57,
     113,     7,    15,    28,    54,    55,    58,    67,    68,    69,
      71,   101,   103,   104,   106,   107,   108,   109,   110,    90,
      81,    41,    53,    56,    86,     5,    87,     3,    89,     8,
      98,    97,    17,    71,    92,    93,   100,    71,   106,   110,
     110,   110,    71,     9,   105,   113,   110,    14,    15,    16,
      17,    18,    20,    21,    22,    23,    24,    25,    26,    27,
      29,    30,     7,    85,    88,    71,    80,    80,   113,    44,
      92,    46,    64,     8,    68,    71,   111,    31,    32,   112,
     102,   103,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,    68,    89,    44,
      44,    50,    71,    71,    10,   110,   113,     8,    46,    64,
     113,    99,    99,   102,    71,    71,   113,   113,    95,    94,
      81,    81,    44,    44,    46,    64,    71,    71,   113,   113
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 97 "Yacc.y"
    { return 0; /* acceptable state */ }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 103 "Yacc.y"
    {
				symbolTable *temp = create(current);
				//lookup(current, $2.ep->variable)->subRegion = temp;
				(yyvsp[(2) - (3)].node).ep->subRegion = temp;
				current = temp;
			}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 109 "Yacc.y"
    {
				current = current->parent;
				derive("program", "program "id("%s")" "gmr("linebreak_p")" "gmr("program_description")" end program "id("%s")" "gmr("ends"), (yyvsp[(2) - (9)].node).ep->variable, (yyvsp[(8) - (9)].node).ep->variable);
				
			}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 115 "Yacc.y"
    { derive("program_description", gmr("var_const_declare_p")" "gmr("interface_declare_p")" "gmr("stmts")); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 118 "Yacc.y"
    {
							derive("var_const_declare_p", gmr("var_const_declare")" "gmr("linebreak_p")" "gmr("var_const_declare_p"));
						}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 124 "Yacc.y"
    {
							
							derive("var_const_declare", gmr("global_declare")" "gmr("type")" "gmr("attr_list")" "gmr("dual_colon")" "gmr("id_list_p"));
						}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 128 "Yacc.y"
    { derive("var_const_declare", gmr("global_declare")); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 130 "Yacc.y"
    { derive("global_declare", "common / "id("%s")" / ", (yyvsp[(3) - (4)].node).ep->variable); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 132 "Yacc.y"
    { (yyval.constant).type = 3; derive("type", "character "); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 133 "Yacc.y"
    { (yyval.constant).type = 1; derive("type", "integer "); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 134 "Yacc.y"
    { (yyval.constant).type = 2; derive("type", "real "); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 135 "Yacc.y"
    { (yyval.constant).type = 4; derive("type", "logical "); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 137 "Yacc.y"
    { derive("attr_list", ", "gmr("attrs")" "gmr("attrs_list")); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 140 "Yacc.y"
    { derive("attrs", "dimension ( %d )", (yyvsp[(3) - (4)].constant).data.Zval); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 141 "Yacc.y"
    { derive("attrs", "pointer"); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 142 "Yacc.y"
    { derive("attrs", "parameter"); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 144 "Yacc.y"
    { derive("dual_colon", "::"); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 148 "Yacc.y"
    {
					/*$$.next = $2;
					$$.ep = lookup($1.data.Str);*/
					derive("id_list_p", id("%s")" "gmr("id_list"), (yyvsp[(1) - (2)].node).ep->variable);
				}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 155 "Yacc.y"
    {
				
				derive("id_list", ", "id("%s")" "gmr("id_list"), (yyvsp[(2) - (3)].node).ep->variable);
			}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 161 "Yacc.y"
    { derive("interface_declare_p", gmr("interface_declare")gmr("interface_declare_p")); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 164 "Yacc.y"
    { derive("interface_declare", "interface "gmr("linebreak_p")" "gmr("procedure_declaration")" end interface "gmr("linebreak_p")); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 170 "Yacc.y"
    {
								symbolTable *temp = create(current);
								//lookup(current, $3.data.Str)->subRegion = temp;
								(yyvsp[(3) - (5)].node).ep->subRegion = temp;
								current = temp;
							}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 178 "Yacc.y"
    {
								current = current->parent;
								derive("procedure_declaration", gmr("recursive_p")" subroutine "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end subroutine "id("%s")" "gmr("linebreak_p"), (yyvsp[(3) - (11)].node).ep->variable, (yyvsp[(3) - (11)].node).ep->variable);
							}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 183 "Yacc.y"
    {
								symbolTable *temp = create(current);
								//lookup(current, $3.data.Str)->subRegion = temp;
								(yyvsp[(3) - (5)].node).ep->subRegion = temp;
								current = temp;
							}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 191 "Yacc.y"
    {
								current = current->parent;
								derive("procedure_declaration", gmr("recursive_p")" function "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end function "id("%s")" "gmr("linebreak_p"), (yyvsp[(3) - (11)].node).ep->variable, (yyvsp[(3) - (11)].node).ep->variable);
							}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 197 "Yacc.y"
    {
								symbolTable *temp = create(current);
								//lookup(current, $3.data.Str)->subRegion = temp;
								(yyvsp[(3) - (5)].node).ep->subRegion = temp;
								current = temp;
							}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 205 "Yacc.y"
    {
								current = current->parent;
								derive("procedure_description", gmr("recursive_p")" subroutine "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end subroutine "id("%s")" "gmr("linebreak_p"), (yyvsp[(3) - (10)].node).ep->variable, (yyvsp[(3) - (10)].node).ep->variable);
							}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 210 "Yacc.y"
    {
								symbolTable *temp = create(current);
								//lookup(current, $3.data.Str)->subRegion = temp;
								(yyvsp[(3) - (5)].node).ep->subRegion = temp;
								current = temp;
							}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 218 "Yacc.y"
    {
								current = current->parent;
								derive("procedure_description", gmr("recursive_p")" function "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end function "id("%s")" "gmr("linebreak_p"), (yyvsp[(3) - (10)].node).ep->variable, (yyvsp[(3) - (10)].node).ep->variable);
							}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 223 "Yacc.y"
    { derive("arguments", "( "gmr("id_list_p")" )"); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 226 "Yacc.y"
    { derive("recursive_p", "recursive"); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 229 "Yacc.y"
    { derive("stmts", gmr("stmt")" "gmr("linebreak_p")" "gmr("stmt_p")); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 231 "Yacc.y"
    { derive("stmt_p", gmr("stmt")" "gmr("linebreak_p")" "gmr("stmt_p")); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 234 "Yacc.y"
    { derive("stmt", "read "id("%s"), (yyvsp[(2) - (2)].node).ep->variable); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 235 "Yacc.y"
    { derive("stmt", gmr("print_p")" "gmr("computable")); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 236 "Yacc.y"
    { derive("stmt", id("%s")" "gmr("array_indexing")" "gmr("assign")" "gmr("computable"), (yyvsp[(1) - (4)].node).ep->variable); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 237 "Yacc.y"
    { derive("stmt", gmr("computable")); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 239 "Yacc.y"
    { derive("print_p", "print"); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 240 "Yacc.y"
    { derive("print_p", "println"); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 242 "Yacc.y"
    { derive("array_indexing", "[ "gmr("integer_expr")" ]"); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 245 "Yacc.y"
    { derive("expr", gmr("mathematical_operation")); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 246 "Yacc.y"
    { derive("expr", gmr("relational_operation")); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 247 "Yacc.y"
    { derive("expr", gmr("boolean_operation")); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 249 "Yacc.y"
    { derive("boolean_operation", gmr("computable")" .AND. "gmr("computable")); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 250 "Yacc.y"
    { derive("boolean_operation", gmr("computable")" .OR. "gmr("computable")); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 251 "Yacc.y"
    { derive("boolean_operation", ".NOT. "gmr("computable")); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 252 "Yacc.y"
    { derive("boolean_operation", gmr("computable")" .EQV. "gmr("computable")); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 253 "Yacc.y"
    { derive("boolean_operation", gmr("computable")" .NEQV. "gmr("computable")); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 255 "Yacc.y"
    { derive("relational_operation", gmr("computable")" .LT. "gmr("computable")); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 256 "Yacc.y"
    { derive("relational_operation", gmr("computable")" .LE. "gmr("computable")); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 257 "Yacc.y"
    { derive("relational_operation", gmr("computable")" .GT. "gmr("computable")); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 258 "Yacc.y"
    { derive("relational_operation", gmr("computable")" .GE. "gmr("computable")); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 259 "Yacc.y"
    { derive("relational_operation", gmr("computable")" .EQ. "gmr("computable")); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 260 "Yacc.y"
    { derive("relational_operation", gmr("computable")" .NE. "gmr("computable")); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 262 "Yacc.y"
    { derive("mathematical_operation", gmr("computable")" + "gmr("computable")); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 263 "Yacc.y"
    { derive("mathematical_operation", gmr("computable")" - "gmr("computable")); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 264 "Yacc.y"
    { derive("mathematical_operation", gmr("computable")" * "gmr("computable")); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 265 "Yacc.y"
    { derive("mathematical_operation", gmr("computable")" / "gmr("computable")); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 266 "Yacc.y"
    { derive("mathematical_operation", gmr("computable")" ** "gmr("computable")); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 267 "Yacc.y"
    { derive("mathematical_operation", "- "gmr("computable")); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 269 "Yacc.y"
    { derive("computable", constant("%d"), (yyvsp[(1) - (1)].constant).data.Zval); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 270 "Yacc.y"
    { derive("computable", constant("%f"), (yyvsp[(1) - (1)].constant).data.Rval); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 271 "Yacc.y"
    { derive("computable", constant("%s"), ((yyvsp[(1) - (1)].constant).data.Zval)?("true"):("false")); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 272 "Yacc.y"
    { derive("computable", id("%s"), (yyvsp[(1) - (1)].node).ep->variable); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 273 "Yacc.y"
    { derive("computable", gmr("expr")); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 274 "Yacc.y"
    { derive("computable", "( "gmr("expr")" )"); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 276 "Yacc.y"
    { derive("integer_expr", constant("%d"), (yyvsp[(1) - (1)].constant).data.Zval); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 277 "Yacc.y"
    { derive("integer_expr", id("%s"), (yyvsp[(1) - (1)].node).ep->variable); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 279 "Yacc.y"
    { derive("assign", "="); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 280 "Yacc.y"
    { derive("assign", "=>"); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 282 "Yacc.y"
    { derive("linkbreak_p", "<C_LF> "gmr("linkbreak")); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 284 "Yacc.y"
    { derive("linkbreak", "<C_LF> "gmr("linkbreak")); }
    break;



/* Line 1806 of yacc.c  */
#line 2219 "Yacc.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 287 "Yacc.y"


int main(int argc, char* argv[]){
	if(argc>1){
		yyin = fopen(argv[1],"r");
		if(yyin != NULL)
			fprintf(stdout, "\033[38;5;46mScanning from file %s\033[0;0m\r\n", argv[1]);
		else
			fprintf(stdout, "\033[38;5;46mScanning from stdin\033[0;0m\r\n");
	}else
		fprintf(stdout, "\033[38;5;46mScanning from stdin\033[0;0m\r\n");

	global = current = create(NULL);
	yyparse();

	fprintf(stdout, "\033[38;5;46mEnd of scanning\033[0;0m\r\n");

	dump(global);
	release(current);
}

