# C Data Structures Library

<!--<p>
  <a href="https://github.com/Vinokaa/CDataStructures/blob/master/README.pt-br.md"> 
    <img src="https://img.shields.io/badge/lang-pt--br-green.svg">
  </a>
</p>-->

<!-- teste -->

<p align="center">
  <img width="500" height="450" src="https://github.com/user-attachments/assets/ea501ff2-3ff4-42a8-a610-db6db94b1f6b">
</p>


# Documentation

The libraries in this repository were made from an idea to make all data structures in C (I swear I'm not going insane), and initially make their usage feel as close as possible to an Object Oriented perspective [1].

> [1] I'll be removing the Object Oriented perspective in the near future, because implementing OO in C requires structs to store one pointer to each method, wasting a lot of memory, and alternatives to that (like storing the pointers to methods in a static methods struct, then having one pointer in every class point to it) require more writing from the person using this library.

<br>

## Linked List

### Important Notes

Values starting with _ (underscore) stored inside the LinkedList struct shouldn't be modified externally. These values are only used internally, e.g. `ListNode* _internalLists` is a list that stores pointers to the internal lists, so that the `list->getStrSize()` function knows how many bytes to allocate in order to print the whole list.

### _LinkedList*_ LinkedListConstructor()

Initializes the linked list, allocating memory for it in the heap, setting its size to `0` and its head to `NULL`.

Returns a pointer to an initialized LinkedList struct.

> The user can and should `free()` the Linked List created with this function when it's not needed anymore. Always use [`LinkedList->clear()`](#void-linkedlistclearlinkedlist-list) before `free()`ing the Linked List itself.

```C
LinkedList* list = LinkedListConstructor();
```

<br>

### _void_ LinkedList->insertInt(_LinkedList* list, int n, int index_)

Adds one Node storing the _`int n`_ given as a parameter to the Linked List.

1. _`LinkedList* list`_: A pointer to the Linked List where _`int n`_ will be stored
2. _`int n`_: The int value to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
LinkedList* list = LinkedListConstructor();

list->insertInt(list, 3, 0);
list->insertInt(list, 7, -1);
list->insertInt(list, 2, 0);
list->insertInt(list, 5, 2);

// stack-allocated string
char list_print[list->getStrSize(list)];
printf("%s\n", list->toString(list));

list->clear(list);
```

or

```C
LinkedList* list = LinkedListConstructor();

list->insertInt(list, 3, 0);
list->insertInt(list, 7, -1);
list->insertInt(list, 2, 0);
list->insertInt(list, 5, 2);

// heap-allocated string
char* list_print = malloc(list->getStrSize(list));
printf("%s\n", list->toString(list));
free(list_print);

list->clear(list);
```

```
[2, 3, 5, 7]
```

<br>

### _void_ LinkedList->insertDouble(_LinkedList* list, double d, int index_)

Adds one Node storing the _`double d`_ given as a parameter to the Linked List.

The original fractional part of _`double d`_ won't be lost, but when printing using [`LinkedList->toString()`](#char-linkedlist-tostringlinkedlist-list), the fractional portion will be limited by a variable, which can be changed with [`LinkedList->changeDoublePrintPrecision()`](#void-linkedlist-changedoubleprintprecisionlinkedlist-list-unsigned-short-n).

1. _`LinkedList* list`_: A pointer to the Linked List where _`double d`_ will be stored
2. _`double d`_: The double value to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
LinkedList* list = LinkedListConstructor();

list->insertDouble(list, 3.14159, -1);
list->insertDouble(list, 7.5, -1);
list->insertDouble(list, 2, -1);

// stack-allocated string
char list_print[list->getStrSize(list)];
printf("%s\n", list->toString(list));

list->clear(list);
```

or

```C
LinkedList* list = LinkedListConstructor();

list->insertDouble(list, 3.14159, -1);
list->insertDouble(list, 7.5, -1);
list->insertDouble(list, 2, -1);

// heap-allocated string
char* list_print = malloc(list->getStrSize(list));
printf("%s\n", list->toString(list));
free(list_print);

list->clear(list);
```

```
// Considering default (2) floating point print precision
[3.14, 7.50, 2.00]
```

<br>

### _void_ LinkedList->insertChar(_LinkedList* list, char c, int index_)

Adds one Node storing the _`char c`_ given as a parameter to the Linked List.

1. _`LinkedList* list`_: A pointer to the Linked List where _`char c`_ will be stored
2. _`char c`_: The char to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
LinkedList* list = LinkedListConstructor();

list->insertChar(list, 'a', 0);
list->insertChar(list, 'n', 0);
list->insertChar(list, 'i', 0);
list->insertChar(list, 'v', 0);

// stack-allocated string
char list_print[list->getStrSize(list)];
printf("%s\n", list->toString(list));

list->clear(list);
```

or

```C
LinkedList* list = LinkedListConstructor();

list->insertChar(list, 'a', 0);
list->insertChar(list, 'n', 0);
list->insertChar(list, 'i', 0);
list->insertChar(list, 'v', 0);

// heap-allocated string
char* list_print = malloc(list->getStrSize(list));
printf("%s\n", list->toString(list));
free(list_print);

list->clear(list);
```

```
[v, i, n, a]
```

<br>

### _void_ LinkedList->insertString(_LinkedList* list, char* s, int index_)

Adds one Node storing the _`char* s`_ given as a parameter to the Linked List.

1. _`LinkedList* list`_: A pointer to the Linked List where _`char* s`_ will be stored
2. _`char* s`_: The string to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
LinkedList* list = LinkedListConstructor();

list->insertString(list, "Dua Lipa", 0);
list->insertString(list, "Matue", -1);
list->insertString(list, "Neoni", 1);

// stack-allocated string
char list_print[list->getStrSize(list)];
printf("%s\n", list->toString(list));

list->clear(list);
```

or

```C
LinkedList* list = LinkedListConstructor();

list->insertString(list, "Dua Lipa", 0);
list->insertString(list, "Matue", -1);
list->insertString(list, "Neoni", 1);

// heap-allocated string
char* list_print = malloc(list->getStrSize(list));
printf("%s\n", list->toString(list));
free(list_print);

list->clear(list);
```

```
[Dua Lipa, Neoni, Matue]
```

<br>

### _void_ LinkedList->insertList(_LinkedList* list, LinkedList* l, int index_)

Adds, to the Linked List, one Node storing another LinkedList given as a parameter.

1. _`LinkedList* list`_: A pointer to the Linked List where _`LinkedList* l`_ will be stored
2. _`LinkedList* l`_: The LinkedList to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
LinkedList* list1 = LinkedListConstructor();
LinkedList* list2 = LinkedListConstructor();
LinkedList* list3 = LinkedListConstructor();

list2->insertInt(list2, 7, -1);

list1->insertList(list1, list2, -1);
list1->insertList(list1, list3, -1);

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list3->insertDouble(list3, 125.5, -1);
list3->insertChar(list3, 'I', -1);

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list1->clear(list1);
list2->clear(list2);
list3->clear(list3);
```

or

```C
LinkedList* list1 = LinkedListConstructor();
LinkedList* list2 = LinkedListConstructor();
LinkedList* list3 = LinkedListConstructor();

list2->insertInt(list2, 7, -1);

list1->insertList(list1, list2, -1);
list1->insertList(list1, list3, -1);

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list3->insertDouble(list3, 125.5, -1);
list3->insertChar(list3, 'I', -1);

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list1->clear(list1);
list2->clear(list2);
list3->clear(list3);
```

```
[[7], []]
[[7], [125.5, I]]
```

> You can also call `list->insertList(list, LinkedListConstructor(), 0)` without facing lost pointer problems, since you can return the pointer to the inserted list with `list->get(list, <list-index>)` or `list->remove(list, <list-index>)` (considering you store the remove return value).

> The `list->clear(list)` function doesn't clear the internal lists yet, so using the insertion with `LinkedListConstructor()` might cause lost pointer problems if the internal lists aren't removed, cleared and freed individually. In later updates I'll be adding a boolean value to the `list->clear(list)` function to define whether the internal lists should be cleared and freed or not.

<br>

### _void_ LinkedList->insertStruct(_LinkedList* list, void* s, int index_)

Adds one Node storing any type of struct given as a parameter to the Linked List.

1. _`LinkedList* list`_: A pointer to the Linked List where _`void* s`_ will be stored (void* is a generic pointer, meaning that it can be a pointer to any type of struct)
2. _`void* s`_: The struct to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
typedef struct Character{
  char* name;
  char* origin;
} Character;

Character* elliot = malloc(sizeof(Character));
elliot->name = "Elliot Alderson";
elliot->origin = "Mr. Robot";

LinkedList* list = LinkedListConstructor();

list->insertStruct(list, elliot, -1);

// stack-allocated string
char list_print[list->getStrSize(list)];
printf("%s\n", list->toString(list));

Character* character = list->get(list, 0);
printf("%s from %s\n", character->name, character->origin);

list->clear(list);
```

or

```C
typedef struct Character{
  char* name;
  char* origin;
} Character;

Character* elliot = malloc(sizeof(Character));
elliot->name = "Elliot Alderson";
elliot->origin = "Mr. Robot";

LinkedList* list = LinkedListConstructor();

list->insertStruct(list, elliot, -1);

// heap-allocated string
char* list_print = list->getStrSize(list);
printf("%s\n", list->toString(list));
free(list_print);

Character* character = list->get(list, 0);
printf("%s from %s\n", character->name, character->origin);

list->clear(list);
```

```
[struct@000001582723A120]
Elliot Alderson from Mr. Robot
```

<br>

### _void*_ LinkedList->remove(_LinkedList* list, int index_)

Removes an element from a Node from the Linked List based on the index given.

Returns a _`void*`_ pointer to the removed value, which can and should be casted to its original type.

1. _`LinkedList* list`_: A pointer to the Linked List from where the value will be removed
2. _`int index`_: The index (from $-1$ to $list.size-1$), being $-1$ to remove the last value, and $\ge0$ the index of the Node from which the value will be removed

> `int`, `double` and `char` are stored and returned as copies, so casting the return value back to their original, and `list` and `struct` are created using `malloc()`, the user can and should `free()` the removed value after it's no longer needed. **Keep in mind that casting the returned pointer into a non-pointer variable causes the loss of the pointer needed to free the allocated memory.**

```C
LinkedList* list1 = LinkedListConstructor();
LinkedList* list2 = LinkedListConstructor();

list1->insertInt(list1, 7, -1);
list1->insertDouble(list1, 3.14, -1);
list1->insertList(list1, list2, -1);

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

int removedInt;
list1->remove(list1, &removedInt, 0);
printf("removed: %d\n", removedInt);

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

LinkedList* removedList;
list1->remove(list1, removedList, -1);

// stack-allocated string
char list_print[removedList->getStrSize(removedList)];
printf("Removed: %s\n", removedList->toString(removedList, list_print));

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list1->clear(list1);
list2->clear(list2);

free(list1);
free(list2);
```

or

```C
LinkedList* list1 = LinkedListConstructor();
LinkedList* list2 = LinkedListConstructor();

list1->insertInt(list1, 7, -1);
list1->insertDouble(list1, 3.14, -1);
list1->insertList(list1, list2, -1);

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

int removedInt;
list1->remove(list1, &removedInt, 0);
printf("removed: %d\n", removedInt);

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

LinkedList* removedList;
list1->remove(list1, removedList, -1);

// heap-allocated string
char* list_print = malloc(removedList->getStrSize(removedList));
printf("Removed: %s\n", removedList->toString(removedList, list_print));
free(list_print);

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list1->clear(list1);
list2->clear(list2);

free(list1);
free(list2);
```

```
[7, 3.14, []]
removed: 7
[3.14, []]
removed: []
[3.14]
```

<br>

### _void*_ LinkedList->get(_LinkedList* list, int index_)

Retrieves the value of a Node from the Linked List based on the index given, without removing its Node from the Linked List.

Returns a _`void*`_ pointer to the value, which can be casted to its original type if needed.

1. _`LinkedList* list`_: A pointer to the Linked List from where the value will be retrieved
2. _`int index`_: The index (from $-1$ to $list.size-1$), being $-1$ to get the last value, and $\ge0$ the index of the Node from which the value will be retrieved

```C
LinkedList* list1 = LinkedListConstructor();
LinkedList* list2 = LinkedListConstructor();

list1->insertInt(list1, 7, -1);
list1->insertDouble(list1, 3.14, -1);
list1->insertList(list1, list2, -1);

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

int* retrievedInt = list1->get(list1, 0);
printf("retrieved: %d\n", *retrievedInt);

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

LinkedList* retrievedList = list1->get(list1, -1);

// stack-allocated string
char list_print[retrievedList->getStrSize(retrievedList)];
printf("retrieved: %s\n", retrievedList->toString(retrievedList));

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list1->clear(list1);
list2->clear(list2);

free(list1);
free(list2);
```

or

```C
LinkedList* list1 = LinkedListConstructor();
LinkedList* list2 = LinkedListConstructor();

list1->insertInt(list1, 7, -1);
list1->insertDouble(list1, 3.14, -1);
list1->insertList(list1, list2, -1);

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

int removedInt;
list1->get(list1, &removedInt, 0);
printf("retrieved: %d\n", removedInt);

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

LinkedList* removedList;
list1->get(list1, removedList, -1);

// heap-allocated string
char* list_print = malloc(removedList->getStrSize(removedList));
printf("retrieved: %s\n", removedList->toString(removedList, list_print));
free(list_print);

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list1->clear(list1);
list2->clear(list2);

free(list1);
free(list2);
```

```
[7, 3.14, []]
retrieved: 7
[7, 3.14, []]
retrieved: []
[7, 3.14, []]
```

<br>

### _void_ LinkedList->changeDoublePrintPrecision(_LinkedList* list, unsigned short n_)

Changes the value of the variable that determines the amount of digits in the fractional portion of `double` values printed using [`list->toString()`](#char-linkedlist-tostringlinkedlist-list)

1. _`LinkedList* list`_: A pointer to the Linked List which will have the double print precision changed
2. _`unsigned short n`_: The new amount of digits in the fractional portion to be displayed when printing

```C
LinkedList* list = LinkedListConstructor();

list->insertDouble(list, 3.14159, -1);
list->insertDouble(list, 7.5, -1);
list->insertDouble(list, 2, -1);

list_print = list->toString(list);
printf("%s\n", list_print);
free(list_print);

list->changeDoublePrintPrecision(list, 5);

list_print = list->toString(list);
printf("%s\n", list_print);
free(list_print);

list->clear(list);
```

```
[3.14, 7.50, 2.00]
[3.14159, 7.50000, 2.00000]
```

<br>

### _char*_ LinkedList->toString(_LinkedList* list_)

Returns a string showing all values stored in the Linked List. The amount of digits in the fractional part of `double` values can be changed with [`LinkedList->changeDoublePrintPrecision()`](#void-linkedlist-changedoubleprintprecisionlinkedlist-list-unsigned-short-n).

1. _`LinkedList* list`_: A pointer to the list to be read

```C
LinkedList* list1 = LinkedListConstructor();
LinkedList* list2 = LinkedListConstructor();

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list1->insertInt(list1, 7, -1);
// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list1->insertDouble(list1, 3.14159, -1);
// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list1->insertChar(list1, 'V', -1);
// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list1->insertString(list1, "Neoni", -1);
// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list1->insertList(list1, list2, -1);
// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list1->clear(list1);

free(list1);
```

or

```C
LinkedList* list1 = LinkedListConstructor();
LinkedList* list2 = LinkedListConstructor();

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list1->insertInt(list1, 7, -1);
// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list1->insertDouble(list1, 3.14159, -1);
// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list1->insertChar(list1, 'V', -1);
// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list1->insertString(list1, "Neoni", -1);
// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list1->insertList(list1, list2, -1);
// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list1->clear(list1);

free(list1);
free(list2);
```

```
[]
[7]
[7, 3.14]
[7, 3.14, V]
[7, 3.14, V, Neoni]
[7, 3.14, V, Neoni, []]
```

<br>

### _void_ LinkedList.clear(_LinkedList* list_)

Recursively `free()`s every Node of the list.

1. _`LinkedList* list`_: A pointer to the list to be cleared

```C
LinkedList* list1 = LinkedListConstructor();
LinkedList* list2 = LinkedListConstructor();

list1->insertInt(list1, 7, -1);
list1->insertDouble(list1, 3.14159, -1);
list1->insertChar(list1, 'V', -1);
list1->insertString(list1, "Neoni", -1);
list1->insertList(list1, list2, -1);

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));

list1->clear(list1);

// stack-allocated string
char list_print[list1->getStrSize(list1)];
printf("%s\n", list1->toString(list1));
```

or

```C
LinkedList* list1 = LinkedListConstructor();
LinkedList* list2 = LinkedListConstructor();

list1->insertInt(list1, 7, -1);
list1->insertDouble(list1, 3.14159, -1);
list1->insertChar(list1, 'V', -1);
list1->insertString(list1, "Neoni", -1);
list1->insertList(list1, list2, -1);

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);

list1->clear(list1);

// heap-allocated string
char* list_print = malloc(list1->getStrSize(list1));
printf("%s\n", list1->toString(list1));
free(list_print);
```

```
[7, 3.14, V, Neoni, []]
[]
```

<br>
