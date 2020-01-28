#include "SingleLinkedList.h"
#include "stack.h"

inline int push(LinkedList **lList, void *inData)
{
    return insertFirst(lList, inData);
}

inline void *pop(LinkedList **lList)
{
    return deleteFirst(lList);
}

inline void *top(LinkedList *lList)
{
    return getFirst(lList);
}
