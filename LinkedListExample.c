#include <stdio.h>
#include "LinkedList/LinkedList.h"

int main(){
    LinkedList* teste = LinkedListConstructor();
    LinkedList* teste2 = LinkedListConstructor();

    listInsertInt(teste2, 1, -1);

    listInsertInt(teste, 7, -1);
    listInsertDouble(teste, 3.14159, -1);
    listInsertChar(teste, 'V', -1);
    listInsertString(teste, "Vina", -1);
    listInsertStruct(teste, teste2, -1);

    listInsertInt(teste2, 2, -1);

    printf("%s\n", listToString(teste));

    int* removedInt = listRemove(teste, 0);
    printf("removed: %d\n\n", *removedInt);

    printf("%s\n", listToString(teste));

    void* removedStruct = listRemove(teste, -1);
    printf("removed: %s\n\n", listToString(removedStruct));

    printf("%s\n", listToString(teste));

    listClear(teste);
    listClear(teste2);

    return 0;
}