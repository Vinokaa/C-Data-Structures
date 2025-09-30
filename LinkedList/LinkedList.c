#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LinkedList.h"

typedef struct SizeList SizeList;

struct SizeList{
    long* val;
    SizeList* next;
};

///////////////////////////////////////////////////////////////////////////////////////////////
//                                  Static Function Headers                                  //
///////////////////////////////////////////////////////////////////////////////////////////////

static void listInsertInt(LinkedList* list, int n, int index);
static void listInsertDouble(LinkedList* list, double d, int index);
static void listInsertChar(LinkedList* list, char c, int index);
static void listInsertString(LinkedList* list, char* s, int index);
static void listInsertList(LinkedList* list, LinkedList* l, int index);
static void listInsertStruct(LinkedList* list, void* s, int index);

static void* listRemove(LinkedList* list, void* _Dst, int index);

static void* listGetValue(LinkedList* list, int index);

static void listChangeDoublePrintPrecision(LinkedList* list, unsigned short n);

static char* listToString(LinkedList* list, char* _Dst);

static long listGetStrSize(LinkedList* list);

static void listClear(LinkedList* list);

///////////////////////////////////////////////////////////////////////////////////////////////
//                                        Constructor                                        //
///////////////////////////////////////////////////////////////////////////////////////////////

LinkedList* LinkedListConstructor(){
    LinkedList* list = malloc(sizeof(LinkedList));

    list->size = 0;
    list->strSize = 3; // [] + '\0'
    list->head = NULL;
    list->tail = NULL;

    list->_sizeFixedAmount = 0;
    list->_sizeDoubleAmount = 0;
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
    list->getStrSize = &listGetStrSize;
    list->clear = &listClear;

    return list;
}

///////////////////////////////////    Static Attributes    ///////////////////////////////////

static unsigned short double_precision = 2;
SizeList* internalListsSizePointers = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////
//                                  Complementary Functions                                  //
///////////////////////////////////////////////////////////////////////////////////////////////

static void clearListRecursive(Node* node){
    if(node != NULL){
        clearListRecursive(node->next);
        free(node);
    }
}

static void listClear(LinkedList* list){
    clearListRecursive(list->head);
    list->head = NULL;
}

static Node* getNodeFromList(LinkedList* list, int index){
    if(index >= list->size || index < -1){
        printf("List retrieval index out of range | List size is %ld\n", list->size);
        return NULL;
    }

    if(index == -1) index = list->size-1;

    Node* tmp = list->head;

    for(int i = 0; i < index; i++){
        tmp = tmp->next;
    }

    return tmp;
}

static char* intToCharAppend(char* _Dst, int n){
    int size = (int) log10(n) + 1;
    
    for(int i = size-1; i >= 0; i--){
        _Dst[i] = n % 10 + 48;
        n /= 10;
    }

    return _Dst + size;
}

