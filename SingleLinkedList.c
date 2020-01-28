
#include <stdlib.h>

#include "SingleLinkedList.h"

/* This function is used to create the first element of the list 
 * does not take a pointer*/
LinkedList *createList()
{
    /*create a new free element before returning it*/
    LinkedList *ret = (LinkedList*) calloc(1, sizeof(LinkedList));
    return ret;
}

/* Warning the deleteList function cannot be used when data from the stack
 * has been set to the data portion of the list element */
int deleteList(LinkedList *lList)
{
    int ret = 0;
    //If this is a valid pointer
    if(lList != NULL)
    {
        //If there are multiple elements
        if(lList->next != NULL)
        {
            ListNode *curr = lList;
            //while there are more elements
            while(lList->next != NULL)
            {
                //If we have data free it first
                if(curr->data != NULL)
                {
                    free(curr->data);
                }
                lList = lList->next;
                free(curr);
                //go to the next element
                curr = lList;
            }
        }
        //If we have data then remove it
        if(lList->data != NULL) free(lList->data);
        //free the last element
        free(lList);
    }
    else ret = 1;
    return ret;
}

int insertFirst(LinkedList **lList, void *inData)
{
    int ret = 0;

    //If we have a valid pointer
    if(*lList != NULL)
    {
        //copy the pointer from the lList
        ListNode *tmp = *lList;
        *lList = (ListNode*) malloc(sizeof(ListNode));
        (*lList)->data = inData;
        //set the previous head to the next of our new head
        (*lList)->next = tmp;
    }
    else
    {
        *lList = createList();
        (*lList)->data = inData;
    }
    return ret;
}

int insertLast(LinkedList *lList, void *inData)
{
    int ret = 0;
    //If we have a valid pointer
    if(lList != NULL)
    {
        //start at the head
        ListNode *end = lList;
        //go to the end of the list
        while(end->next != NULL) end = end->next;
        //add a new one
        end->next = (ListNode*) malloc(sizeof(ListNode));
        end = end->next;
        end->next = NULL;
        end->data = inData;
    }
    else
    {
        lList = createList();
        lList->data = inData;
    }

    return ret;
}

void *getFirst(ListNode *firstNode)
{
    if(firstNode != NULL)
    {
        return firstNode->data; 
    }
    else return NULL;
}

void *getLast(LinkedList *curr)
{
    void *ret = NULL;
    if(curr != NULL)
    {
        while(curr->next != NULL)
        {
            curr = curr->next;
        }
        ret = curr->data;
    }
    return ret;
}

//You need to free the returned data after use manually
void *deleteFirst(LinkedList **lList)
{  
    void *ret = NULL;
    if(*lList != NULL)
    {
        ret = (*lList)->data;
        LinkedList *toDel = *lList;
        *lList = (*lList)->next;
        free(toDel);
    }
    return ret;
}

//You need to free the returned data after use manually
void *deleteLast(LinkedList *lList)
{
    void *ret = NULL;
    if(lList != NULL)
    {
       while(lList->next != NULL)
       {
            lList = lList->next;
       }
       ret = lList->data;
       free(lList);
    }
    return ret;
}

void printList(LinkedList *lList, void (*printEle)(void *data))
{
    while(lList != NULL)
    {
        if(lList->data != NULL)
        {
		    printEle(lList->data);
        }
		lList = lList->next;
    }
}
