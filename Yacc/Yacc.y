%{
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
							(s == INT_T)?("integer"):(			\
								(s == REAL_T)?("real"):(			\
									(s == STR_T)?("string"):(	\
									"empty")						\
								)									\
							)										\
						)

extern FILE *yyin;
extern long int lineNo;
symbolTable *global, *current;
int tokenPrint, derivePrint;

void yyerror(char *msg)
{
    fprintf(stderr, "\033[38;5;196m%d: %s\033[0;0m\r\n", lineNo, msg);
}

void argListCopy(node headNode){
// After a procedure determine its arguments, we need to build a chain points to each element in symbol table.
	nodeP cur = headNode.ep->typeList, oldHead = cur, newC;
	if(cur - oldHead < 0xFFFF){
	// I'm not sure why, but Yacc sometimes change the pointer to NULL.
	// So I use the distance of logical address to check if these pointers were established in a short peroid.
	// These works just copy the original "ep" to the new node.
		newC = (nodeP)malloc(sizeof(node));
		newC->ep = cur->ep;
		cur = cur->next;
		headNode.ep->typeList = newC;
		while(cur - oldHead < 0xFFFF){
			newC->next = (nodeP)malloc(sizeof(node));
			newC = newC->next;
			newC->ep = cur->ep;
			cur = cur->next;
		}
	}else
		headNode.ep->typeList = NULL;
}

%}

%code requires {
#include "SymbolTable.h"
}

%token	DEL_COMMA DEL_COLON DEL_DUAL_COLON DEL_SEMICOLON DEL_L_PARENTHESIS DEL_R_PARENTHESIS
		DEL_L_SQUARE_BRACKET DEL_R_SQUARE_BRACKET DEL_L_BRACKET DEL_R_BRACKET DEL_COMPONENT_REF
 
		OP_ADD OP_SUB  OP_MULTIPLY OP_DIVIDE OP_EXPONENT OP_CONCAT
		OP_LT OP_LE OP_GT OP_GE OP_EQ OP_NE
		OP_AND OP_OR OP_NOT OP_EQV OP_NEQV
		OP_ASSIGN OP_POINTER_ASSIGN

		KW_CALL KW_CASE KW_CHAR KW_CLOSE KW_COMMON KW_CONT KW_CYCLE KW_DATA KW_DIM KW_DO KW_ELSE KW_END KW_EXIT KW_FUNC
		KW_GOTO KW_IF KW_INT KW_INTERFACE KW_LOGIC KW_PROCEDURE KW_PARAMETER KW_PRINT KW_PRINTLN KW_POINTER KW_PROGRAM
		KW_READ KW_REAL KW_RECURSIVE KW_RETURN KW_SELECT KW_STOP KW_SUB KW_TYPE KW_THEN

%token <constant>	CONST_BOOL
%token <constant>	CONST_INT
%token <constant>	CONST_REAL
%token <constant>	CONST_STRING
%token <nodes>		IDENTIFIER

%token C_EOF C_LF

%union {
	struct _CONST{
		int type;	// 0x01 for int, 0x02 for double, 0x03 for string, 0x04 for boolean.
		union _DATA{
			int Zval;
			double Rval;
			char Str[2048];
		} data;
	} constant;
	node nodes;
	struct _TYPEL{
		int type;
		struct _TYPEL *next;
	} typeL;
}

%start file_p
%type	<constant>	type computable expr boolean_operation relational_operation mathematical_operation array_indexing
%type	<nodes>		id_list_p id_list arguments
%type	<typeL>		computable_list computable_list_p pass_arguments

%left	OP_EQV OP_NEQV
%left	OP_OR
%left	OP_AND
%left	OP_NOT
%left	OP_LT OP_LE OP_GT OP_GE OP_EQ OP_NE
%left	OP_ADD OP_SUB
%left	OP_MULTIPLY OP_DIVIDE
%right	OP_EXPONENT
%nonassoc UMINUS

%%

file_p	:	linebreak_p program file C_EOF { return ACCEPTABLE; /* acceptable state */ };

file	:	procedure_description linebreak_p file
		|	;

