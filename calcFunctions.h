#ifndef calcFunction
#define calcFunction

#include <stdlib.h>
#include "stack.h"
#include "SingleLinkedList.h"

//Definitions of the functions in functions.c

typedef struct equationData
{
    char *originalQuestion;
    LinkedList *questionQueue;
    long double ans;
} Equation;

typedef enum {number, symbol} ElementType;

typedef struct EquationElement
{
    union Data
    {
        double f;
        char c;
    } data;
    ElementType type;

} EquationElement;

double calcUserAnswer(double first, char operand, double second);

//This takes a black list and your equation you want to convert into postfix
int processEquationStr(LinkedList **equationQueue, char *inEquation);

//This takes your converted post fix equaiton and returns the answer
double *processPostfixEqa(LinkedList *questionQueue);

/* Takes a string pointer that points to the 
 * start of the number and it will find the number
 * and convert it to a double */
double parseNumber(char **equation);

int isEqaElement(char inElement);


#endif
