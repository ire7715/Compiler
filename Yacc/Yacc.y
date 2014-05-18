%{
#include <stdio.h>
#include "SymbolTable.h"
#include <math.h>

#define oprintf(s, ...)	\
	do{	\
		char format[2048];	\
		sprintf(format, "{%s}\r\n", s);	\
		fprintf(stdout, format, ##__VA_ARGS__);	\
	}while(0)
#define lift2global(s)	insertBucket(global, deleteBucket(current, *(s.ep)))
	
#define grammar(s)	"\033[38;5;12m"s"\033[0;0m"
#define gmr(s)			grammar(s)
#define grammarP(s)	"\033[38;5;69m"s"\033[0;0m"
#define terminal(s)	"\033[38;5;190m"s"\033[0;0m"
#define derive(s, f, ...)	oprintf(grammarP(s)" -> "f, ##__VA_ARGS__)
#define constant(s)	"\033[38;5;197m"s"\033[0;0m"
#define id(s)	"\033[38;5;190m"s"\033[0;0m"
#define isNum(s)	(s.type == INT_T || s.type == REAL_T)
#define typeString(s)	(s.type == BOOL_T)?("boolean"):(			\
							(s.type == INT_T)?("integer"):(			\
								(s.type == REAL_T)?("real"):(		\
									(s.type == STR_T)?("string"):(	\
									)									\
								)										\
							)											\
						)

#define EMPTY_T	0
#define INT_T		1
#define REAL_T		2
#define STR_T		3
#define BOOL_T		4

#define ACCEPTABLE	0
#define REJECT			1

extern FILE *yyin;
extern long int lineNo;
symbolTable *global, *current;

void yyerror(char *msg)
{
    fprintf(stderr, "\033[38;5;196m%d: %s\033[0;0m\r\n", lineNo, msg);
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

%}

%code requires {
#include "SymbolTable.h"

typedef struct _NODE *nodeP;
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
%token <node>	IDENTIFIER

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
	struct _NODE{
		element *ep;
		nodeP next;
	} node;
}

%start file_p
%type	<constant>	type computable expr boolean_operation relational_operation mathematical_operation array_indexing
%type	<node> id_list_p id_list

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

file_p	:	program file C_EOF { return ACCEPTABLE; /* acceptable state */ };

file	:	procedure_description linebreak_p file
		|	;

program : KW_PROGRAM IDENTIFIER linebreak_p 
			{
				symbolTable *temp = create(current);
				$2.ep->subRegion = temp;
				current = temp;
			} program_description KW_END KW_PROGRAM IDENTIFIER linebreak_p
			{
				if(strcmp($2.ep->variable, $8.ep->variable) != 0){
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
						{
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
				{
					if($2.ep != NULL)
						$1.next = &($2);
					else
						$1.next = NULL;
					$$ = $1;
					derive("id_list_p", id("%s")" "gmr("id_list"), $1.ep->variable);
				};

id_list	:	DEL_COMMA IDENTIFIER id_list
			{
				$$.ep = $2.ep;
				if($3.ep != NULL)
					$$.next = &($3);
				else
					$$.next = NULL;
				derive("id_list", ", "id("%s")" "gmr("id_list"), $2.ep->variable);
			}
		|	{	$$.ep = NULL; };

interface_declare_p	:	interface_declare interface_declare_p	{ derive("interface_declare_p", gmr("interface_declare")gmr("interface_declare_p")); }
					|	;

interface_declare	:	KW_INTERFACE linebreak_p procedure_declaration_p KW_END KW_INTERFACE linebreak_p	{ derive("interface_declare", "interface "gmr("linebreak_p")" "gmr("procedure_declaration")" end interface "gmr("linebreak_p")); };

procedure_declaration_p	:	procedure_declaration	procedure_declaration_p
						|	;

procedure_declaration	:	recursive_p KW_SUB IDENTIFIER 
							{
								symbolTable *temp = create(current);
								lift2global($3);
								$3.ep->subRegion = temp;
								current = temp;
							} arguments linebreak_p 
							var_const_declare_p
							KW_END KW_SUB IDENTIFIER linebreak_p
							{
								if(strcmp($3.ep->variable, $10.ep->variable) != 0){
									yyerror("syntex error: subroutine id name doesn't match.\r\n");
									return REJECT;
								}
								current = current->parent;
								derive("procedure_declaration", gmr("recursive_p")" subroutine "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end subroutine "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $10.ep->variable);
							}
						|	recursive_p KW_FUNC IDENTIFIER
							{
								symbolTable *temp = create(current);
								lift2global($3);
								$3.ep->subRegion = temp;
								current = temp;
							} arguments linebreak_p 
							var_const_declare_p
							KW_END KW_FUNC IDENTIFIER linebreak_p
							{
								if(strcmp($3.ep->variable, $10.ep->variable) != 0){
									yyerror("syntex error: function id name doesn't match.\r\n");
									return REJECT;
								}
								current = current->parent;
								derive("procedure_declaration", gmr("recursive_p")" function "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end function "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $10.ep->variable);
							};

procedure_description	:	recursive_p KW_SUB IDENTIFIER 
							{
								symbolTable *temp = create(current);
								$3.ep->subRegion = temp;
								current = temp;
							} arguments linebreak_p 
							program_description
							KW_END KW_SUB IDENTIFIER
							{
								if(strcmp($3.ep->variable, $10.ep->variable) != 0){
									yyerror("syntex error: subroutine id name doesn't match.\r\n");
									return REJECT;
								}
								current = current->parent;
								derive("procedure_description", gmr("recursive_p")" subroutine "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end subroutine "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $10.ep->variable);
							}
						|	recursive_p KW_FUNC IDENTIFIER
							{
								symbolTable *temp = create(current);
								$3.ep->subRegion = temp;
								current = temp;
							} arguments linebreak_p 
							program_description
							KW_END KW_FUNC IDENTIFIER
							{
								if(strcmp($3.ep->variable, $10.ep->variable) != 0){
									yyerror("syntex error: function id name doesn't match.\r\n");
									return REJECT;
								}
								current = current->parent;
								derive("procedure_description", gmr("recursive_p")" function "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end function "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $10.ep->variable);
							};

arguments	:	DEL_L_PARENTHESIS id_list_p DEL_R_PARENTHESIS	{ derive("arguments", "( "gmr("id_list_p")" )"); }
			|	;

recursive_p	:	KW_RECURSIVE	{ derive("recursive_p", "recursive"); }
			|	; 

stmts	:	stmt linebreak_p stmt_p	{ derive("stmts", gmr("stmt")" "gmr("linebreak_p")" "gmr("stmt_p")); };

stmt_p	:	stmt linebreak_p stmt_p	{ derive("stmt_p", gmr("stmt")" "gmr("linebreak_p")" "gmr("stmt_p")); }
		|	;

stmt	:	KW_READ IDENTIFIER							{ derive("stmt", "read "id("%s"), $2.ep->variable); }
		|	print_p computable							{ derive("stmt", gmr("print_p")" "gmr("computable")); }
		|	IDENTIFIER array_indexing assign computable	{ derive("stmt", id("%s")" "gmr("array_indexing")" "gmr("assign")" "gmr("computable"), $1.ep->variable); }
		|	computable									{ derive("stmt", gmr("computable")); };

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
								if(!isNum($1) || !isNum($3)){
									yyerror("semantic error: not arithmatic expression apply arithmatic operator");
									return REJECT;
								}else if($1.type != $3.type){
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
			|	IDENTIFIER									{ $$.type = $1.ep->type; derive("computable", id("%s"), $1.ep->variable); }
			|	IDENTIFIER DEL_L_SQUARE_BRACKET computable DEL_R_SQUARE_BRACKET
				{
					if($3.type != INT_T){
						yyerror("sematic error: array indexing with non-integer type");
						return REJECT;
					}
					$$.type = $1.ep->type;
					derive("computable", id("%s")" [ "gmr("computable")"=%d ]", $1.ep->variable, $3.data.Zval);
				}
			|	expr										{ $$ = $1; derive("computable", gmr("expr")); }
			|	DEL_L_PARENTHESIS expr DEL_R_PARENTHESIS	{ $$ = $2; derive("computable", "( "gmr("expr")" )"); };

assign	:	OP_ASSIGN			{ derive("assign", "="); }
		|	OP_POINTER_ASSIGN	{ derive("assign", "=>"); };

linebreak_p	:	C_LF linebreak	{ derive("linkbreak_p", "<C_LF> "gmr("linkbreak")); };

linebreak	:	C_LF linebreak	{ derive("linkbreak", "<C_LF> "gmr("linkbreak")); };
			|	;

%%

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
