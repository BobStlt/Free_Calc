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


int main( int an, char *arginp[] ){
	float number1 = 0;
	float number2 = 0;
	float ans = 0;
	int sswitch = 0;
	char *s = calloc(1, sizeof(char));
	char *h = "help";
	char *l = "legal";

	if (s == NULL) {
	
	perror("Memory allocation failed");
	return -1;	

	}

	if (an == 2) {
        	if (*arginp[1] == *h) {
                	puts("This is free calc, a symple multi platform calulator");
			printf("\nUsage: numm1 sym numm2\ne.g. 12 * 12\n");
			printf("To exit type 'q q' then return\n\n");
			goto END;
        	}
		else if (*arginp[1] == *l) {
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
                        goto END;
		}
		else {
			puts("Type 'help' for help or 'legal' for legal info");
			goto END;
		}
	}

	printf(":");
	scanf("%f %s %f", &number1,s, &number2);
	
	switch (*s) {

	case '+':
        	printf("\n= %f", number1 + number2);
        	ans = number1 + number2;
		break;
	
	case '-':
		printf("\n= %f", number1 - number2);
        	ans = number1 - number2;
		break;
    
	case '*':
		printf("\n= %f", number1 * number2);
		ans = number1 * number2;
		break;

	case 'x':
		printf("\n= %f", number1 * number2);
                ans = number1 * number2;
                break;	

	case '/':
		printf("\n= %f", number1 / number2);
		ans = number1 / number2;
		break;
	
	default:
		goto END;
	}
		

	do {
		number2 = 0;
		printf("\nans ");
		scanf("%s %f", s, &number2);
			
		switch (*s) {
		
		case '+':
			printf("= %f\n", ans + number2);
			ans = ans + number2;
			break;
        
		case '-':
			printf("= %f\n", ans - number2);
			ans = ans - number2;
			break;

		case '*':
                	printf("\n= %f", ans * number2);
                	ans = ans * number2;
                	break;

	        case 'x':
                	printf("\n= %f", ans * number2);
                	ans = ans * number2;
                	break;
	
		case '/':
			printf("= %f\n", ans / number2);
			ans = ans / number2;
			break;
		
		default:
			printf("= %f\n",ans);
			goto END;
		}
	} while (sswitch == 0);
	
	//printf("\n%f", ans); for debug

	END:
	free(s);
	return 0;
}
