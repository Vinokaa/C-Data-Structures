#include <stdio.h>
#include <stdlib.h>
#include "LinkedList/LinkedList.h"

int main(){
    LinkedList* list = LinkedListConstructor();

    char* list_print = list->toString(list);
    printf("%s\n", list_print);
    free(list_print);

    return 0;
}