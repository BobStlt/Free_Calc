#include "SingleLinkedList.h"
#include "queue.h"

int enqueue(LinkedList **lList, void *inData)
{
    return insertFirst(lList, inData);
}

void *dequeue(LinkedList *lList)
{
    return deleteLast(lList);
}

void *peek(LinkedList *lList)
{
    return getLast(lList);
}
