#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;
typedef struct LinkedList LinkedList;

typedef enum{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_LIST,
    TYPE_STRUCT
} type_t;

struct Node{
    type_t type;
    void* val;
    Node* next;
};

struct LinkedList{
    int size;
    unsigned short double_precision;
    Node* head;
    void (*insertInt)(LinkedList* list, int n, int index);
    void (*insertDouble)(LinkedList* list, double d, int index);
    void (*insertChar)(LinkedList* list, char c, int index);
    void (*insertString)(LinkedList* list, char* s, int index);
    void (*insertList)(LinkedList* list, LinkedList* l, int index);
    void (*insertStruct)(LinkedList* list, void* s, int index);
    void* (*remove)(LinkedList* list, int index);
    void* (*get)(LinkedList* list, int index);
    void (*changeDoublePrintPrecision)(LinkedList* list, unsigned short n);
    char* (*toString)(LinkedList* list);
    void (*clear)(LinkedList* list);
};

LinkedList LinkedListConstructor();

LinkedList* LinkedListHeapConstructor();

#endif