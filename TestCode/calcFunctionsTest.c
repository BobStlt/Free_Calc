#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../calcFunctions.h"
#include "../SingleLinkedList.h"
#include "../stack.h"

int printEquationElements(LinkedList *equationList);
double testProcessPostfix(double num1, double num2, char sym);
double test3ProcessPostfix(double num1, double num2, double num3, char sym1, char sym2);
double testProcessEquationStr(char *equation, double expectedRes);
void printListElement(EquationElement *toPrint);

//A pointer to printLinkedList so we can use it with SingleLinkedLists' printList(list, callback) 
static void (*printListEle)(EquationElement *toPrint) = &printListElement;

int main(void)
{
    //test calcUserAnswer
    printf("Testing calcUserAnswer:\n");
    printf("testing neg numbers:\n");
    printf("-42 + 43 = %.0f\n", calcUserAnswer(-42, '+', 43));
    printf("40 - 80 = %.0f\n", calcUserAnswer(40, '-', 80));
    printf("-200 / 2 = %.0f\n", calcUserAnswer(-200, '/', 2));
    printf("100 * -1 = %.0f\n", calcUserAnswer(100, '*', -1));
    printf("-2^5 = %.0f\n", calcUserAnswer(-2, '^', 5));
    printf("-2^6 = %.0f\n", calcUserAnswer(-2, '^', 6));
    printf("-16^3 = %.0f\n", calcUserAnswer(-16, '^', 3));
    printf("testing pos numbers:\n");
    printf("80 + 80 = %.0f\n", calcUserAnswer(80, '+', 80));
    printf("2^5 = %.0f\n", calcUserAnswer(2, '^', 5));
    printf("2^6 = %.0f\n", calcUserAnswer(2, '^', 6));
    printf("16^3 = %.0f\n", calcUserAnswer(16, '^', 3));

    //test parsing numbers
    puts("\nTesting the number parser:");
    
    char *toParse = (char*)malloc(80*sizeof(char));
    char *toParse0Pos = toParse;

    strcpy(toParse, "16");
    double parseAns = 0;
    double expAns = 16;
    parseAns = parseNumber(&toParse);
    printf("Input was %.2f output %.2f %s\n",expAns ,parseAns, expAns == parseAns ? "PASSED":"FAILED");

    //should stop at the +
    strcpy(toParse, "2+2");
    parseAns = 0;
    expAns = 2;
    parseAns = parseNumber(&toParse);
    printf("Input was %.2f output %.2f %s\n",expAns ,parseAns, expAns == parseAns ? "PASSED":"FAILED");

    strcpy(toParse, "2.2+4");
    parseAns = 0;
    expAns = 2.2;
    parseAns = parseNumber(&toParse);
    printf("Input was %.2f output %.2f %s\n",expAns ,parseAns, expAns == parseAns ? "PASSED":"FAILED");

    strcpy(toParse, "(2+2)");
    parseAns = 0;
    expAns = 0;
    parseAns = parseNumber(&toParse);
    printf("Input was %.2f output %.2f %s\n",expAns ,parseAns, expAns == parseAns ? "PASSED":"FAILED");

    strcpy(toParse, "0.05");
    parseAns = 0;
    expAns = 0.05;
    parseAns = parseNumber(&toParse);
    printf("Input was %.2f output %.2f %s\n",expAns ,parseAns, expAns == parseAns ? "PASSED":"FAILED");

    strcpy(toParse, "10.10");
    parseAns = 0;
    expAns = 10.10;
    parseAns = parseNumber(&toParse);
    printf("Input was %.2f output %.2f %s\n",expAns ,parseAns, expAns == parseAns ? "PASSED":"FAILED");

    strcpy(toParse, "12.12");
    parseAns = 0;
    expAns = 12.12;
    parseAns = parseNumber(&toParse);
    printf("Input was %.2f output %.2f %s\n",expAns ,parseAns, expAns == parseAns ? "PASSED":"FAILED");

    strcpy(toParse, "1.0/2");
    parseAns = 0;
    expAns = 1.00;
    parseAns = parseNumber(&toParse);
    printf("Input was %.2f output %.2f %s\n",expAns ,parseAns, expAns == parseAns ? "PASSED":"FAILED");

    free(toParse0Pos);

    /* calc the user answer from the previously converted postfix using
     * processPostfixEqa */
    puts("\nTesting processPostfixEqa:");
    puts("5.0+2.0 should be 7.0");
    double ans = testProcessPostfix(5.0, 2.0, '+');
    printf("The answer is: %.2lf\n", ans);
    if(ans == 7.0) puts("PASSED");
    else puts("FAILED");

    // 144/12=12
    puts("144/12 should be 12.0");
    ans = testProcessPostfix(12.0, 144.0, '/');
    printf("The answer is: %.2lf\n", ans);
    if(ans == 12.0) puts("PASSED");
    else puts("FAILED");
    
    // 1/2=0.5
    puts("1/2 should be 0.5");
    ans = testProcessPostfix(2.0, 1.0, '/');
    printf("The answer is: %.2lf\n", ans);
    if(ans == 0.5) puts("PASSED");
    else puts("FAILED");

    // 1 + 2/1 = 3 
    puts("1+2/1 should be 1.5");
    ans = test3ProcessPostfix(1.0, 2.0, 1.0, '/', '+');
    printf("The answer is: %.2lf\n", ans);
    if(ans == 3) puts("PASSED");
    else puts("FAILED");

    puts("\nTesting processEquationString: ");

    //Test basic addition
    testProcessEquationStr("2+5", 7);

    //Test bimdas, if it reads the eqation correctly the ans would be 6 else 8
    testProcessEquationStr("2+2*2", 6);

    //Test the use of brackets should be 8
    testProcessEquationStr("2*(2+2)", 8);
    testProcessEquationStr("2*((1*2)+2)", 8);
    
    puts("\nTesting multy digit and floating point:");

    testProcessEquationStr("16*16", 256); //test multy digit
    testProcessEquationStr("1.0/2", 0.5); //test floating point
    testProcessEquationStr("10.1/2", 5.05);

    puts("\nEND OF TESTS");
    return 0;
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

//Test the full equation processing system
double testProcessEquationStr(char *equation, double expectedRes)
{
    double *tmpAns;
    LinkedList *equationQueue = NULL;
    processEquationStr(&equationQueue, equation);
	printf("This is what we have in the stack:\n");
	printList(equationQueue, printListEle);
    tmpAns = processPostfixEqa(equationQueue);
    printf("The answer is: %.2lf\n", *tmpAns);
    if(*tmpAns == expectedRes) puts("PASSED");
    else puts("FAILED");
    double ret = *tmpAns;
    free(tmpAns);
    return ret;
}

/* takes two numbers puts them in a reverse polish notation stack and runs
 * processPostfixEqa */
double testProcessPostfix(double num1, double num2, char sym)
{
    EquationElement *tmpEquElement = (EquationElement*) 
        malloc(sizeof(EquationElement));
    tmpEquElement->data.f = num2;
    tmpEquElement->type = number;
    LinkedList *testEquQueue = NULL;
    push(&testEquQueue, tmpEquElement);
    printf("Pushed %.0f of type %d\n", tmpEquElement->data.f, 
        tmpEquElement->type);

    //print out what we have now
    printEquationElements(testEquQueue);

    tmpEquElement = (EquationElement*) malloc(sizeof(EquationElement));
    tmpEquElement->data.f = num1;
    tmpEquElement->type = number;
    push(&testEquQueue, tmpEquElement);
    printf("Pushed %.0f of type %d\n", tmpEquElement->data.f, 
        tmpEquElement->type);

    printEquationElements(testEquQueue);

    tmpEquElement = (EquationElement*) malloc(sizeof(EquationElement));
    tmpEquElement->data.c = sym;
    tmpEquElement->type = symbol;
    push(&testEquQueue, tmpEquElement);
    printf("Pushed %c of type %d\n", tmpEquElement->data.c, 
        tmpEquElement->type);

    printEquationElements(testEquQueue);

    double *ans = processPostfixEqa(testEquQueue);
    double ret = *ans;
    free(ans);

    //all mallocs should have been freed so we should not need to use deleteList()
    return ret;
}

double test3ProcessPostfix(double num1, double num2, double num3, char sym1, char sym2)
{
    EquationElement *tmpEquElement = (EquationElement*) 
        malloc(sizeof(EquationElement));
    tmpEquElement->data.f = num3;
    tmpEquElement->type = number;
    LinkedList *testEquQueue = NULL;
    push(&testEquQueue, tmpEquElement);
    printf("Pushed %.0f of type %d\n", tmpEquElement->data.f, 
        tmpEquElement->type);

    //print out what we have now
    printEquationElements(testEquQueue);

    tmpEquElement = (EquationElement*) malloc(sizeof(EquationElement));
    tmpEquElement->data.f = num2;
    tmpEquElement->type = number;
    push(&testEquQueue, tmpEquElement);
    printf("Pushed %.0f of type %d\n", tmpEquElement->data.f, 
        tmpEquElement->type);

    printEquationElements(testEquQueue);

    tmpEquElement = (EquationElement*) malloc(sizeof(EquationElement));
    tmpEquElement->data.f = num1;
    tmpEquElement->type = number;
    push(&testEquQueue, tmpEquElement);
    printf("Pushed %.0f of type %d\n", tmpEquElement->data.f, 
        tmpEquElement->type);

    printEquationElements(testEquQueue);

    tmpEquElement = (EquationElement*) malloc(sizeof(EquationElement));
    tmpEquElement->data.c = sym1;
    tmpEquElement->type = symbol;
    push(&testEquQueue, tmpEquElement);
    printf("Pushed %c of type %d\n", tmpEquElement->data.c, 
        tmpEquElement->type);

    printEquationElements(testEquQueue);

    tmpEquElement = (EquationElement*) malloc(sizeof(EquationElement));
    tmpEquElement->data.c = sym2;
    tmpEquElement->type = symbol;
    push(&testEquQueue, tmpEquElement);
    printf("Pushed %c of type %d\n", tmpEquElement->data.c, 
        tmpEquElement->type);

    printEquationElements(testEquQueue);

    double *ans = processPostfixEqa(testEquQueue);
    double ret = *ans;
    free(ans);

    //all mallocs should have been freed so we should not need to use deleteList()

    return ret;
}

int printEquationElements(LinkedList *equationList)
{
    //If the list was never used
    if(equationList == NULL)
    {
        return 1;
    }

    int i = 1;
    EquationElement *currentElement = equationList->data;
    while(equationList != NULL)
    {
        printf("Element %d is a %s and has the value of ", i,
                currentElement->type == number ? "number" : "symbol");
        if(currentElement->type == symbol)
        {
            printf("%c\n", currentElement->data.c);
        }
        else if(currentElement->type == number)
        {
            printf("%.2lf\n", currentElement->data.f);
        }

        equationList = equationList->next;
        if(equationList != NULL)
        {
            currentElement = equationList->data;
        }
        i++;
    }
    return 0;
}
