#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkXMAS(int x, int y, char **matrice, int numberOfLines, int numberOfCols){
    int sum = 0;
    for (int Xi = -1; Xi < 2; Xi++){
        for (int Yj = -1; Yj < 2; Yj++){
            if (0 <= x + Xi*3 && x + Xi*3 <= numberOfCols-1 && 0 <= y + Yj*3 && y + Yj*3 <= numberOfLines-1){
                if (matrice[x+Xi*1][y+Yj*1] == 'M' && matrice[x+Xi*2][y+Yj*2] == 'A' && matrice[x+Xi*3][y+Yj*3] == 'S')
                    sum++;
            }
        }
    }
    return sum;
}

int checkX_MAS(int x, int y, char **matrice, int numberOfLines, int numberOfCols){
    if (x-1 < 0 || x+1 > numberOfCols-1 || y-1 < 0 || y+1 > numberOfLines-1) return 0;
    
    for (int Xi = -1; Xi < 2; Xi+=2){
        for (int Yj = -1; Yj < 2; Yj+=2){
            if (matrice[x+Xi][y+Yj] == 'M' && matrice[x+Xi][y-Yj] == 'M' && matrice[x-Xi][y+Yj] == 'S' && matrice[x-Xi][y-Yj] == 'S')
                return 1;
            if (matrice[x+Xi][y+Yj] == 'M' && matrice[x-Xi][y+Yj] == 'M' && matrice[x+Xi][y-Yj] == 'S' && matrice[x-Xi][y-Yj] == 'S')
                return 1;
        }
    }
    return 0;
}

int main(){
    FILE* input = fopen("input.txt","r");
    int numberOfLines = 140;
    int numberOfCols = 140;
    int sum = 0;

    char **inputMatrice = malloc(sizeof(char*)*numberOfLines);
    for (int i = 0; i < numberOfLines; i++){
        inputMatrice[i] = malloc(numberOfCols+3);
        fgets(inputMatrice[i],numberOfCols+3,input);
        // zkurvene crlf
    }

    for (int i = 0; i < numberOfLines; i++){
        for (int j = 0; j < numberOfCols; j++){
            // if (inputMatrice[i][j] == 'X') sum += checkXMAS(i,j,inputMatrice,numberOfLines,numberOfCols);

            if (inputMatrice[i][j] == 'A') sum += checkX_MAS(i,j,inputMatrice,numberOfLines,numberOfCols);
        }
    }
    printf("%d\n",sum);
    
    return 0;
}