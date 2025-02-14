#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short double_precision = 2;

typedef struct Node Node;
typedef struct LinkedList LinkedList;
typedef struct String String;

typedef enum{
    TYPE_UNDEFINED,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_STRUCT
}type_t;

struct Node{
    type_t type;
    void* val;
    Node* next;
};

struct LinkedList{
    int size;
    Node* head;
};

///////////////////////////////////////////////////////////////////////////////////////////////
//                                  Complementary Functions                                  //
///////////////////////////////////////////////////////////////////////////////////////////////

LinkedList* LinkedListConstructor();

void listInsertChar(LinkedList* list, char c, int index);

void* removeLastFromList(LinkedList* list);

void clearNode(Node* node){
    if(node->val != NULL){
        free(node->val);
    }

    free(node);
}

void clearListRecursive(Node* node){
    if(node != NULL){
        clearListRecursive(node->next);
        clearNode(node);
    }
}

void clearList(LinkedList* list){
    clearListRecursive(list->head);
}

Node* getNodeFromList(LinkedList* list, int index){
    if(index > list->size-1 || index < 0){
        puts("List index out of range");
        return NULL;
    }

    Node* tmp = list->head;

    for(int i = 0; i < index; i++){
        tmp = tmp->next;
    }

    return tmp;
}

