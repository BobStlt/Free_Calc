/* 
 *  04/04/2018 Is this when it was last edited or the date of creation?
 *  last edited 3rd Aug 2019
 * 
 *  Freecalc ver 2 by Perrin Smith
 * 
 *  Theory of operation:
 *  User input is taken as one string or cmd args and coverted from infix to post fix then
 *  processed into the final answer.
 *  In the case of cmd args the args are serched for
 *  program controll switches, thease include TODO
 *  If no switches are found then the cmd args are linked together as one string and
 *  routed through the normal calculation methods.
 *
 *  Once one answer has been calculated the pointer to that answer is retained and then
 *  reinserted if the new equation is determined to have ans as one of the equation elements.
 *
 *  The program may be exited by entering 'q', 'Q', 'Quit', 'quit' or 'QUIT'.
 *
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#include "SingleLinkedList.h"
#include "calcFunctions.h"
#include "inputOutput.h"

//TODO: mem leak when entering something starting with '+'

typedef enum {USEAGE=1, LICENSE} cmdflag; //for storing which cmd flag has been selected

const char *progName;

void outputPrgInfo(cmdflag flag)
//For outputting license and help info
{
   if(flag == LICENSE)
   {
        FILE *license = fopen("/usr/share/fcalc/LICENSE", "r");
        if(license != NULL)
        {
            int tmp;
            tmp = fgetc(license);
            while(tmp != EOF)
            {
                printf("%c", (char)tmp);
                tmp = fgetc(license);
            }
            fclose(license);
        }
        else perror("Sorry I could not show you the license.\n"
                     "It may be missing or may have been renamed\n");
   }
   //if we get a USEAGE flag or anthing else
   else
   {
        printf("To use fcalc you can either just run it with %s or you can put it into\n"
                "your equation into the command line for example: %s 4+4\n"
                "if you need to see the license you can enter the license flag -l or if\n"
                "you use the -u flag you can show this screen.\n", progName, progName);
   }
}

int main(int argc, char **args)
{
    int returnVal = 0;
    /* This stores the elemets of our equation while and after the equation
     * string is processed by processEquationString
     * before the elements are processed by processPostfixEquation */
    //a linked list with all the parsed elements of the equation the user entered
    LinkedList *equationList = NULL;    
    char *eqaStr = NULL; //The string containing equation the user entered
    double *ansPtr = NULL; //Our answer is returned as a pointer, so we can reuse it in other equations
    int exit = 0;
    progName = args[0]; //save the progam name as a global variable


    if(argc >= 2)
    {
        char **cmdArgs = args;
        cmdArgs++; //skip over the prog name
        //parse cmd args, we only scan the start of each of the entered strings for flags.
        //TODO: if your add support for - to denote a negative number remember your equations could start with '-'
        for(int i = 0; i < argc-1; i++) //we start at 0 as we already skipped the prog name
        {
            //if we have the indicator of a command flag
            if(**cmdArgs == '-')
            {
                //capture what is after the '-'
                char tmpCmdArg = *((*cmdArgs)+1);
                //if we have "--" check for the seccond '-'
                if(tmpCmdArg == '-')
                {
                    (*cmdArgs)++; //skip past the extra '-'
                }
                
                //if we don't have a "--" nor simply have a negative number
                if(!isdigit(tmpCmdArg))
                {
                    (*cmdArgs)++; //skip past the first '-'
                }
                
                //if we have a letter to denote a flag
                if(isalpha(**cmdArgs))
                {
                    char tmpFlag = **cmdArgs;
                    if(tmpFlag == 'l')
                    {
                        tmpFlag -= (char) 32; //make the flag an 'L' so we test true below
                    }
                    //if we have an 'L' we + the defference between 'L' and 'l'
                    if(tmpFlag + 32 == 'l')
                    {
                        outputPrgInfo(LICENSE); //If we have an l flag print out the license
                        return 0;
                    }
                    else
                    {
                        outputPrgInfo(USEAGE); //If we get a bad flag or a 'u' flag to denote useage print the useage
                        return 0;
                    }
                }
            }
            //if we have a number or symbol as the first item in the string we have an equation element so we add it
            //we have to use 39 to represent ' as ''' isn't recognised by gcc
            //TODO: change 39 to '\'' and test
            else if(isEqaElement(**cmdArgs) && (**cmdArgs != (char) 39)) 
            {
                if(eqaStr == NULL)
                {
                    //Set the last to delimit the end of the strin
                    eqaStr = (char*) malloc(EQUATION_STR_LEN*sizeof(char));
                    eqaStr[EQUATION_STR_LEN] = '\0';
                }
                strcat(eqaStr, *cmdArgs);
            }
            else
            {
                outputPrgInfo(USEAGE); //tell the user what the cmd args are for and how to use the program
                return 0;
            }
            cmdArgs++; //go to the next arg
        }
    }

    //if we didn't have any args or didn't parse any equation from the args 
    if(eqaStr == NULL)
    {
        //Set the last to delimit the end of the strin
        eqaStr = (char*) malloc(EQUATION_STR_LEN*sizeof(char));
        //get the user equation string
        getUserEquation(eqaStr); 
        //If the user wants to quit
        if(isQuitString(eqaStr))
        {
            exit = true;
        }
    }

    /* currRetVal stores the return value for the current iteration for the
     * event loop that way it isnt cleared whenever a new loop starts*/
    int currRetVal = 0;
    
    //continuously get user input and calc the answer until they quit
    while(!exit)
    {
        currRetVal = processEquationStr(&equationList, eqaStr, ansPtr);

        if(currRetVal)
        {
            perror("ERROR: could not process the equation string");
            returnVal = currRetVal;
        }
        else
        {
            ansPtr = processPostfixEqa(equationList);
            /* There is nothing on the stack but as the memory
            * is not cleared on free the stack logic thinks
            * there is still data. */
            equationList = NULL;
            if(ansPtr == NULL)
            {
                perror("ERROR: could not process equation");
                returnVal = 2;
            }
        }

        if(!currRetVal)
            printResault(ansPtr);

        getUserEquation(eqaStr);
        //If the user wants to quit
        if(isQuitString(eqaStr))
        {
            exit = true;
        }
    }

    if(ansPtr != NULL)
    {
        free(ansPtr);
        ansPtr = NULL;
    }

    if(equationList != NULL) free(equationList);
    if(ansPtr != NULL) free(ansPtr);
    if(eqaStr != NULL) free(eqaStr);
    return returnVal; 
}
