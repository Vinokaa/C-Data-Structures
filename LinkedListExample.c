#include <stdio.h>
#include "LinkedList/LinkedList.h"

int main(){
    LinkedList list = LinkedListConstructor();
    LinkedList list2 = LinkedListConstructor();

    list2.insertInt(&list2, 47, -1);
    list2.insertDouble(&list2, 23.26, -1);

    printf("%s\n", list.toString(&list));

    list.insertInt(&list, 7, -1);
    printf("%s\n", list.toString(&list));

    list.insertDouble(&list, 3.14159, -1);
    printf("%s\n", list.toString(&list));

    list.insertChar(&list, 'V', -1);
    printf("%s\n", list.toString(&list));

    list.insertString(&list, "Neoni", -1);
    printf("%s\n", list.toString(&list));

    list.insertList(&list, &list2, -1);
    printf("%s\n\n", list.toString(&list));

    int* retrievedInt = list.get(&list, 0);
    printf("retrieved: %d\n", *retrievedInt);

    printf("%s\n\n", list.toString(&list));

    double* removedDouble = list.remove(&list, 1);
    printf("removed: %.5f\n", *removedDouble);

    printf("%s\n\n", list.toString(&list));

    LinkedList* removedList = list.remove(&list, -1);
    printf("removed: %s\n", removedList->toString(removedList));

    printf("%s\n", list.toString(&list));

    list.clear(&list);

    return 0;
}