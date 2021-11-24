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

typedef struct {
    const int          pArgc;
    const char** const pArgs;
    const char*  const progName;
} prog_info_t;

typedef struct{
    bool  quit;
    char* eqa;
} chp_or_done;

typedef enum {USEAGE=1, LICENSE} cmdflag; //for storing which cmd flag has been selected

prog_info_t processCmdArgs(int argc, char **args)
{
    const char *progName = *args;
    const int pArgc = argc-1;
    const char ** const pArgs = args+1;

    prog_info_t ret = {
        pArgc,
        pArgs,
        progName
    };

    return ret;
}

void outputPrgInfo(cmdflag flag, const char *const progName)
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

/* Takes the cmd line args and processes them.
 * We either output the infomation requested or return a processed a equation line. */
chp_or_done handleArgs(int argc, char **args)
{
    prog_info_t processedArgs = processCmdArgs(argc, args);
    char *eqaStr = NULL; //The string containing equation the user entered
    if(processedArgs.pArgc >= 1)
    {
        char ** const cmdArgs = processedArgs.pArgs;
        //parse cmd args, we only scan the start of each of the entered strings for flags.
        //TODO: if your add support for - to denote a negative number remember your equations could start with '-'
        for(int i = 0; i < processedArgs.pArgc; i++)
        {
            char * currArg = processedArgs.pArgs[i];
            //if we have the indicator of a command flag
            if(*currArg == '-')
            {
                //capture what is after the '-'
                char tmpCmdArg = *((currArg)+1);
                //if we have "--" check for the seccond '-'
                if(tmpCmdArg == '-')
                {
                    currArg++; //skip past the extra '-'
                }
                
                //if we don't have a "--" nor simply have a negative number
                if(!isdigit(tmpCmdArg))
                {
                    currArg++; //skip past the first '-'
                }
                
                //if we have a letter to denote a flag
                if(isalpha(*currArg))
                {
                    char tmpFlag = *currArg;
                    if(tmpFlag == 'l')
                    {
                        tmpFlag -= (char) 32; //make the flag an 'L' so we test true below
                    }
                    //if we have an 'L' we + the defference between 'L' and 'l'
                    if(tmpFlag + 32 == 'l')
                    {
                        //If we have an l flag print out the license
                        outputPrgInfo(LICENSE, processedArgs.progName);
                        if (eqaStr == NULL)
                            break;
                        else {
                            free(eqaStr);
                            eqaStr = NULL;
                            break;
                        }
                    }
                    else
                    {
                        outputPrgInfo(USEAGE, processedArgs.progName); //If we get a bad flag or a 'u' flag to denote useage print the useage
                        if (eqaStr == NULL)
                            break;
                        else {
                            free(eqaStr);
                            eqaStr = NULL;
                            break;
                        }
                    }
                }
            }
            //if we have a number or symbol as the first item in the string we have an equation element so we add it
            else if(isEqaElement(*currArg) && (*currArg != (char) '\''))
            {
                if(eqaStr == NULL)
                {
                    //Set the last to delimit the end of the strin
                    eqaStr = (char*) malloc(EQUATION_STR_SIZE*sizeof(char));
                    eqaStr[EQUATION_STR_SIZE] = '\0';
                }
                strncat(eqaStr, currArg, EQUATION_STR_SIZE-1);
            }
            else
            {
                outputPrgInfo(USEAGE, processedArgs.progName); //tell the user what the cmd args are for and how to use the program
                if (eqaStr == NULL)
                    break;
                else {
                    free(eqaStr);
                    eqaStr = NULL;
                    break;
                }
            }
        }
    }

    //default to quit
    chp_or_done ret = { 1, NULL };
    if (eqaStr != NULL)
    {
        ret.quit = 0;
        ret.eqa = eqaStr;
    }
    else if (!processedArgs.pArgc) {
        //if there where no args don't quit
        ret.quit = 0;
    }
    return ret;
}

int main(int argc, char **args)
{
    int returnVal = 0;
    /* This stores the elemets of our equation while and after the equation
     * string is processed by processEquationString
     * before the elements are processed by processPostfixEquation */
    //a linked list with all the parsed elements of the equation the user entered
    LinkedList *equationList = NULL;    
    double *ansPtr = NULL; //Our answer is returned as a pointer, so we can reuse it in other equations
    int exit = 0;
    chp_or_done quitOrProcess = handleArgs(argc, args); //The string containing equation the user entered
    char *eqaStr = NULL;


    if (!quitOrProcess.quit)
    {
        eqaStr = quitOrProcess.eqa;
        //if we didn't have any args or didn't parse any equation from the args
        if(eqaStr == NULL)
        {
            //Set the last to delimit the end of the strin
            eqaStr = (char*) malloc(EQUATION_STR_SIZE*sizeof(char));
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
                fprintf(stderr, "ERROR: could not process the equation string\n");
                returnVal = currRetVal;
            }
            else
            {
                double *lastPtr = ansPtr;
                ansPtr = processPostfixEqa(equationList);
                /* The last equations data may have been used in the processing of
                * the equation so we cant delete it until we finish making the
                * calculation. */
                if(lastPtr != NULL)
                {
                    free(lastPtr);
                    lastPtr = NULL;
                }

                /* There is nothing on the stack but as the memory
                * is not cleared on free the stack logic thinks
                * there is still data. */
                equationList = NULL;
                if(ansPtr == NULL)
                {
                    fprintf(stderr, "ERROR: could not process equation");
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

    }
    if(equationList != NULL) free(equationList);
    if(ansPtr != NULL) free(ansPtr);
    if(eqaStr != NULL) free(eqaStr);

    return returnVal; 
}
