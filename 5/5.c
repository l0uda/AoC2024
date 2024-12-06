#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getIntIndex(int num, int* array){
    for (int i = 0; array[i]; i++){
        if (array[i] == num) return i;
    }
    return -1;
}

void swapInts(int indexA, int indexB, int *array){
    int temp = array[indexA];
    array[indexA] = array[indexB];
    array[indexB] = temp;
    return;
}

int main(){
    FILE *input = fopen("input.txt","r");
    int longestRule = 6, longestUpdate = 100, countOfRules = 1176;
    
    int **rules = malloc(sizeof(*rules)*countOfRules+1);
    char *rule = malloc(longestRule+2);
    char *update = malloc(longestUpdate+2);
    char *token;
    int i = 0;

    while (fgets(rule,longestRule+2,input)){
        if (!strcmp(rule,"\r\n")) break;
        rules[i] = malloc(sizeof(rules)*2);

        token = strtok(rule, "|");
        rules[i][0] = atoi(token);

        token = strtok(NULL, "|");
        rules[i++][1] = atoi(token);

        // printf("%d %d\n",rules[i-1][0],rules[i-1][1]);
    }

    int sum = 0;

    while(fgets(update,longestUpdate+2,input)){
        i = 1;
        for (int j = 0; update[j]; j++)
            if (update[j] == ',') i++;
        int *updateArr = malloc(sizeof(updateArr) * i);
        
        i = 0;
        token = strtok(update, ",");
        while (token != NULL){
            updateArr[i++] = atoi(token);
            token = strtok(NULL, ",");
        }
        int wrongFlag = 0;

        for (int j = 0; rules[j]; j++){
            if (getIntIndex(rules[j][0],updateArr) >= 0 && getIntIndex(rules[j][1],updateArr) >= 0){
                if (getIntIndex(rules[j][0],updateArr) > getIntIndex(rules[j][1],updateArr)){
                    swapInts(getIntIndex(rules[j][0],updateArr), getIntIndex(rules[j][1],updateArr), updateArr);
                    wrongFlag = 1;
                    j = 0;
                }
            }
        }

        if (wrongFlag){
            sum += updateArr[i/2];
        }
    }
    printf("%d\n", sum);
    return 0;
}