static char* doubleToCharAppend(char* _Dst, double d){
    long decimalInt = (long) (d * pow(10, double_precision));
    int size = (int) log10(decimalInt) + 2;
    int offset = size - 1;

    for(int i = 0; i < double_precision; i++, offset--){
        _Dst[offset] = decimalInt % 10 + 48;
        decimalInt /= 10;
    }

    _Dst[offset] = '.';
    offset--;

    for(; offset >= 0; offset--){
        _Dst[offset] = decimalInt % 10 + 48;
        decimalInt /= 10;
    }

    return _Dst + size;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//                                       Main Functions                                      //
///////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////    List Insert Functions    /////////////////////////////////

static Node* listInsertFirst(LinkedList* list, Node* new){
    Node* head = list->head;

    if(head == NULL){
        list->head = new;
        list->tail = new;
    }else{
        new->next = head;
        list->head = new;
    }

    return new;
}

static Node* listInsertLast(LinkedList* list, Node* new){
    Node* tail = list->tail;

    if(tail == NULL){
        listInsertFirst(list, new);
    }else{
        list->tail->next = new;
        list->tail = new;
    }

    return new;
}

static Node* listInsert(LinkedList* list, Node* new, int index){
    if(index > list->size || index < -1){
        printf("List insertion index out of range | List size is %ld\n", list->size);
        return NULL;
    }

    if(index == 0){
        new = listInsertFirst(list, new);
    }else if(index == -1){
        new = listInsertLast(list, new);
    }else{
        Node* tmp = getNodeFromList(list, index-1);

        new->next = tmp->next;
        tmp->next = new;
    }

    list->size++;

    if(list->size > 1) list->strSize += 2; // consider every ", " needed to print

    return new;
}

static void listInsertInt(LinkedList* list, int n, int index){
    Node* new = malloc(sizeof(Node) + sizeof(int));
    listInsert(list, new, index);
    new->type = TYPE_INT;
    *(int*) (new+1) = n;
    list->_sizeFixedAmount += (int) (log10(n) + 1);
}

static void listInsertDouble(LinkedList* list, double d, int index){
    Node* new = malloc(sizeof(Node) + sizeof(double));
    listInsert(list, new, index);
    new->type = TYPE_FLOAT;
    *(double*) (new+1) = d;
    list->_sizeFixedAmount += (int) (log10(d) + 1);
    list->_sizeDoubleAmount += 1;
}

static void listInsertChar(LinkedList* list, char c, int index){
    Node* new = malloc(sizeof(Node) + sizeof(char));
    listInsert(list, new, index);
    new->type = TYPE_CHAR;
    *(char*) (new+1) = c;
    list->_sizeFixedAmount += 1;
}

static void listInsertString(LinkedList* list, char* s, int index){
    Node* new = malloc(sizeof(Node) + sizeof(char*));
    listInsert(list, new, index);
    new->type = TYPE_STRING;
    *(char**) (new+1) = s;
    list->_sizeFixedAmount += strlen(s);
}

static void listInsertList(LinkedList* list, LinkedList* l, int index){
    Node* new = malloc(sizeof(Node) + sizeof(LinkedList*));
    listInsert(list, new, index);
    new->type = TYPE_LIST;
    LinkedList** tmp = (LinkedList**) (new+1);
    *tmp = l;
}

static void listInsertStruct(LinkedList* list, void* s, int index){
    Node* new = malloc(sizeof(Node) + sizeof(void*));
    listInsert(list, new, index);
    new->type = TYPE_STRUCT;
    *(void**) (new+1) = s;
    list->_sizeFixedAmount += 16; // See listToString() implementation to understand how structs are printed
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

static void* listRemove(LinkedList* list, void* _Dst, int index){
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

    switch(removedNode->type){
        case TYPE_CHAR:
            memcpy(_Dst, removedNode+1, sizeof(char));
            list->strSize -= 1;
            break;
        case TYPE_INT:
            memcpy(_Dst, removedNode+1, sizeof(int));
            list->strSize -= (int) log10(*(int*) _Dst) + 1;
            break;
        case TYPE_FLOAT:
            memcpy(_Dst, removedNode+1, sizeof(double));
            break;
        default:
            _Dst = removedNode+1;
            break;
    }

    free(removedNode);
    list->size--;
    if(list->size > 0) list->strSize -= 2; // consider every ", " needed to print

    return _Dst;
}

/////////////////////////////////////    Get Method    ////////////////////////////////////////

static void* listGetValue(LinkedList* list, int index){
    Node* tmp = getNodeFromList(list, index);

    if(tmp != NULL) return tmp+1;

    return tmp;
}

////////////////////////////////////    List Printing    //////////////////////////////////////

static long listGetStrSize(LinkedList* list){
    long comma_space_amount = list->size ? list->size-1 : 0;
    return (long)(list->_sizeFixedAmount + list->_sizeDoubleAmount * (1 + double_precision) + 2 * comma_space_amount + 3);
}

static void listChangeDoublePrintPrecision(LinkedList* list, unsigned short n){
    double_precision = n;
}

static char* listToString(LinkedList* list, char* _Dst){
    char* tmp_s = _Dst;
    *tmp_s = '[';
    tmp_s++;

    Node* tmp = list->head;
    char* s = NULL;

    while(tmp != NULL){
        switch(tmp->type){
            case TYPE_INT:
                int n = *(int*) (tmp+1);
                tmp_s = intToCharAppend(tmp_s, n);
                
                break;
            case TYPE_FLOAT:
                double d = *(double*) (tmp+1);
                tmp_s = doubleToCharAppend(tmp_s, d);

                break;
            case TYPE_CHAR:
                char c = *(char*) (tmp+1);
                *tmp_s = c;
                tmp_s++;

                break;
            case TYPE_STRING:
                for(char* s = *(char**) (tmp+1); *s != '\0'; tmp_s++, s++){
                    *tmp_s = *s;
                }
                
                break;
            case TYPE_LIST:
                {
                    LinkedList* l = *(LinkedList**) (tmp+1);

                    listToString(l, tmp_s);

                    tmp_s += l->getStrSize(l) - 1;
                    
                    break;
                }
            case TYPE_STRUCT:
                char structStr[24];
                sprintf(structStr, "struct@%p", *(void**) (tmp+1));

                s = structStr;

                while(*s != '\0'){
                    *tmp_s = *s;
                    tmp_s++;
                    s++;
                }

                break;
        }
        
        if(tmp->next != NULL){
            *tmp_s = ',';
            tmp_s++;
            *tmp_s = ' ';
            tmp_s++;
        }

        tmp = tmp->next;
    }

    *tmp_s = ']';
    tmp_s++;
    *tmp_s = '\0';

    return _Dst;
}

///////////////////////////////////////////////////////////////////////////////////////////////