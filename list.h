#ifndef LIST_H
#define LIST_H

#include "main.h"

struct List_Node {
    struct List_Node *next;
    struct List_Node *previous;
    char *data;
};

struct List {
    struct List_Node *head;
    struct List_Node *tail;
    int length;
};

struct List *l_new(void);
bool l_node_new(struct List *l, struct List_Node **node, const char* data);
void l_free(struct List **list);
void l_node_free(struct List *l, struct List_Node *n);
bool l_index_node(struct List *l, struct List_Node **node, int index);
bool l_push(struct List *l, const char* data);
char* l_pop(struct List *l);
bool l_shift(struct List *l, const char* data);
char* l_unshift(struct List *l);
bool l_insert(struct List *list, const char* data, int index);
char* l_extract(struct List *list, int index); 
char* l_get(struct List *l, int index);
bool l_remove(struct List *l, int index);
void l_print(struct List *l);

#endif
