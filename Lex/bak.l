%{

#include <stdio.h>
#include <stdlib.h>

#define ID_LEN 128
#define TABLE_SIZE 227 
#define OUT_SIZE 256

long int lineNo = 1;
char outputBuf[OUT_SIZE];
symbolTable *st;

typedef struct _ELEMENT{
	char variable[ID_LEN];
} element;

typedef struct _BUCKET *bucketP;
typedef struct _BUCKET{
	element inner;
	bucketP link;
} bucket;

typedef struct _SYMBOLTABLE{
	bucket table[TABLE_SIZE];
} symbolTable;

void printElement(element e){
	fprintf(stdout, "%s\r\n", e.variable);
}

symbolTable *create(){
	st = (symbolTable *)malloc(sizeof(symbolTable));
	int i;
	for(i = 0; i < TABLE_SIZE ; i++){
		st->table[i].link = NULL;
	}
	return st;
}

unsigned int hash(char *s){
	unsigned int hash = 0, i;
	for(i = 0; i < strlen(s) ; i++){
		hash += *(s+i);
		hash += (hash << 5);
		hash ^= (hash >> 3);
	}
	hash += (hash << 2);
    hash ^= (hash >> 6);
	hash += (hash << 8);
	return hash % TABLE_SIZE;
}

element *lookup(char *s){
	unsigned int h = hash(s);
	bucket *cur = st->table[h].link;
	while(cur != NULL){
		if(strcmp(cur->inner.variable, s) == 0)
			return &(cur->inner);
		cur = cur->link;
	}
	return &(cur->inner);
}

element *insert(char *s){
	unsigned int h = hash(s);
	bucket *newB = (bucket *)malloc(sizeof(bucket));
	sprintf(newB->inner.variable, "%s", s);
	newB->link = st->table[h].link;
	st->table[h].link = newB;
	return &(newB->inner);
}

symbolTable *dump(){
	int i;
	bucket *cur;
	fprintf(stdout, "Symbol table:\r\n");
	for(i = 0; i< TABLE_SIZE ; i++){
		cur = st->table[i].link;
		while(cur != NULL){
			printElement(cur->inner);
			cur = cur->link;
		}
	}
	return st;
}

void release(){
	int i;
	bucket *cur, *temp;
	for(i = 0; i < TABLE_SIZE; i++){
		cur = st->table[i].link;
		while(cur != NULL){
			temp = cur;
			cur = cur->link;
			free(temp);
		}
	}
	free(st);
}

%}

realNumber (\+|-)?[0-9]+(\.[0-9]+)?
integer (\+|-)?[0-9]+

%x COMMENTS
%x STRING

%%

	/* delimiter begin */ 
"," { fprintf(stdout, "%s", yytext); sprintf(outputBuf, "%s<delimiter: %s (comma)> @ line %ld\r\n", %s, yytext, lineNo);} }
	/* "," { fprintf(stdout, "<delimiter: %s (comma)> @ line %ld\r\n", yytext, lineNo);} */
":"":"? { fprintf(stdout, "<delimiter: %s (colon)> @ line %ld\r\n", yytext, lineNo);}
";" { fprintf(stdout, "<delimiter: %s (semicolon)> @ line %ld\r\n", yytext, lineNo);}
"(" { fprintf(stdout, "<delimiter: %s (left parentheses)> @ line %ld\r\n", yytext, lineNo);}
")" { fprintf(stdout, "<delimiter: %s (right parentheses)> @ line %ld\r\n", yytext, lineNo);}
"[" { fprintf(stdout, "<delimiter: %s (left square bracket)> @ line %ld\r\n", yytext, lineNo);}
"]" { fprintf(stdout, "<delimiter: %s (right sqare bracket)> @ line %ld\r\n", yytext, lineNo);}
"{" { fprintf(stdout, "<delimiter: %s (left bracket)> @ line %ld\r\n", yytext, lineNo);}
"}" { fprintf(stdout, "<delimiter: %s (right bracket)> @ line %ld\r\n", yytext, lineNo);}
"%" { fprintf(stdout, "<delimiter: %s (component reference)> @ line %ld\r\n", yytext, lineNo);}
	/* delemiter end */

	/* operators begin */
