#include <stdio.h>
#include "inputOutput.h"


//TODO: impliment a find invalid strings / find exit condition
void getUserEquation(char *eqaStr)
{
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