program : KW_PROGRAM IDENTIFIER linebreak_p 
			{	// Each symbol table presents a scope.
				symbolTable *temp = create(current);
				$2.ep->subRegion = temp;
				$2.ep->type = 0;
				current = temp;
			} program_description KW_END KW_PROGRAM IDENTIFIER linebreak_p
			{
				if(strcmp($2.ep->variable, $8.ep->variable) != 0){	// Check if the program id are matched or not.
					yyerror("syntex error: program id name doesn't match.\r\n");
					return REJECT;
				}
				current = current->parent;
				derive("program", "program "id("%s")" "gmr("linebreak_p")" "gmr("program_description")" end program "id("%s")" "gmr("ends"), $2.ep->variable, $8.ep->variable);
			};

program_description	:	var_const_declare_p	interface_declare_p	stmts	{ derive("program_description", gmr("var_const_declare_p")" "gmr("interface_declare_p")" "gmr("stmts")); };

var_const_declare_p	:	var_const_declare linebreak_p	var_const_declare_p
						{
							derive("var_const_declare_p", gmr("var_const_declare")" "gmr("linebreak_p")" "gmr("var_const_declare_p"));
						}
					|	;

var_const_declare	:	type attr_list dual_colon id_list_p
						{	// Assign the type of identifiers.
							nodeP cur = &($4);
							while(cur != NULL){
								cur->ep->type = $1.type;
								cur = cur->next;
							}
							derive("var_const_declare", gmr("type")" "gmr("attr_list")" "gmr("dual_colon")" "gmr("id_list_p"));
						}
					|	global_declare	{ derive("var_const_declare", gmr("global_declare")); }
					|	var_init		{ derive("var_const_declare", gmr("var_init")); }
					|	const_init		{ derive("var_const_declare", gmr("const_init")); };

const_init	:	KW_PARAMETER DEL_L_PARENTHESIS const_init_list_p DEL_R_PARENTHESIS
				{
					derive("const_init", "parameter ( "gmr("const_init_list_p")" )");
				};

const_init_list_p	:	IDENTIFIER OP_ASSIGN computable const_init_list
						{
							if($1.ep->type != $3.type){
								yyerror("semantic error: type doesn't match while constant initalizing");
								return REJECT;
							}
							derive("const_init_list_p", id("%s")" = "gmr("computable")" "gmr("const_init_list"), $1.ep->variable);
						};

const_init_list	:	DEL_COMMA IDENTIFIER OP_ASSIGN computable const_init_list
					{
						if($2.ep->type != $4.type){
							yyerror("semantic error: type doesn't match while constant initalizing");
							return REJECT;
						}
						derive("const_init_list", ", "id("%s")" = "gmr("computable")" "gmr("const_init_list"), $2.ep->variable);
					}
				|	;

var_init	:	KW_DATA OP_DIVIDE IDENTIFIER OP_DIVIDE computable OP_DIVIDE
				{
					if($3.ep->type != $5.type){
						yyerror("semantic error: type doesn't match while variable initalizing");
						return REJECT;
					}
					derive("var_init", "data / "id("%s")" / "gmr("computable")" /", $3.ep->variable);
				};

global_declare	:	KW_COMMON OP_DIVIDE IDENTIFIER OP_DIVIDE
					{
						lift2global($3);
						derive("global_declare", "common / "id("%s")" / ", $3.ep->variable);
					};

type	:	KW_CHAR	{ $$.type = STR_T; derive("type", "character "); }
		|	KW_INT	{ $$.type = INT_T; derive("type", "integer "); }
		|	KW_REAL	{ $$.type = REAL_T; derive("type", "real "); }
		|	KW_LOGIC{ $$.type = BOOL_T; derive("type", "logical "); };

attr_list	:	DEL_COMMA attrs attr_list	{ derive("attr_list", ", "gmr("attrs")" "gmr("attrs_list")); }
			|	;

attrs	:	KW_DIM DEL_L_PARENTHESIS CONST_INT DEL_R_PARENTHESIS	{ derive("attrs", "dimension ( %d )", $3.data.Zval); }
		|	KW_POINTER												{ derive("attrs", "pointer"); }
		|	KW_PARAMETER											{ derive("attrs", "parameter"); };

dual_colon	:	DEL_DUAL_COLON	{ derive("dual_colon", "::"); }
			|	;

