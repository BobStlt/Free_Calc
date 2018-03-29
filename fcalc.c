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

/*
	To do:
	Put in rounding capacilities.
	Add version information.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define KNRM  "\x1B[0m"  //sets colour back to default 
#define KRED  "\x1B[31m" //sets colour to red
#define KGRN  "\x1B[32m" //green
#define KYEL  "\x1B[33m" //yellow
#define KBLU  "\x1B[34m" //blue
#define KMAG  "\x1B[35m" //magenta
#define KCYN  "\x1B[36m" //cyan
#define KWHT  "\x1B[37m" //white
#define CLRS  "\x1B[2J"  //Clears the screen
#define RSETPOS "\x1B[;H"//reset the cursor possition

float calc(float number1, char *symbol, float number2, float ans, short which_run){
	
	float calc_temp;
	
	if (which_run == 0){
	calc_temp = number1;
	}
	
	else {
		calc_temp = ans;
	}
	
	
	switch (*symbol) {
		
		case '+':
			printf("%s", KWHT);
			printf("= %f\n", calc_temp + number2);
               		printf("%s", KNRM);
			ans = calc_temp + number2;
			break;
        	
		case '-':
			printf("%s", KWHT);
			printf("= %f\n", calc_temp - number2);
			printf("%s", KNRM);
			ans = calc_temp - number2;
			break;
		
		case 'X': case 'x': case '*':
			printf("%s", KWHT);
			printf("\n= %f", calc_temp * number2);
			printf("%s", KNRM);
               		ans = calc_temp * number2;
                	break;
	
		case '/':
			printf("%s", KWHT);
			printf("= %f\n", calc_temp / number2);
                	printf("%s", KNRM);
			ans = calc_temp / number2;
			break;
			
		default:
			printf("%s", KWHT);
			if (which_run == 0){
				return -1;
			}
			else {
				printf("= %f\n",ans);
			}
			printf("%s", KNRM);
		
	}

	return ans;
}





/*char rounding( float ans ){
	char rounded_no[246];
	float flt_tmp = 0;
	
	//flt_tmp = floor(ans);
	printf("%.1lf\n", floor(ans));
	
	return 0; //rounded_no;
} */





int main( int no_of_args, char *arginp[] ){
	float number1 = 0;
	float number2 = 0;
	float ans = 0;
	char *symbol = calloc(1, sizeof(char));
	char *h = "help";
	char *l = "legal";
	short which_run = 0;

	if (symbol == NULL) {
	printf("%s", KRED);
	perror("Memory allocation failed");
        printf("%s", KNRM);
	return 1;	

	}

	if (no_of_args == 2) {
        	if (*arginp[1] == *h) {
                        printf("%s", KRED);
                	puts("This is free calc, a simple multi platform calulator");
                        printf("%s", KNRM);
			printf("\nUsage: %snumm1 sym numm2%s\ne.g. %s12 * 12%s\n", KCYN, KNRM, KCYN, KNRM);
                        printf("then after %sans%s sym numm2%s\n", KGRN, KCYN, KNRM);
			printf("To exit type %sq q%s then %sreturn%s\n\n", KCYN, KNRM, KCYN, KNRM);
                        printf("%s", KNRM);
			goto END;
        	}
		else if (*arginp[1] == *l) {
                        printf("%s", KRED);
			printf("This is free calc, a symple multi platform calulator\n\n");
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
			goto END;
		}
	}
	

	printf("%s", CLRS);
	printf("%s", RSETPOS);
        printf("%s", KRED);
	printf(":");
        printf("%s", KNRM);
	scanf("%f %s %f", &number1, symbol, &number2);
	if(strcmp(symbol, "q") == 0 || strcmp(symbol,"Q") == 0){
		goto END;
	}
	ans = calc(number1, symbol, number2, ans, which_run);
	which_run++;

	do {
			number2 = 0;
               		printf("%s", KGRN);
			printf("\nans ");
        	        printf("%s", KNRM);
			scanf(" %s %f", symbol, &number2);
			ans = calc(number1, symbol, number2, ans, which_run);

	} while(strcmp(symbol, "q") == 0 || strcmp(symbol,"Q"));

	
	//printf("\n%f", ans); for debug

	END:
        printf("Type %shelp%s for help or %slegal%s for legal info\n", KCYN, KNRM, KCYN, KNRM);
	free(symbol);
	return 0;
}
