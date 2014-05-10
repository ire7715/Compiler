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

void printToken(char *text){
	fprintf(stdout, "%s", text);
}

void newLine(){	// Gives a new line
	// Increase lineNo, and prints all token tags of previous line.
	// And then gives new line No. 
	lineNo++;
	//-- fprintf(stdout, "\r\n%s\033[38;5;190m%ld\033[0;0m: ", outputBuff, lineNo);
	//-- outputBuff[0] = '\0';
	fprintf(stdout, "%s\r\n", outputBuff);
	fflush(stdout);
}

%}

realNumber (\+|-)?[0-9]+(\.[0-9]+)?
integer (\+|-)?[0-9]+

%x COMMENTS
%x STRING

%%

	/* delimiter begin */ 
","		{ printToken(yytext); return DEL_COMMA;}
":"		{ printToken(yytext); return DEL_COLON;}
"::"	{ printToken(yytext); return DEL_DUAL_COLON;}
";"		{ printToken(yytext); return DEL_SEMICOLON;}
"("		{ printToken(yytext); return DEL_L_PARENTHESIS;}
")"		{ printToken(yytext); return DEL_R_PARENTHESIS;}
"["		{ printToken(yytext); return DEL_L_SQUARE_BRACKET;}
"]"		{ printToken(yytext); return DEL_R_SQUARE_BRACKET;}
"{"		{ printToken(yytext); return DEL_L_BRACKET;}
"}"		{ printToken(yytext); return DEL_R_BRACKET;}
"%"		{ printToken(yytext); return DEL_COMPONENT_REF;}
	/* delemiter end */

	/* operators begin */
	/*	Arithmatic */
"+"		{ printToken(yytext); return OP_ADD;}
"-"		{ printToken(yytext); return OP_SUB;}
"*"		{ printToken(yytext); return OP_MULTIPLY;}
"/"		{ printToken(yytext); return OP_DIVIDE;}
"**"	{ printToken(yytext); return OP_EXPONENT;}
"//"	{ printToken(yytext); return OP_CONCAT;}

	/*	Relation */
"<"|".LT."	{ printToken(yytext); return OP_LT;}
"<="|".LE."	{ printToken(yytext); return OP_LE;}
">"|".GT."	{ printToken(yytext); return OP_GT;}
">="|".GE."	{ printToken(yytext); return OP_GE;}
"=="|".EQ."	{ printToken(yytext); return OP_EQ;}
"/="|".NE."	{ printToken(yytext); return OP_NE;}

	/*	Logic */
".AND."		{ printToken(yytext); return OP_AND;}
".OR."		{ printToken(yytext); return OP_OR;}
".NOT."		{ printToken(yytext); return OP_NOT;}
".EQV."		{ printToken(yytext); return OP_EQV;}
".NEQV."	{ printToken(yytext); return OP_NEQV;}

	/*	Assign */
"="		{ printToken(yytext); return OP_ASSIGN;}
"=>"	{ printToken(yytext); return OP_POINTER_ASSIGN;};
	/* operators end */

	/* keywords begin */
"call"			{ printToken(yytext); return KW_CALL;}
"case"			{ printToken(yytext); return KW_CASE;}
"character"		{ printToken(yytext); return KW_CHAR;}
"close"			{ printToken(yytext); return KW_CLOSE;}
"common"		{ printToken(yytext); return KW_COMMON;}
"continue"		{ printToken(yytext); return KW_CONT;}
"cycle"			{ printToken(yytext); return KW_CYCLE;}
"data"			{ printToken(yytext); return KW_DATA;}
"dimension"		{ printToken(yytext); return KW_DIM;}
"do"			{ printToken(yytext); return KW_DO;}
"else"			{ printToken(yytext); return KW_ELSE;}
"end"			{ printToken(yytext); return KW_END;}
"exit"			{ printToken(yytext); return KW_EXIT;}
"function"		{ printToken(yytext); return KW_FUNC;}
"goto"			{ printToken(yytext); return KW_GOTO;}
"if"			{ printToken(yytext); return KW_IF;}
"integer"		{ printToken(yytext); return KW_INT;}
"interface"		{ printToken(yytext); return KW_INTERFACE;}
"logical"		{ printToken(yytext); return KW_LOGIC;}
"procedure"		{ printToken(yytext); return KW_PROCEDURE;}
"parameter"		{ printToken(yytext); return KW_PARAMETER;}
"print"			{ printToken(yytext); return KW_PRINT;}
"println"		{ printToken(yytext); return KW_PRINTLN;}
"pointer"		{ printToken(yytext); return KW_POINTER;}
"program"		{ printToken(yytext); return KW_PROGRAM;}
"real"			{ printToken(yytext); return KW_REAL;}
"recursive"		{ printToken(yytext); return KW_RECURSIVE;}
"return"		{ printToken(yytext); return KW_RETURN;}
"select"		{ printToken(yytext); return KW_SELECT;}
"stop"			{ printToken(yytext); return KW_STOP;}
"subroutine"	{ printToken(yytext); return KW_SUB;}
"type"			{ printToken(yytext); return KW_TYPE;}
	/* keywords end */

	/* booleans begin */
".TRUE."	{ printToken(yytext); yylval.Zval = 1; return CONST_BOOL;}
".FALSE."	{ printToken(yytext); yylval.Zval = 0; return CONST_BOOL;}
	/* booleans end */

	/* integers begin */
{integer}	{
				printToken(yytext);
				int temp;
				sscanf(yytext, "%d", &(yylval.Zval));
				return CONST_INT;
			}
	/* integers end */

	/* real numbers */
{realNumber}E{integer}	{
							printToken(yytext);
							double temp;
							sscanf(yytext, "%lf", &(yylval.Rval));
							YYLVAL(temp);
							return CONST_REAL;
						}
((\+|-)?[0-9]*\.[0-9]+)	{
							printToken(yytext);
							double temp; 
							sscanf(yytext, "%lf", &(yylval.Rval));
							YYLVAL(temp);
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
		printToken(strBuff);
		memcpy(yylval.Str, strBuff, strlen(strBuff)+1);
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
^(C|"*")" ".*$ { fprintf(stdout, "\033[38;5;247m%s\033[0;0m", yytext); }
"!".*$ { fprintf(stdout, "\033[38;5;247m%s\033[0;0m", yytext); }
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
		printToken(yytext);
		if(lookup(current, yytext) == NULL)
			insert(current, yytext);
		memcpy(yylval.Str, yytext, strlen(yytext)+1);
		return IDENTIFIER;
	}
	/* identifiers end */

" "|"\t" { fprintf(stdout, "%s", yytext); }
"\n" { newLine(); return C_LF;}
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