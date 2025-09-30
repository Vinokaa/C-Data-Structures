#include <stdlib.h>
#include <stdio.h>
#include "ArrayList.h"

void insertInt(ArrayList* list, int n){
    printf("%d\n", n);
};

void insertFloat(ArrayList* list, double d){

};

int main(){
    ArrayList* list = malloc(sizeof(ArrayList));

    list->insert = &insertInt;

    list->insert(list, 1);

    return 0;
}