#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "calcFunctions.h"
#include "SingleLinkedList.h"
#include "stack.h"

/* TODO:Add a 'unparse number' function and a function to allow
 * the replacement of the string 'ans' inside an equation
 * for use after at least one equation has been calculated
 * so as to allow a user to incoperate thair previous
 * answer into their next equation */

//This is only used once so it is faster to make inline
static inline double calcPower(double first, double second)
//use the first variable so you can use a preveous resault
{
    long double ans = 1;
    if(second != 0)
    //any thing to the power of 0 is 1
    {
        for(int i = 0; i < second; i++)
        {
            ans *= first;
        }
    }
    return ans;
}

//use to calc the answer to each part of the equation
double calcUserAnswer(double first, char operand, double second)
{

    double ans = 0;

    switch(operand)
    {
        case '*':
            ans = first * second;
            break;
            
        case '/':
            ans = first / second;  
            break;
            
        case '+':
            ans = first + second;
            break;
            
        case '-':
            ans = first - second;
            break;
            
        case '^':
            if(0 <= second){
                ans = calcPower(first, second);
            }
            else
            {
                ans = calcPower(first, second);
                ans = 1 / ans;
            }
            break;
    }
    
    return ans;
}

//Evaluetes and inserts an operand into an operand queue
static char *optToStack(int prec1, char *theOpt, LinkedList **operandStack, LinkedList **equationQueue)
{
    /* stop stops the while loop when = 1
     * prec1 and prec2 are the precidence levels of both 
     * the operands we're currently looking at */
    int stop = 0, prec2; //prec2 for the seccond op
    char opTmp;
    EquationElement *dataTmp;
    while(stop != 1)
    {
        if(*operandStack != NULL)
        {
           opTmp = *(char*)(*operandStack)->data; //the top item on the operand stack is
           if(opTmp == '+' || opTmp == '-') //+ and - have a prec of 1
           {
                prec2 = 1;
           }
           else if(opTmp == '*' || opTmp == '/')
           {
                prec2 = 2; //if it's * or / then it has a prec of 2
           }

           /* if our new operand has a higher precidence and should be processed first
            * but if we have a bracket act as if we are dealing with a new equation */
           if(prec1 > prec2 || opTmp == '(')
           {
                push(operandStack, theOpt);
                stop++;
           }
           else //lower precidence
           {
                dataTmp = (EquationElement*)malloc(sizeof(EquationElement));
                dataTmp->data.c = *((char*)pop(operandStack));
                dataTmp->type = symbol;
                push(equationQueue, dataTmp);
           }
        }
        else //If we have nothing on the stack then the current operand automatically has the highest prescidence
        {
            push(operandStack, theOpt);
            stop++;
        }
    }
    return 0;
}

//place all current operands onto the equation queue stop if thair inside a pair of brackets
static void insertOpts(LinkedList **equationQueue, LinkedList **operandStack)
{
    short stop = 0;
    while(*operandStack != NULL && stop == 0)
    {
        if(*((char*)((*operandStack)->data)) == '(')
        {
            pop(operandStack);
            stop++;
        }
        else
        {
            EquationElement *dataTmp = (EquationElement*)malloc(sizeof(EquationElement));
            dataTmp->data.c = *((char*)pop(operandStack));
            dataTmp->type = symbol;
            push(equationQueue, dataTmp);
        }
    }
}

