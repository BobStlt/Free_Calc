#include <stdlib.h>
#include <stdio.h>
#include "calcFunctions.h"
#include "SingleLinkedList.h"

void printListElement(EquationElement *toPrint);

static void (*printListEle)(EquationElement *toPrint) = &printListElement;

int main(int argc, char **args)
{
    LinkedList *equationList = NULL;
    printf("Enter your calc: ");
    char tmpin = '~'; //~ is a place holder that is not \n or \0
    char *inEquation = (char*) malloc(80*sizeof(char));
    tmpin = getchar();
    int i;
    for(i = 0; i < 80 && tmpin != '\n'; i++)
    {
        inEquation[i] = tmpin;
        tmpin = getchar();
    }
    i++;
    inEquation[i] = '\0';
    processEquationStr(&equationList, inEquation, NULL);
    printList(equationList, printListEle);
    double *ans;
    ans = processPostfixEqa(equationList);
    printf("here is the answer: %.2f\n", *ans);
    free(ans);
    free(inEquation);
}

//For use with linked lists' printList  
void printListElement(EquationElement *toPrint)
{
	if(toPrint->type == number)
	{
		printf("This element is a number and has the value of %.2f\n", toPrint->data.f);
	}
	else
	{
		printf("This element is a symbol and has the value of %c\n", toPrint->data.c);
	}
}
