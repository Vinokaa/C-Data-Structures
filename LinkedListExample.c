#include <stdio.h>
#include "LinkedList/LinkedList.h"

int main(){
    LinkedList list1 = LinkedListConstructor();
    LinkedList list2 = LinkedListConstructor();

    list1.insertInt(&list1, 7, -1);
    list1.insertDouble(&list1, 3.14159, -1);
    list1.insertChar(&list1, 'V', -1);
    list1.insertString(&list1, "Neoni", -1);
    list1.insertStruct(&list1, &list2, -1);

    printf("%s\n", list1.toString(&list1));

    list1.clear(&list1);

    printf("%s\n", list1.toString(&list1));

    return 0;
}