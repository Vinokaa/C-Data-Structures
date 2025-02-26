#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

///////////////////////////////////////////////////////////////////////////////////////////////
//                                  Static Function Headers                                  //
///////////////////////////////////////////////////////////////////////////////////////////////

static void listInsertInt(LinkedList* list, int n, int index);
static void listInsertDouble(LinkedList* list, double d, int index);
static void listInsertChar(LinkedList* list, char c, int index);
static void listInsertString(LinkedList* list, char* s, int index);
static void listInsertList(LinkedList* list, LinkedList* l, int index);
static void listInsertStruct(LinkedList* list, void* s, int index);

static void* listRemove(LinkedList* list, int index);

static void* listGetValue(LinkedList* list, int index);

static void listChangeDoublePrintPrecision(LinkedList* list, unsigned short n);

static char* listToString(LinkedList* list);

static void listClear(LinkedList* list);

///////////////////////////////////////////////////////////////////////////////////////////////
//                                  Complementary Functions                                  //
///////////////////////////////////////////////////////////////////////////////////////////////

static void clearNode(Node* node){
    if(node->val != NULL){
        if(node->type != TYPE_STRING && node->type != TYPE_STRUCT)
            free(node->val);
    }

    free(node);
}

static void clearListRecursive(Node* node){
    if(node != NULL){
        clearListRecursive(node->next);
        clearNode(node);
    }
}

static void listClear(LinkedList* list){
    clearListRecursive(list->head);
    list->head = NULL;
}