"+"|"-"|"*"|"/" { fprintf(stdout, "operator: %s (arithmetic) @ line %ld\r\n", yytext, lineNo);}
"**" { fprintf(stdout, "<operator: %s (expenetiation)> @ line %ld\r\n", yytext, lineNo);}
"//" { fprintf(stdout, "<operator: %s (concatetation)> @ line %ld\r\n", yytext, lineNo);}
(("<"|">")"="?)|(("/"|"=")"=") { fprintf(stdout, "<operator: %s (relational)> @ line %ld\r\n", yytext, lineNo);}
((".L"|".G")("T."|"E."))|(".EQ."|".NE.") { fprintf(stdout, "<operator: %s (relational)> @ line %ld\r\n", yytext, lineNo);}
"."("AND"|"OR"|"NOT"|"EQV"|"NEQV")"." { fprintf(stdout, "<logical: %s (relational)> @ line %ld\r\n", yytext, lineNo);}
"=" { fprintf(stdout, "<operator: %s (assignment)> @ line %ld\r\n", yytext, lineNo);}
"=>" { fprintf(stdout, "<operator: %s (pointer assignment)> @ line %ld\r\n", yytext, lineNo);}
	/* operators end */

	/* keywords begin */
"call"|"case"|"character"|"close"|"continue"|"cycle"|"data"|"dimension"|"do"|"else"|"end"|"exit"|"function"|"goto"|"if"|"integer"|"logical"|"procedure"|"parameter"|"print"|"println"|"pointer"|"program"|"real"|"recursive"|"return"|"select"|"stop"|"subroutine"|"type" {fprintf(stdout, "<keyword: %s> @ line %ld\r\n", yytext, lineNo);}
	/* keywords end */

	/* booleans begin */
"."("TRUE"|"FALSE")"." { fprintf(stdout, "<boolean: %s> @ line %ld\r\n", yytext, lineNo);}
	/* booleans end */

	/* integers begin */
{integer} { fprintf(stdout, "<integer: %s> @ line %ld\r\n", yytext, lineNo);}
	/* integers end */

	/* real numbers */
{realNumber}E{integer} { fprintf(stdout, "<real number: %s (with exponent notation)> @ line %ld\r\n", yytext, lineNo);}
((\+|-)?[0-9]*\.[0-9]+) { fprintf(stdout, "<real number: %s (decimal representation)> @ line %ld\r\n", yytext, lineNo);}
	/* real numbers */

	/* strings begin */
\" { BEGIN(STRING); fprintf(stdout, "<string: "); }
<STRING>\" { fprintf(stdout, " > @ line %ld\r\n", lineNo); BEGIN(INITIAL); };
<STRING>\"\" { fprintf(stdout, "%c", (char)0x22);}
<STRING>[^(\"|\n)]* { fprintf(stdout, "%s", yytext); }
<STRING>\n { fprintf(stdout, "> \033[38;5;196mun-closed String\033[0;0m @ line %ld\r\n", lineNo); BEGIN(INITIAL); lineNo++; }
	/* strings end */

	/* comments begin */
^(C|"*").*$ { fprintf(stdout, "<comment: %s> @ line %ld\r\n", yytext, lineNo);}
"!".*$ { fprintf(stdout, "<comment: %s> @ line %ld\r\n", yytext, lineNo);}
"/*" { BEGIN(COMMENTS); fprintf(stdout, "multi-line comment:\r\n%s", yytext);}
<COMMENTS>"\n" { lineNo++; fprintf(stdout, "%s", yytext);}
<COMMENTS>"*/" { fprintf(stdout, "%s @ line %ld\r\n", yytext, lineNo); BEGIN(INITIAL);}
<COMMENTS><<EOF>> { fprintf(stdout, "> \033[38;5;196mun-closed Comment\033[0;0m @ line %ld\r\n", lineNo); BEGIN(INITIAL); }
	/* comments end */

	/* identifiers begin */
[A-Z][0-9A-Z]* { 
		if(lookup(yytext) == NULL)
			insert(yytext);
		fprintf(stdout, "<identifier: %s> @ line %ld\r\n", yytext, lineNo);
	}
	/* identifiers end */

(" "|"\t")* { fprintf(stdout, "%s", yytext); }
"\n" { fprintf(stdout, "%ld: %s", lineNo, outputBuff); lineNo++;}
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
	//char lineBuff[100]={'1', '2', '\0'}; fgets(lineBuff, 100, yyin); fprintf(stdout, "%ld: %s\r\n", lineNo, lineBuff);
	yylex();
	dump();
	fprintf(stdout, "\033[38;5;46mEnd of scanning\033[0;0m\r\n");
	release();
	return 0;
}