//This does manipulate the equation position
double parseNumber(char **equation)
{
    int firstRun = 1;
    /* shift factor denotes how many desimal places each digit below the desimal place
     * should go */
    int numDecPlaces = 0, shiftFactor; 
    double ans = 0, subAns = 0;
    char *numEnd; //the end of the number

    if(*equation != NULL)
    {
        //Parse numbers before the desimal point
        while((char)**equation >= '0' && (char)**equation <= '9')
        {
            if(firstRun)
            {
                //the charactor - the start of numbers in the ascii table
                ans += (double)(**equation)-'0';
            }
            else
            {
                //the ans moved up by a decimal place + the next value
                ans = ans*10 + (**equation)-'0';
            }
            if(firstRun) firstRun--;
            (*equation)++;
        }

        //if we actually have a floating point number
        if((char)**equation == '.')
        {
            (*equation)++; //move past the desimal point

            //If we had notheing after the desimal place then do nothing
            if((char)**equation >= '0' && (char)**equation <= '9')
            {
                //then after the desimal point
                while((char)**equation >= '0' && (char)**equation <= '9')
                {
                    numDecPlaces++;
                    (*equation)++;
                }
                (*equation)--; //go back to the last digit
                numEnd = *equation; //keep where the end of the number is
                
                //while we havent gotten back to the desimal place put in the charactors
                for(int i = numDecPlaces; i > 0; i--)
                {
                    shiftFactor = calcPower(10, i);
                    subAns += (double)((**equation)-'0')/(double)shiftFactor; //where i is the placement
                    (*equation)--;//go to the next desimal place
                }
                
                *equation = numEnd;//place the equation processing pointer back at the end of the number
            }
        }
        else (*equation)--; //put it back to the last digit so the processEquationString does not have to be changed
    }
    return (ans + subAns); //add the fractional part and the whole part together
}

//convert string to postfix
int processEquationStr(LinkedList **equationQueue, char *inEquation)
{
    /* This array is for the cases when we need to insert extra chars into the
     * equation for example if we have a number then a bracket, this indicates
     * a maltiplication in this case we must add in the '*' char to the stack
     * so the parser can create the postfix equation correctly */
    /* '*' for between a num and '(' or ')'. '0' for between a '(' and '-' or
     * when we have a '-' at the start of the line */
    static const char addInRuleChars[] = {'*', '(', ')', '0'};
    bool zeroMinusBefore = false;
    char* equation = inEquation;
    LinkedList *operandStack = NULL; //to hold our symbols while we work out thair ordering.
    //This is for wrighting our data to the equation queue if we're not using the optToStack func
    EquationElement *dataTmp;
    int pos = 0;
    while(*equation != '\0')
    {
        switch(*equation)
        {
            case '+': //+ and - have the same presidence
            case '-':
                /* This is to handle the case where we have a '-' not next to a number */
                if(*equation == '-')
                {
                    /* If we are not past the start of the string or don't have
                     * a number before where the '-' is or what we have before
                     * is not a ')' then we have nothing before our '-' */
                    if((!pos) ||
                        (((*(equation-1) < '0') || (*(equation-1) > '9')) &&
                        (*(equation-1) != ')')))
                    {
                        /* Add (0 - to the stack if there is nothing next to a zero
                         * not including a ')' */
                        //Add a '('
                        optToStack(2, &addInRuleChars[1], &operandStack, equationQueue);

                        //add a '0' to the equation queue
                        dataTmp = (EquationElement*)malloc(sizeof(EquationElement));
                        dataTmp->data.f = 0.0;
                        dataTmp->type = number;
                        push(equationQueue, dataTmp);

                        //add the '-'
                        optToStack(1, equation, &operandStack, equationQueue);
                        /* sets the flag that allows us to - when it comes to the
                         * next number - know when to add a ')' after the number */
                        zeroMinusBefore = true;
                    }
                    else
                    {
                        optToStack(1, equation, &operandStack, equationQueue);
                    }
                }
                else
                {
                    optToStack(1, equation, &operandStack, equationQueue);
                }
                break;

            case '*': //same for * and /
            case '/':
                optToStack(2, equation, &operandStack, equationQueue);
                break;

            /* This is just the start of a bracketed section so just
             * push it so we know for later */
           case '(': //if the previous char is a number then we are maltiplying
                if(pos && (*(equation-1) >= '0' && *(equation-1) <= '9'))
                {
                    /* addInRuleChars[0] is '*', thus we add a
                     * '*' between the num and the '(' */
                    optToStack(2, &addInRuleChars[0], &operandStack, equationQueue);
                }
                push(&operandStack, equation);
                break;

           case ')':
                insertOpts(equationQueue, &operandStack);
                
                //if we have a number directly after the ')' we need to add '*'
                if(*(equation+1) >= '0' && *(equation+1) <= '9')
                {
                    /* addInRuleChars[0] is '*', thus we add a
                     * '*' between the num and the '(' */
                    optToStack(2, &addInRuleChars[0], &operandStack, equationQueue);
                }
                break;
            
           default: //If we just have a number
                dataTmp = (EquationElement*)malloc(sizeof(EquationElement));
                //convert the char to int
                dataTmp->data.f = parseNumber(&equation);
                dataTmp->type = number;
                push(equationQueue, dataTmp);
                
                //If we had a '-' on it's own before this number
                //The handling of a '-' by it's self, is done in the '-' section
                if(zeroMinusBefore)
                {
                    /* Emulate a ')' to close the bracket created if a '-' was
                     * found to be on it's own */
                    insertOpts(equationQueue, &operandStack);
                }
                break;
        }
        equation++; //set the pointer to the charactor ready for the next iteration
        //if the first pass has just ended set the firstChar flag to false
        pos++;
    }

    //Put the rest of the operands onto the stack
    insertOpts(equationQueue, &operandStack);

    return 0;
}

