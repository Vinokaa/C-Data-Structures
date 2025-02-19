# C Data Structures Library

<!--<p>
  <a href="https://github.com/Vinokaa/CDataStructures/blob/master/README.pt-br.md"> 
    <img src="https://img.shields.io/badge/lang-pt--br-green.svg">
  </a>
</p>-->

<p align="center">
  <img width="550" height="400" src="https://github.com/user-attachments/assets/ea501ff2-3ff4-42a8-a610-db6db94b1f6b">
</p>


# Documentation

The libraries in this repository were made from an idea to make all data structures in C (famous last words), and make their usage feel as close as possible to an Object Oriented perspective.

<br>

## Linked List

### _LinkedList*_ LinkedListConstructor()

Initializes the linked list, allocating memory for it using `malloc()`, setting its size to `0` and its head to `NULL`.

Returns a pointer to the memory address where the Linked List was allocated.

```C
LinkedList* list = LinkedListConstructor();
```

<br>

### _void_ LinkedList.insertInt(_LinkedList* list, int n, int index_)

Adds one Node storing the _`int n`_ given as a parameter to the Linked List.

1. _`LinkedList* list`_: A pointer to the Linked List where _`int n`_ will be stored
2. _`int n`_: The int value to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
LinkedList list = LinkedListConstructor();

list.insertInt(&list, 3, 0);
list.insertInt(&list, 7, -1);
list.insertInt(&list, 2, 0);
list.insertInt(&list, 5, 1);

printf("%s\n", list.toString(&list));

list.clear(&list);
```

```
[2, 3, 5, 7]
```

<br>

### _void_ LinkedList.insertDouble(_LinkedList* list, double d, int index_)

Adds one Node storing the _`double d`_ given as a parameter to the Linked List.

The original fractional part of _`double d`_ won't be lost, but when printing using [`listToString()`](#char-listtostringlinkedlist-list), the fractional portion will be limited by a variable, which can be changed with [`LinkedList.changeDoublePrintPrecision()`](#void-linkedlistchangedoubleprintprecisionlinkedlist-list-unsigned-short-n).

1. _`LinkedList* list`_: A pointer to the Linked List where _`double d`_ will be stored
2. _`double d`_: The double value to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
LinkedList list = LinkedListConstructor();

list.insertDouble(&list, 3.14159, -1);
list.insertDouble(&list, 7.5, -1);
list.insertDouble(&list, 2, -1);

printf("%s\n", list.toString(&list));

list.clear(&list);
```

```
// Considering default floating point print precision
[3.14, 7.50, 2.00]
```

<br>

### _void_ LinkedList.insertChar(_LinkedList* list, char c, int index_)

Adds one Node storing the _`char c`_ given as a parameter to the Linked List.

1. _`LinkedList* list`_: A pointer to the Linked List where _`char c`_ will be stored
2. _`char c`_: The char to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
LinkedList list = LinkedListConstructor();

list.insertChar(&list, 'a', 0);
list.insertChar(&list, 'n', 0);
list.insertChar(&list, 'i', 0);
list.insertChar(&list, 'v', 0);

printf("%s\n", list.toString(&list));

list.clear(&list);
```

```
[v, i, n, a]
```

<br>

### _void_ LinkedList.insertString(_LinkedList* list, char* s, int index_)

Adds one Node storing the _`char* s`_ given as a parameter to the Linked List.

1. _`LinkedList* list`_: A pointer to the Linked List where _`char* s`_ will be stored
2. _`char* s`_: The string to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
LinkedList list = LinkedListConstructor();

list.insertString(&list, "AViVA", 0);
list.insertString(&list, "Matue", -1);
list.insertString(&list, "Neoni", 0);

printf("%s\n", list.toString(&list));

list.clear(&list);
```

```
[Neoni, AViVA, Matue]
```

<br>

### _void_ LinkedList.insertStruct(_LinkedList* list, void* s, int index_)

Adds one Node storing any type of struct given as a parameter to the Linked List.

1. _`LinkedList* list`_: A pointer to the Linked List where _`char* s`_ will be stored
2. _`void* s`_: The struct to be stored
3. _`int index`_: The index (from $-1$ to $list.size$), being $-1$ to insert at the end, $0$ at the start, and $\ge1$ the index of the Node when it gets inserted

```C
typedef struct Character{
  char* name;
  char* origin;
} Character;

Character* elliot = (Character*) malloc(sizeof(Character));
elliot->name = "Elliot Alderson";
elliot->origin = "Mr. Robot";

LinkedList list1 = LinkedListConstructor();
LinkedList list2 = LinkedListConstructor();

list1.insertStruct(&list1, &list2, -1);
list1.insertStruct(&list1, elliot, -1);

list2.insertInt(&list2, 7, -1);

printf("%s\n", list1.toString(&list1));

LinkedList* removedList = list1.get(&list1, 0);
printf("%s\n", removedList->toString(removedList));

Character* removedCharacter = list1.get(&list1, 1);
printf("%s from %s\n", removedCharacter->name, removedCharacter->origin);

list1.clear(&list1);
list2.clear(&list2);
```

```
[struct@000001582723A120, struct@00000237C7209FE0]
[7]
Elliot Alderson from Mr. Robot
```

<br>

### _void*_ LinkedList.remove(_LinkedList* list, int index_)

Removes a Node from the Linked List based on the index given.

Returns a _`void*`_ pointer to the removed value, which can be casted to its original type if needed.

