#include <stdio.h>
#include <string.h>
#include "inputOutput.h"


//TODO: impliment a find invalid strings / find exit condition
//For testing weather the user input is valid
void testInputValidity(char *eqaStr)
{

}

void getUserEquation(char *eqaStr)
{
    //clear the equation string so it can be reused
    memset(eqaStr, 0, EQUATION_STR_LEN);

    char tmpChar = 0xff;
    printf(":");

    int i;
    for(i = 0; i < EQUATION_STR_LEN; i++)
    {
        tmpChar = getchar();

        if(tmpChar == '\n') break; //If the user presses enter

        if(tmpChar != ' ') //Ignore spaces
        {
            *eqaStr = tmpChar;
            eqaStr++;
        }

    }
    *eqaStr = '\0';
    
}

void printResault(double *resault)
{
    //This is only a stub
    printf("= %.2f\n", *resault);
}
