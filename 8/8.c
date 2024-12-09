#include <stdio.h>
#include <stdlib.h>

#define rowLen 50
#define rowCount 50
// 48 - 122
// 0 - 74 = 75

typedef struct AntennaCoordinatesTemplate{
    int x;
    int y;
    struct AntennaCoordinatesTemplate *next;
} AntennaCoordinates;

void allocAntennaSetCoords(AntennaCoordinates *begin, int i, int j){
    AntennaCoordinates *new = malloc(sizeof(new));
    new->x = i;
    new->y = j;
    new->next = NULL;
    if (!begin){
        begin = new;
    } else {
        while (begin->next)
            begin = begin->next;
        begin->next = new;
    }
}

void printCoords(AntennaCoordinates **antennasLists){
    for (int i = 0; i < 75; i++){
        if (antennasLists[i]){
            printf("%c:\n",i+47);
            AntennaCoordinates *antenna = antennasLists[i];
            while(antenna){
                printf("x:%d y:%d\n", antenna->x, antenna->y);
                antenna = antenna->next;
            }
            printf("\n\n");
        }
    }
}

void calculateAntinodes(int **antinodes, AntennaCoordinates **antennasLists){
    for (int i = 0; i < 75; i++){
        AntennaCoordinates *actual = antennasLists[i];
        while (actual){
            int x = actual->x;
            int y = actual->y;
            AntennaCoordinates *next = actual->next;
            while(next){
                antinodes[y][x] = 1;
                antinodes[next->y][next->x] = 1;

                int xDiff = abs(x-next->x);
                int yDiff = abs(y-next->y);

                int AY, BY, AX, BX;
                int xDiffA = xDiff;
                int yDiffA = yDiff;
                int xDiffB = xDiff;
                int yDiffB = yDiff;
                while (1){
                    AY = y < next->y ? y - yDiffA : y + yDiffA; 
                    AX = x < next->x ? x-xDiffA : x+xDiffA;
                    if (AY >= 0 && AY < rowCount && AX >= 0 && AX < rowLen)
                        antinodes[AY][AX] = 1;
                    else
                        break;
                    xDiffA += xDiff;
                    yDiffA += yDiff;
                }
                while (1){
                    BY = next->y < y ? next->y-yDiffB : next->y+yDiffB;
                    BX = next->x < x ? next->x-xDiffB : next->x+xDiffB;
                    if (BY >= 0 && BY < rowCount && BX >= 0 && BX < rowLen)
                        antinodes[BY][BX] = 1;
                    else
                        break;
                    xDiffB += xDiff;
                    yDiffB += yDiff;
                }
                next = next->next;
            }
            actual = actual->next;
        }
    }
}

int main(){
    FILE *input = fopen("input.txt", "r");

    AntennaCoordinates **antennasLists = calloc(75, sizeof(*antennasLists));
    int **antinodes = malloc(sizeof(*antinodes)*rowCount);
    char *row = malloc(rowLen+3);
    int j = 0;

    while (fgets(row,rowLen+3,input)){
        antinodes[j] = calloc(rowLen, sizeof(antinodes));
        row[rowLen] = '\0';
        for (int i = 0; row[i]; i++){
            if (row[i] != '.'){
                allocAntennaSetCoords(&antennasLists[row[i]-48],i,j);
            }
        }
        j++;
    }

    calculateAntinodes(antinodes, antennasLists);
    // printCoords(antennasLists);

    int sum = 0;
    for (int i = 0; i < rowLen; i++){
        for (int j = 0; j < rowCount; j++){
            if (antinodes[i][j])
                sum++;
        }
    }

    printf("%d\n", sum);
    return 0;
}