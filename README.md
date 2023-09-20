# A simple Link List Demo
This is a double link list of strings.
## Link List fuctions
Instance new list on the heap.

    struct List *list = l_new();

Push item to end of list, Shift item to beginding of list. Insert item to index of list. All return a bool error.

    l_push(list, "push to tail");
    l_shift(list, "shift to head");
    l_insert(list, "insert to index 1" 1);

Pop, remove and return item from tail. Unshift, remove and return item from head. Extract, remove and return item from index. All return NULL if error.

    char *pop1 = l_pop(list);
    char *unshift1 = l_unshift(list);
    char *extract1 = l_extract(list, 0);

Get returns item at index. Remove, removes item at index. Errors are NULL and Bool respectively.

    char *get1 = l_get(list, 0);
    l_remove(list, 0);

Print, prints the entire list. Free, frees the entire list. both return void. Free takes a reference to the list and nulls the pointer too.

    l_print(list);
    l_free(&list);

## Note heap memory
This is all on the heap. All functions internally handle and take care of freeing there own memory. To free the list l_free will free all memory given to the list and it will also null the list pointer. However any string that is returned from the list from, l_pop, l_unshift, l_extract and l_get are all heap strings no longer in the list. You will need to capture them and free them yourself.
