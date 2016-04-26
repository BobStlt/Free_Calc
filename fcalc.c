/*
    Free calc is a simple malti platform calculator program. 
    Copyright (C) 2016 Perrin Smith

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int main( int an, char *arginp[] ){
	float number1 = 0;
	float number2 = 0;
	float ans = 0;
	int sswitch = 0;
	char *s = calloc(1, sizeof(char));
	char *h = "help";
	char *l = "legal";

	if (s == NULL) {
	printf("%s", KRED);
	perror("Memory allocation failed");
        printf("%s", KNRM);
	return -1;	

	}

	if (an == 2) {
        	if (*arginp[1] == *h) {
                        printf("%s", KRED);
                	puts("This is free calc, a symple multi platform calulator");
                        printf("%s", KNRM);
			printf("\nUsage: %snumm1 sym numm2%s\ne.g. 12 * 12\n", KCYN, KNRM);
                        printf("then after %sans%s sym numm2%s\n", KGRN, KCYN, KNRM);
			printf("To exit type %sq q%s then %sreturn%s\n\n", KCYN, KNRM, KCYN, KNRM);
                        printf("%s", KNRM);
			goto END;
        	}
		else if (*arginp[1] == *l) {
                        printf("%s", KRED);
			printf("This is free calc, a symple multi platform calulator");
			printf("Copyright (C) 2016 Perrin Smith\n\n");
                        printf("This program is free software: you can redistribute it and/or modify\n");
                        printf("it under the terms of the GNU General Public License as published by\n");
                        printf("the Free Software Foundation, either version 3 of the License, or\n");
                        printf("any later version.\n\n");
                        printf("This program is distributed in the hope that it will be useful,\n");
                        printf("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
                        printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
                        printf("See the GNU General Public License for more details.\n\n");
                        printf("You should have received a copy of the GNU General Public License\n");
                        printf("along with this program.  If not, see <http://www.gnu.org/licenses/>.\n");
                        printf("%s", KNRM);
                        goto END;
		}
		else {
			puts("Type 'help' for help or 'legal' for legal info");
			goto END;
		}
	}

        printf("%s", KRED);
	printf(":");
        printf("%s", KNRM);
	scanf("%f %s %f", &number1,s, &number2);
	
	switch (*s) {

	case '+':
                printf("%s", KWHT);
        	printf("\n= %f", number1 + number2);
                printf("%s", KNRM);
        	ans = number1 + number2;
		break;
	
	case '-':
                printf("%s", KWHT);
		printf("\n= %f", number1 - number2);
                printf("%s", KNRM);
        	ans = number1 - number2;
		break;
    
	case '*':
                printf("%s", KWHT);
		printf("\n= %f", number1 * number2);
                printf("%s", KNRM);
		ans = number1 * number2;
		break;

	case 'x':
                printf("%s", KWHT);
		printf("\n= %f", number1 * number2);
                printf("%s", KNRM);
                ans = number1 * number2;
                break;	

	case '/':
                printf("%s", KWHT);
		printf("\n= %f", number1 / number2);
                printf("%s", KNRM);
		ans = number1 / number2;
		break;
	
	default:
		goto END;
	}
		

	do {
		number2 = 0;
                printf("%s", KGRN);
		printf("\nans ");
                printf("%s", KNRM);
		scanf("%s %f", s, &number2);
			
		switch (*s) {
		
		case '+':
                        printf("%s", KWHT);
			printf("= %f\n", ans + number2);
                        printf("%s", KNRM);
			ans = ans + number2;
			break;
        
		case '-':
                        printf("%s", KWHT);
			printf("= %f\n", ans - number2);
                        printf("%s", KNRM);
			ans = ans - number2;
			break;

		case '*':
                        printf("%s", KWHT);
                	printf("\n= %f", ans * number2);
                        printf("%s", KNRM);
                	ans = ans * number2;
                	break;

	        case 'x':
                        printf("%s", KWHT);
                	printf("\n= %f", ans * number2);
                        printf("%s", KNRM);
                	ans = ans * number2;
                	break;
	
		case '/':
                        printf("%s", KWHT);
			printf("= %f\n", ans / number2);
                        printf("%s", KNRM);
			ans = ans / number2;
			break;
		
		default:
                        printf("%s", KWHT);
			printf("= %f\n",ans);
                        printf("%s", KNRM);
			goto END;
		}
	} while (sswitch == 0);
	
	//printf("\n%f", ans); for debug

	END:
	free(s);
	return 0;
}
