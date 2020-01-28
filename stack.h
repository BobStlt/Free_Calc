#ifndef STACK
#define STACK

#include "SingleLinkedList.h"

int push(LinkedList **lList, void *inData);
void *pop(LinkedList **lList);
void *top(LinkedList *lList);

#endif
