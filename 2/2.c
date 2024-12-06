#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(int* line){
    int sign = line[0] - line[1];
    if (sign < 0){
        for (int i = 0; line[i+1] != NULL; i++){
            if (line[i] - line[i+1] >= 0 || abs(line[i] - line[i+1]) > 3)
                return 1;
        }
    }
    else {
        for (int i = 0; line[i+1] != NULL; i++){
            if (line[i] - line[i+1] <= 0 || abs(line[i] - line[i+1]) > 3)
                return 1;
        }
    }

    return 0;
}

int check2(int* line){
    int prev = 0;
    int line1[100];
    int line2[100];
    int flag1 = 0, flag2 = 0;

    for (int i = 0; line[i+1] != NULL; i++){
        if ((line[i] - line[i+1] >= 0 && prev < 0) || (line[i] - line[i+1] <= 0 && prev > 0) || (abs(line[i] - line[i+1]) > 3)){
            int j = 0;
            for (; line[j] != NULL; j++){
                if (j != i){
                    if (flag1)
                        line1[j-1] = line[j];
                    else 
                        line1[j] = line[j];
                }
                else
                    flag1 = 1;
                if (j != i+1){
                    if (flag2)
                        line2[j-1] = line[j];
                    else
                        line2[j] = line[j];
                }
                else
                    flag2 = 1;
            }
            line1[j-1] = NULL;
            line2[j-1] = NULL;
            // for (int i = 0; line1[i] != NULL; i++){
            //     printf("%d\n",line1[i]);
            // }
            // printf("\n");
            // for (int i = 0; line2[i] != NULL; i++){
            //     printf("%d\n",line2[i]);
            // }

            if (!check(line1) || !check(line2)) return 0;
            return 1;
        }
        prev = line[i] - line[i+1];
    }

    return 0;   
}



int main(){
    FILE* input = fopen("input.txt","r");
    int line[100];
    char str[1000];
    int safeCounter = 0;
    
    while(fgets(str,100,input)){
        char* token;
        int i = 0;
        token = strtok(str, " ");
        while (token != NULL){
            line[i++] = atoi(token);
            token = strtok(NULL, " ");
        }
        line[i] = NULL;
        if (!check2(line)) {
            safeCounter++;
        }
    }
    printf("%d\n", safeCounter);
    return 0;
}