static Node* getNodeFromList(LinkedList* list, int index){
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

static void numToCharList(LinkedList* dest, double d, type_t type){
    if(type == TYPE_INT || type == TYPE_FLOAT){
        LinkedList list = LinkedListConstructor();
        int n;

        if(type == TYPE_FLOAT){
            for(int i = 0; i < dest->double_precision; i++){
                d *= 10;
            }

            n = (int) d;

            for(int i = 0; i < dest->double_precision; i++){
                list.insertChar(&list, n % 10 + 48, -1);
                n = (int) (n / 10);
            }

            list.insertChar(&list, '.', -1);
        }else{
            n = (int) d;
        }

        while(n > 0){
            list.insertChar(&list, n % 10 + 48, -1);
            n = (int) (n / 10);
        }

        while(list.size > 0){
            char c = *(char*) list.remove(&list, -1);
            dest->insertChar(dest, c, -1);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
//                                       Main Functions                                      //
///////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////    Constructors    /////////////////////////////////////

LinkedList LinkedListConstructor(){
    LinkedList list = { 0,
                        2,
                        NULL,
                        &listInsertInt,
                        &listInsertDouble,
                        &listInsertChar,
                        &listInsertString,
                        &listInsertList,
                        &listInsertStruct,
                        &listRemove,
                        &listGetValue,
                        &listChangeDoublePrintPrecision,
                        &listToString,
                        &listClear };

    return list;
}

LinkedList* LinkedListHeapConstructor(){
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));

    list->size = 0;
    list->double_precision = 2;
    list->head = NULL;
    list->insertInt = &listInsertInt;
    list->insertDouble = &listInsertDouble;
    list->insertChar = &listInsertChar;
    list->insertString = &listInsertString;
    list->insertList = &listInsertList;
    list->insertStruct = &listInsertStruct;
    list->remove = &listRemove;
    list->get = &listGetValue;
    list->changeDoublePrintPrecision = &listChangeDoublePrintPrecision;
    list->toString = &listToString;
    list->clear = &listClear;

    return list;
}

/////////////////////////////////    List Insert Functions    /////////////////////////////////

static Node* listInsertFirst(LinkedList* list){
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

static Node* listInsertLast(LinkedList* list){
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

static Node* listInsert(LinkedList* list, int index){
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
        new = (Node*) malloc(sizeof(Node));

        Node* tmp = getNodeFromList(list, index-1);

        new->next = tmp->next;
        tmp->next = new;
    }

    list->size++;
    return new;
}

static void listInsertInt(LinkedList* list, int n, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_INT;
    new->val = malloc(sizeof(int));
    memcpy(new->val, &n, sizeof(int));
}

static void listInsertDouble(LinkedList* list, double d, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_FLOAT;
    new->val = malloc(sizeof(double));
    memcpy(new->val, &d, sizeof(double));
}

static void listInsertChar(LinkedList* list, char c, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_CHAR;
    new->val = malloc(sizeof(char));
    memcpy(new->val, &c, sizeof(char));
}

static void listInsertString(LinkedList* list, char* s, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_STRING;
    new->val = s;
}

static void listInsertList(LinkedList* list, LinkedList* l, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_LIST;
    new->val = l;
}

static void listInsertStruct(LinkedList* list, void* s, int index){
    Node* new = listInsert(list, index);
    new->type = TYPE_STRUCT;
    new->val = s;
}

/////////////////////////////////    List Remove Functions    /////////////////////////////////

static Node* listRemoveFirstNode(LinkedList* list){
    Node* removedNode = list->head;
    list->head = removedNode->next;
    return removedNode;
}

static Node* listRemoveLastNode(LinkedList* list){
    if(list->size == 1){
        return listRemoveFirstNode(list);
    }else{
        Node* nxtToLast = getNodeFromList(list, list->size - 2);
        Node* removedNode = nxtToLast->next;
        nxtToLast->next = NULL;

        return removedNode;
    }
}

static void* listRemove(LinkedList* list, int index){
    if(index >= list->size || index < -1){
        puts("List removal index out of range");
        return NULL;
    }

    Node* removedNode;

    if(index == 0){
        removedNode = listRemoveFirstNode(list);
    }else if(index == -1){
        removedNode = listRemoveLastNode(list);
    }else{
        Node* prev = getNodeFromList(list, index-1);
        removedNode = prev->next;
        prev->next = removedNode->next;
    }

    void* removedValue = removedNode->val;

    free(removedNode);
    list->size--;
    return removedValue;
}

/////////////////////////////////////    Get Method    ////////////////////////////////////////

static void* listGetValue(LinkedList* list, int index){
    Node* tmp = getNodeFromList(list, index);

    if(tmp != NULL) return tmp->val;

    return tmp;
}

////////////////////////////////////    List Printing    //////////////////////////////////////

static void listChangeDoublePrintPrecision(LinkedList* list, unsigned short n){
    list->double_precision = n;
}

static char* listToString(LinkedList* list){
    LinkedList string = LinkedListConstructor();
    string.changeDoublePrintPrecision(&string, list->double_precision);
    char* s;
    string.insertChar(&string, '[', -1);

    Node* tmp = list->head;

    while(tmp != NULL){
        switch(tmp->type){
            case TYPE_INT:
                int n = *(int*) tmp->val;
                numToCharList(&string, n, TYPE_INT);
                
                break;
            case TYPE_FLOAT:
                double d = *(double*) tmp->val;
                numToCharList(&string, d, TYPE_FLOAT);

                break;
            case TYPE_CHAR:
                char c = *(char*) tmp->val;
                string.insertChar(&string, c, -1);

                break;
            case TYPE_STRING:
                s = (char*) tmp->val;

                while(*s != '\0'){
                    string.insertChar(&string, *s, -1);
                    s++;
                }
                
                break;
            case TYPE_LIST:
                LinkedList* l = tmp->val;
                s = l->toString(l);

                while(*s != '\0'){
                    string.insertChar(&string, *s, -1);
                    s++;
                }
                
                break;
            case TYPE_STRUCT:
                char* structStr = (char*) malloc(sizeof("struct@") + 16);
                sprintf(structStr, "struct@%p", tmp->val);

                s = structStr;

                while(*s != '\0'){
                    string.insertChar(&string, *s, -1);
                    s++;
                }

                free(structStr);

                break;
        }
        
        string.insertChar(&string, ',', -1);
        string.insertChar(&string, ' ', -1);
        tmp = tmp->next;
    }

    if(string.size > 1){
        string.remove(&string, -1); // remove unwanted ','
        string.remove(&string, -1); // remove unwanted ' '
    }

    string.insertChar(&string, ']', -1);

    char* returnedString = (char*) malloc(string.size + 1);
    returnedString[string.size] = '\0';

    for(int i = 0; string.size > 0; i++){
        returnedString[i] = *(char*) string.remove(&string, 0);
    }

    return returnedString;
}

///////////////////////////////////////////////////////////////////////////////////////////////