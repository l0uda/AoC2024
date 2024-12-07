#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

long long int calculateEquation(long long int *equation, int operatorBits, int memberCount){
    long long int result = equation[1];
    for (int i = 2; i <= memberCount; i++){
        if (operatorBits%2)
            result += equation[i];
        else
            result *= equation[i];
        operatorBits >>= 1;
    }
    return result == equation[0] ? result : 0;
}

long long int processEquation(long long int *equation, int memberCount){
    int operatorBits = pow(2, memberCount-1)-1;
    
    while (1) {
        if (calculateEquation(equation, operatorBits, memberCount))
            return equation[0];
        if (!operatorBits)
            break;
        int temp = operatorBits, mask = 1, i = 1;
        
        for (; !(temp%2); i++){
            mask+=pow(2,i);
            temp>>=1;
        }
        operatorBits ^= mask;        
    }
    return 0;
}

long long int calculateEquationFucked(long long int *equation, int *operatorBits, int memberCount){
    long long int result = equation[1];
    for (int i = 0; i < memberCount-1; i++){
        if (operatorBits[i] == 0)
            result += equation[i+2];
        else if (operatorBits[i] == 1)
            result *= equation[i+2];
        else {
            char *mrdka = malloc(50);
            char *mrdka2 = malloc(50);
            sprintf(mrdka,"%lld",result);
            sprintf(mrdka2,"%lld",equation[i+2]);
            strcat(mrdka,mrdka2);
            result = atoll(mrdka);
            free(mrdka);
            free(mrdka2);
        }
    }
    return result == equation[0] ? result : 0;
}

long long int processEquationFucked(long long int *equation, int memberCount){
    int *operatorBits = calloc((memberCount-1), sizeof(operatorBits));
    int limit = (int) pow(3,memberCount-1);

    for (int i = 0; i < limit; i++) {
        if (calculateEquationFucked(equation, operatorBits, memberCount))
            return equation[0];
        int j;
        for (j = memberCount-2; j >= 0; j--){
            if (operatorBits[j] != 2)
                break;
        }
        for (int k = j; k < memberCount; k++){
            operatorBits[k] = (operatorBits[k] + 1) % 3;
        }
    }
    return 0;
}

int main(){
    FILE* input = fopen("input.txt","r");
    int longestLine = 69;
    long long int sum = 0;

    char *equation = malloc(longestLine);
    while (fgets(equation,longestLine+3,input)){
        long long int *equationInts = malloc(1);
        char *token = strtok(equation, " ");
        int i = 0;
        while (token != NULL){
            realloc(equationInts, sizeof(equationInts)*(i+1));
            equationInts[i++] = atoll(token);
            token = strtok(NULL, " ");
        }
        sum += processEquationFucked(equationInts, i-1);
        // free(equationInts);
    }
    free(equation);

    printf("%lld\n", sum);

    return 0;
}
