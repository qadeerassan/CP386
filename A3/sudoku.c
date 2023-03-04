#include "stdio.h"
#include "stdlib.h"
#include <pthread.h>
#include "string.h"

typedef struct {
    int row[9];
    int col[9];
    int sq[9];
} parameters;

int validator(parameters *arg) {
    int isValid = 1;

    // check row
    int occurrences[9] = {0};
    for (int ri = 0; ri < 9; ri++) {
        occurrences[arg->row[ri]]++;
        if (occurrences[arg->row[ri]] > 1) {
            isValid = 0;
            break;
        }
    }

    // check col
    if (isValid == 1) {
        int occurrences[9] = {0};
        for (int ci = 0; ci < 9; ci++) {
            occurrences[arg->col[ci]]++;
            if (occurrences[arg->col[ci]] > 1) {
                isValid = 0;
                break;
            }
        }
    }

    // check square
    if (isValid == 1) {
        int occurrences[9] = {0};
        for (int si = 0; si < 9; si++) {
            occurrences[arg->sq[si]]++;
            if (occurrences[arg->sq[si]] > 1) {
                isValid = 0;
                break;
            }
        }
    }

    return isValid;
}

int main(int argc, char* argv[]) {
    FILE* board_fp;
    int sudoku_matrix[9][9];
    int isValid = 1;

    board_fp = fopen(argv[1], "r");
    if (board_fp == NULL) {
        printf("File open error. \n");
        return 1;
    }

    char line[56];

    for (int i = 0; i < 9; i++) {
        if (fgets(line, sizeof(line), board_fp) == NULL) {
            printf("Error reading file. \n");
            return 1;
        }
        int j = 0;
        char *val = strtok(line, " ");
        while (val != NULL) {
            sudoku_matrix[i][j] = atoi(val);
            j++;
            val  = strtok(NULL, " ");
        }
        printf("\n");

    }

    int sq_start_indices[9][2] = {
        {0,0}, {0,3}, {0,6},
        {3,0}, {3,3}, {3,6},
        {6,0}, {6,3}, {6,6},
    };

    for (int i = 0; i < 9; i++) {
        pthread_t thread;
        int row[9];
        int col[9];
        int sq[9];

        for (int j = 0; j < 9; j++) {
            row[j] = sudoku_matrix[i][j];
        }
        for (int k = 0; k < 9; k++) {
            col[k] = sudoku_matrix[k][i];
        }

        // iterate over the rows of the i-th square
        for (int j = sq_start_indices[i][0]; j < sq_start_indices[i][0] + 3; j++) {
            // iterate over the columns of the i-th square
            for (int k = sq_start_indices[i][1]; k < sq_start_indices[i][1] + 3; k++) {
                // store the value in the square in the array
                sq[(j - sq_start_indices[i][0]) * 3 + k - sq_start_indices[i][1]] = sudoku_matrix[j][k];
                }
        }

        parameters args = { {0}, {0}, {0} };
        memcpy(args.row, row, sizeof(row));
        memcpy(args.col, col, sizeof(col));
        memcpy(args.sq, sq, sizeof(sq));        
        pthread_create(&thread, NULL, (void *) *(*validator) , (void*) &args);

        pthread_join(thread, (void**) &isValid);
        if (isValid == 0) {
            break;
        }
    }
    printf("Sudoku puzzle solution is:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", sudoku_matrix[i][j]);
        }
        printf("end \n");
    }

    if (isValid == 1) {
        printf("Sudoku puzzle is valid.\n");
    }
    else {
        printf("Sudoku puzzle is not valid.\n");     
    }

    return isValid;
}
