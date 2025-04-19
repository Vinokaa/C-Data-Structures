#include <stdio.h>
#include <stdlib.h>
#include "LinkedList/LinkedList.h"

int main(){
    LinkedList* list = LinkedListConstructor();
    LinkedList* list2 = LinkedListConstructor();
    char* list_print;

    list2->insertInt(list2, 47, -1);
    list2->insertDouble(list2, 23.26, -1);

    list_print = list->toString(list);
    printf("%s\n", list_print);
    free(list_print);

    list->insertInt(list, 7, -1);
    list_print = list->toString(list);
    printf("%s\n", list_print);
    free(list_print);

    list->insertDouble(list, 3.14159, -1);
    list_print = list->toString(list);
    printf("%s\n", list_print);
    free(list_print);

    list->insertChar(list, 'V', -1);
    list_print = list->toString(list);
    printf("%s\n", list_print);
    free(list_print);

    list->insertString(list, "Neoni", -1);
    list_print = list->toString(list);
    printf("%s\n", list_print);
    free(list_print);

    list->insertList(list, list2, -1);
    list_print = list->toString(list);
    printf("%s\n\n", list_print);
    free(list_print);

    int* retrievedInt = list->get(list, 0);
    printf("retrieved: %d\n", *retrievedInt);

    list_print = list->toString(list);
    printf("%s\n\n", list_print);
    free(list_print);

    double* removedDouble = list->remove(list, 1);
    printf("removed: %.5f\n", *removedDouble);
    free(removedDouble);

    list_print = list->toString(list);
    printf("%s\n\n", list_print);
    free(list_print);

    LinkedList* removedList = list->remove(list, -1);
    list_print = removedList->toString(removedList);
    printf("removed: %s\n", list_print);
    free(list_print);

    list_print = list->toString(list);
    printf("%s\n\n", list_print);
    free(list_print);

    list->clear(list);

    list_print = list->toString(list);
    printf("%s\n", list_print);
    free(list_print);

    return 0;
}