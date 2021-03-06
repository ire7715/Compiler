#include <stdio.h>
#include <stdlib.h>
#include "SymbolTable.h"

#define EMPTY_T	0
#define INT_T		1
#define REAL_T		2
#define STR_T		3
#define BOOL_T		4

#define isNum(s)	(s.type == INT_T || s.type == REAL_T)
#define typeString(s)	(s == BOOL_T)?("boolean"):(			\
							(s == INT_T)?("int"):(			\
								(s == REAL_T)?("real"):(		\
									(s == STR_T)?("java.lang.String"):(	\
									"void")									\
								)										\
							)											\
						)

void printElement(element e){	// Simply prints an element.
	nodeP cur;
	int first;
	fprintf(stdout, "%s ::", e.variable);
	switch(e.type){		// Prints the type of this variable or procedure.
	case 0:
			break;
	case 1:
			fprintf(stdout, " integer");
			break;
	case 2:
			fprintf(stdout, " real");
			break;
	case 3:
			fprintf(stdout, " string");
			break;
	case 4:
			fprintf(stdout, " boolean");
			break;
	default:
			fprintf(stdout, " illegal identifier");
			break;
	}
	if(e.subRegion != NULL){	// subRegion is not NULL means this is a procedure.
		if(e.type >=1 && e.type <= 4)		// Have a return type.
			fprintf(stdout, " function");
		else								// Doesn't have a return type
			fprintf(stdout, " procedure");
		cur = e.typeList;
		if(cur != NULL){			// This block prints each parameter's name and type.
			fprintf(stdout, "( ");
			first = 1;
			while(cur != NULL /*&& cur - e.typeList < 0xFFFF*/){
				if(first)
					first = 0;
				else
					fprintf(stdout, ", ");
				fprintf(stdout, "%s %s", typeString(cur->ep->type), cur->ep->variable);
				cur = cur->next;
			}
			fprintf(stdout, " )");
		}
	}else{
		fprintf(stdout, " @ %d, const(%s), subRegion(%s)", e.location, (e.isConst)?("ture"):("false"), (e.subRegion == NULL)?("NULL"):("not NULL"));
	}
	fprintf(stdout, "\n\r");
}

symbolTable *create(symbolTable *parent){	// Initialize a symbol table and return the pointer of that symbol table.
	symbolTable *st;
	st = (symbolTable *)malloc(sizeof(symbolTable));
	st->parent = parent;
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

int isInGlobal(symbolTable *global, element e){
	return (lookupLocally(global, e.variable) == NULL)?(0):(1);
}

int isArgument(element scope, element *examin){
	nodeP cur = scope.typeList;
	while(cur != NULL){
		if(strcmp(cur->ep->variable, examin->variable) == 0)
			return 1;
		cur = cur->next;
	}
	return 0;
}

element *lookupLocally(symbolTable *st, char *s){
	unsigned int h = hash(s);
	bucket *cur = st->table[h].link;	// Hash to the corresponded slot, and then traverse the chain to find the correct string.
	element *temp;
	while(cur != NULL){
		if(strcmp(cur->inner.variable, s) == 0)
			return &(cur->inner);
		cur = cur->link;
	}	// If the while loop ends, this identifier doesn't exist in this scope.
	return NULL;
}

element *lookup(symbolTable *st, char *s){	// Look up a specific variable name.
	unsigned int h = hash(s);
	bucket *cur = st->table[h].link;	// Hash to the corresponded slot, and then traverse the chain to find the correct string.
	element *temp;
	while(cur != NULL){
		if(strcmp(cur->inner.variable, s) == 0)
			return &(cur->inner);
		cur = cur->link;
	}	// If the while loop ends, this identifier doesn't exist in this scope.
	if(st->parent == NULL)
		return NULL;			// Can't find such a identifier.
	else
		return lookup(st->parent, s);	// Return the identifier in the parent scope.
}

element *insert(symbolTable *st, char *s){	// Insert a variable name into symbol table.
	/** 
	 *	Create a new bucket to contain this string.
	 *	Compute the hash value, and insert the new bucket onto the chain.
	 *	Return the pointer of the element which containing the variable name.
	**/
	unsigned int h = hash(s);
	bucket *newB = (bucket *)malloc(sizeof(bucket));
	sprintf(newB->inner.variable, "%s", s);
	newB->inner.subRegion = NULL;
	newB->inner.typeList = NULL;
	newB->link = st->table[h].link;
	st->table[h].link = newB;
	return &(newB->inner);
}

bucket *insertBucket(symbolTable *st, bucket *buck){
	unsigned int h = hash(buck->inner.variable);
	buck->link = st->table[h].link;
	st->table[h].link = buck;
	return buck;
}

bucket *deleteBucket(symbolTable *st, element e){
	unsigned int h = hash(e.variable);
	bucket *cur = st->table[h].link, *prev = &(st->table[h]);
	element *temp;
	while(cur != NULL){
		if(strcmp(cur->inner.variable, e.variable) == 0){
			prev->link = cur->link;
			cur->link = NULL;
			return cur;
		}
		prev = cur;
		cur = cur->link;
	}
}

symbolTable *dump(symbolTable *st){	// Visit all slots and traverse all buckets in the chain, and print all data contained.
	fprintf(stdout, "\033[38;5;45m*** Symbol table ***\033[0;0m\r\n");	// \033 is for the console color. For more information please refer to https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
	dump_real(st, 0);
	fprintf(stdout, "\033[38;5;45m*** End symbol table ***\033[0;0m\r\n");
	return st;
}

void dump_real(symbolTable *st, int depth){	// Visit all slots and traverse all buckets in the chain, and print all data contained.
	int i;
	char padding[256];
	bucket *cur;
	
	for(i = 0; i<depth; i++)
		padding[i] = '\t';
	padding[i] = '\0';
	
	for(i = 0; i< TABLE_SIZE ; i++){
		cur = st->table[i].link;
		while(cur != NULL){
			fprintf(stdout, "%s", padding, i);
			printElement(cur->inner);
			if(cur->inner.subRegion != NULL)
				dump_real(cur->inner.subRegion, depth+1);
			cur = cur->link;
		}
	}
}

symbolTable *release(symbolTable *st){	// This function is for releasing memories of symbol table.
	int i;
	symbolTable *parent = st->parent;
	bucket *cur, *temp;
	node *curN, *prevN;
	for(i = 0; i < TABLE_SIZE; i++){	// Traverse all buckets and release them.
		cur = st->table[i].link;
		while(cur != NULL){
			temp = cur;
			cur = cur->link;
			if(temp->inner.subRegion != NULL){
				release(temp->inner.subRegion);
				curN = temp->inner.typeList;
				while(curN != NULL){
					prevN = curN;
					curN = curN->next;
					free(prevN);
				}
			}
			free(temp);
		}
	}
	free(st);
	return parent;
}