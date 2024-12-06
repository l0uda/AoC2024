#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    int int_a = * ( (int*) a );
    int int_b = * ( (int*) b );
    
    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}

int main(){
    FILE* input = fopen("input.txt","r");
    int i1, i2, i = 0;
    int first[1000];
    int second[1000];
    char str[100];

    while(fgets(str,100,input)){
        sscanf(str,"%d\t%d",&i1,&i2);
        first[i] = i1;
        second[i] = i2;
        i++;
    }
    qsort(first,i,sizeof (int), compare);
    qsort(second,i,sizeof (int), compare);

    
    int sum = 0;
    for (int j = 0; j < i; j++){
        sum += abs(first[j] - second[j]);
    }
    //printf("%d\n",sum);

    int difference = 0;

    for (int j = 0; j < i; j++){
        for (int k = 0; k < i; k++){
            if (first[j] == second[k]){
                difference += first[j];
            }
        }
    }
    
    printf("%d\n", difference);

    return 0;
}