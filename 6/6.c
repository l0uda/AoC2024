#include <stdio.h>
#include <stdlib.h>

int checkFatalities(int x, int y, int dir, int i, int **fatalities){
    for (int j = 0; j < i; j++){
        if (fatalities[j][0] == x && fatalities[j][1] == y && fatalities[j][2] == dir){
            return 1;
        }
    }
    return 0;
}

int simulate(int x, int y, int prevX, int prevY, int dir, int numberOfCols, int numberOfLines, char **matrice){
    int **fatalities = malloc(sizeof(*fatalities)*1000);
    int i = 0;
    fatalities[i] = malloc(sizeof(fatalities)*3);
    fatalities[i][0] = x;
    fatalities[i][1] = y;
    fatalities[i][2] = dir;
    i++;

    x = prevX;
    y = prevY;
    dir = (dir+1)%4;
    switch (dir){
                case 0:
                    y--;
                    break;
                case 1:
                    x++;
                    break;
                case 2:
                    y++;
                    break;
                case 3:
                    x--;
                    break;
                default:
                    break;
    }
    while (1){
        if (x >= 0 && y >= 0 && x < numberOfCols && y < numberOfLines){
            if (matrice[y][x] == '#'){
                // printf("%d %d\n",y,x);
                if (checkFatalities(x, y, dir, i, fatalities)){
                    return 1;
                }
                else {
                    fatalities[i] = malloc(sizeof(fatalities)*3);
                    fatalities[i][0] = x;
                    fatalities[i][1] = y;
                    fatalities[i][2] = dir;
                    i++;
                }
                dir = (dir+1)%4;
                x = prevX;
                y = prevY;
            }
            prevX = x; 
            prevY = y;
            switch (dir){
                case 0:
                    y--;
                    break;
                case 1:
                    x++;
                    break;
                case 2:
                    y++;
                    break;
                case 3:
                    x--;
                    break;
                default:
                    break;
                }
        }
        else {
            return 0;
        }    
    }
}

int printMap(char **matrice, int x, int y){
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            printf("%c",matrice[i][j]);
        }
        printf("\n");
    }
}

int main(){
    FILE* input = fopen("input.txt","r");
    int numberOfLines = 130;
    int numberOfCols = 130;
    int sum = 0;
    int nextX, nextY;
    int dir;

    char **inputMatrice = malloc(sizeof(*inputMatrice)*numberOfLines);
    for (int i = 0; i < numberOfLines; i++){
        inputMatrice[i] = malloc(numberOfCols+3);
        fgets(inputMatrice[i],numberOfCols+3,input);
        inputMatrice[i][numberOfCols] = '\0';
        // zkurvene crlf
    }
    for (int i = 0; i < numberOfLines; i++){
        int j = 0;
        while (inputMatrice[i][j]){
            if (inputMatrice[i][j] == '^' || inputMatrice[i][j] == '>' || inputMatrice[i][j] == 'v' || inputMatrice[i][j] == '<'){
                nextX = j;
                nextY = i;
                switch (inputMatrice[i][j]){
                    case '^':
                        dir = 0;
                        break;
                    case '>':
                        dir = 1;
                        break;
                    case 'v':
                        dir = 2;
                        break;
                    case '<':
                        dir = 3;
                        break;
                    
                    default:
                        break;
                }
            }
        j++;
        }
    }
    // printf("uh\n");
    int prevX = nextX, prevY = nextY;
    
    while (1){
        // printf("%d %d\n",nextX,nextY);
        
        if (nextY >= 0 && nextX >= 0 && nextX < numberOfCols && nextY < numberOfLines){
            if (inputMatrice[nextY][nextX] != '#'){
                if (inputMatrice[nextY][nextX] != 'X'){
                    inputMatrice[nextY][nextX] = '#';
                    sum += simulate(nextX, nextY, prevX, prevY, dir, numberOfCols, numberOfLines, inputMatrice);
                    inputMatrice[nextY][nextX] = 'X';
                }                
            }
            else {
                dir = (dir+1)%4;
                nextX = prevX;
                nextY = prevY;
            }
            prevX = nextX; 
            prevY = nextY;
            switch (dir){
                case 0:
                    nextY--;
                    break;
                case 1:
                    nextX++;
                    break;
                case 2:
                    nextY++;
                    break;
                case 3:
                    nextX--;
                    break;
                default:
                    break;
                }
        }
        else {
            printf("%d\n", sum);
            break;
        }
    }

    return 0;
}