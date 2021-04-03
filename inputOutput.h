#ifndef IOFuncts
#define IOFuncts

//Definitions of the functions in inputOutput.c
#define EQUATION_STR_LEN 80

int isQuitString(char *eqaStr);
int isValidEquation(char *eqaStr);

void printResault(double *resault);
void getUserEquation(char *eqaStr);

#endif
