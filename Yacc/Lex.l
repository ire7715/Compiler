%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Yacc.tab.h"
#include "SymbolTable.h"

#define YYLVAL(t) yylval = (YYSTYPE)t
#define OUT_SIZE 4096
#define MAX_STR_SIZE 2048

long int lineNo = 0;
char outputBuff[OUT_SIZE], strBuff[MAX_STR_SIZE];	// outputBuff stores token tags in current line.
extern int tokenPrint;

void printTokenOrd(char *text){
	fprintf(stdout, "<%s>\r\n", text);
}

void printToken(char *text, char *tokenType){
	if(tokenPrint)
		fprintf(stdout, "<\033[38;5;46m%s\033[0;0m: \033[38;5;204m%s\033[0;0m> @ line %ld\r\n", tokenType, text, lineNo);
}

void newLine(){	// Gives a new line
	// Increase lineNo, and prints all token tags of previous line.
	// And then gives new line No. 
	lineNo++;
	//-- fprintf(stdout, "\r\n%s\033[38;5;190m%ld\033[0;0m: ", outputBuff, lineNo);
	//-- outputBuff[0] = '\0';
	//-- fprintf(stdout, "%s\r\n", outputBuff);
	//-- fflush(stdout);
}

%}

realNumber (\+|-)?[0-9]+(\.[0-9]+)?
integer (\+|-)?[0-9]+

%x COMMENTS
%x STRING

%%

	/* delimiter begin */ 
","		{ printToken(yytext, "delimiter"); return DEL_COMMA;}
":"		{ printToken(yytext, "delimiter"); return DEL_COLON;}
"::"	{ printToken(yytext, "delimiter"); return DEL_DUAL_COLON;}
";"		{ printToken(yytext, "delimiter"); return DEL_SEMICOLON;}
"("		{ printToken(yytext, "delimiter"); return DEL_L_PARENTHESIS;}
")"		{ printToken(yytext, "delimiter"); return DEL_R_PARENTHESIS;}
"["		{ printToken(yytext, "delimiter"); return DEL_L_SQUARE_BRACKET;}
"]"		{ printToken(yytext, "delimiter"); return DEL_R_SQUARE_BRACKET;}
"{"		{ printToken(yytext, "delimiter"); return DEL_L_BRACKET;}
"}"		{ printToken(yytext, "delimiter"); return DEL_R_BRACKET;}
"%"		{ printToken(yytext, "delimiter"); return DEL_COMPONENT_REF;}
	/* delemiter end */

	/* operators begin */
	/*	Arithmatic */
"+"		{ printToken(yytext, "operator"); return OP_ADD;}
"-"		{ printToken(yytext, "operator"); return OP_SUB;}
"*"		{ printToken(yytext, "operator"); return OP_MULTIPLY;}
"/"		{ printToken(yytext, "operator"); return OP_DIVIDE;}
"**"	{ printToken(yytext, "operator"); return OP_EXPONENT;}
"//"	{ printToken(yytext, "operator"); return OP_CONCAT;}

	/*	Relation */
"<"|".LT."	{ printToken(yytext, "operator"); return OP_LT;}
"<="|".LE."	{ printToken(yytext, "operator"); return OP_LE;}
">"|".GT."	{ printToken(yytext, "operator"); return OP_GT;}
">="|".GE."	{ printToken(yytext, "operator"); return OP_GE;}
"=="|".EQ."	{ printToken(yytext, "operator"); return OP_EQ;}
"/="|".NE."	{ printToken(yytext, "operator"); return OP_NE;}

	/*	Logic */
".AND."		{ printToken(yytext, "operator"); return OP_AND;}
".OR."		{ printToken(yytext, "operator"); return OP_OR;}
".NOT."		{ printToken(yytext, "operator"); return OP_NOT;}
".EQV."		{ printToken(yytext, "operator"); return OP_EQV;}
".NEQV."	{ printToken(yytext, "operator"); return OP_NEQV;}

	/*	Assign */
