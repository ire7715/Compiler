%{

#include <stdio.h>
#include <stdlib.h>

#define ID_LEN 128
#define TABLE_SIZE 227	// Just a prime number
#define OUT_SIZE 4096

typedef struct _ELEMENT{
	char variable[ID_LEN];
} element;	// A smallest unit in hash table, presents an element.

typedef struct _BUCKET *bucketP;
typedef struct _BUCKET{
	element inner;
	bucketP link;
} bucket;	// A bucket is used for containing an element, providing linked list functionality as wall as.

typedef struct _SYMBOLTABLE{
	bucket table[TABLE_SIZE];
} symbolTable;	// A simple symbol table implemented by chaining hash table.

long int lineNo = 0;
char outputBuff[OUT_SIZE];	// outputBuff stores token tags in current line.
symbolTable *st;

void printElement(element e){	// Simply prints an element.
	fprintf(stdout, "%s\r\n", e.variable);
}

symbolTable *create(){	// Initialize a symbol table and return the pointer of that symbol table.
	st = (symbolTable *)malloc(sizeof(symbolTable));
	int i;
	for(i = 0; i < TABLE_SIZE ; i++){	// the very first bucket in each slot are head node, not for data containing.
		st->table[i].link = NULL;
	}
	return st;
}

unsigned int hash(char *str){	// BKDR hash
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	while (*str)
		hash = hash * seed + (*str++);

	return hash % TABLE_SIZE;
}

element *lookup(char *s){	// Look up a specific variable name.
	unsigned int h = hash(s);
	bucket *cur = st->table[h].link;	// Hash to the corresponded slot, and then traverse the chain to find the correct string.
	while(cur != NULL){
		if(strcmp(cur->inner.variable, s) == 0)
			return &(cur->inner);
		cur = cur->link;
	}
	return &(cur->inner);
}

element *insert(char *s){	// Insert a variable name into symbol table.
	/** 
	 *	Create a new bucket to contain this string.
	 *	Compute the hash value, and insert the new bucket onto the chain.
	 *	Return the pointer of the element which containing the variable name.
	**/
	unsigned int h = hash(s);
	bucket *newB = (bucket *)malloc(sizeof(bucket));
	sprintf(newB->inner.variable, "%s", s);
	newB->link = st->table[h].link;
	st->table[h].link = newB;
	return &(newB->inner);
}

symbolTable *dump(){	// Visit all slots and traverse all buckets in the chain, and print all data contained.
	int i;
	bucket *cur;
	fprintf(stdout, "\033[38;5;45m*** Symbol table ***\033[0;0m\r\n");	// \033 is for the console color. For more information please refer to https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
	for(i = 0; i< TABLE_SIZE ; i++){
		cur = st->table[i].link;
		while(cur != NULL){
			printElement(cur->inner);
			cur = cur->link;
		}
	}
	return st;
}

void release(){	// This function is for releasing memories of symbol table.
	int i;
	bucket *cur, *temp;
	for(i = 0; i < TABLE_SIZE; i++){	// Traverse all buckets and release them.
		cur = st->table[i].link;
		while(cur != NULL){
			temp = cur;
			cur = cur->link;
			free(temp);
		}
	}
	free(st);
}

void printTokenAndStore(char *yytext, char *tokenType, char *specify){
	// Prints the matched text out, and stores the token tag in outputBuff.
	fprintf(stdout, "%s", yytext);
	if(specify == NULL)
		sprintf(outputBuff, "%s\t<\033[38;5;46m%s\033[0;0m: \033[38;5;204m%s\033[0;0m> @ line %ld\r\n", outputBuff, tokenType, yytext, lineNo);
	else
		sprintf(outputBuff, "%s\t<\033[38;5;46m%s\033[0;0m: \033[38;5;204m%s\033[0;0m (%s)> @ line %ld\r\n", outputBuff, tokenType, yytext, specify, lineNo);
	
}

void newLine(){	// Gives a new line
	// Increase lineNo, and prints all token tags of previous line.
	// And then gives new line No. 
	lineNo++;
	fprintf(stdout, "\r\n%s\033[38;5;190m%ld\033[0;0m: ", outputBuff, lineNo);
	outputBuff[0] = '\0';
}

%}

realNumber (\+|-)?[0-9]+(\.[0-9]+)?
integer (\+|-)?[0-9]+

%x COMMENTS
%x STRING

%%

	/* Due to the proj.pdf file isn't clear. */
	/* I'm not sure if all characters are case-insensitive or not. */
	/* If there shall be case in-sensitive, please execute flex with -i parameter. */

	/* delimiter begin */ 
"," { printTokenAndStore(yytext, "delimiter", "comma");}
":"":"? { printTokenAndStore(yytext, "delimiter", "colon");}
";" { printTokenAndStore(yytext, "delimiter", "semicolon");}
"(" { printTokenAndStore(yytext, "delimiter", "left parentheses");}
")" { printTokenAndStore(yytext, "delimiter", "right parentheses");}
"[" { printTokenAndStore(yytext, "delimiter", "left square bracket");}
"]" { printTokenAndStore(yytext, "delimiter", "right square bracket");}
"{" { printTokenAndStore(yytext, "delimiter", "left bracket");}
"}" { printTokenAndStore(yytext, "delimiter", "right parentheses");}
"%" { printTokenAndStore(yytext, "delimiter", "component reference");}
	/* delemiter end */

	/* operators begin */
