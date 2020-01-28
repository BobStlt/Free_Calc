#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../SingleLinkedList.h"

/* This is the test code for the functions in SingleLinkedList.c */

int main(void)
{
    puts("Starting linked list testing:");

    LinkedList *testList = createList();
    //if we could not create the list successfully
    if(testList == NULL)
    {
       perror("Failed: Could not create a linked list!");
       return 1;
    }
    puts("Passed: successfully created a linked list!");

    //create and set the data pointer of the list item created by createList
    testList->data = (char*) malloc(6*sizeof(char));
    strcpy(testList->data, "First");  
    
    char *tempPtr = (char*) malloc(7*sizeof(char));
    strcpy(tempPtr, "Second");  
    int ret = insertLast(testList, tempPtr); //Test insert last
    if(strcmp(testList->next->data, "Second") != 0 || ret != 0)
    {
        perror("Failed: Insert last did not correctly create the second element.");
        deleteList(testList);
        return 2;
    }
   puts("Passed: Insert last!");

    tempPtr = (char*) malloc(6*sizeof(char));
    strcpy(tempPtr, "Third");  
    ret = insertFirst(&testList, tempPtr);
    if(strcmp(testList->data, "Third") != 0 || ret != 0)
    {
        perror("Failed: could not insert first!");
        deleteList(testList);
        return 3;
    }
    puts("Passed: successfully inserted first!");

    puts("Here is the list so far; we should have: 'Third', 'First', 'Second'");

    LinkedList *tmpListPtr = testList;
    while(tmpListPtr->next != NULL)
    {
        printf("%s ", (char*)tmpListPtr->data);
        tmpListPtr = tmpListPtr->next;
    }
    /* We now have the last pointer but we exited the loop before printing it
     * so we print it here */
    printf("%s ", (char*)tmpListPtr->data);
    puts("");

    ret = deleteList(testList);
    if(ret) //if deleteList returns 1
    {
        perror("Could not delete list");
        return 4;
    }
    puts("Passed: successfully deleted the list!");

    return 0;
}

