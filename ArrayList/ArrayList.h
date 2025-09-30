#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct ArrayList ArrayList;

struct ArrayList{
    size_t size;
    void* array;

    void (*insert)();
};

#endif