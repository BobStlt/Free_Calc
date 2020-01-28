#ifndef QUEUE
#define QUEUE

#include "SingleLinkedList.h"

int enqueue(LinkedList **lList, void *inData);
void *dequeue(LinkedList *lList);
void *peek(LinkedList *lList);

#endif
