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
    tmp->next = NULL;

    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    list->size = 0;
    list->head = tmp;

    return list;
}

void lstInsertInt(LinkedList* list, int n){
    Node* head = list->head;

    Node* new = (Node*) malloc(sizeof(Node));
    new->type = TYPE_INT;

    new->val = malloc(sizeof(int));
    memcpy(new->val, &n, sizeof(int));

    new->next = NULL;

    if(head->type == TYPE_UNDEFINED){
        head->val = malloc(sizeof(int));
        memcpy(head, new, sizeof(*new));
        free(new);
    }else{
        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    list->size += 1;
}

void lstInsertDouble(LinkedList* list, double d){
    Node* head = list->head;

    Node* new = (Node*) malloc(sizeof(Node));
    new->type = TYPE_FLOAT;

    new->val = malloc(sizeof(double));
    memcpy(new->val, &d, sizeof(double));

    new->next = NULL;

    if(head->type == TYPE_UNDEFINED){
        head->val = malloc(sizeof(double));
        memcpy(head, new, sizeof(*new));
        free(new);
    }else{
        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    list->size += 1;
}

void lstInsertChar(LinkedList* list, char c){
    Node* head = list->head;

    Node* new = (Node*) malloc(sizeof(Node));
    new->type = TYPE_CHAR;

    new->val = malloc(sizeof(char));
    memcpy(new->val, &c, sizeof(char));

    new->next = NULL;

    if(head->type == TYPE_UNDEFINED){
        head->val = malloc(sizeof(char));
        memcpy(head, new, sizeof(*new));
        free(new);
    }else{
        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    list->size += 1;
}

void printList(LinkedList* list){
    Node* tmp = list->head;

    printf("[");

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
                printf("Struct, ");
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
            printf("Struct]\n");
    }
}

int main(){
    LinkedList* teste = LinkedListConstructor();

    printList(teste);
    printf("\n");

    lstInsertInt(teste, 1);

    printList(teste);
    printf("\n");

    lstInsertChar(teste, 'a');

    printList(teste);
    printf("\n");

    lstInsertDouble(teste, 3.14);

    printList(teste);

    free(teste);

    return 0;
}