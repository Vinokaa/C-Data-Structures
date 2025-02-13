#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void listInsertInt(LinkedList* list, int n){
    Node* head = list->head;

    if(head->type == TYPE_UNDEFINED){
        head->type = TYPE_INT;
        head->val = malloc(sizeof(int));
        memcpy(head->val, &n, sizeof(int));
    }else{
        Node* new = (Node*) malloc(sizeof(Node));
        new->type = TYPE_INT;

        new->val = malloc(sizeof(int));
        memcpy(new->val, &n, sizeof(int));

        new->next = NULL;

        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    list->size += 1;
}

void listInsertDouble(LinkedList* list, double d){
    Node* head = list->head;

    if(head->type == TYPE_UNDEFINED){
        head->type = TYPE_FLOAT;
        head->val = malloc(sizeof(double));
        memcpy(head->val, &d, sizeof(double));
    }else{
        Node* new = (Node*) malloc(sizeof(Node));
        new->type = TYPE_FLOAT;

        new->val = malloc(sizeof(double));
        memcpy(new->val, &d, sizeof(double));

        new->next = NULL;

        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    list->size += 1;
}

void listInsertChar(LinkedList* list, char c){
    Node* head = list->head;

    if(head->type == TYPE_UNDEFINED){
        head->type = TYPE_CHAR;
        head->val = malloc(sizeof(char));
        memcpy(head->val, &c, sizeof(char));
    }else{
        Node* new = (Node*) malloc(sizeof(Node));
        new->type = TYPE_CHAR;

        new->val = malloc(sizeof(char));
        memcpy(new->val, &c, sizeof(char));

        new->next = NULL;

        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    list->size += 1;
}

void listInsertString(LinkedList* list, char* s){
    Node* head = list->head;

    if(head->type == TYPE_UNDEFINED){
        head->type = TYPE_STRING;
        head->val = malloc(sizeof(s));
        memcpy(head->val, s, sizeof(s));
    }else{
        Node* new = (Node*) malloc(sizeof(Node));
        new->type = TYPE_STRING;

        new->val = malloc(sizeof(s));
        memcpy(new->val, s, sizeof(s));

        new->next = NULL;

        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    list->size += 1;
}

void listInsertStruct(LinkedList* list, void* s){
    Node* head = list->head;

    if(head->type == TYPE_UNDEFINED){
        head->type = TYPE_STRUCT;
        head->val = malloc(sizeof(s));
        memcpy(head->val, s, sizeof(s));
    }else{
        Node* new = (Node*) malloc(sizeof(Node));
        new->type = TYPE_STRUCT;

        new->val = malloc(sizeof(s));
        memcpy(new->val, s, sizeof(s));

        new->next = NULL;

        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    list->size += 1;
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

void printList(LinkedList* list){
    LinkedList* string = LinkedListConstructor();

    printf("[");

    Node* tmp = list->head;

    while(tmp->next != NULL){
        switch(tmp->type){
            case TYPE_UNDEFINED:
                break;
            case TYPE_INT:
                printf("%d, ", *(int*) tmp->val);
                break;
            case TYPE_FLOAT:
                printf("%.2f, ", *(double*) tmp->val);
                break;
            case TYPE_CHAR:
                printf("%c, ", *(char*) tmp->val);
                break;
            case TYPE_STRING:
                printf("%s, ", (char*) tmp->val);
                break;
            default:
                printf("struct@%p, ", tmp);
        }
        
        tmp = tmp->next;
    }

    switch(tmp->type){
        case TYPE_UNDEFINED:
            printf("]\n");
            break;
        case TYPE_INT:
            printf("%d]\n", *(int*) tmp->val);
            break;
        case TYPE_FLOAT:
            printf("%.2f]\n", *(double*) tmp->val);
            break;
        case TYPE_CHAR:
            printf("%c]\n", *(char*) tmp->val);
            break;
        case TYPE_STRING:
            printf("%s]\n", (char*) tmp->val);
            break;
        default:
            printf("struct@%p]\n", tmp);
    }

    if(string->size > 0){
        printList(string);
    }

    clearList(string);
}

void listToString(LinkedList* list){
    LinkedList* string = LinkedListConstructor();

    Node* tmp = list->head;

    while(tmp != NULL){
        switch(tmp->type){
            case TYPE_UNDEFINED:
                break;
            case TYPE_INT:
                LinkedList* intList = LinkedListConstructor();
                int n = *(int*) tmp->val;

                while(n > 0){
                    listInsertChar(intList, n % 10 + 48);
                    n = (int) (n / 10);
                }

                while(intList->size > 0){
                    char c = *(char*) removeLastFromList(intList);
                    listInsertChar(string, c);
                }

                clearList(intList);
                break;
            case TYPE_FLOAT:

                break;
            case TYPE_CHAR:
                
                break;
            case TYPE_STRING:
                
                break;
            default:
                
        }
        
        tmp = tmp->next;
    }

    if(string->size > 0){
        printList(string);
    }

    clearList(string);
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

    printList(teste);
    printf("\n");

    listInsertInt(teste, 154);

    printList(teste);
    printf("\n");

    listInsertChar(teste, 'a');

    printList(teste);
    printf("\n");

    listInsertDouble(teste, 3.14);

    printf("listToString() = ");
    listToString(teste);

    printList(teste);
    printf("\n");

    listInsertString(teste, "Vina");

    printList(teste);
    printf("\n");

    int i = *(int*) removeFirstFromList(teste);
    printf("removed: %d\n", i);

    printList(teste);
    printf("\n");

    char* s = (char*) removeLastFromList(teste);
    printf("removed: %s\n", s);

    printList(teste);
    printf("\n");

    listInsertStruct(teste, LinkedListConstructor());

    printList(teste);
    printf("\n");

    char n = *(char*) getValueFromList(teste, 0);
    printf("%c", n);

    free(teste);

    return 0;
}