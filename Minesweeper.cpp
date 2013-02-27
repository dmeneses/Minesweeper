/* 
 * File:   Minesweeper.cpp
 * Author: Daniela
 *
 * Created on February 22, 2013, 12:28 PM
 */

#include <iostream>

int rows;
int columns;

char** buildMatrix() {
    char** matrix = (char**) malloc(rows * sizeof (char*));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (char*) calloc(columns, sizeof (char));
        memset(matrix[i], '\0', columns);
    }

    return matrix;
}

void destroyMatrix(char** matrix) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

void buildInitialState(char** matrix) {
    char tmp;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf(" %c ", &tmp);
            matrix[i][j] = tmp;
        }
    }
}

int countNeighbours(char** matrix, int row, int column) {
    int res = 0;
    int endRow = row + 1;
    int endColumn = column + 1;

    for (int startRow = row - 1; startRow <= endRow; startRow++) {
        for (int startColumn = column - 1; startColumn <= endColumn; startColumn++) {
            if (startRow >= 0 && startRow < rows) {
                if (startColumn >= 0 && startColumn < columns) {
                    if (startColumn != column || startRow != row) {
                        res += matrix[startRow][startColumn] == '*' ? 1 : 0;
                    }
                }
            }
        }
    }
    return res;
}

void printClues(char** matrix) {
    int temp;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            temp = countNeighbours(matrix, i, j);
            printf("|%d|", temp);
        }
        printf("\n");
    }
    printf("\n");
}

bool put(char** matrix, int row, int column) {
    if (matrix[row][column] == '*') {
        matrix[row][column] = '/';
        return false;
    } else {
        matrix[row][column] = '1';
        return true;
    }
}

void printMatrix(char** matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("|%c|", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void play() {
    char** matrix = buildMatrix();
    int inputsNbr;
    buildInitialState(matrix);
    scanf("%d", &inputsNbr);
    printClues(matrix);

    int row, column;
    bool result = true;
    while (inputsNbr-- && result) {
        scanf("%d %d", &row, &column);
        result = put(matrix, row, column);
    }

    printf("%s", result ? "YOU WON\n" : "YOU LOSE\n");
    printMatrix(matrix);

    destroyMatrix(matrix);
}

int main() {
    freopen("Minesweeper.in", "r", stdin);

    int testCases;
    scanf("%d", &testCases);

    while (testCases--) {
        printf("----------------------Test---------------------\n");
        scanf("%d %d", &rows, &columns);
        play();
        printf("\n");
    }

    return 0;
}

