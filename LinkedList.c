#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short double_precision = 2;

typedef struct Node Node;
typedef struct LinkedList LinkedList;

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

void* removeFromList(LinkedList* list, int index);

void clearNode(Node* node){
    if(node->val != NULL){
        if(node->type != TYPE_STRING && node->type != TYPE_STRUCT)
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

    free(list);
}

Node* getNodeFromList(LinkedList* list, int index){
    if(index >= list->size || index < -1){
        printf("List retrieval index out of range | List size is %d\n", list->size);
        return NULL;
    }

    if(index == -1) index = list->size-1;

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
            char c = *(char*) removeFromList(list, -1);
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
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    list->size = 0;
    list->head = NULL;

    return list;
}

/////////////////////////////////    List Insert Functions    /////////////////////////////////

Node* listInsertFirst(LinkedList* list){
    Node* head = list->head;
    Node* new;

    if(head == NULL){
        list->head = (Node*) malloc(sizeof(Node));
        list->head->next = NULL;
        new = list->head;
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

    if(head == NULL){
        new = listInsertFirst(list);
    }else{
        new = (Node*) malloc(sizeof(Node));
        new->next = NULL;

        Node* tmp = getNodeFromList(list, list->size-1);

        tmp->next = new;
    }

    return new;
}

Node* listInsert(LinkedList* list, int index){
    if(index > list->size || index < -1){
        printf("List insertion index out of range | List size is %d\n", list->size);
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

        Node* tmp = getNodeFromList(list, index);

        new->next = tmp->next;
        tmp->next = new;
    }

    list->size++;
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
    new->val = s;
}

void listInsertStruct(LinkedList* list, void* s, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_STRUCT;
    new->val = s;
}

/////////////////////////////////    List Remove Functions    /////////////////////////////////

Node* removeFirstNodeFromList(LinkedList* list){
    Node* removedNode = list->head;
    list->head = removedNode->next;
    return removedNode;
}

Node* removeLastNodeFromList(LinkedList* list){
    if(list->size == 1){
        return removeFirstNodeFromList(list);
    }else{
        Node* nxtToLast = getNodeFromList(list, list->size - 2);
        Node* removedNode = nxtToLast->next;
        nxtToLast->next = NULL;

        return removedNode;
    }
}

void* removeFromList(LinkedList* list, int index){
    if(index >= list->size || index < -1){
        puts("List removal index out of range");
        return NULL;
    }

    Node* removedNode;

    if(index == 0){
        removedNode = removeFirstNodeFromList(list);
    }else if(index == -1){
        removedNode = removeLastNodeFromList(list);
    }else{
        Node* prev = getNodeFromList(list, index-1);
        removedNode = prev->next;
        prev->next = removedNode->next;
    }

    void* removedValue = removedNode->val;

    //removedValue = malloc(sizeof(removedNode->val));
    //memcpy(removedValue, removedNode->val, sizeof(removedNode->val));

    //clearNode(removedNode);
    free(removedNode);
    list->size--;
    return removedValue;
}

/////////////////////////////////////    Get Method    ////////////////////////////////////////

void* getValueFromList(LinkedList* list, int index){
    Node* tmp = getNodeFromList(list, index);

    if(tmp != NULL) return tmp->val;

    return tmp;
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
                char* structStr = (char*) malloc(sizeof("struct@") + 16);
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

    if(string->size > 1){
        removeFromList(string, -1); // remove unwanted ','
        removeFromList(string, -1); // remove unwanted ' '
    }

    listInsertChar(string, ']', -1);

    char* returnedString = (char*) malloc(string->size + 1);
    returnedString[string->size] = '\0';

    for(int i = 0; string->size > 0; i++){
        returnedString[i] = *(char*) removeFromList(string, 0);
    }

    clearList(string);

    return returnedString;
}

/////////////////////////////////////    Converters    ////////////////////////////////////////

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

int main(){
    LinkedList* teste = LinkedListConstructor();
    LinkedList* teste2 = LinkedListConstructor();

    listInsertInt(teste, 7, -1);
    listInsertDouble(teste, 3.14159, -1);
    listInsertChar(teste, 'V', -1);
    listInsertString(teste, "Vina", -1);
    listInsertStruct(teste, teste2, -1);

    listInsertInt(teste2, 3, 0);

    printf("%s\n", listToString(teste));

    void* removed = removeFromList(teste, 3);
    printf("%s\n", removed);

    clearList(teste);

    return 0;
}