//post fix to ans this should go to the current equations lists answer
//This function is destructive
double *processPostfixEqa(LinkedList *inQueue)
{
    EquationElement *tmpEle = NULL;
    LinkedList *questionQueue = NULL;
    double *resault = (double*) malloc(sizeof(double));

    //so if we get a bad input we don't crash
    if(inQueue != NULL)
    {
        /* Flip the stack so we don't have to go the end of the linked list
         * each time we want the next value, we need to see the stack
         * from the other end. */
        while(inQueue != NULL)
        {
            tmpEle = (EquationElement*) pop(&inQueue);
            push(&questionQueue, tmpEle);
        }
        
        //cursor for the current element to process
        EquationElement *qQcurr = questionQueue->data; 
        LinkedList *processingStack = NULL;
        tmpEle = NULL; //make sure we're not pointing to something in the equstionQueue

        double firstParram, secParram;
        char sym;

        /* We should only have one pice of data in the question queue
         * after this has run, this will be removed when we pop it in
         * the return statement. */
        while(questionQueue != NULL)
        {
            if(qQcurr->type == number) //if we have a number push to stack
            {
                //we send it the data
                push(&processingStack, pop(&questionQueue)); 
            }
            //it's a symbol whose command we must execute
            else if(qQcurr->type == symbol) 
            {
                /* The numbers are receved in reverse order as they
                 * are put onto a seccond stack (the processing stack) */
                /* get the pointer to the data from the equation element within the
                 * stack and derefference it*/
                sym = qQcurr->data.c;
                free(pop(&questionQueue)); //remove the symbol from the stack
                tmpEle = (EquationElement*) pop(&processingStack);
                secParram = tmpEle->data.f;
                free(tmpEle);
                tmpEle = (EquationElement*) pop(&processingStack);
                firstParram = tmpEle->data.f;
                free(tmpEle);
                //This must be done so it's stored in memory and thus can get the address
                double tmpRes = calcUserAnswer(firstParram, sym, secParram);
                tmpEle = (EquationElement*) malloc(sizeof(EquationElement));
                tmpEle->data.f = tmpRes;
                tmpEle->type = number;
                push(&processingStack, tmpEle); //push the answer of that operation back to the stack
            }
            if(questionQueue != NULL)
            {
                qQcurr = questionQueue->data; //get the next data element

            }
            /* We don't need to go to the next element in questionQueue as
             * we already would have by poping it off the stack */
        }
        tmpEle = pop(&processingStack);
        *resault = tmpEle->data.f;
        free(tmpEle);
    }
    else { *resault = 0; } //set resault as error state

    return (resault); //the answer should be the only thing on the stack at this point
}

inline int isEqaElement(char inElement)
{
    if((inElement == '(' ||
        inElement == ')') ||
        (inElement >= '0' && inElement <= '9') ||
        inElement == '+' ||
        inElement == '*' ||
        inElement == '/')
    {
        return 1;
    }
    else return 0;
}