void numToCharList(LinkedList* dest, double d, type_t type){
    if(type == TYPE_INT || type == TYPE_FLOAT){
        LinkedList* list = LinkedListConstructor();
        int n;

        if(type == TYPE_FLOAT){
            for(int i = 0; i < double_precision; i++){
                d *= 10;
            }

            n = (int) d;

            for(int i = 0; i < double_precision; i++){
                listInsertChar(list, n % 10 + 48, -1);
                n = (int) (n / 10);
            }

            listInsertChar(list, '.', -1);
        }else{
            n = (int) d;
        }

        while(n > 0){
            listInsertChar(list, n % 10 + 48, -1);
            n = (int) (n / 10);
        }

        while(list->size > 0){
            char c = *(char*) removeLastFromList(list);
            listInsertChar(dest, c, -1);
        }

        clearList(list);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
//                                       Main Functions                                      //
///////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////    Constructors    /////////////////////////////////////

LinkedList* LinkedListConstructor(){
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->type = TYPE_UNDEFINED;
    tmp->val = NULL;
    tmp->next = NULL;

    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    list->size = 0;
    list->head = tmp;

    return list;
}

/////////////////////////////////    List Insert Functions    /////////////////////////////////

Node* listInsertFirst(LinkedList* list){
    Node* head = list->head;
    Node* new;

    if(head->type == TYPE_UNDEFINED){
        new = head;
    }else{
        new = (Node*) malloc(sizeof(Node));

        new->next = head;
        list->head = new;
    }

    return new;
}

Node* listInsertLast(LinkedList* list){
    Node* head = list->head;
    Node* new;

    if(head->type == TYPE_UNDEFINED){
        new = head;
    }else{
        new = (Node*) malloc(sizeof(Node));

        new->next = NULL;

        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    return new;
}

Node* listInsert(LinkedList* list, int index){
    if(index >= list->size || index < -1){
        puts("List insertion index out of range");
        return NULL;
    }

    Node* new;

    if(index == 0){
        new = listInsertFirst(list);
    }else if(index == -1){
        new = listInsertLast(list);
    }else{
        Node* head = list->head;
        new = (Node*) malloc(sizeof(Node));

        Node* tmp = head;
        for(int i = 0; i < index; i++){
            tmp = tmp->next;
        }

        new->next = tmp->next;
        tmp->next = new;
    }

    list->size += 1;
    return new;
}

void listInsertInt(LinkedList* list, int n, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_INT;
    new->val = malloc(sizeof(int));
    memcpy(new->val, &n, sizeof(int));
}

void listInsertDouble(LinkedList* list, double d, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_FLOAT;
    new->val = malloc(sizeof(double));
    memcpy(new->val, &d, sizeof(double));
}

void listInsertChar(LinkedList* list, char c, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_CHAR;
    new->val = malloc(sizeof(char));
    memcpy(new->val, &c, sizeof(char));
}

void listInsertString(LinkedList* list, char* s, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_STRING;
    new->val = malloc(sizeof(s));
    memcpy(new->val, s, sizeof(s));
}

void listInsertStruct(LinkedList* list, void* s, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_STRUCT;
    new->val = malloc(sizeof(s));
    memcpy(new->val, s, sizeof(s));
}

/////////////////////////////////    List Remove Functions    /////////////////////////////////

void* removeFirstFromList(LinkedList* list){
    if(list->size < 1){
        puts("List is empty");
        return NULL;
    }else{
        Node* removedNode = list->head;
        void* removedValue = malloc(sizeof(removedNode->val));
        memcpy(removedValue, removedNode->val, sizeof(removedNode->val));

        if(list->size == 1){
            removedNode->type = TYPE_UNDEFINED;
            free(removedNode->val);
            removedNode->val = NULL;
        }else{
            list->head = list->head->next;
        
            clearNode(removedNode);
        }

        list->size--;
        return removedValue;
    }
}

void* removeLastFromList(LinkedList* list){
    if(list->size < 1){
        puts("List is empty");
        return NULL;
    }else if(list->size == 1){
        return removeFirstFromList(list);
    }else{
        Node* nxtToLast = getNodeFromList(list, list->size - 2);

        Node* removedNode = nxtToLast->next;
        nxtToLast->next = NULL;
        void* removedValue = malloc(sizeof(removedNode->val));
        memcpy(removedValue, removedNode->val, sizeof(removedNode->val));

        clearNode(removedNode);
        list->size--;

        return removedValue;
    }
}

void* removeFromList(LinkedList* list, int index){
    if(index >= list->size || index < list->size * -1){
        puts("List index out of range");
        return NULL;
    }

    if(index < 0){
        index += list->size;
    }

    Node* removedValue;

    if(index == 0){
        removedValue = removeFirstFromList(list);
    }else if(index == list->size-1){
        removedValue = removeLastFromList(list);
    }else{
        Node* prev = getNodeFromList(list, index-1);
        Node* removedNode = prev->next;
        prev->next = removedNode->next;

        removedValue = malloc(sizeof(removedNode->val));
        memcpy(removedValue, removedNode->val, sizeof(removedNode->val));

        clearNode(removedNode);
        list->size--;
    }

    return removedValue;
}

////////////////////////////////////    List Printing    //////////////////////////////////////

void changeDoublePrintPrecision(short n){
    double_precision = n;
}

char* listToString(LinkedList* list){
    LinkedList* string = LinkedListConstructor();
    char* s;
    listInsertChar(string, '[', -1);

    Node* tmp = list->head;

    while(tmp != NULL){
        switch(tmp->type){
            case TYPE_UNDEFINED:
                break;
            case TYPE_INT:
                int n = *(int*) tmp->val;
                numToCharList(string, n, TYPE_INT);
                
                break;
            case TYPE_FLOAT:
                double d = *(double*) tmp->val;
                numToCharList(string, d, TYPE_FLOAT);

                break;
            case TYPE_CHAR:
                char c = *(char*) tmp->val;
                listInsertChar(string, c, -1);

                break;
            case TYPE_STRING:
                s = (char*) tmp->val;

                while(*s != '\0'){
                    listInsertChar(string, *s, -1);
                    s++;
                }
                
                break;
            case TYPE_STRUCT:
                char* structStr = (char*) malloc(sizeof("struct@") + sizeof(void*));
                sprintf(structStr, "struct@%p", tmp->val);

                s = structStr;

                while(*s != '\0'){
                    listInsertChar(string, *s, -1);
                    s++;
                }

                free(structStr);

                break;
        }
        
        listInsertChar(string, ',', -1);
        listInsertChar(string, ' ', -1);
        tmp = tmp->next;
    }

    removeLastFromList(string); // remove unwanted ','
    removeLastFromList(string); // remove unwanted ' '
    listInsertChar(string, ']', -1);

    char* returnedString = (char*) malloc(string->size + 1);
    returnedString[string->size] = '\0';

    for(int i = 0; string->size > 0; i++){
        returnedString[i] = *(char*) removeFirstFromList(string);
    }

    clearList(string);

    return returnedString;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int voidPointerToInt(void* value){
    if(value != NULL){
        return *(int*) value;
    }

    return -1;
}

double voidPointerToDouble(void* value){
    if(value != NULL){
        return *(double*) value;
    }

    return -1.0;
}

char voidPointerToChar(void* value){
    if(value != NULL){
        return *(char*) value;
    }

    return 0;
}

void* getValueFromList(LinkedList* list, int index){
    if(index > list->size-1 || index < 0){
        puts("Index out of range");
        return NULL;
    }

    Node* tmp = list->head;

    for(int i = 0; i < index; i++){
        tmp = tmp->next;
    }

    return tmp->val;
}

int main(){
    LinkedList* teste = LinkedListConstructor();

    printf("%s\n", listToString(teste));

    listInsertInt(teste, 154, -1);

    printf("%s\n", listToString(teste));

    listInsertChar(teste, 'a', -1);

    printf("%s\n", listToString(teste));

    listInsertDouble(teste, 3.14, -1);

    printf("%s\n", listToString(teste));

    listInsertString(teste, "Vina", -1);

    printf("%s\n", listToString(teste));

    int i = *(int*) removeFirstFromList(teste);
    printf("removed: %d\n", i);

    printf("%s\n", listToString(teste));

    char* s = (char*) removeLastFromList(teste);
    printf("removed: %s\n", s);

    printf("%s\n", listToString(teste));

    listInsertStruct(teste, LinkedListConstructor(), -1);

    printf("%s\n", listToString(teste));

    char n = *(char*) getValueFromList(teste, 0);
    printf("%c\n", n);

    double d = *(double*) removeFromList(teste, 1);
    printf("Removed: %.2f\n%s\n%d", d, listToString(teste), teste->size);

    listInsertInt(teste, 7, -1);
    printf("%s\n", listToString(teste));

    char sete = *(char*) removeFromList(teste, -4);
    printf("removed: %c\n%s", sete, listToString(teste));

    free(teste);

    return 0;
}