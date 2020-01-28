#include "../SingleLinkedList.h"
#include "../stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    puts("Testing stack fuctions:");

    //tests push
    puts("Testing push:");
    LinkedList *testList = NULL;
    char *testString = (char*) malloc(6*sizeof(char)); //5 + the \0
    strcpy(testString, "Hello");
    push(&testList, testString);
    testString = (char*) malloc(9*sizeof(char)); //7 + \n + \0
    strcpy(testString, ", world\n");
    push(&testList, testString);

    printf("Pushed 'Hello', and ', world', we should have the seccond string"
        "at the top and we have '%s'\n", (char*)top(testList)); //tests top
    puts("If that printed correctly then push and top worked!");

    //this is not how you would normally usr pop
    puts("Testing pop: ");
    char *tmpStr = pop(&testList);
    printf("If we pop we should get that same value %s\n", tmpStr);
    free(tmpStr); //deleteList will not remove this as it is outside the list
    tmpStr = pop(&testList);
    printf("and pop again we should get 'Hello' and we actually get: %s\n", tmpStr);
    free(tmpStr);

    puts("End of stack test");

    //we have already deleted all the elements so we should have no mem leaks
    
    return 0;
}
