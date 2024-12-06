#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    FILE* input = fopen("input.txt","r");
    char *line = malloc(3578);
    int doFlag = 1;


    int sum = 0;
    while (fgets(line,3578,input)){
        while (*line != NULL){
            if (doFlag && *line == 'm' && line+1 && *(line+1) == 'u' && line+2 && *(line+2) == 'l' && line+3 && *(line+3) == '('){
                line+=4;
                char num1[4] = "\0\0\0\0";
                char num2[4] = "\0\0\0\0";
                //printf("%c\n", *line);
                for (int i = 0; i < 3; i++){
                    if (line && isdigit(*line))
                        num1[i] = *(line++);
                    else
                        break;
                }
                if (line && *line == ','){
                    line++;
                    num2[0] = '\0';
                    for (int i = 0; i < 3; i++){
                        if (line && isdigit(*line))
                            num2[i] = *(line++);
                        else
                            break;
                    }
                }
                if (*line == ')'){
                    sum += atoi(num1) * atoi(num2);
                }
            }
            if (doFlag && *line == 'd' && line+1 && *(line+1) == 'o' && line+2 && *(line+2) == 'n' && line+3 && *(line+3) == '\'' && line+4 && *(line+4) == 't' && line+5 && *(line+5) == '(' && line+6 && *(line+6) == ')'){
                line+=6;
                doFlag = 0;
            }
            if (!doFlag && *line == 'd' && line+1 && *(line+1) == 'o' && line+2 && *(line+2) == '(' && line+3 && *(line+3) == ')'){
                line+=3;
                doFlag = 1;
            }
            line++;

        }
        line = malloc(3578);
    }
    printf("%d\n", sum);
    return 0;
}