id_list_p	:	IDENTIFIER id_list
				{	// Make all ids a chain, so we can get all these ids which were claimed in a row.
					if($2.ep != NULL)
						$1.next = &($2);
					else
						$1.next = NULL;
					$$ = $1;
					derive("id_list_p", id("%s")" "gmr("id_list"), $1.ep->variable);
				};

id_list	:	DEL_COMMA IDENTIFIER id_list
			{	// Make chain, same as previous grammar.
				if($3.ep != NULL)
					$2.next = &($3);
				else
					$2.next = NULL;
				$$ = $2;
				derive("id_list", ", "id("%s")" "gmr("id_list"), $2.ep->variable);
			}
		|	{	$$.ep = NULL; };

interface_declare_p	:	interface_declare interface_declare_p	{ derive("interface_declare_p", gmr("interface_declare")gmr("interface_declare_p")); }
					|	;

interface_declare	:	KW_INTERFACE linebreak_p procedure_declaration_p KW_END KW_INTERFACE linebreak_p	{ derive("interface_declare", "interface "gmr("linebreak_p")" "gmr("procedure_declaration")" end interface "gmr("linebreak_p")); };

procedure_declaration_p	:	procedure_declaration	procedure_declaration_p
						|	;

procedure_declaration	:	recursive_p KW_SUB IDENTIFIER 
							{	// Create a new scope
								symbolTable *temp = create(current);
								lift2global($3);
								$3.ep->type = 0;
								$3.ep->subRegion = temp;
								current = temp;
							} arguments 
							{	// get all arguments
								if($5.ep == NULL)
									$3.ep->typeList = NULL;
								else{
									$3.ep->typeList = &($5);
								}
							}
							linebreak_p 
							var_const_declare_p
							KW_END KW_SUB IDENTIFIER linebreak_p
							{
								if(strcmp($3.ep->variable, $11.ep->variable) != 0){
									yyerror("syntex error: subroutine id name doesn't match.\r\n");
									return REJECT;
								}
								current = current->parent;
								argListCopy($3);	// build a new chain to indicate to all arguments.
								derive("procedure_declaration", gmr("recursive_p")" subroutine "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end subroutine "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $11.ep->variable);
							}
						|	recursive_p KW_FUNC IDENTIFIER
							{	// doing the same thing as subroutine version.
								symbolTable *temp = create(current);
								lift2global($3);
								$3.ep->subRegion = temp;
								current = temp;
							} arguments 
							{
								if($5.ep == NULL)
									$3.ep->typeList = NULL;
								else
									$3.ep->typeList = &($5);
							}
							linebreak_p 
							var_const_declare_p
							KW_END KW_FUNC IDENTIFIER linebreak_p
							{
								if(strcmp($3.ep->variable, $11.ep->variable) != 0){
									yyerror("syntex error: function id name doesn't match.\r\n");
									return REJECT;
								}
								$3.ep->type = lookup(current, $3.ep->variable)->type;
								current = current->parent;
								argListCopy($3);
								derive("procedure_declaration", gmr("recursive_p")" function "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end function "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $11.ep->variable);
							};

procedure_description	:	recursive_p KW_SUB IDENTIFIER 
							{	// same as previous rule, but need to check is this procedure had already built.
								if($3.ep->subRegion == NULL){
									symbolTable *temp = create(current);
									$3.ep->subRegion = temp;
									$3.ep->type = 0;
								}
								current = $3.ep->subRegion;
							} arguments 
							{
								if($3.ep->typeList == NULL){
									if($5.ep == NULL)
										$3.ep->typeList = NULL;
									else
										$3.ep->typeList = &($5);
								}
							}
							linebreak_p 
							program_description
							KW_END KW_SUB IDENTIFIER
							{
								if(strcmp($3.ep->variable, $11.ep->variable) != 0){
									yyerror("syntex error: subroutine id name doesn't match.\r\n");
									return REJECT;
								}
								current = current->parent;
								if($3.ep->typeList == &($5))
									argListCopy($3);
								derive("procedure_description", gmr("recursive_p")" subroutine "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end subroutine "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $11.ep->variable);
							}
						|	recursive_p KW_FUNC IDENTIFIER
							{
								if($3.ep->subRegion == NULL){
									symbolTable *temp = create(current);
									$3.ep->subRegion = temp;
									$3.ep->type = 0;
								}
								current = $3.ep->subRegion;
							} arguments 
							{
								if($3.ep->typeList == NULL){
								if($5.ep == NULL)
									$3.ep->typeList = NULL;
								else
									$3.ep->typeList = &($5);
								}
							}
							linebreak_p 
							program_description
							KW_END KW_FUNC IDENTIFIER
							{
								if(strcmp($3.ep->variable, $11.ep->variable) != 0){
									yyerror("syntex error: function id name doesn't match.\r\n");
									return REJECT;
								}
								$3.ep->type = lookup(current, $3.ep->variable)->type;
								current = current->parent;
								if($3.ep->typeList == &($5))
									argListCopy($3);
								derive("procedure_description", gmr("recursive_p")" function "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end function "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $11.ep->variable);
							};

arguments	:	DEL_L_PARENTHESIS id_list_p DEL_R_PARENTHESIS
				{	// pass the id chain.
					$$ = $2;
					derive("arguments", "( "gmr("id_list_p")" )");
				}
			|	{ $$.ep = NULL; };

recursive_p	:	KW_RECURSIVE	{ derive("recursive_p", "recursive"); }
			|	; 

stmts	:	stmt linebreak_p stmt_p	{ derive("stmts", gmr("stmt")" "gmr("linebreak_p")" "gmr("stmt_p")); };

stmt_p	:	stmt linebreak_p stmt_p	{ derive("stmt_p", gmr("stmt")" "gmr("linebreak_p")" "gmr("stmt_p")); }
		|	;

stmt	:	KW_READ IDENTIFIER							{ derive("stmt", "read "id("%s"), $2.ep->variable); }
		|	print_p computable							{ derive("stmt", gmr("print_p")" "gmr("computable")); }
		|	assignment									{ derive("stmt", gmr("assignment")); }
		|	computable									{ derive("stmt", gmr("computable")); }
		|	condition									{ derive("stmt", gmr("condition")); }
		|	KW_RETURN									{ derive("stmt", "return"); }
		|	KW_DO do_parameter linebreak_p do_stmt KW_END KW_DO	{ derive("stmt", "do "gmr("do_parameter")" "gmr("linebreak_p")" "gmr("stmt_p")" end do"); }
		|	KW_CALL IDENTIFIER	pass_arguments
			{
				if($2.ep->type != 0){	// Check this id is a subroutine.
					yyerror("syntex error: invoke a non-subroutine with call");
					return REJECT;
				}
				if($3.type != 0){				// There is one or more arguments passed in.
					struct _TYPEL *tp = &($3);
					nodeP curN = $2.ep->typeList;
					while(tp != NULL && curN != NULL){	// Check the arguments' type.
						if(tp->type != curN->ep->type){
							yyerror("sematic error: argument type doesn't match");
							return REJECT;
						}
						tp = tp->next;
						curN = curN->next;
					}
					if(tp != NULL && tp - &($3) < 0xFFFF){	// number of arguments doesn't match.
						yyerror("sematic error: given too much arguments");
						return REJECT;
					}else if(curN != NULL){
						yyerror("sematic error: given too less arguments");
						return REJECT;
					}
				}
				derive("stmt", "call "id("%s")" "gmr("pass_arguments"), $2.ep->variable);
			};

condition	:	KW_IF DEL_L_PARENTHESIS computable DEL_R_PARENTHESIS KW_THEN linebreak_p stmt_p KW_ELSE linebreak_p stmt_p KW_END KW_IF
				{
					if($3.type != BOOL_T){
						yyerror("syntex error: given a non-boolean expression");
					}
					derive("condition", "if ( "gmr("computable")" ) then "gmr("linebreak_p")" "gmr("stmt_p")" else "gmr("linebreak_p")" "gmr("stmt_p")" end if");
				}
			|	KW_IF DEL_L_PARENTHESIS computable DEL_R_PARENTHESIS KW_THEN linebreak_p stmt_p KW_END KW_IF
				{
					if($3.type != BOOL_T){
						yyerror("syntex error: given a non-boolean expression");
					}
					derive("condition", "if ( "gmr("computable")" ) then "gmr("linebreak_p")" "gmr("stmt_p")" end if");
				}
			|	KW_IF DEL_L_PARENTHESIS computable DEL_R_PARENTHESIS stmt
				{
					if($3.type != BOOL_T){
						yyerror("syntex error: given a non-boolean expression");
					}
					derive("condition", "if ( "gmr("computable")" ) "gmr("stmt"));
				};

assignment	:	IDENTIFIER array_indexing assign computable
				{
					if($1.ep->type != $4.type){
						yyerror("syntex error: type doesn't match");
					}
					derive("assignment", id("%s")" "gmr("array_indexing")" "gmr("assign")" "gmr("computable"), $1.ep->variable);
				};

do_stmt	:	stmt linebreak_p do_stmt	{ derive("do_stmt", gmr("stmt")" "gmr("linebreak_p")" "gmr("do_stmt")); }
		|	KW_EXIT	linebreak_p do_stmt	{ derive("do_stmt", "exit"); }
		|	;

do_parameter	:	assignment DEL_COMMA computable do_diff	{ derive("do_parameter", gmr("assignment")", "gmr("computable")" "gmr("do_diff")); }
				|	;

do_diff	:	DEL_COMMA computable	{ derive("do_diff", ", "gmr("computable"));}
		|	;

print_p	:	KW_PRINT	{ derive("print_p", "print"); }
		|	KW_PRINTLN	{ derive("print_p", "println"); };

array_indexing	:	DEL_L_SQUARE_BRACKET computable DEL_R_SQUARE_BRACKET
					{
						if($2.type != INT_T){
							yyerror("sematic error: array indexing with non-integer type");
							return REJECT;
						}
						$$ = $2;
						derive("array_indexing", "[ "gmr("computable")" ]");
					}
				|	{ $$.type = EMPTY_T; };

expr	:	mathematical_operation	{ $$ = $1; derive("expr", gmr("mathematical_operation")); }
		|	relational_operation	{ $$ = $1; derive("expr", gmr("relational_operation")); }
		|	boolean_operation		{ $$ = $1; derive("expr", gmr("boolean_operation")); };

boolean_operation	:	computable OP_AND computable	
						{
							if($1.type == BOOL_T && $3.type == BOOL_T){
								$$.type = BOOL_T;
								$$.data.Zval = $1.data.Zval & $3.data.Zval;
							}else{
								yyerror("semantic error: boolean");
								return REJECT;
							}
							derive("boolean_operation", gmr("computable")" .AND. "gmr("computable"));
						}
					|	computable OP_OR computable
						{
							if($1.type == BOOL_T && $3.type == BOOL_T){
								$$.type = BOOL_T;
								$$.data.Zval = $1.data.Zval | $3.data.Zval;
							}else{
								yyerror("semantic error: boolean");
								return REJECT;
							}
							derive("boolean_operation", gmr("computable")" .OR. "gmr("computable"));
						}
					|	OP_NOT computable
						{
							if($2.type == BOOL_T){
								$$.type = BOOL_T;
								$$.data.Zval = !($2.data.Zval);
							}else{
								yyerror("semantic error: boolean");
								return REJECT;
							}
							derive("boolean_operation", ".NOT. "gmr("computable"));
						}
					|	computable OP_EQV computable
						{
							if($1.type == BOOL_T && $3.type == BOOL_T){
								$$.type = BOOL_T;
								// 0^0 = 1^1 = 0; 0^1 = 1^0 = 1 => not equal boolean
								$$.data.Zval = !($1.data.Zval ^ $3.data.Zval);
							}else{
								yyerror("semantic error: boolean");
								return REJECT;
							}
							derive("boolean_operation", gmr("computable")" .EQV. "gmr("computable"));
						}
					|	computable OP_NEQV computable
						{
							if($1.type == BOOL_T && $3.type == BOOL_T){
								$$.type = BOOL_T;
								$$.data.Zval = ($1.data.Zval ^ $3.data.Zval);
							}else{
								yyerror("semantic error: boolean");
								return REJECT;
							}
							derive("boolean_operation", gmr("computable")" .NEQV. "gmr("computable"));
						};

relational_operation	:	computable OP_LT computable
							{
								$$.data.Zval = ($1.data.Zval < $3.data.Zval);
								$$.type = BOOL_T;
								derive("relational_operation", gmr("computable")" .LT. "gmr("computable"));
							}
						|	computable OP_LE computable
							{
								$$.data.Zval = ($1.data.Zval <= $3.data.Zval);
								$$.type = BOOL_T;
								derive("relational_operation", gmr("computable")" .LE. "gmr("computable"));
							}
						|	computable OP_GT computable
							{
								$$.data.Zval = ($1.data.Zval > $3.data.Zval);
								$$.type = BOOL_T;
								derive("relational_operation", gmr("computable")" .GT. "gmr("computable"));
							}
						|	computable OP_GE computable
							{
								$$.data.Zval = ($1.data.Zval >= $3.data.Zval);
								$$.type = BOOL_T;
								derive("relational_operation", gmr("computable")" .GE. "gmr("computable"));
							}
						|	computable OP_EQ computable
							{
								$$.data.Zval = ($1.data.Zval == $3.data.Zval);
								$$.type = BOOL_T;
								derive("relational_operation", gmr("computable")" .EQ. "gmr("computable"));
							}
						|	computable OP_NE computable
							{
								$$.data.Zval = ($1.data.Zval != $3.data.Zval);
								$$.type = BOOL_T;
								derive("relational_operation", gmr("computable")" .NE. "gmr("computable"));
							};

mathematical_operation	:	computable OP_ADD computable
							{
								if(!isNum($1) || !isNum($3)){	// the case anyone isn't a numrical variable.
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if($1.type != $3.type){	// the case two are different type (one int, one double).
									yyerror("semantic error: arithmatic type difference");
									return REJECT;
								}
								$$.type = $1.type;
								if($$.type == INT_T)
									$$.data.Zval = $1.data.Zval + $3.data.Zval;
								else
									$$.data.Rval = $1.data.Rval + $3.data.Rval;
								derive("mathematical_operation", gmr("computable")" + "gmr("computable"));
							}
						|	computable OP_SUB computable
							{
								if(!isNum($1) || !isNum($3)){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if($1.type != $3.type){
									yyerror("semantic error: arithmatic type difference");
									return REJECT;
								}
								$$.type = $1.type;
								if($$.type == INT_T)
									$$.data.Zval = $1.data.Zval - $3.data.Zval;
								else
									$$.data.Rval = $1.data.Rval - $3.data.Rval;
								derive("mathematical_operation", gmr("computable")" - "gmr("computable"));
							}
						|	computable OP_MULTIPLY computable
							{
								if(!isNum($1) || !isNum($3)){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if($1.type != $3.type){
									yyerror("semantic error: arithmatic type difference");
									return REJECT;
								}
								$$.type = $1.type;
								if($$.type == INT_T)
									$$.data.Zval = $1.data.Zval * $3.data.Zval;
								else
									$$.data.Rval = $1.data.Rval * $3.data.Rval;
								derive("mathematical_operation", gmr("computable")" * "gmr("computable"));
							}
						|	computable OP_DIVIDE computable
							{
								if(!isNum($1) || !isNum($3)){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if($1.type != $3.type){
									yyerror("semantic error: arithmatic type difference");
									return REJECT;
								}
								$$.type = $1.type;
								if($$.type == INT_T)
									$$.data.Zval = $1.data.Zval / $3.data.Zval;
								else
									$$.data.Rval = $1.data.Rval / $3.data.Rval;
								derive("mathematical_operation", gmr("computable")" / "gmr("computable"));
							}
						|	computable OP_EXPONENT computable
							{
								if(!isNum($1) || !isNum($3)){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if($1.type != $3.type){
									yyerror("semantic error: arithmatic type difference");
									return REJECT;
								}
								$$.type = $1.type;
								if($$.type == INT_T)
									$$.data.Zval = pow($1.data.Zval, $3.data.Zval);
								else
									$$.data.Rval = pow($1.data.Rval, $3.data.Rval);
								derive("mathematical_operation", gmr("computable")" ** "gmr("computable"));
							}
						|	OP_SUB computable %prec UMINUS
							{
								if(!isNum($2)){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}
								$$.type = $2.type;
								if($$.type == INT_T)
									$$.data.Zval = - $2.data.Zval;
								else
									$$.data.Rval = - $2.data.Rval;
								derive("mathematical_operation", " - "gmr("computable"));
							};

computable	:	CONST_INT									{ $$ = $1; derive("computable", constant("%d"), $1.data.Zval); }
			|	CONST_REAL									{ $$ = $1; derive("computable", constant("%f"), $1.data.Rval); }
			|	CONST_BOOL									{ $$ = $1; derive("computable", constant("%s"), ($1.data.Zval)?("true"):("false")); }
			|	IDENTIFIER pass_arguments
				{
					if($1.ep->type == 0){	// Check if it is a function.
						yyerror("syntex error: apply a subroutine as function");
						return REJECT;
					}
					if($2.type != 0){				// There is one or more arguments passed in.
						struct _TYPEL *tp = &($2);
						nodeP curN = $1.ep->typeList;
						while(tp != NULL && curN != NULL){
							if(tp->type != curN->ep->type){
								yyerror("sematic error: argument type doesn't match");
								return REJECT;
							}
							tp = tp->next;
							curN = curN->next;
						}
						if(tp != NULL && tp - &($2) < 0xFFFF){
							yyerror("sematic error: given too much arguments");
							return REJECT;
						}else if(curN != NULL){
							yyerror("sematic error: given too less arguments");
							return REJECT;
						}
					}

					$$.type = $1.ep->type;
					derive("computable", id("%s")" "gmr("pass_arguments"), $1.ep->variable);
				}
			|	IDENTIFIER DEL_L_SQUARE_BRACKET computable DEL_R_SQUARE_BRACKET
				{	// an array element.
					if($3.type != INT_T){
						yyerror("sematic error: array indexing with non-integer type");
						return REJECT;
					}
					$$.type = $1.ep->type;
					derive("computable", id("%s")" [ "gmr("computable")" ]", $1.ep->variable);
				}
			|	expr										{ $$ = $1; derive("computable", gmr("expr")); }
			|	DEL_L_PARENTHESIS expr DEL_R_PARENTHESIS	{ $$ = $2; derive("computable", "( "gmr("expr")" )"); };

pass_arguments	:	DEL_L_PARENTHESIS computable_list_p DEL_R_PARENTHESIS
					{	// same as grammar argument, but this rule only stores type.
						$$ = $2;
						derive("pass_arguments", "( "gmr("computable_list_p")" )");
					}
				|	{ $$.type = 0;};

computable_list_p	:	computable computable_list
						{	// Like id_list_p
							if($2.type != 0)
								$$.next = &($2);
							else
								$$.next = NULL;
							$$.type = $1.type;
							derive("computable_list_p", gmr("computable")" "gmr("computable_list"));
						};

computable_list	:	DEL_COMMA computable computable_list
					{	// Like id_list
						if($3.type != 0)
							$$.next = &($3);
						else
							$$.next = NULL;
						$$.type = $2.type;
						derive("computable_list", ", "gmr("computable")" "gmr("computable_list"));
					}
				|	{ $$.type = 0; };

assign	:	OP_ASSIGN			{ derive("assign", "="); }
		|	OP_POINTER_ASSIGN	{ derive("assign", "=>"); };
 
linebreak_p	:	C_LF linebreak	{ derive("linkbreak_p", "<C_LF> "gmr("linkbreak")); };

linebreak	:	C_LF linebreak	{ derive("linkbreak", "<C_LF> "gmr("linkbreak")); };
			|	;

%%

int main(int argc, char* argv[]){
// the path of input file shall follow the execution command.( e.g. ./scanner test.sf)
// you can append some argument to show more information. 
//		-t shows each token
//		-d shows each derive
//		no arguements only prints comment in *.sf and error message.
// file name must be the first place, the order of other arguments doesn't matter.
	int i;
	tokenPrint = derivePrint = 0;
	if(argc>=2){
		yyin = fopen(argv[1],"r");
		if(yyin != NULL)
			fprintf(stdout, "\033[38;5;46mScanning from file %s\033[0;0m\r\n", argv[1]);
		else
			fprintf(stdout, "\033[38;5;46mScanning from stdin\033[0;0m\r\n");
	}else
		fprintf(stdout, "\033[38;5;46mScanning from stdin\033[0;0m\r\n");
	for(i = 2; i<argc; i++){
		if(strcmp(argv[i], "-t")==0)
			tokenPrint = 1;
		if(strcmp(argv[i], "-d")==0)
			derivePrint = 1;
	}

	global = current = create(NULL);	// there shall be a global scope, and it is the root.
	yyparse();

	fprintf(stdout, "\033[38;5;46mEnd of scanning\033[0;0m\r\n");

	dump(global);
	release(current);
	fclose(yyin);
}