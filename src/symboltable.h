#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "ast.h"
#include "types.h"


// TODO: maybe different kind for function parameters

typedef enum {
    SYMBOL_NONE,

    SYMBOL_VARIABLE,
    /*SYMBOL_STATIC_VARIABLE,*/
    SYMBOL_PROCEDURE,
} SymbolKind;

typedef struct {
    SymbolKind kind;
    Type type;

    /* symbol-specific fields */
    const char *label; // used for procedured and static variables
    size_t stack_addr; // used for variables
} Symbol;

typedef struct HashtableEntry {
    const char *key;
    struct HashtableEntry *next;
    Symbol value;
} HashtableEntry;

typedef struct Hashtable {
    size_t size;
    HashtableEntry **buckets;
    struct Hashtable *parent;
} Hashtable;

void hashtable_init(Hashtable *ht, size_t size);
void hashtable_destroy(Hashtable *ht);
/* returns -1 if key already exists, else 0 */
int  hashtable_insert(Hashtable *ht, const char *key, Symbol value);
/* does a lookup in the current hashtable */
/* returns NULL if the key does not exist */
Symbol *hashtable_get(const Hashtable *ht, const char *key);
void hashtable_print(const Hashtable *ht);



typedef struct {
    size_t size, capacity;
    Hashtable *items;
} Symboltable;

void symboltable_init(Symboltable *s, size_t capacity, size_t table_size);
void symboltable_destroy(Symboltable *s);
void symboltable_append(Symboltable *s, Hashtable *parent);
Hashtable *symboltable_get_last(const Symboltable *s);
/* does a lookup in the current and parent hashtables */
Symbol *symboltable_lookup(const Hashtable *ht, const char *key);
/* addresses are filled in at code generation */
Symboltable symboltable_construct(AstNode *root, size_t table_size);
void symboltable_print(const Symboltable *st);




#endif // _SYMBOLTABLE_H
