#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#define ID_LEN 128
#define TABLE_SIZE 227	// Just a prime number

typedef struct _SYMBOLTABLE *symbolTableP;

typedef struct _ELEMENT *elementP;
typedef struct _NODE *nodeP;
typedef struct _NODE{
	elementP ep;
	nodeP next;
} node;
typedef struct _ELEMENT{
	char variable[ID_LEN];
	int type;
	symbolTableP subRegion;
	nodeP typeList;
	// typeList stores the pointers point to those arguments of this procedure, NULL for no any arguments.
} element;	// A smallest unit in hash table, presents an element.

typedef struct _BUCKET *bucketP;
typedef struct _BUCKET{
	element inner;
	bucketP link;
} bucket;	// A bucket is used for containing an element, providing linked list functionality as wall as.
typedef struct _SYMBOLTABLE{
	bucket table[TABLE_SIZE];
	symbolTableP parent;
} symbolTable;	// A simple symbol table implemented by chaining hash table.

extern symbolTable *global, *current;

void printElement(element);

symbolTable *create(symbolTable *);

unsigned int hash(char *);

element *lookup(symbolTable *, char *);

element *insert(symbolTable *, char *);

bucket *insertBucket(symbolTable *, bucket *);

bucket *deleteBucket(symbolTable *, element);

symbolTable *dump(symbolTable *);

void dump_real(symbolTable *, int);

symbolTable *release(symbolTable *);

#endif