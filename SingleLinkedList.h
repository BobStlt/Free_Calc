#ifndef LList
#define LList

/*Thease are all the type declearations needed for the use of SingleLinkedList.c*/

//generic list node
typedef struct ListNode
{
    void *data;
    struct ListNode *next;
} ListNode;

typedef ListNode LinkedList;

//Function declarations
LinkedList *createList();
int deleteList(LinkedList *lList);
int insertFirst(LinkedList **lList, void *inData);
int insertLast(LinkedList *lList, void *inData);
void *getFirst(ListNode *firstNode);
void *getLast(LinkedList *curr);
void *deleteFirst(LinkedList **lList);
void *deleteLast(LinkedList *lList);
void printList(LinkedList *lList, void (*printEle)(void *data));

#endif
