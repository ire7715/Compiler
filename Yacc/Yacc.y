%{
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
%type	<constant>	type
%type	<node> id_list_p

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

file_p	:	program file C_EOF { return 0; /* acceptable state */ };

file	:	procedure_description linebreak_p file
		|	;

program : KW_PROGRAM IDENTIFIER linebreak_p 
			{
				symbolTable *temp = create(current);
				//lookup(current, $2.ep->variable)->subRegion = temp;
				$2.ep->subRegion = temp;
				current = temp;
			} program_description KW_END KW_PROGRAM IDENTIFIER linebreak_p
			{
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
							
							derive("var_const_declare", gmr("global_declare")" "gmr("type")" "gmr("attr_list")" "gmr("dual_colon")" "gmr("id_list_p"));
						}
					|	global_declare						{ derive("var_const_declare", gmr("global_declare")); };

global_declare	:	KW_COMMON OP_DIVIDE IDENTIFIER OP_DIVIDE
					{
						derive("global_declare", "common / "id("%s")" / ", $3.ep->variable);
					};

type	:	KW_CHAR	{ $$.type = 3; derive("type", "character "); }
		|	KW_INT	{ $$.type = 1; derive("type", "integer "); }
		|	KW_REAL	{ $$.type = 2; derive("type", "real "); }
		|	KW_LOGIC{ $$.type = 4; derive("type", "logical "); };

attr_list	:	DEL_COMMA attrs attr_list	{ derive("attr_list", ", "gmr("attrs")" "gmr("attrs_list")); }
			|	;

attrs	:	KW_DIM DEL_L_PARENTHESIS CONST_INT DEL_R_PARENTHESIS	{ derive("attrs", "dimension ( %d )", $3.data.Zval); }
		|	KW_POINTER												{ derive("attrs", "pointer"); }
		|	KW_PARAMETER											{ derive("attrs", "parameter"); };

dual_colon	:	DEL_DUAL_COLON	{ derive("dual_colon", "::"); }
			|	;

id_list_p	:	IDENTIFIER id_list
				{
					/*$$.next = $2;
					$$.ep = lookup($1.data.Str);*/
					derive("id_list_p", id("%s")" "gmr("id_list"), $1.ep->variable);
				};

id_list	:	DEL_COMMA IDENTIFIER id_list
			{
				
				derive("id_list", ", "id("%s")" "gmr("id_list"), $2.ep->variable);
			}
		|	;

interface_declare_p	:	interface_declare interface_declare_p	{ derive("interface_declare_p", gmr("interface_declare")gmr("interface_declare_p")); }
					|	;

interface_declare	:	KW_INTERFACE linebreak_p procedure_declaration_p KW_END KW_INTERFACE linebreak_p	{ derive("interface_declare", "interface "gmr("linebreak_p")" "gmr("procedure_declaration")" end interface "gmr("linebreak_p")); };

procedure_declaration_p	:	procedure_declaration	procedure_declaration_p
						|	;

procedure_declaration	:	recursive_p KW_SUB IDENTIFIER arguments linebreak_p 
							{
								symbolTable *temp = create(current);
								//lookup(current, $3.data.Str)->subRegion = temp;
								$3.ep->subRegion = temp;
								current = temp;
							} 
							var_const_declare_p
							KW_END KW_SUB IDENTIFIER linebreak_p
							{
								current = current->parent;
								derive("procedure_declaration", gmr("recursive_p")" subroutine "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end subroutine "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $3.ep->variable);
							}
						|	recursive_p KW_FUNC IDENTIFIER arguments linebreak_p
							{
								symbolTable *temp = create(current);
								//lookup(current, $3.data.Str)->subRegion = temp;
								$3.ep->subRegion = temp;
								current = temp;
							} 
							var_const_declare_p
							KW_END KW_FUNC IDENTIFIER linebreak_p
							{
								current = current->parent;
								derive("procedure_declaration", gmr("recursive_p")" function "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end function "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $3.ep->variable);
							};

procedure_description	:	recursive_p KW_SUB IDENTIFIER arguments linebreak_p 
							{
								symbolTable *temp = create(current);
								//lookup(current, $3.data.Str)->subRegion = temp;
								$3.ep->subRegion = temp;
								current = temp;
							} 
							program_description
							KW_END KW_SUB IDENTIFIER
							{
								current = current->parent;
								derive("procedure_description", gmr("recursive_p")" subroutine "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end subroutine "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $3.ep->variable);
							}
						|	recursive_p KW_FUNC IDENTIFIER arguments linebreak_p
							{
								symbolTable *temp = create(current);
								//lookup(current, $3.data.Str)->subRegion = temp;
								$3.ep->subRegion = temp;
								current = temp;
							} 
							program_description
							KW_END KW_FUNC IDENTIFIER
							{
								current = current->parent;
								derive("procedure_description", gmr("recursive_p")" function "id("%s")" "gmr("arguments")" "gmr("linebreak_p")" "gmr("program_description")" end function "id("%s")" "gmr("linebreak_p"), $3.ep->variable, $3.ep->variable);
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

array_indexing	:	DEL_L_SQUARE_BRACKET integer_expr DEL_R_SQUARE_BRACKET	{ derive("array_indexing", "[ "gmr("integer_expr")" ]"); }
				|	;

expr	:	mathematical_operation	{ derive("expr", gmr("mathematical_operation")); };
		|	relational_operation	{ derive("expr", gmr("relational_operation")); };
		|	boolean_operation		{ derive("expr", gmr("boolean_operation")); };

boolean_operation	:	computable OP_AND computable	{ derive("boolean_operation", gmr("computable")" .AND. "gmr("computable")); }
					|	computable OP_OR computable		{ derive("boolean_operation", gmr("computable")" .OR. "gmr("computable")); }
					|	OP_NOT computable				{ derive("boolean_operation", ".NOT. "gmr("computable")); }
					|	computable OP_EQV computable	{ derive("boolean_operation", gmr("computable")" .EQV. "gmr("computable")); }
					|	computable OP_NEQV computable	{ derive("boolean_operation", gmr("computable")" .NEQV. "gmr("computable")); };

relational_operation	:	computable OP_LT computable	{ derive("relational_operation", gmr("computable")" .LT. "gmr("computable")); }
						|	computable OP_LE computable	{ derive("relational_operation", gmr("computable")" .LE. "gmr("computable")); }
						|	computable OP_GT computable	{ derive("relational_operation", gmr("computable")" .GT. "gmr("computable")); }
						|	computable OP_GE computable	{ derive("relational_operation", gmr("computable")" .GE. "gmr("computable")); }
						|	computable OP_EQ computable	{ derive("relational_operation", gmr("computable")" .EQ. "gmr("computable")); }
						|	computable OP_NE computable	{ derive("relational_operation", gmr("computable")" .NE. "gmr("computable")); };

mathematical_operation	:	computable OP_ADD computable		{ derive("mathematical_operation", gmr("computable")" + "gmr("computable")); }
						|	computable OP_SUB computable		{ derive("mathematical_operation", gmr("computable")" - "gmr("computable")); }
						|	computable OP_MULTIPLY computable	{ derive("mathematical_operation", gmr("computable")" * "gmr("computable")); }
						|	computable OP_DIVIDE computable		{ derive("mathematical_operation", gmr("computable")" / "gmr("computable")); }
						|	computable OP_EXPONENT computable	{ derive("mathematical_operation", gmr("computable")" ** "gmr("computable")); }
						|	OP_SUB computable %prec UMINUS		{ derive("mathematical_operation", "- "gmr("computable")); };

computable	:	CONST_INT									{ derive("computable", constant("%d"), $1.data.Zval); }
			|	CONST_REAL									{ derive("computable", constant("%f"), $1.data.Rval); }
			|	CONST_BOOL									{ derive("computable", constant("%s"), ($1.data.Zval)?("true"):("false")); }
			|	IDENTIFIER									{ derive("computable", id("%s"), $1.ep->variable); }
			|	expr										{ derive("computable", gmr("expr")); }
			|	DEL_L_PARENTHESIS expr DEL_R_PARENTHESIS	{ derive("computable", "( "gmr("expr")" )"); };

integer_expr:	CONST_INT	{ derive("integer_expr", constant("%d"), $1.data.Zval); }
			|	IDENTIFIER	{ derive("integer_expr", id("%s"), $1.ep->variable); };

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
