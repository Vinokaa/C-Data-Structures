#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;
typedef struct LinkedList LinkedList;
typedef union Value Value;

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
    Node* next;
};

struct LinkedList{
    long size;
    long strSize;
    Node* head;
    Node* tail;
    long _sizeFixedAmount;
    int _sizeDoubleAmount;
    void (*insertInt)(LinkedList* list, int n, int index);
    void (*insertDouble)(LinkedList* list, double d, int index);
    void (*insertChar)(LinkedList* list, char c, int index);
    void (*insertString)(LinkedList* list, char* s, int index);
    void (*insertList)(LinkedList* list, LinkedList* l, int index);
    void (*insertStruct)(LinkedList* list, void* s, int index);
    void* (*remove)(LinkedList* list, void* _Dst, int index);
    void* (*get)(LinkedList* list, int index);
    void (*changeDoublePrintPrecision)(LinkedList* list, unsigned short n);
    char* (*toString)(LinkedList* list, char* _Dst);
    long (*getStrSize)(LinkedList* list);
    void (*clear)(LinkedList* list);
};

LinkedList* LinkedListConstructor();

#endif