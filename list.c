#include "list.h"

struct List *l_new(void) {
    struct List *list = calloc(1, sizeof(struct List));
    if (!list) {
        fprintf(stderr, "Error in calloc of new list!\n");
        return NULL;
    }

    return list;
}

bool l_node_new(struct List *list, struct List_Node **node, const char* data) {
    *node = calloc(1, sizeof(struct List));
    if (!(*node)) {
        fprintf(stderr, "Error in calloc of new list node!\n");
        return true;
    }

    size_t data_length = strlen(data) + 1;

    (*node)->data = (char *)calloc(1, data_length * sizeof(char));
    if (!(*node)->data) {
        fprintf(stderr, "Error in calloc of node data!\n");
        free(*node);
        return true;
    }

    snprintf((*node)->data, data_length, "%s", data);

    list->length++;

    return false;
}

void l_free(struct List **list) {
    while ((*list)->head) {
        l_node_free((*list), (*list)->head);
    }

    free(*list);

    *list = NULL;
}


void l_node_free(struct List *list, struct List_Node *node) {
    if (node) {
        if (node->data) {
            free(node->data);
            node->data = NULL;
        }

        if (node->previous) {
            node->previous->next = node->next;
        } else {
            list->head = node->next;
        }

        if (node->next) {
            node->next->previous = node->previous;
        } else {
            list->tail = node->previous;
        }

        free(node);

        list->length--;
    }
}

bool l_index_node(struct List *list, struct List_Node **node, int index) {
    if (index >= 0) {
        *node = list->head;
        for (int i = 0; i < index; i++) {
            if (!(*node)->next) {
                fprintf(stderr, "Error traversing list to target node!");
                return true;
            }
            *node = (*node)->next;
        }
    } else {
        *node = list->tail;
        for (int i = -1; i > index; i--) {
            if (!(*node)->previous) {
                fprintf(stderr, "Error traversing list to target node!");
                return true;
            }
            *node = (*node)->previous;
        }
    }

    return false;
}

bool l_push(struct List *list, const char* data) {
    struct List_Node *node = NULL;
    if (l_node_new(list, &node, data)) {
        return true;
    }

    if (list->tail) {
        list->tail->next = node;
        node->previous = list->tail;
    } else {
        list->head = node;
    }
    list->tail = node;

    return false;
}

char* l_pop(struct List *list) {
    if (!list->tail) {
        fprintf(stderr, "Error list is empty, nothing to return!\n");
        return NULL;
    }

    char *data = list->tail->data;
    list->tail->data = NULL;

    l_node_free(list, list->tail);

    return data;
}

bool l_shift(struct List *list, const char* data) {
    struct List_Node *node = NULL;
    if (l_node_new(list, &node, data)) {
        return true;
    }

    if (list->head) {
        list->head->previous = node;
        node->next = list->head;
    } else {
        list->tail = node;
    }
    list->head = node;

    return false;
}

char* l_unshift(struct List *list) {
    if (!list->head) {
        fprintf(stderr, "Error list is empty, nothing to return!\n");
        return NULL;
    }
    
    char *data = list->head->data;
    list->head->data = NULL;

    l_node_free(list, list->head);

    return data;
}

bool l_insert(struct List *list, const char* data, int index) {
    if (index != 0) {
        if (index >= list->length || index < -list->length) {
            fprintf(stderr, "Error %d is not a valid index!\n", index);
            return true;
        }
    }

   struct List_Node *node = NULL;
    if (l_index_node(list, &node, index)) {
        return true;
    }
 
    struct List_Node *new_node = NULL;
    if (l_node_new(list, &new_node, data)) {
        return true;
    }

    if (node) {
        new_node->next = node;
        new_node->previous = node->previous;
        node->previous = new_node;
        if (new_node->previous) {
            new_node->previous->next = new_node;
        }
    }

    if (!list->head || !new_node->previous) {
        list->head = new_node;
    }

    if (!list->tail || !new_node->next) {
        list->tail = new_node;
    }
    
    return false;
}

char* l_extract(struct List *list, int index) {
    if (index >= list->length || index < -list->length) {
        fprintf(stderr, "Error %d is not a valid index!\n", index);
        return NULL;
    }

   struct List_Node *node = NULL;

    if (l_index_node(list, &node, index)) {
        return NULL;
    }

    char* data = NULL;

    if (node) {
        data = node->data;

        node->data = NULL;

        l_node_free(list, node);
    }

    return data;
}

char* l_get(struct List *list, int index) {
    if (index >= list->length || index < -list->length) {
        fprintf(stderr, "Error %d is not a valid index!\n", index);
        return NULL;
    }

   struct List_Node *node = NULL;

    if (l_index_node(list, &node, index)) {
        return NULL;
    }

    if (!node) {
        return NULL;
    }
    
    size_t data_length = strlen(node->data) + 1;

    char *data = (char *)calloc(1, data_length * sizeof(char));
    if (!data) {
        fprintf(stderr, "Error in calloc of return data!\n");
        return NULL;
    }

    snprintf(data, data_length, "%s", node->data);

    return data;
}


bool l_remove(struct List *list, int index) {
    if (index >= list->length || index < -list->length) {
        fprintf(stderr, "Error %d is not a valid index!\n", index);
        return true;
    }

   struct List_Node *node = NULL;

    if (l_index_node(list, &node, index)) {
        return true;
    }

    if (!node) {
        return true;
    }

    l_node_free(list, node);

    return false;
}

void l_print(struct List *list) {
    if (!list) {
        printf("%p\n", list);
        return;
    }

    struct List_Node *node = list->head;

    while (node) {
        printf("%s\n", node->data);
        node = node->next;
    }
}
