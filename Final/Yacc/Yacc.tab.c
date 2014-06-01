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
#include <math.h>

#define oprintf(s, ...)								\
	do{													\
		char format[2048];							\
		sprintf(format, "{%s}\r\n", s);				\
		fprintf(stdout, format, ##__VA_ARGS__);	\
	}while(0)
#define lift2global(s)											\
	do{																\
		insertBucket(global, deleteBucket(current, *(s.ep)));	\
		if(s.ep->subRegion != NULL)								\
			s.ep->subRegion->parent = global;					\
	}while(0)
// The do while wrapping is for the semicolon swallowing
// Please refer to http://gcc.gnu.org/onlinedocs/cpp/Swallowing-the-Semicolon.html
	
#define grammar(s)	"\033[38;5;12m"s"\033[0;0m"
#define gmr(s)			grammar(s)
#define grammarP(s)	"\033[38;5;69m"s"\033[0;0m"
#define terminal(s)	"\033[38;5;190m"s"\033[0;0m"
#define derive(s, f, ...)								\
do{															\
	if(derivePrint)										\
		oprintf(grammarP(s)" -> "f, ##__VA_ARGS__);	\
}while(0)

#define constant(s)	"\033[38;5;197m"s"\033[0;0m"
#define id(s)	"\033[38;5;190m"s"\033[0;0m"
// Preproccessor can auto-connect those strings which are close and without any tokens between them.

#define ACCEPTABLE	0	// Acceptance state for yyparse
#define REJECT			1	// Rejected state fo yyparse

#define EMPTY_T	0	// each datatype presented by a code.
#define INT_T		1
#define REAL_T		2
#define STR_T		3
#define BOOL_T		4

#define isNum(s)	(s.type == INT_T || s.type == REAL_T)
#define typeString(s)	(s == BOOL_T)?("boolean"):(				\
							(s == INT_T)?("int"):(				\
								(s == REAL_T)?("real"):(			\
									(s == STR_T)?("string"):(	\
									"void")							\
								)									\
							)										\
						)

extern FILE *yyin;
extern long int lineNo;
symbolTable *global, *current;
int tokenPrint, derivePrint, errorOccured, failedRemove;
FILE *byteCode;
char className[250], tab_pad[] = {'\0', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\0'};
int local_count, tab_count = 0;

void yyerror(char *msg)
{
    fprintf(stderr, "\033[38;5;196m%d: %s\033[0;0m\r\n", lineNo, msg);
	errorOccured = 1;
}

void argListCopy(node headNode){
// After a procedure determine its arguments, we need to build a chain points to each element in symbol table.
	nodeP cur = headNode.ep->typeList, oldHead = cur, newC;
	if(cur != NULL && cur - oldHead < 0xFFFF){
	// I'm not sure why, but Yacc sometimes change the pointer to NULL.
	// So I use the distance of logical address to check if these pointers were established in a short peroid.
	// These works just copy the original "ep" to the new node.
		newC = (nodeP)malloc(sizeof(node));
		newC->ep = cur->ep;
		cur = cur->next;
		headNode.ep->typeList = newC;
		while(cur != NULL && cur - oldHead < 0xFFFF){
			newC->next = (nodeP)malloc(sizeof(node));
			newC = newC->next;
			newC->ep = cur->ep;
			cur = cur->next;
		}
	}else
		headNode.ep->typeList = NULL;
}

void tab(){
	if(tab_count >= 10){
		fprintf(stderr, "Error: over-nested program\r\n");
		return;
	}
	tab_pad[tab_count++] = '\t';
	tab_pad[tab_count] = '\0';
}

void tabShift(){
	if(tab_count <= 0){
		fprintf(stderr, "Error: minus tabShift called\r\n");
		return;
	}
	tab_pad[tab_count--] = '\t';
	tab_pad[tab_count] = '\0';
}

void printsAllGlobal(){
	int i;
	bucket *cur;
	for(i = 0; i< TABLE_SIZE ; i++){
		cur = global->table[i].link;
		while(cur != NULL){
			if(cur->inner.subRegion == NULL)		// Only int type needs to declare. Strings are treated as constant.
				fprintf(byteCode, "%sfield static %s %s\r\n", tab_pad, typeString(cur->inner.type), cur->inner.variable);
			cur = cur->link;
		}
	}
}

void printMethod(element e){
	nodeP cur;
	int first = 1;
	fprintf(byteCode, "%smethod public static %s %s(", tab_pad, typeString(e.type), e.variable);
	cur = e.typeList;
	while(cur != NULL){
		if(!first)
			fprintf(byteCode, ", ");
		else
			first = 0;
		fprintf(byteCode, typeString(cur->ep->type));
		cur = cur->next;
	}
	fprintf(byteCode, ")\r\n%smax_stack 15\r\n%smax_locals 15\r\n%s{\r\n", tab_pad, tab_pad, tab_pad);
	tab();
}

void enumerateLocalVar(symbolTable *st){
	int i, local_count=0;
	bucket *cur;
	for(i = 0; i< TABLE_SIZE ; i++){
		cur = st->table[i].link;
		while(cur != NULL){
			if(cur->inner.subRegion == NULL && cur->inner.type == INT_T)	// variable don't have sub-scope and shall be integer  
				cur->inner.location = local_count++;
			else
				cur->inner.location = -1; 
			cur = cur->link;
		}
	}
}

void put(element e){
	// the result of computable shall be on the top of stack.
	if(isInGlobal(global, e))
		fprintf(byteCode, "%sputstatic int %s.%s\r\n", tab_pad, className, e.variable);
	else
		fprintf(byteCode, "%sistore %d\r\n", tab_pad, e.location);
}



/* Line 268 of yacc.c  */
#line 233 "Yacc.tab.c"

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
#line 162 "Yacc.y"

#include "SymbolTable.h"

typedef struct _TYPEL{
		int type;
		struct _TYPEL *next;
} typeLs;




/* Line 288 of yacc.c  */
#line 269 "Yacc.tab.c"

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
#line 192 "Yacc.y"

	struct _CONST{
		int type;	// 0x01 for int, 0x02 for double, 0x03 for string, 0x04 for boolean.
		union _DATA{
			int Zval;
			double Rval;
			char Str[2048];
		} data;
	} constant;
	node nodes;
	node *nodePointer;
	typeLs *typeL;



/* Line 293 of yacc.c  */
#line 376 "Yacc.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 388 "Yacc.tab.c"

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
#define YYLAST   461

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNRULES -- Number of states.  */
#define YYNSTATES  275

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
       0,     0,     3,     9,    13,    14,    15,    25,    26,    27,
      33,    37,    38,    43,    45,    47,    49,    54,    55,    61,
      62,    69,    70,    77,    82,    84,    86,    88,    90,    94,
      95,   100,   102,   104,   106,   107,   110,   114,   115,   118,
     119,   126,   129,   130,   131,   132,   145,   146,   147,   160,
     161,   162,   163,   164,   165,   182,   183,   184,   185,   186,
     187,   204,   208,   209,   211,   212,   216,   220,   221,   224,
     227,   229,   231,   233,   235,   242,   246,   259,   269,   275,
     280,   284,   288,   289,   294,   295,   298,   299,   301,   303,
     307,   308,   310,   312,   314,   318,   322,   325,   329,   333,
     337,   341,   345,   349,   353,   357,   361,   365,   369,   373,
     377,   380,   382,   384,   386,   388,   391,   396,   398,   402,
     406,   407,   410,   414,   415,   417,   419,   422,   425
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      76,     0,    -1,   139,    77,    78,    77,    72,    -1,   106,
     138,    77,    -1,    -1,    -1,    57,    71,   138,    79,    80,
      44,    57,    71,   138,    -1,    -1,    -1,    81,    83,    82,
      98,   119,    -1,    84,   138,    83,    -1,    -1,    92,    93,
      95,    96,    -1,    91,    -1,    90,    -1,    85,    -1,    53,
       7,    86,     8,    -1,    -1,    71,    31,   133,    87,    88,
      -1,    -1,     3,    71,    31,   133,    89,    88,    -1,    -1,
      40,    17,    71,    17,   133,    17,    -1,    37,    17,    71,
      17,    -1,    35,    -1,    49,    -1,    59,    -1,    51,    -1,
       3,    94,    93,    -1,    -1,    41,     7,    68,     8,    -1,
      56,    -1,    53,    -1,     5,    -1,    -1,    71,    97,    -1,
       3,    71,    97,    -1,    -1,    99,    98,    -1,    -1,    50,
     138,   100,    44,    50,   138,    -1,   101,   100,    -1,    -1,
      -1,    -1,   118,    64,    71,   102,   117,   103,   138,    83,
      44,    64,    71,   138,    -1,    -1,    -1,   118,    46,    71,
     104,   117,   105,   138,    83,    44,    46,    71,   138,    -1,
      -1,    -1,    -1,    -1,    -1,   118,    64,    71,   107,   117,
     108,   138,   109,    83,   110,    98,   111,   119,    44,    64,
      71,    -1,    -1,    -1,    -1,    -1,    -1,   118,    46,    71,
     112,   117,   113,   138,   114,    83,   115,    98,   116,   119,
      44,    46,    71,    -1,     7,    96,     8,    -1,    -1,    60,
      -1,    -1,   121,   138,   120,    -1,   121,   138,   120,    -1,
      -1,    58,    71,    -1,   127,   133,    -1,   123,    -1,   133,
      -1,   122,    -1,    61,    -1,    42,   125,   138,   124,    44,
      42,    -1,    33,    71,   134,    -1,    48,     7,   133,     8,
      66,   138,   120,    43,   138,   120,    44,    48,    -1,    48,
       7,   133,     8,    66,   138,   120,    44,    48,    -1,    48,
       7,   133,     8,   121,    -1,    71,   128,   137,   133,    -1,
     121,   138,   124,    -1,    45,   138,   124,    -1,    -1,   123,
       3,   133,   126,    -1,    -1,     3,   133,    -1,    -1,    54,
      -1,    55,    -1,     9,   133,    10,    -1,    -1,   132,    -1,
     131,    -1,   130,    -1,   133,    26,   133,    -1,   133,    27,
     133,    -1,    28,   133,    -1,   133,    29,   133,    -1,   133,
      30,   133,    -1,   133,    20,   133,    -1,   133,    21,   133,
      -1,   133,    22,   133,    -1,   133,    23,   133,    -1,   133,
      24,   133,    -1,   133,    25,   133,    -1,   133,    14,   133,
      -1,   133,    15,   133,    -1,   133,    16,   133,    -1,   133,
      17,   133,    -1,   133,    18,   133,    -1,    15,   133,    -1,
      70,    -1,    68,    -1,    69,    -1,    67,    -1,    71,   134,
      -1,    71,     9,   133,    10,    -1,   129,    -1,     7,   129,
       8,    -1,     7,   135,     8,    -1,    -1,   133,   136,    -1,
       3,   133,   136,    -1,    -1,    31,    -1,    32,    -1,    73,
     139,    -1,    73,   139,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   223,   223,   225,   226,   229,   228,   251,   255,   251,
     260,   264,   266,   276,   277,   278,   280,   286,   285,   299,
     298,   310,   312,   323,   329,   330,   331,   332,   334,   335,
     337,   338,   339,   341,   342,   344,   356,   367,   369,   370,
     372,   374,   375,   378,   385,   377,   401,   407,   400,   425,
     433,   439,   443,   447,   424,   466,   474,   480,   484,   495,
     465,   514,   519,   521,   522,   524,   526,   527,   529,   530,
     531,   532,   533,   534,   535,   536,   564,   571,   578,   586,
     594,   595,   596,   598,   599,   601,   602,   604,   605,   607,
     616,   618,   619,   620,   622,   633,   644,   655,   667,   679,
     685,   691,   697,   703,   709,   716,   732,   748,   764,   780,
     796,   810,   811,   812,   813,   814,   843,   852,   853,   855,
     860,   862,   870,   877,   879,   880,   882,   884,   885
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
  "program_description", "$@2", "$@3", "var_const_declare_p",
  "var_const_declare", "const_init", "const_init_list_p", "$@4",
  "const_init_list", "$@5", "var_init", "global_declare", "type",
  "attr_list", "attrs", "dual_colon", "id_list_p", "id_list",
  "interface_declare_p", "interface_declare", "procedure_declaration_p",
  "procedure_declaration", "$@6", "$@7", "$@8", "$@9",
  "procedure_description", "$@10", "$@11", "$@12", "$@13", "$@14", "$@15",
  "$@16", "$@17", "$@18", "$@19", "arguments", "recursive_p", "stmts",
  "stmt_p", "stmt", "condition", "assignment", "do_stmt", "do_parameter",
  "do_diff", "print_p", "array_indexing", "expr", "boolean_operation",
  "relational_operation", "mathematical_operation", "computable",
  "pass_arguments", "computable_list_p", "computable_list", "assign",
  "linebreak_p", "linebreak", 0
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
       0,    75,    76,    77,    77,    79,    78,    81,    82,    80,
      83,    83,    84,    84,    84,    84,    85,    87,    86,    89,
      88,    88,    90,    91,    92,    92,    92,    92,    93,    93,
      94,    94,    94,    95,    95,    96,    97,    97,    98,    98,
      99,   100,   100,   102,   103,   101,   104,   105,   101,   107,
     108,   109,   110,   111,   106,   112,   113,   114,   115,   116,
     106,   117,   117,   118,   118,   119,   120,   120,   121,   121,
     121,   121,   121,   121,   121,   121,   122,   122,   122,   123,
     124,   124,   124,   125,   125,   126,   126,   127,   127,   128,
     128,   129,   129,   129,   130,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   132,   132,   132,   132,   132,
     132,   133,   133,   133,   133,   133,   133,   133,   133,   134,
     134,   135,   136,   136,   137,   137,   138,   139,   139
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     3,     0,     0,     9,     0,     0,     5,
       3,     0,     4,     1,     1,     1,     4,     0,     5,     0,
       6,     0,     6,     4,     1,     1,     1,     1,     3,     0,
       4,     1,     1,     1,     0,     2,     3,     0,     2,     0,
       6,     2,     0,     0,     0,    12,     0,     0,    12,     0,
       0,     0,     0,     0,    16,     0,     0,     0,     0,     0,
      16,     3,     0,     1,     0,     3,     3,     0,     2,     2,
       1,     1,     1,     1,     6,     3,    12,     9,     5,     4,
       3,     3,     0,     4,     0,     2,     0,     1,     1,     3,
       0,     1,     1,     1,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     1,     1,     2,     4,     1,     3,     3,
       0,     2,     3,     0,     1,     1,     2,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     128,   128,     0,    64,   127,     1,    63,     0,     0,     0,
       0,    64,   128,     4,     0,     0,     0,     0,   126,     3,
      55,    49,     5,     2,    62,    62,     7,     0,    56,    50,
       0,    11,    37,     0,     0,     0,     0,    24,     0,     0,
      25,    27,     0,    26,     8,     0,    15,    14,    13,    29,
       0,    35,    61,    57,    51,     0,     0,     0,     0,    39,
      11,     0,    34,    37,    11,    11,     0,     0,     0,     0,
       0,     0,     0,    39,    10,     0,    32,    31,    29,    33,
       0,    36,    58,    52,     6,    23,     0,     0,    16,    64,
       0,     0,     0,     0,    84,     0,    87,    88,     0,    73,
     114,   112,   113,   111,   120,     9,     0,    72,    70,     0,
     117,    93,    92,    91,    71,    38,     0,    28,    12,    39,
      39,   120,     0,    17,     0,    64,     0,   117,     0,   110,
      96,   120,    90,     0,     0,     0,    68,     0,     0,     0,
     115,    67,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    59,
      53,     0,    22,    21,     0,    41,     0,     0,   118,    75,
       0,     0,    82,     0,   123,     0,     0,   124,   125,     0,
      65,     0,   105,   106,   107,   108,   109,    99,   100,   101,
     102,   103,   104,    94,    95,    97,    98,    30,     0,     0,
       0,     0,    18,     0,    46,    43,     0,    86,     0,     0,
       0,     0,     0,   121,   119,   116,    79,    67,     0,     0,
     116,     0,    40,    62,    62,    89,     0,    83,    82,    82,
       0,     0,    78,   123,    66,     0,     0,     0,    47,    44,
      85,    81,    80,    74,    67,   122,     0,     0,    19,     0,
       0,     0,    60,    54,    21,    11,    11,     0,     0,    20,
       0,     0,    67,    77,     0,     0,     0,     0,     0,     0,
       0,     0,    76,    48,    45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,    11,    26,    30,    31,    59,    44,    45,
      46,    70,   163,   202,   254,    47,    48,    49,    62,    78,
      80,    33,    51,    72,    73,   124,   125,   224,   250,   223,
     249,     8,    25,    35,    65,   120,   199,    24,    34,    64,
     119,   198,    28,     9,   105,   180,   181,   107,   108,   210,
     134,   227,   109,   139,   110,   111,   112,   113,   114,   140,
     175,   213,   179,    13,     3
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -214
static const yytype_int16 yypact[] =
{
     -60,   -60,    20,   -17,  -214,  -214,  -214,   -27,   -38,   -36,
     -23,   -34,   -60,   -37,   -10,    -4,   -38,   -33,  -214,  -214,
    -214,  -214,  -214,  -214,    76,    76,  -214,    14,  -214,  -214,
      58,   154,    88,   112,   -38,   -38,    64,  -214,   106,   107,
    -214,  -214,   119,  -214,  -214,   -38,  -214,  -214,  -214,   124,
      65,  -214,  -214,  -214,  -214,    68,    69,    70,    72,    78,
     154,   -20,   128,    88,   154,   154,   -38,   117,   132,   121,
     142,   -38,   225,    78,  -214,   146,  -214,  -214,   124,  -214,
      14,  -214,  -214,  -214,  -214,  -214,    30,    30,  -214,   -19,
      30,    30,    30,    83,    85,   150,  -214,  -214,    87,  -214,
    -214,  -214,  -214,  -214,    15,  -214,   -38,  -214,  -214,    30,
    -214,  -214,  -214,  -214,   375,  -214,    93,  -214,  -214,    78,
      78,    47,   392,   375,   120,   -19,   -32,   155,   375,  -214,
     436,   164,   171,   180,   -38,    30,  -214,    30,    30,    57,
    -214,   225,   375,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    30,    30,   176,  -214,
    -214,    30,    30,   182,   136,  -214,   130,   131,  -214,  -214,
      30,    30,    77,   304,   152,   187,   322,  -214,  -214,    30,
    -214,   -38,    48,    48,   172,   172,   172,    97,    97,    97,
      97,    97,    97,   436,   423,   409,   409,  -214,   225,   225,
     340,   133,  -214,   -38,  -214,  -214,   358,   284,   -38,   -38,
     162,   181,    30,  -214,  -214,    62,   375,   225,   166,   167,
    -214,   177,  -214,    76,    76,  -214,    30,  -214,    77,    77,
     170,   -38,  -214,   152,  -214,   173,   153,    30,  -214,  -214,
     375,  -214,  -214,  -214,   225,  -214,   145,   147,   375,   -38,
     -38,    63,  -214,  -214,   182,   154,   154,   -38,   174,  -214,
     183,   184,   225,  -214,   175,   156,   186,   160,   185,   178,
     -38,   -38,  -214,  -214,  -214
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -214,  -214,    46,  -214,  -214,  -214,  -214,  -214,   -58,  -214,
    -214,  -214,  -214,   -30,  -214,  -214,  -214,  -214,   159,  -214,
    -214,   158,   194,   -68,  -214,   100,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,   -24,   -81,   -90,  -213,   -69,  -214,   149,  -112,
    -214,  -214,  -214,  -214,   169,  -214,  -214,  -214,   -75,   113,
    -214,    12,  -214,   -16,    41
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -91
static const yytype_int16 yytable[] =
{
      22,    29,    74,   106,   234,   115,    82,    83,   126,   -64,
      14,   122,   123,     1,   166,   128,   129,   130,    53,    54,
       5,    75,   137,     6,   138,   -42,     6,   -64,    15,    60,
      10,   251,   167,    76,   142,    12,    77,    90,    -4,    23,
      -4,     6,     4,     6,   126,    91,   -90,   -90,    16,   266,
      84,   159,   160,    18,   137,    89,   161,    17,    92,    19,
     173,    20,   174,   176,   145,   146,   147,    21,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,    27,    90,    32,   200,   185,   177,   178,
     141,    50,    91,   -89,   -89,   206,   207,   100,   101,   102,
     103,   121,    36,   209,   216,    92,   257,   258,   218,   219,
      93,   143,   144,   145,   146,   147,   241,   242,   172,    94,
      52,    55,   208,    56,    57,    95,    58,    61,    71,   106,
     106,    96,    97,    79,    85,    98,    63,   233,    99,    66,
      67,    68,   232,    69,   100,   101,   102,   103,   104,    86,
      88,   240,    87,   116,   131,   212,   132,   135,   136,   209,
     209,   158,   248,   168,   164,   217,   143,   144,   145,   146,
     147,   137,   148,   149,   150,   151,   152,   153,   154,   155,
     170,   156,   157,   171,   197,   201,   203,   222,    90,    37,
     147,    38,   228,   229,    39,   214,    91,   260,   261,   238,
     239,   204,   205,    40,   221,    41,   230,    42,   237,    92,
     235,   236,   243,    43,    93,   244,   252,   247,   253,   246,
     268,   267,   263,    94,   259,   165,   272,   264,   265,    95,
     269,   270,    90,   255,   256,    96,    97,   117,   118,    98,
      91,   262,    99,   133,   169,   245,     0,   231,   100,   101,
     102,   103,   104,    92,   273,   274,   271,    81,    93,   127,
       0,     0,     0,     0,     0,     0,     0,    94,     0,     0,
       0,     0,     0,    95,     0,     0,     0,     0,     0,    96,
      97,     0,     0,    98,     0,     0,    99,   226,     0,     0,
       0,     0,   100,   101,   102,   103,   104,     0,   143,   144,
     145,   146,   147,     0,   148,   149,   150,   151,   152,   153,
     154,   155,   211,   156,   157,     0,     0,     0,   143,   144,
     145,   146,   147,     0,   148,   149,   150,   151,   152,   153,
     154,   155,   215,   156,   157,     0,   143,   144,   145,   146,
     147,     0,   148,   149,   150,   151,   152,   153,   154,   155,
     220,   156,   157,     0,   143,   144,   145,   146,   147,     0,
     148,   149,   150,   151,   152,   153,   154,   155,   225,   156,
     157,     0,   143,   144,   145,   146,   147,     0,   148,   149,
     150,   151,   152,   153,   154,   155,     0,   156,   157,   143,
     144,   145,   146,   147,     0,   148,   149,   150,   151,   152,
     153,   154,   155,     0,   156,   157,   143,   144,   145,   162,
     147,     0,   148,   149,   150,   151,   152,   153,   154,   155,
       0,   156,   157,   143,   144,   145,   146,   147,     0,   148,
     149,   150,   151,   152,   153,   154,   155,   143,   144,   145,
     146,   147,     0,   148,   149,   150,   151,   152,   153,   154,
     143,   144,   145,   146,   147,     0,   148,   149,   150,   151,
     152,   153
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-214))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      16,    25,    60,    72,   217,    73,    64,    65,    89,    46,
      46,    86,    87,    73,    46,    90,    91,    92,    34,    35,
       0,    41,     7,    60,     9,    44,    60,    64,    64,    45,
      57,   244,    64,    53,   109,    73,    56,     7,    72,    72,
      57,    60,     1,    60,   125,    15,    31,    32,    71,   262,
      66,   119,   120,    12,     7,    71,     9,    11,    28,    13,
     135,    71,   137,   138,    16,    17,    18,    71,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,     7,     7,    71,   161,   162,    31,    32,
     106,     3,    15,    31,    32,   170,   171,    67,    68,    69,
      70,    71,    44,   172,   179,    28,    43,    44,   198,   199,
      33,    14,    15,    16,    17,    18,   228,   229,   134,    42,
       8,    57,    45,    17,    17,    48,     7,     3,    50,   198,
     199,    54,    55,     5,    17,    58,    71,   212,    61,    71,
      71,    71,   211,    71,    67,    68,    69,    70,    71,    17,
       8,   226,    31,     7,    71,     3,    71,     7,    71,   228,
     229,    68,   237,     8,    44,   181,    14,    15,    16,    17,
      18,     7,    20,    21,    22,    23,    24,    25,    26,    27,
       9,    29,    30,     3,     8,     3,    50,   203,     7,    35,
      18,    37,   208,   209,    40,     8,    15,   255,   256,   223,
     224,    71,    71,    49,    71,    51,    44,    53,    31,    28,
      44,    44,    42,    59,    33,   231,    71,    64,    71,    46,
      64,    46,    48,    42,   254,   125,    48,    44,    44,    48,
      44,    71,     7,   249,   250,    54,    55,    78,    80,    58,
      15,   257,    61,    94,   131,   233,    -1,    66,    67,    68,
      69,    70,    71,    28,   270,   271,    71,    63,    33,    90,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    -1,    -1,    58,    -1,    -1,    61,     3,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    -1,    14,    15,
      16,    17,    18,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,     8,    29,    30,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    10,    29,    30,    -1,    14,    15,    16,    17,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      10,    29,    30,    -1,    14,    15,    16,    17,    18,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    10,    29,
      30,    -1,    14,    15,    16,    17,    18,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    29,    30,    14,
      15,    16,    17,    18,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    29,    30,    14,    15,    16,    17,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    29,    30,    14,    15,    16,    17,    18,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    14,    15,    16,
      17,    18,    -1,    20,    21,    22,    23,    24,    25,    26,
      14,    15,    16,    17,    18,    -1,    20,    21,    22,    23,
      24,    25
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    73,    76,   139,   139,     0,    60,    77,   106,   118,
      57,    78,    73,   138,    46,    64,    71,    77,   139,    77,
      71,    71,   138,    72,   112,   107,    79,     7,   117,   117,
      80,    81,    71,    96,   113,   108,    44,    35,    37,    40,
      49,    51,    53,    59,    83,    84,    85,    90,    91,    92,
       3,    97,     8,   138,   138,    57,    17,    17,     7,    82,
     138,     3,    93,    71,   114,   109,    71,    71,    71,    71,
      86,    50,    98,    99,    83,    41,    53,    56,    94,     5,
      95,    97,    83,    83,   138,    17,    17,    31,     8,   138,
       7,    15,    28,    33,    42,    48,    54,    55,    58,    61,
      67,    68,    69,    70,    71,   119,   121,   122,   123,   127,
     129,   130,   131,   132,   133,    98,     7,    93,    96,   115,
     110,    71,   133,   133,   100,   101,   118,   129,   133,   133,
     133,    71,    71,   123,   125,     7,    71,     7,     9,   128,
     134,   138,   133,    14,    15,    16,    17,    18,    20,    21,
      22,    23,    24,    25,    26,    27,    29,    30,    68,    98,
      98,     9,    17,    87,    44,   100,    46,    64,     8,   134,
       9,     3,   138,   133,   133,   135,   133,    31,    32,   137,
     120,   121,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,     8,   116,   111,
     133,     3,    88,    50,    71,    71,   133,   133,    45,   121,
     124,     8,     3,   136,     8,    10,   133,   138,   119,   119,
      10,    71,   138,   104,   102,    10,     3,   126,   138,   138,
      44,    66,   121,   133,   120,    44,    44,    31,   117,   117,
     133,   124,   124,    42,   138,   136,    46,    64,   133,   105,
     103,   120,    71,    71,    89,   138,   138,    43,    44,    88,
      83,    83,   138,    48,    44,    44,   120,    46,    64,    44,
      71,    71,    48,   138,   138
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
#line 223 "Yacc.y"
    { return ACCEPTABLE; /* acceptable state */ }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 229 "Yacc.y"
    {	// Each symbol table presents a scope.
				symbolTable *temp = create(current);
				(yyvsp[(2) - (3)].nodes).ep->subRegion = temp;
				(yyvsp[(2) - (3)].nodes).ep->type = 0;
				current = temp;

				fprintf(byteCode, "%smethod public static void main(java.lang.String[])\r\n%smax_stack 15\r\n%smax_locals 15\r\n%s{\r\n", tab_pad, tab_pad, tab_pad, tab_pad);
				tab();
			}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 238 "Yacc.y"
    {
				if(strcmp((yyvsp[(2) - (9)].nodes).ep->variable, (yyvsp[(8) - (9)].nodes).ep->variable) != 0){	// Check if the program id are matched or not.
					yyerror("syntex error: program id name doesn't match.\r\n");
					return REJECT;
				}
				current = current->parent;
				derive("program", "program "id("%s")" "gmr("linebreak_p")" "gmr("program_description")" end program "id("%s")" "gmr("ends"), (yyvsp[(2) - (9)].nodes).ep->variable, (yyvsp[(8) - (9)].nodes).ep->variable);

				fprintf(byteCode, "%sreturn\r\n", tab_pad);
				tabShift();
				fprintf(byteCode, "%s}\r\n", tab_pad);
			}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 251 "Yacc.y"
    {
							local_count = 0;
						}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 255 "Yacc.y"
    {
							//enumerateLocalVar(current);
						}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 258 "Yacc.y"
    { derive("program_description", gmr("var_const_declare_p")" "gmr("interface_declare_p")" "gmr("stmts")); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 261 "Yacc.y"
    {
							derive("var_const_declare_p", gmr("var_const_declare")" "gmr("linebreak_p")" "gmr("var_const_declare_p"));
						}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 267 "Yacc.y"
    {	// Assign the type of identifiers.
							nodeP cur = (yyvsp[(4) - (4)].nodePointer);
							while(cur != NULL){
								cur->ep->type = (yyvsp[(1) - (4)].constant).type;
								cur->ep->location = local_count++;
								cur = cur->next;
							}
							derive("var_const_declare", gmr("type")" "gmr("attr_list")" "gmr("dual_colon")" "gmr("id_list_p"));
						}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 276 "Yacc.y"
    { derive("var_const_declare", gmr("global_declare")); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 277 "Yacc.y"
    { derive("var_const_declare", gmr("var_init")); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 278 "Yacc.y"
    { derive("var_const_declare", gmr("const_init")); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 281 "Yacc.y"
    {
					derive("const_init", "parameter ( "gmr("const_init_list_p")" )");
				}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 286 "Yacc.y"
    {
							if((yyvsp[(1) - (3)].nodes).ep->type != (yyvsp[(3) - (3)].constant).type){
								yyerror("semantic error: type doesn't match while constant initalizing");
								return REJECT;
							}

							put(*((yyvsp[(1) - (3)].nodes).ep));
						}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 294 "Yacc.y"
    {
							derive("const_init_list_p", id("%s")" = "gmr("computable")" "gmr("const_init_list"), (yyvsp[(1) - (5)].nodes).ep->variable);
						}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 299 "Yacc.y"
    {
						if((yyvsp[(2) - (4)].nodes).ep->type != (yyvsp[(4) - (4)].constant).type){
							yyerror("semantic error: type doesn't match while constant initalizing");
							return REJECT;
						}

						put(*((yyvsp[(2) - (4)].nodes).ep));
					}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 307 "Yacc.y"
    {
						derive("const_init_list", ", "id("%s")" = "gmr("computable")" "gmr("const_init_list"), (yyvsp[(2) - (6)].nodes).ep->variable);
					}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 313 "Yacc.y"
    {
					if((yyvsp[(3) - (6)].nodes).ep->type != (yyvsp[(5) - (6)].constant).type){
						yyerror("semantic error: type doesn't match while variable initalizing");
						return REJECT;
					}
					derive("var_init", "data / "id("%s")" / "gmr("computable")" /", (yyvsp[(3) - (6)].nodes).ep->variable);

					put(*((yyvsp[(3) - (6)].nodes).ep));
				}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 324 "Yacc.y"
    {
						lift2global((yyvsp[(3) - (4)].nodes));
						derive("global_declare", "common / "id("%s")" / ", (yyvsp[(3) - (4)].nodes).ep->variable);
					}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 329 "Yacc.y"
    { (yyval.constant).type = STR_T; derive("type", "character "); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 330 "Yacc.y"
    { (yyval.constant).type = INT_T; derive("type", "integer "); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 331 "Yacc.y"
    { (yyval.constant).type = REAL_T; derive("type", "real "); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 332 "Yacc.y"
    { (yyval.constant).type = BOOL_T; derive("type", "logical "); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 334 "Yacc.y"
    { derive("attr_list", ", "gmr("attrs")" "gmr("attrs_list")); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 337 "Yacc.y"
    { derive("attrs", "dimension ( %d )", (yyvsp[(3) - (4)].constant).data.Zval); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 338 "Yacc.y"
    { derive("attrs", "pointer"); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 339 "Yacc.y"
    { derive("attrs", "parameter"); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 341 "Yacc.y"
    { derive("dual_colon", "::"); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 345 "Yacc.y"
    {	// Make all ids a chain, so we can get all these ids which were claimed in a row.
					if((yyvsp[(2) - (2)].nodePointer) != NULL)
						(yyvsp[(1) - (2)].nodes).next = (yyvsp[(2) - (2)].nodePointer);
					else
						(yyvsp[(1) - (2)].nodes).next = NULL;
					(yyval.nodePointer) = (nodeP)malloc(sizeof(node));
					memcpy((yyval.nodePointer), &((yyvsp[(1) - (2)].nodes)), sizeof(node));					
					//$$ = $1;
					derive("id_list_p", id("%s")" "gmr("id_list"), (yyvsp[(1) - (2)].nodes).ep->variable);
				}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 357 "Yacc.y"
    {	// Make chain, same as previous grammar.
				if((yyvsp[(3) - (3)].nodePointer) != NULL)
					(yyvsp[(2) - (3)].nodes).next = (yyvsp[(3) - (3)].nodePointer);
				else
					(yyvsp[(2) - (3)].nodes).next = NULL;
				(yyval.nodePointer) = (nodeP)malloc(sizeof(node));
				memcpy((yyval.nodePointer), &((yyvsp[(2) - (3)].nodes)), sizeof(node));
				//$$ = $2;
				derive("id_list", ", "id("%s")" "gmr("id_list"), (yyvsp[(2) - (3)].nodes).ep->variable);
			}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 367 "Yacc.y"
    {	(yyval.nodePointer) = NULL; }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 369 "Yacc.y"
    { derive("interface_declare_p", gmr("interface_declare")gmr("interface_declare_p")); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 372 "Yacc.y"
    { derive("interface_declare", "interface "gmr("linebreak_p")" "gmr("procedure_declaration")" end interface "gmr("linebreak_p")); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 378 "Yacc.y"
    {	// Create a new scope
								symbolTable *temp = create(current);
								lift2global((yyvsp[(3) - (3)].nodes));
								(yyvsp[(3) - (3)].nodes).ep->type = 0;
								(yyvsp[(3) - (3)].nodes).ep->subRegion = temp;
								current = temp;
							}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 385 "Yacc.y"
    {	// get all arguments
								(yyvsp[(3) - (5)].nodes).ep->typeList = (yyvsp[(5) - (5)].nodePointer);
							}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 391 "Yacc.y"
    {
								if(strcmp((yyvsp[(3) - (12)].nodes).ep->variable, (yyvsp[(11) - (12)].nodes).ep->variable) != 0){
									yyerror("syntex error: subroutine id name doesn't match.\r\n");
									return REJECT;
								}
								current = current->parent;
								//argListCopy($3);	// build a new chain to indicate to all arguments.
								derive("procedure_declaration", gmr("recursive_p")" subroutine "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end subroutine "id("%s")" "gmr("linebreak_p"), (yyvsp[(3) - (12)].nodes).ep->variable, (yyvsp[(11) - (12)].nodes).ep->variable);
							}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 401 "Yacc.y"
    {	// doing the same thing as subroutine version.
								symbolTable *temp = create(current);
								lift2global((yyvsp[(3) - (3)].nodes));
								(yyvsp[(3) - (3)].nodes).ep->subRegion = temp;
								current = temp;
							}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 407 "Yacc.y"
    {
								(yyvsp[(3) - (5)].nodes).ep->typeList = (yyvsp[(5) - (5)].nodePointer);
							}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 413 "Yacc.y"
    {
								if(strcmp((yyvsp[(3) - (12)].nodes).ep->variable, (yyvsp[(11) - (12)].nodes).ep->variable) != 0){
									yyerror("syntex error: function id name doesn't match.\r\n");
									return REJECT;
								}
								(yyvsp[(3) - (12)].nodes).ep->type = lookup(current, (yyvsp[(3) - (12)].nodes).ep->variable)->type;
								current = current->parent;
								//argListCopy($3);
								derive("procedure_declaration", gmr("recursive_p")" function "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end function "id("%s")" "gmr("linebreak_p"), (yyvsp[(3) - (12)].nodes).ep->variable, (yyvsp[(11) - (12)].nodes).ep->variable);
							}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 425 "Yacc.y"
    {	// same as previous rule, but need to check if this procedure had already built.
								if((yyvsp[(3) - (3)].nodes).ep->subRegion == NULL){
									symbolTable *temp = create(current);
									(yyvsp[(3) - (3)].nodes).ep->subRegion = temp;
									(yyvsp[(3) - (3)].nodes).ep->type = 0;
								}
								current = (yyvsp[(3) - (3)].nodes).ep->subRegion;
							}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 433 "Yacc.y"
    {
								if((yyvsp[(3) - (5)].nodes).ep->typeList == NULL){
										(yyvsp[(3) - (5)].nodes).ep->typeList = (yyvsp[(5) - (5)].nodePointer);
								}
							}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 439 "Yacc.y"
    {
								local_count = 0;
							}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 443 "Yacc.y"
    {
								//enumerateLocalVar(current);
							}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 447 "Yacc.y"
    {
								printMethod(*((yyvsp[(3) - (11)].nodes).ep));
							}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 452 "Yacc.y"
    {
								if(strcmp((yyvsp[(3) - (16)].nodes).ep->variable, (yyvsp[(16) - (16)].nodes).ep->variable) != 0){
									yyerror("syntex error: subroutine id name doesn't match.\r\n");
									return REJECT;
								}
								current = current->parent;
								/*if($3.ep->typeList == &($5))
									argListCopy($3);*/
								derive("procedure_description", gmr("recursive_p")" subroutine "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end subroutine "id("%s")" "gmr("linebreak_p"), (yyvsp[(3) - (16)].nodes).ep->variable, (yyvsp[(16) - (16)].nodes).ep->variable);

								tabShift();
								fprintf(byteCode, "%s}\r\n", tab_pad);
							}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 466 "Yacc.y"
    {
								if((yyvsp[(3) - (3)].nodes).ep->subRegion == NULL){
									symbolTable *temp = create(current);
									(yyvsp[(3) - (3)].nodes).ep->subRegion = temp;
									(yyvsp[(3) - (3)].nodes).ep->type = 0;
								}
								current = (yyvsp[(3) - (3)].nodes).ep->subRegion;
							}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 474 "Yacc.y"
    {
								if((yyvsp[(3) - (5)].nodes).ep->typeList == NULL){
									(yyvsp[(3) - (5)].nodes).ep->typeList = (yyvsp[(5) - (5)].nodePointer);
								}
							}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 480 "Yacc.y"
    {
								local_count = 0;
							}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 484 "Yacc.y"
    {
								element *func_buff;
								(yyvsp[(3) - (9)].nodes).ep->type = lookup(current, (yyvsp[(3) - (9)].nodes).ep->variable)->type;
								if(lookupLocally(current, (yyvsp[(3) - (9)].nodes).ep->variable) == NULL){
									func_buff = insert(current, (yyvsp[(3) - (9)].nodes).ep->variable);
									func_buff->type = (yyvsp[(3) - (9)].nodes).ep->type;
									func_buff->location = local_count++;
								}
								//enumerateLocalVar(current);
							}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 495 "Yacc.y"
    {
								printMethod(*((yyvsp[(3) - (11)].nodes).ep));
							}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 500 "Yacc.y"
    {
								if(strcmp((yyvsp[(3) - (16)].nodes).ep->variable, (yyvsp[(16) - (16)].nodes).ep->variable) != 0){
									yyerror("syntex error: function id name doesn't match.\r\n");
									return REJECT;
								}
								current = current->parent;
								/*if($3.ep->typeList == &($5))
									argListCopy($3);*/
								derive("procedure_description", gmr("recursive_p")" function "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end function "id("%s")" "gmr("linebreak_p"), (yyvsp[(3) - (16)].nodes).ep->variable, (yyvsp[(16) - (16)].nodes).ep->variable);

								tabShift();
								fprintf(byteCode, "%s}\r\n", tab_pad);
							}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 515 "Yacc.y"
    {	// pass the id chain.
					(yyval.nodePointer) = (yyvsp[(2) - (3)].nodePointer);
					derive("arguments", "( "gmr("id_list_p")" )");
				}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 519 "Yacc.y"
    { (yyval.nodePointer) = NULL; }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 521 "Yacc.y"
    { derive("recursive_p", "recursive"); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 524 "Yacc.y"
    { derive("stmts", gmr("stmt")" "gmr("linebreak_p")" "gmr("stmt_p")); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 526 "Yacc.y"
    { derive("stmt_p", gmr("stmt")" "gmr("linebreak_p")" "gmr("stmt_p")); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 529 "Yacc.y"
    { derive("stmt", "read "id("%s"), (yyvsp[(2) - (2)].nodes).ep->variable); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 530 "Yacc.y"
    { derive("stmt", gmr("print_p")" "gmr("computable")); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 531 "Yacc.y"
    { derive("stmt", gmr("assignment")); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 532 "Yacc.y"
    { derive("stmt", gmr("computable")); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 533 "Yacc.y"
    { derive("stmt", gmr("condition")); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 534 "Yacc.y"
    { derive("stmt", "return"); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 535 "Yacc.y"
    { derive("stmt", "do "gmr("do_parameter")" "gmr("linebreak_p")" "gmr("stmt_p")" end do"); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 537 "Yacc.y"
    {
				if((yyvsp[(2) - (3)].nodes).ep->type != 0){	// Check this id is a subroutine.
					yyerror("syntex error: invoke a non-subroutine with call");
					return REJECT;
				}
				if((yyvsp[(3) - (3)].typeL) != NULL){				// There is one or more arguments passed in.
					typeLs *tp = (yyvsp[(3) - (3)].typeL);
					nodeP curN = (yyvsp[(2) - (3)].nodes).ep->typeList;
					while(tp != NULL && curN != NULL){	// Check the arguments' type.
						if(tp->type != curN->ep->type){
							yyerror("sematic error: argument type doesn't match");
							return REJECT;
						}
						tp = tp->next;
						curN = curN->next;
					}
					if(tp != NULL){	// number of arguments doesn't match.
						yyerror("sematic error: given too much arguments");
						return REJECT;
					}else if(curN != NULL){
						yyerror("sematic error: given too less arguments");
						return REJECT;
					}
				}
				derive("stmt", "call "id("%s")" "gmr("pass_arguments"), (yyvsp[(2) - (3)].nodes).ep->variable);
			}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 565 "Yacc.y"
    {
					if((yyvsp[(3) - (12)].constant).type != BOOL_T){
						yyerror("syntex error: given a non-boolean expression");
					}
					derive("condition", "if ( "gmr("computable")" ) then "gmr("linebreak_p")" "gmr("stmt_p")" else "gmr("linebreak_p")" "gmr("stmt_p")" end if");
				}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 572 "Yacc.y"
    {
					if((yyvsp[(3) - (9)].constant).type != BOOL_T){
						yyerror("syntex error: given a non-boolean expression");
					}
					derive("condition", "if ( "gmr("computable")" ) then "gmr("linebreak_p")" "gmr("stmt_p")" end if");
				}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 579 "Yacc.y"
    {
					if((yyvsp[(3) - (5)].constant).type != BOOL_T){
						yyerror("syntex error: given a non-boolean expression");
					}
					derive("condition", "if ( "gmr("computable")" ) "gmr("stmt"));
				}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 587 "Yacc.y"
    {
					if((yyvsp[(1) - (4)].nodes).ep->type != (yyvsp[(4) - (4)].constant).type){
						yyerror("syntex error: type doesn't match");
					}
					derive("assignment", id("%s")" "gmr("array_indexing")" "gmr("assign")" "gmr("computable"), (yyvsp[(1) - (4)].nodes).ep->variable);
				}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 594 "Yacc.y"
    { derive("do_stmt", gmr("stmt")" "gmr("linebreak_p")" "gmr("do_stmt")); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 595 "Yacc.y"
    { derive("do_stmt", "exit"); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 598 "Yacc.y"
    { derive("do_parameter", gmr("assignment")", "gmr("computable")" "gmr("do_diff")); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 601 "Yacc.y"
    { derive("do_diff", ", "gmr("computable"));}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 604 "Yacc.y"
    { derive("print_p", "print"); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 605 "Yacc.y"
    { derive("print_p", "println"); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 608 "Yacc.y"
    {
						if((yyvsp[(2) - (3)].constant).type != INT_T){
							yyerror("sematic error: array indexing with non-integer type");
							return REJECT;
						}
						(yyval.constant) = (yyvsp[(2) - (3)].constant);
						derive("array_indexing", "[ "gmr("computable")" ]");
					}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 616 "Yacc.y"
    { (yyval.constant).type = EMPTY_T; }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 618 "Yacc.y"
    { (yyval.constant) = (yyvsp[(1) - (1)].constant); derive("expr", gmr("mathematical_operation")); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 619 "Yacc.y"
    { (yyval.constant) = (yyvsp[(1) - (1)].constant); derive("expr", gmr("relational_operation")); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 620 "Yacc.y"
    { (yyval.constant) = (yyvsp[(1) - (1)].constant); derive("expr", gmr("boolean_operation")); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 623 "Yacc.y"
    {
							if((yyvsp[(1) - (3)].constant).type == BOOL_T && (yyvsp[(3) - (3)].constant).type == BOOL_T){
								(yyval.constant).type = BOOL_T;
								(yyval.constant).data.Zval = (yyvsp[(1) - (3)].constant).data.Zval & (yyvsp[(3) - (3)].constant).data.Zval;
							}else{
								yyerror("semantic error: boolean");
								return REJECT;
							}
							derive("boolean_operation", gmr("computable")" .AND. "gmr("computable"));
						}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 634 "Yacc.y"
    {
							if((yyvsp[(1) - (3)].constant).type == BOOL_T && (yyvsp[(3) - (3)].constant).type == BOOL_T){
								(yyval.constant).type = BOOL_T;
								(yyval.constant).data.Zval = (yyvsp[(1) - (3)].constant).data.Zval | (yyvsp[(3) - (3)].constant).data.Zval;
							}else{
								yyerror("semantic error: boolean");
								return REJECT;
							}
							derive("boolean_operation", gmr("computable")" .OR. "gmr("computable"));
						}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 645 "Yacc.y"
    {
							if((yyvsp[(2) - (2)].constant).type == BOOL_T){
								(yyval.constant).type = BOOL_T;
								(yyval.constant).data.Zval = !((yyvsp[(2) - (2)].constant).data.Zval);
							}else{
								yyerror("semantic error: boolean");
								return REJECT;
							}
							derive("boolean_operation", ".NOT. "gmr("computable"));
						}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 656 "Yacc.y"
    {
							if((yyvsp[(1) - (3)].constant).type == BOOL_T && (yyvsp[(3) - (3)].constant).type == BOOL_T){
								(yyval.constant).type = BOOL_T;
								// 0^0 = 1^1 = 0; 0^1 = 1^0 = 1 => not equal boolean
								(yyval.constant).data.Zval = !((yyvsp[(1) - (3)].constant).data.Zval ^ (yyvsp[(3) - (3)].constant).data.Zval);
							}else{
								yyerror("semantic error: boolean");
								return REJECT;
							}
							derive("boolean_operation", gmr("computable")" .EQV. "gmr("computable"));
						}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 668 "Yacc.y"
    {
							if((yyvsp[(1) - (3)].constant).type == BOOL_T && (yyvsp[(3) - (3)].constant).type == BOOL_T){
								(yyval.constant).type = BOOL_T;
								(yyval.constant).data.Zval = ((yyvsp[(1) - (3)].constant).data.Zval ^ (yyvsp[(3) - (3)].constant).data.Zval);
							}else{
								yyerror("semantic error: boolean");
								return REJECT;
							}
							derive("boolean_operation", gmr("computable")" .NEQV. "gmr("computable"));
						}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 680 "Yacc.y"
    {
								(yyval.constant).data.Zval = ((yyvsp[(1) - (3)].constant).data.Zval < (yyvsp[(3) - (3)].constant).data.Zval);
								(yyval.constant).type = BOOL_T;
								derive("relational_operation", gmr("computable")" .LT. "gmr("computable"));
							}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 686 "Yacc.y"
    {
								(yyval.constant).data.Zval = ((yyvsp[(1) - (3)].constant).data.Zval <= (yyvsp[(3) - (3)].constant).data.Zval);
								(yyval.constant).type = BOOL_T;
								derive("relational_operation", gmr("computable")" .LE. "gmr("computable"));
							}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 692 "Yacc.y"
    {
								(yyval.constant).data.Zval = ((yyvsp[(1) - (3)].constant).data.Zval > (yyvsp[(3) - (3)].constant).data.Zval);
								(yyval.constant).type = BOOL_T;
								derive("relational_operation", gmr("computable")" .GT. "gmr("computable"));
							}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 698 "Yacc.y"
    {
								(yyval.constant).data.Zval = ((yyvsp[(1) - (3)].constant).data.Zval >= (yyvsp[(3) - (3)].constant).data.Zval);
								(yyval.constant).type = BOOL_T;
								derive("relational_operation", gmr("computable")" .GE. "gmr("computable"));
							}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 704 "Yacc.y"
    {
								(yyval.constant).data.Zval = ((yyvsp[(1) - (3)].constant).data.Zval == (yyvsp[(3) - (3)].constant).data.Zval);
								(yyval.constant).type = BOOL_T;
								derive("relational_operation", gmr("computable")" .EQ. "gmr("computable"));
							}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 710 "Yacc.y"
    {
								(yyval.constant).data.Zval = ((yyvsp[(1) - (3)].constant).data.Zval != (yyvsp[(3) - (3)].constant).data.Zval);
								(yyval.constant).type = BOOL_T;
								derive("relational_operation", gmr("computable")" .NE. "gmr("computable"));
							}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 717 "Yacc.y"
    {
								if(!isNum((yyvsp[(1) - (3)].constant)) || !isNum((yyvsp[(3) - (3)].constant))){	// the case anyone isn't a numrical variable.
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if((yyvsp[(1) - (3)].constant).type != (yyvsp[(3) - (3)].constant).type){	// the case two are different type (one int, one double).
									yyerror("semantic error: arithmatic type difference");
									return REJECT;
								}
								(yyval.constant).type = (yyvsp[(1) - (3)].constant).type;
								if((yyval.constant).type == INT_T)
									(yyval.constant).data.Zval = (yyvsp[(1) - (3)].constant).data.Zval + (yyvsp[(3) - (3)].constant).data.Zval;
								else
									(yyval.constant).data.Rval = (yyvsp[(1) - (3)].constant).data.Rval + (yyvsp[(3) - (3)].constant).data.Rval;
								derive("mathematical_operation", gmr("computable")" + "gmr("computable"));
							}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 733 "Yacc.y"
    {
								if(!isNum((yyvsp[(1) - (3)].constant)) || !isNum((yyvsp[(3) - (3)].constant))){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if((yyvsp[(1) - (3)].constant).type != (yyvsp[(3) - (3)].constant).type){
									yyerror("semantic error: arithmatic type difference");
									return REJECT;
								}
								(yyval.constant).type = (yyvsp[(1) - (3)].constant).type;
								if((yyval.constant).type == INT_T)
									(yyval.constant).data.Zval = (yyvsp[(1) - (3)].constant).data.Zval - (yyvsp[(3) - (3)].constant).data.Zval;
								else
									(yyval.constant).data.Rval = (yyvsp[(1) - (3)].constant).data.Rval - (yyvsp[(3) - (3)].constant).data.Rval;
								derive("mathematical_operation", gmr("computable")" - "gmr("computable"));
							}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 749 "Yacc.y"
    {
								if(!isNum((yyvsp[(1) - (3)].constant)) || !isNum((yyvsp[(3) - (3)].constant))){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if((yyvsp[(1) - (3)].constant).type != (yyvsp[(3) - (3)].constant).type){
									yyerror("semantic error: arithmatic type difference");
									return REJECT;
								}
								(yyval.constant).type = (yyvsp[(1) - (3)].constant).type;
								if((yyval.constant).type == INT_T)
									(yyval.constant).data.Zval = (yyvsp[(1) - (3)].constant).data.Zval * (yyvsp[(3) - (3)].constant).data.Zval;
								else
									(yyval.constant).data.Rval = (yyvsp[(1) - (3)].constant).data.Rval * (yyvsp[(3) - (3)].constant).data.Rval;
								derive("mathematical_operation", gmr("computable")" * "gmr("computable"));
							}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 765 "Yacc.y"
    {
								if(!isNum((yyvsp[(1) - (3)].constant)) || !isNum((yyvsp[(3) - (3)].constant))){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if((yyvsp[(1) - (3)].constant).type != (yyvsp[(3) - (3)].constant).type){
									yyerror("semantic error: arithmatic type difference");
									return REJECT;
								}
								(yyval.constant).type = (yyvsp[(1) - (3)].constant).type;
								if((yyval.constant).type == INT_T)
									(yyval.constant).data.Zval = (yyvsp[(1) - (3)].constant).data.Zval / (yyvsp[(3) - (3)].constant).data.Zval;
								else
									(yyval.constant).data.Rval = (yyvsp[(1) - (3)].constant).data.Rval / (yyvsp[(3) - (3)].constant).data.Rval;
								derive("mathematical_operation", gmr("computable")" / "gmr("computable"));
							}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 781 "Yacc.y"
    {
								if(!isNum((yyvsp[(1) - (3)].constant)) || !isNum((yyvsp[(3) - (3)].constant))){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if((yyvsp[(1) - (3)].constant).type != (yyvsp[(3) - (3)].constant).type){
									yyerror("semantic error: arithmatic type difference");
									return REJECT;
								}
								(yyval.constant).type = (yyvsp[(1) - (3)].constant).type;
								if((yyval.constant).type == INT_T)
									(yyval.constant).data.Zval = pow((yyvsp[(1) - (3)].constant).data.Zval, (yyvsp[(3) - (3)].constant).data.Zval);
								else
									(yyval.constant).data.Rval = pow((yyvsp[(1) - (3)].constant).data.Rval, (yyvsp[(3) - (3)].constant).data.Rval);
								derive("mathematical_operation", gmr("computable")" ** "gmr("computable"));
							}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 797 "Yacc.y"
    {
								if(!isNum((yyvsp[(2) - (2)].constant))){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}
								(yyval.constant).type = (yyvsp[(2) - (2)].constant).type;
								if((yyval.constant).type == INT_T)
									(yyval.constant).data.Zval = - (yyvsp[(2) - (2)].constant).data.Zval;
								else
									(yyval.constant).data.Rval = - (yyvsp[(2) - (2)].constant).data.Rval;
								derive("mathematical_operation", " - "gmr("computable"));
							}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 810 "Yacc.y"
    { (yyval.constant) = (yyvsp[(1) - (1)].constant); derive("computable", constant("%s"), (yyvsp[(1) - (1)].constant).data.Str); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 811 "Yacc.y"
    { (yyval.constant) = (yyvsp[(1) - (1)].constant); derive("computable", constant("%d"), (yyvsp[(1) - (1)].constant).data.Zval); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 812 "Yacc.y"
    { (yyval.constant) = (yyvsp[(1) - (1)].constant); derive("computable", constant("%f"), (yyvsp[(1) - (1)].constant).data.Rval); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 813 "Yacc.y"
    { (yyval.constant) = (yyvsp[(1) - (1)].constant); derive("computable", constant("%s"), ((yyvsp[(1) - (1)].constant).data.Zval)?("true"):("false")); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 815 "Yacc.y"
    {
					if((yyvsp[(1) - (2)].nodes).ep->type == 0){	// Check if it is a function.
						yyerror("syntex error: apply a subroutine as function");
						return REJECT;
					}
					if((yyvsp[(2) - (2)].typeL) != NULL){				// There is one or more arguments were passed in.
						typeLs *tp = (yyvsp[(2) - (2)].typeL);
						nodeP curN = (yyvsp[(1) - (2)].nodes).ep->typeList;
						while(tp != NULL && curN != NULL){
							if(tp->type != curN->ep->type){
								yyerror("sematic error: argument type doesn't match");
								return REJECT;
							}
							tp = tp->next;
							curN = curN->next;
						}
						if(tp != NULL){
							yyerror("sematic error: given too much arguments");
							return REJECT;
						}else if(curN != NULL){
							yyerror("sematic error: given too less arguments");
							return REJECT;
						}
					}

					(yyval.constant).type = (yyvsp[(1) - (2)].nodes).ep->type;
					derive("computable", id("%s")" "gmr("pass_arguments"), (yyvsp[(1) - (2)].nodes).ep->variable);
				}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 844 "Yacc.y"
    {	// an array element.
					if((yyvsp[(3) - (4)].constant).type != INT_T){
						yyerror("sematic error: array indexing with non-integer type");
						return REJECT;
					}
					(yyval.constant).type = (yyvsp[(1) - (4)].nodes).ep->type;
					derive("computable", id("%s")" [ "gmr("computable")" ]", (yyvsp[(1) - (4)].nodes).ep->variable);
				}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 852 "Yacc.y"
    { (yyval.constant) = (yyvsp[(1) - (1)].constant); derive("computable", gmr("expr")); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 853 "Yacc.y"
    { (yyval.constant) = (yyvsp[(2) - (3)].constant); derive("computable", "( "gmr("expr")" )"); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 856 "Yacc.y"
    {	// same as grammar argument, but this rule only stores type.
						(yyval.typeL) = (yyvsp[(2) - (3)].typeL);
						derive("pass_arguments", "( "gmr("computable_list_p")" )");
					}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 860 "Yacc.y"
    { (yyval.typeL) = NULL;}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 863 "Yacc.y"
    {	// Like id_list_p
							(yyval.typeL) = (typeLs *)malloc(sizeof(typeLs));
							(yyval.typeL)->next = (yyvsp[(2) - (2)].typeL);
							(yyval.typeL)->type = (yyvsp[(1) - (2)].constant).type;
							derive("computable_list_p", gmr("computable")" "gmr("computable_list"));
						}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 871 "Yacc.y"
    {	// Like id_list
						(yyval.typeL) = (typeLs *)malloc(sizeof(typeLs));
						(yyval.typeL)->next = (yyvsp[(3) - (3)].typeL);
						(yyval.typeL)->type = (yyvsp[(2) - (3)].constant).type;
						derive("computable_list", ", "gmr("computable")" "gmr("computable_list"));
					}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 877 "Yacc.y"
    { (yyval.typeL) = NULL; }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 879 "Yacc.y"
    { derive("assign", "="); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 880 "Yacc.y"
    { derive("assign", "=>"); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 882 "Yacc.y"
    { derive("linkbreak_p", "<C_LF> "gmr("linkbreak")); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 884 "Yacc.y"
    { derive("linkbreak", "<C_LF> "gmr("linkbreak")); }
    break;



/* Line 1806 of yacc.c  */
#line 3128 "Yacc.tab.c"
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
#line 887 "Yacc.y"


int main(int argc, char* argv[]){
// the path of input file shall follow the execution command.( e.g. ./scanner test.sf)
// you can append some argument to show more information. 
//		-t shows each token
//		-d shows each derive
//		-f delete the bytecode if there exists an error(either syntex or semantic).
//		no arguements only prints comment in *.sf and error message.
// file name must be the first place, the order of other arguments doesn't matter.
	char fileName[256];
	int i;
	tokenPrint = derivePrint = failedRemove = errorOccured = 0;
	if(argc>=2){
		yyin = fopen(argv[1],"r");
		if(yyin != NULL)
			fprintf(stdout, "\033[38;5;46mScanning from file %s\033[0;0m\r\n", argv[1]);
		else{
			fprintf(stdout, "\033[38;5;46mError, cannot find file named \"%s\"\033[0;0m\r\n", argv[1]);
			return 0;
		}
	}else
		fprintf(stdout, "\033[38;5;46mScanning from stdin\033[0;0m\r\n");
	for(i = 2; i<argc; i++){
		if(strcmp(argv[i], "-t")==0)
			tokenPrint = 1;
		else if(strcmp(argv[i], "-d")==0)
			derivePrint = 1;
		else if(strcmp(argv[i], "-f")==0)
			failedRemove = 1;
	}

	if(yyin == NULL || yyin==stdin){				// generates this class.
		sprintf(className, "defaultClass");
	}else{	// Avoid some illegal characters for class name, I didn't list all of illegal characters.
		sscanf(argv[1], "%[^(\. ~)]", className);
	}
	sprintf(fileName, "%s.jasm", className);
	byteCode = fopen(fileName, "w");
	if(byteCode == NULL){
		fprintf(stdout, "\033[38;5;46mError, cannot create file named \"%s\"\033[0;0m\r\n", fileName);
		return 0;
	}
	fprintf(byteCode, "class %s{\r\n", className);
	tab();

	global = current = create(NULL);	// there shall be a global scope, and it is the root.
	yyparse();

	printsAllGlobal();

	tabShift();
	fprintf(byteCode, "}", className);
	fprintf(stdout, "\033[38;5;46mEnd of scanning\033[0;0m\r\n");

	dump(global);
	release(current);
	fclose(byteCode);
	fclose(yyin);

	if(errorOccured && failedRemove)
		remove(fileName);
}
