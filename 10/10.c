#include <stdio.h>
#include <stdlib.h>

#define rowLen 60
#define rowCount 60

typedef struct {
    int i;
    int j;
} Coordinates;

int 
isInMerged(Coordinates **merged, Coordinates *inQuestion){
    return 0;
    for (int i = 0; merged[i]; i++){
        if (merged[i] && merged[i]->i == inQuestion->i && merged[i]->j == inQuestion->j)
            return 1;
    }
    return 0;
}

Coordinates** 
merge(Coordinates** new0, Coordinates** new1, Coordinates** new2, Coordinates** new3){
    Coordinates** merged = malloc(sizeof(*merged)*100);
    int mergedCounter = 0;

    for (int i = 0; new0 && new0[i]; i++) {
        if (!isInMerged(merged,new0[i]))
            merged[mergedCounter++] = new0[i];
    }
    for (int i = 0; new1 && new1[i]; i++) {
        if (!isInMerged(merged,new1[i]))
            merged[mergedCounter++] = new1[i];
    }
    for (int i = 0; new2 && new2[i]; i++) {
        if (!isInMerged(merged,new2[i]))
            merged[mergedCounter++] = new2[i];
    }
    for (int i = 0; new3 && new3[i]; i++) {
        if (!isInMerged(merged,new3[i]))
            merged[mergedCounter++] = new3[i];
    }
    return merged;
}

Coordinates**
goUp(Coordinates *locality, int **topoMap){
    Coordinates **new0 = NULL, **new1 = NULL, **new2 = NULL, **new3 = NULL;
    int i = locality->i, j = locality->j;
    
    // printf("%d %d = %d\n",i,j,topoMap[j][i]);
    if (topoMap[j][i] == 9){
        // printf("ss\n");
        new0 = malloc(sizeof(*new0));
        new0[0] = malloc(sizeof(new0));
        new0[0]->i = i;
        new0[0]->j = j;
        return new0;
    }

    if (i+1 < rowLen && topoMap[j][i+1] == topoMap[j][i]+1){
        locality->j = j;
        locality->i = i+1;
        new0 = goUp(locality, topoMap);
    }
    if (i-1 >= 0 && topoMap[j][i-1] == topoMap[j][i]+1){
        locality->j = j;
        locality->i = i-1;
        new1 = goUp(locality, topoMap);
    }
    if (j+1 < rowCount && topoMap[j+1][i] == topoMap[j][i]+1){
        locality->i = i;
        locality->j = j+1;
        new2 = goUp(locality, topoMap);
    }
    if (j-1 >= 0 && topoMap[j-1][i] == topoMap[j][i]+1){
        locality->i = i;
        locality->j = j-1;
        new3 = goUp(locality, topoMap);
    }

    return merge(new0, new1, new2, new3);
}

int 
main(){
    FILE *input = fopen("input.txt","r");
    int **topoMap = malloc(sizeof(*topoMap)*rowCount);
    char *row = malloc(rowLen+3);
    Coordinates **trailheads = malloc(sizeof(*trailheads)*rowLen*rowCount);
    Coordinates **peaks = malloc(sizeof(*peaks)*rowLen*rowCount);
    int j = 0, trailheadCounter = 0, peakCounter = 0, score = 0;
    
    while(fgets(row,rowLen+3,input)){
        row[rowLen] = '\0';
        topoMap[j] = malloc(sizeof(int)*rowLen);
        for (int i = 0; i < rowLen; i++){
            if (row[i] == '0'){
                trailheads[trailheadCounter] = malloc(sizeof(trailheads));
                trailheads[trailheadCounter]->i = i;
                trailheads[trailheadCounter++]->j = j;
            }
            if (row[i] == '9'){
                peaks[peakCounter] = malloc(sizeof(peaks));
                peaks[peakCounter]->i = i;
                peaks[peakCounter++]->j = j;
            }
            topoMap[j][i] = (int) row[i] - 48;
        }
        j++;
    }

    Coordinates **final = NULL;
    int finalCounter = 0;
    // final = merge(peaks, peaks, trailheads, NULL);
    // printf("%d %d\n",final[1]->i, final[1]->j);
    
    for (int i = 0; trailheads[i]; i++){
        final = NULL;
        Coordinates **res = goUp(trailheads[i], topoMap);
        final = merge(res, final, NULL, NULL);
        int k;
        for (k = 0; final && final[k]; k++){
            score++;
        }
        // printf("%d\n",k);
    }
    printf("%d\n",score);


    // for (int i = 0; i < rowCount; i++){
    //     for (int j = 0; j < rowLen; j++){
    //         printf("%d",topoMap[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("%d Trailheads:\n", trailheadCounter);
    // for (int i = 0; trailheads[i]; i++){
    //     printf("%d %d\n", trailheads[i]->i+1, trailheads[i]->j+1);
    // }

    // printf("%d Peaks:\n", peakCounter);
    // for (int i = 0; peaks[i]; i++){
    //     printf("%d %d\n", peaks[i]->i+1, peaks[i]->j+1);
    // }

    return 0;
}