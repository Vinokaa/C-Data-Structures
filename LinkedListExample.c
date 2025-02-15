#include <stdio.h>
#include "LinkedList/LinkedList.h"

int main(){
    LinkedList* list = LinkedListConstructor();

    printf("%s\n", listToString(list));

    listInsertInt(list, 7, -1);
    printf("%s\n", listToString(list));

    listInsertDouble(list, 3.14159, -1);
    printf("%s\n", listToString(list));

    listInsertChar(list, 'V', -1);
    printf("%s\n", listToString(list));

    listInsertString(list, "Neoni", -1);
    printf("%s\n", listToString(list));

    listInsertStruct(list, LinkedListConstructor(), -1);
    printf("%s\n", listToString(list));

    listClear(list);

    return 0;
}