"+"|"-"|"*"|"/" { printTokenAndStore(yytext, "operator", "arithmetic");}
"**" { printTokenAndStore(yytext, "operator", "exponentiation");}
"//" { printTokenAndStore(yytext, "operator", "concatenation");}
(("<"|">")"="?)|(("/"|"=")"=") { printTokenAndStore(yytext, "operator", "relational");}
((".L"|".G")("T."|"E."))|(".EQ."|".NE.") { printTokenAndStore(yytext, "operator", "relational");}
"."("AND"|"OR"|"NOT"|"EQV"|"NEQV")"." { printTokenAndStore(yytext, "operator", "logical");}
"=" { printTokenAndStore(yytext, "operator", "assignment");}
"=>" { printTokenAndStore(yytext, "operator", "pointer assignment");}
	/* operators end */

	/* keywords begin */
"call"|"case"|"character"|"close"|"continue"|"cycle"|"data"|"dimension"|"do"|"else"|"end"|"exit"|"function"|"goto"|"if"|"integer"|"logical"|"procedure"|"parameter"|"print"|"println"|"pointer"|"program"|"real"|"recursive"|"return"|"select"|"stop"|"subroutine"|"type" { printTokenAndStore(yytext, "keyword", NULL);}
	/* keywords end */

	/* booleans begin */
"."("TRUE"|"FALSE")"." { printTokenAndStore(yytext, "boolean", NULL);}
	/* booleans end */

	/* integers begin */
{integer} { printTokenAndStore(yytext, "integer", NULL);}
	/* integers end */

	/* real numbers */
{realNumber}E{integer} { printTokenAndStore(yytext, "real number", "with exponent notation");}
((\+|-)?[0-9]*\.[0-9]+) { printTokenAndStore(yytext, "operator", "decimal representation");}
	/* real numbers */

	/* strings begin */
\" { 
		// Start string pattern
		BEGIN(STRING);
		fprintf(stdout, "\033[38;5;85m%s", yytext);
		sprintf(outputBuff, "%s\t<string: \033[38;5;204m", outputBuff); 
	}
<STRING>\" {
		// Met one double-quote implies string ends. Complete the string tag and back to initial state.
		fprintf(stdout, "%s\033[0;0m", yytext);
		sprintf(outputBuff, "%s\033[0;0m > @ line %ld\r\n", outputBuff, lineNo);
		BEGIN(INITIAL);
	}
<STRING>\\\" {
		// Met a slash and a double-quote implies a double-quote in string.
		fprintf(stdout, "%slalal", yytext);
		sprintf(outputBuff, "%s%c", outputBuff, (char)0x22);
	}
<STRING>\"\" {
		// Met two double-quote implies a double-quote in string.
		fprintf(stdout, "%s", yytext);
		sprintf(outputBuff, "%s%c", outputBuff, (char)0x22);
	}
<STRING>[^(\"|\n|(\\\"))]* {
		// Met anything neither double-quote nor line break then it is a part of string. Store it.
		fprintf(stdout, "%s", yytext);
		sprintf(outputBuff, "%s%s", outputBuff, yytext);
	}
<STRING>\n {
		// Met a line break in the string implies it's an un-closed string.
		fprintf(stdout, "\033[0;0m"); 
		sprintf(outputBuff, "%s> \033[38;5;196mun-closed String\033[0;0m @ line %ld\r\n", outputBuff, lineNo);
		newLine();
		BEGIN(INITIAL);
	}
<STRING><<EOF>> {
		// Reach the end-of-file in the string implies it's an un-closed string.
		fprintf(stdout, "\033[0;0m"); 
		sprintf(outputBuff, "%s> \033[38;5;196mun-closed String\033[0;0m @ line %ld\r\n", outputBuff, lineNo);
		BEGIN(INITIAL);
	}
	/* strings end */

	/* comments begin */
^(C|"*")" ".*$ { fprintf(stdout, "\033[38;5;247m%s\033[0;0m", yytext); }
"!".*$ { fprintf(stdout, "\033[38;5;247m%s\033[0;0m", yytext); }
"/*" {
		fprintf(stdout, "\033[38;5;247m%s", yytext);
		BEGIN(COMMENTS);
	}
<COMMENTS>"\n" { newLine(); fprintf(stdout, "\033[38;5;247m");}
<COMMENTS>"*/" {
		fprintf(stdout, "%s\033[0;0m", yytext);
		BEGIN(INITIAL);
	}
<COMMENTS><<EOF>> {
		fprintf(stdout, "\r\n\t%s\033[38;5;196mun-closed Comment\033[0;0m @ line %ld\r\n", outputBuff, lineNo);
		BEGIN(INITIAL); 
	}
	/* comments end */

	/* identifiers begin */
[A-Za-z][0-9A-Za-z]* { 
		if(lookup(yytext) == NULL)
			insert(yytext);
		printTokenAndStore(yytext, "identifier", NULL);
	}
	/* identifiers end */

" "|"\t" { fprintf(stdout, "%s", yytext); }
"\n" { newLine();}
<<EOF>> { fprintf(stdout, "\r\n%s\r\n", outputBuff); return 0;}
%%

int main(int argc, char *argv[]){
	if(argc>1){
		yyin = fopen(argv[1],"r");
		if(yyin != NULL)
			fprintf(stdout, "\033[38;5;46mScanning from file %s\033[0;0m\r\n", argv[1]);
		else
			fprintf(stdout, "\033[38;5;46mScanning from stdin\033[0;0m\r\n");
	}else
		fprintf(stdout, "\033[38;5;46mScanning from stdin\033[0;0m\r\n");
	create();
	outputBuff[0] = '\0';
	newLine();
	yylex();
	dump();
	fprintf(stdout, "\r\n\033[38;5;46mEnd of scanning\033[0;0m\r\n");
	release();
	return 0;
}