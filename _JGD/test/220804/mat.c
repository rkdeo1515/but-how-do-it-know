#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 1024
#define INCREASE 0
#define RANDOM 1

typedef struct MATRIX_ {
  int col;
  int row;
  int elements[BUF_SIZE];
} MATRIX;

int initMatrix(MATRIX *matrix, int col, int row);
void setMatrix(MATRIX *matrix, int mode);
void printMatrix(MATRIX matrix);
void addMatrix_1(MATRIX *matrix_a, MATRIX matrix_b);
MATRIX *addMatrix_2(MATRIX matrix_a, MATRIX matrix_b);

int main(int argc, char *argv[]) {
  MATRIX matrix_1;
  MATRIX matrix_2;
  MATRIX *matrix_3;

  initMatrix(&matrix_1, 10, 10);
  initMatrix(&matrix_2, 10, 10);

  setMatrix(&matrix_1, RANDOM);
  puts("\nMatrix_1");
  puts("----------------------------------------");
  printMatrix(matrix_1);

  setMatrix(&matrix_2, RANDOM);
  puts("\nMatrix_2");
  puts("----------------------------------------");
  printMatrix(matrix_2);

  addMatrix_1(&matrix_1, matrix_2);  // matrix_1 = matrix_1 + matrix_2
  puts("\nMatrix_1 = Matrix_1 + Matrix_2");
  puts("----------------------------------------");
  printMatrix(matrix_1);

  matrix_3 = addMatrix_2(matrix_1, matrix_2);  // matrix_3 = matrix_1 + matrix_2
  puts("\nMatrix_3 = Matrix_1 + Matrix_2");
  puts("----------------------------------------");
  printMatrix(*matrix_3);

  free(matrix_3);
  return 0;
}

int initMatrix(MATRIX *matrix, int col, int row) {
  int i;
  matrix->col = col;
  matrix->row = row;

  if ((col * row) > BUF_SIZE) return -1;

  for (i = 0; i < BUF_SIZE; i++) matrix->elements[i] = 0;
  return 0;
}

void setMatrix(MATRIX *matrix, int mode) {
  int i;
  if (mode == INCREASE) {
    for (i = 0; i < BUF_SIZE; i++) matrix->elements[i] = i;
  } else if (mode == RANDOM) {
    srand(time(NULL));
    for (i = 0; i < BUF_SIZE; i++) matrix->elements[i] = (rand() % 900) + 100;
  }
}

void addMatrix_1(MATRIX *matrix_a, MATRIX matrix_b) {
  int i, j;
  int col, row;
  if ((matrix_a->col != matrix_b.col) || (matrix_a->row != matrix_b.row)) {
    puts("ERR: Must have the same number of rows and columns.");
    exit(-1);  // return -1;
  }

  col = matrix_a->col;
  row = matrix_a->row;

  for (i = 0; i < col * row; i++)
    matrix_a->elements[i] = matrix_a->elements[i] + matrix_b.elements[i];
}

MATRIX *addMatrix_2(MATRIX matrix_a, MATRIX matrix_b) {
  int i, j;
  int col, row;
  MATRIX *pMatrix;
  if ((matrix_a.col != matrix_b.col) || (matrix_a.row != matrix_b.row)) {
    puts("ERR: Must have the same number of rows and columns.");
    exit(-1);  // return -1;
  }

  pMatrix = (MATRIX *)malloc(sizeof(MATRIX));
  initMatrix(pMatrix, matrix_a.col, matrix_a.row);

  col = matrix_a.col;
  row = matrix_a.row;
  for (i = 0; i < col * row; i++)
    pMatrix->elements[i] = matrix_a.elements[i] + matrix_b.elements[i];

  return pMatrix;
}

void printMatrix(MATRIX matrix) {
  int i, j;
  int col, row;

  for (i = 0; i < matrix.col; i++) {
    for (j = 0; j < matrix.row; j++) {
      printf("%4d ", matrix.elements[j + (i * matrix.row)]);
    }
    putchar('\n');
  }
}