"="		{ printToken(yytext, "operator"); return OP_ASSIGN;}
"=>"	{ printToken(yytext, "operator"); return OP_POINTER_ASSIGN;};
	/* operators end */

	/* keywords begin */
"call"			{ printToken(yytext, "keyword"); return KW_CALL;}
"case"			{ printToken(yytext, "keyword"); return KW_CASE;}
"character"		{ printToken(yytext, "keyword"); return KW_CHAR;}
"close"			{ printToken(yytext, "keyword"); return KW_CLOSE;}
"common"		{ printToken(yytext, "keyword"); return KW_COMMON;}
"continue"		{ printToken(yytext, "keyword"); return KW_CONT;}
"cycle"			{ printToken(yytext, "keyword"); return KW_CYCLE;}
"data"			{ printToken(yytext, "keyword"); return KW_DATA;}
"dimension"		{ printToken(yytext, "keyword"); return KW_DIM;}
"do"			{ printToken(yytext, "keyword"); return KW_DO;}
"else"			{ printToken(yytext, "keyword"); return KW_ELSE;}
"end"			{ printToken(yytext, "keyword"); return KW_END;}
"exit"			{ printToken(yytext, "keyword"); return KW_EXIT;}
"function"		{ printToken(yytext, "keyword"); return KW_FUNC;}
"goto"			{ printToken(yytext, "keyword"); return KW_GOTO;}
"if"			{ printToken(yytext, "keyword"); return KW_IF;}
"integer"		{ printToken(yytext, "keyword"); return KW_INT;}
"interface"		{ printToken(yytext, "keyword"); return KW_INTERFACE;}
"logical"		{ printToken(yytext, "keyword"); return KW_LOGIC;}
"procedure"		{ printToken(yytext, "keyword"); return KW_PROCEDURE;}
"parameter"		{ printToken(yytext, "keyword"); return KW_PARAMETER;}
"print"			{ printToken(yytext, "keyword"); return KW_PRINT;}
"println"		{ printToken(yytext, "keyword"); return KW_PRINTLN;}
"pointer"		{ printToken(yytext, "keyword"); return KW_POINTER;}
"program"		{ printToken(yytext, "keyword"); return KW_PROGRAM;}
"read"			{ printToken(yytext, "keyword"); return KW_PROGRAM;}
"real"			{ printToken(yytext, "keyword"); return KW_REAL;}
"recursive"		{ printToken(yytext, "keyword"); return KW_RECURSIVE;}
"return"		{ printToken(yytext, "keyword"); return KW_RETURN;}
"select"		{ printToken(yytext, "keyword"); return KW_SELECT;}
"stop"			{ printToken(yytext, "keyword"); return KW_STOP;}
"subroutine"	{ printToken(yytext, "keyword"); return KW_SUB;}
"type"			{ printToken(yytext, "keyword"); return KW_TYPE;}
"then"			{ printToken(yytext, "keyword"); return KW_THEN;}

	/* keywords end */

	/* booleans begin */
".TRUE."	{ printToken(yytext, "boolean"); yylval.constant.type = 4; yylval.constant.data.Zval = 1; return CONST_BOOL;}
".FALSE."	{ printToken(yytext, "boolean"); yylval.constant.type = 4; yylval.constant.data.Zval = 0; return CONST_BOOL;}
	/* booleans end */

	/* integers begin */
{integer}	{
				printToken(yytext, "integer");
				yylval.constant.type = 1;
				sscanf(yytext, "%d", &(yylval.constant.data.Zval));
				return CONST_INT;
			}
	/* integers end */

	/* real numbers */
{realNumber}E{integer}	{
							printToken(yytext, "real");
							yylval.constant.type = 2;
							sscanf(yytext, "%lf", &(yylval.constant.data.Rval));
							return CONST_REAL;
						}
