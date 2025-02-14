typedef struct Node Node;
typedef struct LinkedList LinkedList;

typedef enum{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_STRUCT
} type_t;

struct Node{
    type_t type;
    void* val;
    Node* next;
};

struct LinkedList{
    int size;
    Node* head;
};

void listClear(LinkedList* list);

LinkedList* LinkedListConstructor();

void listInsertInt(LinkedList* list, int n, int index);

void listInsertDouble(LinkedList* list, double d, int index);

void listInsertChar(LinkedList* list, char c, int index);

void listInsertString(LinkedList* list, char* s, int index);

void listInsertStruct(LinkedList* list, void* s, int index);

void* listRemove(LinkedList* list, int index);

void* listGetValue(LinkedList* list, int index);

void listChangeDoublePrintPrecision(unsigned short n);

char* listToString(LinkedList* list);