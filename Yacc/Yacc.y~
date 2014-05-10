%{
#include <stdio.h>
#include "SymbolTable.h"

extern FILE *yyin;
symbolTable *global, *current;

void yyerror(char *msg)
{
    fprintf(stderr, "%s\r\n", msg);
}

%}

%token	DEL_COMMA DEL_COLON DEL_DUAL_COLON DEL_SEMICOLON DEL_L_PARENTHESIS DEL_R_PARENTHESIS
		DEL_L_SQUARE_BRACKET DEL_R_SQUARE_BRACKET DEL_L_BRACKET DEL_R_BRACKET DEL_COMPONENT_REF
 
		OP_ADD OP_SUB  OP_MULTIPLY OP_DIVIDE OP_EXPONENT OP_CONCAT
		OP_LT OP_LE OP_GT OP_GE OP_EQ OP_NE
		OP_AND OP_OR OP_NOT OP_EQV OP_NEQV
		OP_ASSIGN OP_POINTER_ASSIGN

		KW_CALL KW_CASE KW_CHAR KW_CLOSE KW_COMMON KW_CONT KW_CYCLE KW_DATA KW_DIM KW_DO KW_ELSE KW_END KW_EXIT KW_FUNC
		KW_GOTO KW_IF KW_INT KW_INTERFACE KW_LOGIC KW_PROCEDURE KW_PARAMETER KW_PRINT KW_PRINTLN KW_POINTER KW_PROGRAM
		KW_REAL KW_RECURSIVE KW_RETURN KW_SELECT KW_STOP KW_SUB KW_TYPE

%token <Zval>	CONST_BOOL
%token <Zval>	CONST_INT
%token <Rval>	CONST_REAL
%token <Str>	CONST_STRING
%token <Str>	IDENTIFIER

%token C_EOF C_LF

%union {
	int Zval;
	double Rval;
	char Str[2048];
}

%start program

%left	OP_ADD OP_SUB
%left	OP_MULTIPLY OP_DIVIDE
%right	OP_EXPONENT

%%

program : KW_PROGRAM IDENTIFIER C_LF 
			{
				symbolTable *temp = create(current);
				lookup(current, $2)->subRegion = temp;
				current = temp;
			} program_description KW_END KW_PROGRAM IDENTIFIER end
			{
				current = current->parent;
			};

program_description	:	var_const_declare_p	interface_declare_p	stmts;

var_const_declare_p	:	var_const_declare C_LF	var_const_declare_p
					|	;

var_const_declare	:	type attr_list dual_colon id_list_p
					|	global_declare
					|	;

global_declare	:	KW_COMMON OP_DIVIDE IDENTIFIER OP_DIVIDE;

type	:	KW_CHAR
		|	KW_INT
		|	KW_REAL
		|	KW_LOGIC;

attr_list	:	DEL_COMMA attrs attr_list
			|	;

attrs	:	KW_DIM DEL_L_PARENTHESIS CONST_INT DEL_R_PARENTHESIS
		|	KW_POINTER
		|	KW_PARAMETER;

dual_colon	:	DEL_DUAL_COLON
			|	;

id_list_p	:	IDENTIFIER id_list;

id_list	:	DEL_COMMA IDENTIFIER id_list
		|	;

interface_declare_p	:	interface_declare interface_declare_p
					|	;

interface_declare	:	KW_INTERFACE C_LF procedure_description KW_END KW_INTERFACE;

procedure_description	:	recursive_p KW_SUB IDENTIFIER arguments C_LF
							program_description
							KW_END KW_SUB IDENTIFIER C_LF
						|	recursive_p KW_FUNC IDENTIFIER arguments C_LF
							program_description
							KW_END KW_FUNC IDENTIFIER C_LF;

arguments	:	DEL_L_PARENTHESIS id_list_p DEL_R_PARENTHESIS
			|	;

recursive_p	:	KW_RECURSIVE
			|	; 

stmts	:	 stmt stmts 
		| ;

stmt	:	expr_p C_LF;

expr_p	:	

expr	:	computable operation computable { /*fprintf(stdout, "%d + %d", $1, $3);*/}
		|	OP_SUB computable %prec OP_MULTIPLY
		|	IDENTIFIER assign expr;

computable	:	CONST_INT
			|	CONST_REAL
			|	CONST_BOOL
			|	IDENTIFIER;

operation	:	OP_ADD
			|	OP_SUB
			|	OP_MULTIPLY
			|	OP_DIVIDE
			|	OP_EXPONENT;

assign	:	OP_ASSIGN
		|	OP_POINTER_ASSIGN;

end		:	C_EOF
		|	C_LF;

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

	fprintf(stdout, "\r\n\033[38;5;46mEnd of scanning\033[0;0m\r\n");
	release(current);
}