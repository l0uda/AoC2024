#include <stdio.h>
#include <stdlib.h>

// #define inputLen 19//999

typedef struct {
    int ID;
    int count;
} diskMapMember;


int main(){
    int inputLen = 19999;
    FILE *input = fopen("input.txt", "r");
    char *diskMap = malloc(inputLen+3);
    fgets(diskMap,inputLen+3,input);
    diskMap[inputLen] = '\0';
    
    long long int sum = 0;

    diskMapMember *newMap = calloc(inputLen,sizeof(newMap));

    for (long long int i = 0; i < inputLen; i++){
        if (!(i%2)){
            newMap[i].ID = i/2;
        }
        else {
            newMap[i].ID = -1;
        }
        // prlong long intf("%d %d\n", i, newMap[i].ID);
        newMap[i].count = (long long int) diskMap[i]-48;
    }
        
    for (long long int i = inputLen-1; i > 0; i--){
        // for (int s = 0; s < inputLen; s++){
        //     if (newMap[s].ID >= 0){
        //         int cnt = newMap[s].count;
        //         while(cnt--){
        //             printf("%d", newMap[s].ID);
        //         }
        //     } else {
        //         printf(" |");
        //         int cnt = newMap[s].count;
        //         while (cnt--){
        //             printf(".");
        //         }
        //         printf("| ");            
        //     }
        // }
        printf("\n");
        if(newMap[i].ID > 0){
            for (long long int j = 0; j < i; j++){
                if (newMap[j].ID < 0 && newMap[j].count >= newMap[i].count){
                    long long int diff = newMap[j].count - newMap[i].count;

                    newMap[j].ID = newMap[i].ID;
                    newMap[j].count = newMap[i].count;
                    newMap[i].ID = -1;
                    int localSpaceSum = newMap[i].count;
                    if (newMap[i+1].ID < 0){
                        newMap[i].count += newMap[i+1].count;
                        for (int r = i+1; r < inputLen-1; r++){
                            newMap[r].ID = newMap[r+1].ID;
                            newMap[r].count = newMap[r+1].count;
                        }
                        inputLen--;
                    }
                    if (newMap[i-1].ID < 0){
                        newMap[i].count += newMap[i-1].count;
                        for (int r = i-1; r < inputLen-1; r++){
                            newMap[r].ID = newMap[r+1].ID;
                            newMap[r].count = newMap[r+1].count;
                        }
                        inputLen--;
                    }
                    if (diff){
                        diskMapMember new;
                        new.count = diff;
                        new.ID = -1;
                        inputLen++;
                        for (int g = inputLen; g > j+1; g--){
                            newMap[g].count = newMap[g-1].count;
                            newMap[g].ID = newMap[g-1].ID;
                        }
                        newMap[j+1] = new;
                    }

                    break;
                }
            }
        }
    }

    int position = 0;

    for (int s = 0; s < inputLen; s++){
        if (newMap[s].ID >= 0){
            int cnt = newMap[s].count;
            while(cnt--){
                // printf("%d", newMap[s].ID);
                sum += newMap[s].ID*position++;                
            }
        } else {
            // printf(" |");
            int cnt = newMap[s].count;
            while (cnt--){
                // printf(".");
                position++;
            }
            // printf("| ");            
        }
    }
    printf("\n");
/*  // part 1
    int position = 0;
    int ID, k = inputLen;
    char j, ceil;

    for (int i = 0; i < k; i++){
        ID = i/2;
        for (j = '0'; j < diskMap[i]; j++){
            sum += ID*position++;
        }
        if (++i >= k)
            break;
        ID = k/2;
        for (j = '0'; j < diskMap[i]; j++){
            sum += ID*position++;
            diskMap[k-1]--;
            if (diskMap[k-1] == '0'){
                k-=2;
                ID = k/2;
            }
        }
    } */

    printf("%lld\n",sum);
    return 0;
}