((\+|-)?[0-9]*\.[0-9]+)	{
							printToken(yytext, "real");
							yylval.constant.type = 2;
							sscanf(yytext, "%lf", &(yylval.constant.data.Rval));
							return CONST_REAL;
						}
	/* real numbers */

	/* strings begin */
\" { 
		// Start string pattern
		BEGIN(STRING);
		strBuff[0] = '\0'; 
	}
<STRING>\" {
		// Met one double-quote implies string ends. Complete the string tag and back to initial state.
		BEGIN(INITIAL);
		printToken(strBuff, "string");
		yylval.constant.type = 3;
		memcpy(yylval.constant.data.Str, strBuff, strlen(strBuff)+1);
		return CONST_STRING;
	}
<STRING>\\\" {
		// Met a slash and a double-quote implies a double-quote in string.
		sprintf(strBuff, "%s%c", strBuff, (char)0x22);
	}
<STRING>\"\" {
		// Met two double-quote implies a double-quote in string.
		sprintf(strBuff, "%s%c", strBuff, (char)0x22);
	}
<STRING>[^(\"|\n|(\\\"))]* {
		// Met anything neither double-quote nor line break then it is a part of string. Store it.
		sprintf(strBuff, "%s%s", strBuff, yytext);
	}
<STRING>\n {
		// Met a line break in the string implies it's an un-closed string.
		fprintf(stdout, "\033[38;5;196mun-closed String\033[0;0m @ line %ld\r\n", lineNo);
		newLine();
		BEGIN(INITIAL);
		return C_LF;
	}
<STRING><<EOF>> {
		// Reach the end-of-file in the string implies it's an un-closed string.
		fprintf(stdout, "\033[38;5;196mun-closed String\033[0;0m @ line %ld\r\n", lineNo);
		BEGIN(INITIAL);
		return C_EOF;
	}
	/* strings end */

	/* comments begin */
^(C|"*")" ".*$ { fprintf(stdout, "\033[38;5;247m%s\033[0;0m\r\n", yytext); }
"!".*$ { fprintf(stdout, "\033[38;5;247m%s\033[0;0m\r\n", yytext); }
"/*" {
		fprintf(stdout, "\033[38;5;247m%s", yytext);
		BEGIN(COMMENTS);
	}
<COMMENTS>"\n" { newLine(); fprintf(stdout, "\033[38;5;247m"); return C_LF;}
<COMMENTS>"*/" {
		fprintf(stdout, "%s\033[0;0m", yytext);
		BEGIN(INITIAL);
	}
<COMMENTS><<EOF>> {
		fprintf(stdout, "\r\n\t%s\033[38;5;196mun-closed Comment\033[0;0m @ line %ld\r\n", outputBuff, lineNo);
		BEGIN(INITIAL); 
		return C_EOF;
	}
	/* comments end */

	/* identifiers begin */
[A-Za-z][0-9A-Za-z]* { 
		printToken(yytext, "identifier");
		if((yylval.nodes.ep = lookup(current, yytext)) == NULL)
			yylval.nodes.ep = insert(current, yytext);
		return IDENTIFIER;
	}
	/* identifiers end */

" "|"\t" { /*fprintf(stdout, "%s", yytext);*/ }
"\n" { printToken("C_LF", "LineBreak"); newLine(); return C_LF;}
<<EOF>> { return C_EOF;}
%%

/*int t_main(int argc, char *argv[]){
	if(argc>1){
		yyin = fopen(argv[1],"r");
		if(yyin != NULL)
			fprintf(stdout, "\033[38;5;46mScanning from file %s\033[0;0m\r\n", argv[1]);
		else
			fprintf(stdout, "\033[38;5;46mScanning from stdin\033[0;0m\r\n");
	}else
		fprintf(stdout, "\033[38;5;46mScanning from stdin\033[0;0m\r\n");
	create(NULL);
	outputBuff[0] = '\0';
	newLine();
	yylex();
	dump(current);
	fprintf(stdout, "\r\n\033[38;5;46mEnd of scanning\033[0;0m\r\n");
	release(current);
	return 0;
}*/
