#include "main.h"
#include "list.h"

int main() {

    struct List *list = l_new();
    if (!list) {
        return true;
    }

    l_push(list, "six");
    l_push(list, "seven");
    l_push(list, "eight");

    printf("\n");
    l_print(list);

    l_shift(list, "two");
    l_shift(list, "one");
    l_shift(list, "zero");

    printf("\n");
    l_print(list);

    l_insert(list, "five", 3);
    l_insert(list, "four", 3);
    l_insert(list, "three", 3);

    printf("\n");
    l_print(list);

    printf("\n");
    char* pop1 = l_pop(list);
    printf("pop %s\n", pop1);
    free(pop1);

    printf("\n");
    char* unshift1 = l_unshift(list);
    printf("unshift %s\n", unshift1);
    free(unshift1);

    printf("\n");
    char* extract1 = l_extract(list, 1);
    printf("extract %s\n", extract1);
    free(extract1);


    printf("\n");
    l_print(list);

    l_free(&list);

    printf("\n");
    l_print(list);

    return false;
}
