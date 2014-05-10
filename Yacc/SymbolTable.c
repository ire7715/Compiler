#include <stdio.h>
#include <stdlib.h>
#include "SymbolTable.h"

void printElement(element e){	// Simply prints an element.
	fprintf(stdout, "%s\r\n", e.variable);
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

element *lookup(symbolTable *st, char *s){	// Look up a specific variable name.
	unsigned int h = hash(s);
	bucket *cur = st->table[h].link;	// Hash to the corresponded slot, and then traverse the chain to find the correct string.
	while(cur != NULL){
		if(strcmp(cur->inner.variable, s) == 0)
			return &(cur->inner);
		cur = cur->link;
	}
	return &(cur->inner);
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
	newB->link = st->table[h].link;
	st->table[h].link = newB;
	return &(newB->inner);
}

symbolTable *dump(symbolTable *st){	// Visit all slots and traverse all buckets in the chain, and print all data contained.
	fprintf(stdout, "\033[38;5;45m*** Symbol table ***\033[0;0m\r\n");	// \033 is for the console color. For more information please refer to https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
	dump_real(st, 1);
	fprintf(stdout, "\033[38;5;45m*** End symbol table ***\033[0;0m\r\n");
	return st;
}

void dump_real(symbolTable *st, int depth){	// Visit all slots and traverse all buckets in the chain, and print all data contained.
	int i;//fprintf(stdout, "%d\r\n", depth);
	char padding[256];
	bucket *cur;
	for(i = 0; i<depth; i++)
		padding[i] = '\t';
	padding[i] = '\0';
	for(i = 0; i< TABLE_SIZE ; i++){
		cur = st->table[i].link;
		while(cur != NULL){
			if(cur->inner.subRegion != NULL)
				dump_real(st, depth+1);
			else{
				fprintf(stdout, "%s", padding);
				printElement(cur->inner);
			}
			cur = cur->link;
		}
	}
}

symbolTable *release(symbolTable *st){	// This function is for releasing memories of symbol table.
	int i;
	symbolTable *parent = st->parent;
	bucket *cur, *temp;
	for(i = 0; i < TABLE_SIZE; i++){	// Traverse all buckets and release them.
		cur = st->table[i].link;
		while(cur != NULL){
			temp = cur;
			cur = cur->link;
			if(temp->inner.subRegion != NULL)
				release(temp->inner.subRegion);
			free(temp);
		}
	}
	free(st);
	return parent;
}