1. _`LinkedList* list`_: A pointer to the Linked List from where the value will be removed
2. _`int index`_: The index (from $-1$ to $list.size-1$), being $-1$ to remove the last value, and $\ge0$ the index of the Node from which the value will be removed

```C
LinkedList list1 = LinkedListConstructor();
LinkedList list2 = LinkedListConstructor();

list1.insertInt(&list1, 7, -1);
list1.insertDouble(&list1, 3.14, -1);
list1.insertStruct(&list1, &list2, -1);

printf("%s\n", list1.toString(&list1));

int* removedInt = list1.remove(&list1, 0);
printf("removed: %d\n", *removedInt);

printf("%s\n", list1.toString(&list1));

LinkedList* removedList = list1.remove(&list1, -1);
printf("removed: %s\n", removedList->toString(removedList));

printf("%s\n", list1.toString(&list1));

list1.clear(&list1);
list2.clear(&list2);
```

```
[7, 3.14, struct@00000261EB80A080]
removed: 7
[3.14, struct@00000261EB80A080]
removed: []
[3.14]
```

<br>

### _void*_ LinkedList.get(_LinkedList* list, int index_)

Retrieves the value of a Node from the Linked List based on the index given, without removing its Node from the Linked List.

Returns a _`void*`_ pointer to the value, which can be casted to its original type if needed.

1. _`LinkedList* list`_: A pointer to the Linked List from where the value will be retrieved
2. _`int index`_: The index (from $-1$ to $list.size-1$), being $-1$ to get the last value, and $\ge0$ the index of the Node from which the value will be retrieved

```C
LinkedList list1 = LinkedListConstructor();
LinkedList list2 = LinkedListConstructor();

list1.insertInt(&list1, 7, -1);
list1.insertDouble(&list1, 3.14, -1);
list1.insertStruct(&list1, &list2, -1);

printf("%s\n", list1.toString(&list1));

int* retrievedInt = list1.get(&list1, 0);
printf("retrieved: %d\n", *retrievedInt);

printf("%s\n", list1.toString(&list1));

LinkedList* retrievedList = list1.get(&list1, -1);
printf("retrieved: %s\n", retrievedList->toString(retrievedList));

printf("%s\n", list1.toString(&list1));

list1.clear(&list1);
list2.clear(&list2);
```

```
[7, 3.14, struct@00000261EB80A080]
retrieved: 7
[7, 3.14, struct@00000261EB80A080]
retrieved: []
[7, 3.14, struct@00000261EB80A080]
```

<br>

### _void_ LinkedList.changeDoublePrintPrecision(_LinkedList* list, unsigned short n_)

Changes the value of the variable that determines the amount of digits in the fractional portion of `double` values printed using [`listToString()`](#char-linkedlisttostringlinkedlist-list)

1. _`LinkedList* list`_: A pointer to the Linked List which will have the double print precision changed
2. _`unsigned short n`_: The new amount of digits in the fractional portion to be displayed when printing

```C
LinkedList list = LinkedListConstructor();

list.insertDouble(&list, 3.14159, -1);
list.insertDouble(&list, 7.5, -1);
list.insertDouble(&list, 2, -1);

printf("%s\n", list.toString(&list));

list.changeDoublePrintPrecision(&list, 5);

printf("%s\n", list.toString(&list));

listClear(list);
```

```
[3.14, 7.50, 2.00]
[3.14159, 7.50000, 2.00000]
```

<br>

### _char*_ LinkedList.toString(_LinkedList* list_)

Returns a string showing all values stored in the Linked List. The amount of digits in the fractional part of `double` values can be changed with [`LinkedList.changeDoublePrintPrecision()`](#void-linkedlistchangedoubleprintprecisionlinkedlist-list-unsigned-short-n).

1. _`LinkedList* list`_: A pointer to the list to be read

```C
LinkedList list1 = LinkedListConstructor();
LinkedList list2 = LinkedListConstructor();

printf("%s\n", list1.toString(&list1));

list1.insertInt(&list1, 7, -1);
printf("%s\n", list1.toString(&list1));

list1.insertDouble(&list1, 3.14159, -1);
printf("%s\n", list1.toString(&list1));

list1.insertChar(&list1, 'V', -1);
printf("%s\n", list1.toString(&list1));

list1.insertString(&list1, "Neoni", -1);
printf("%s\n", list1.toString(&list1));

list1.insertStruct(&list1, &list2, -1);
printf("%s\n", list1.toString(&list1));

list1.clear(&list1);
```

```
[]
[7]
[7, 3.14]
[7, 3.14, V]
[7, 3.14, V, Neoni]
[7, 3.14, V, Neoni, struct@000001FD94F907F0]
```

<br>

### _void_ LinkedList.clear(_LinkedList* list_)

Recursively `free()`s every Node of the list.

1. _`LinkedList* list`_: A pointer to the list to be cleared

```C
LinkedList list1 = LinkedListConstructor();
LinkedList list2 = LinkedListConstructor();

list1.insertInt(&list1, 7, -1);
list1.insertDouble(&list1, 3.14159, -1);
list1.insertChar(&list1, 'V', -1);
list1.insertString(&list1, "Neoni", -1);
list1.insertStruct(&list1, &list2, -1);

printf("%s\n", list1.toString(&list1));

list1.clear(&list1);

printf("%s\n", list1.toString(&list1));
```

```
[7, 3.14, V, Neoni, struct@000002335960A120]
[]
```

<br>

## Work In Progress
