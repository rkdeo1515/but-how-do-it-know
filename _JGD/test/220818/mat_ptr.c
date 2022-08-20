#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// ref : https://matrixcalc.org/

/* ---------- DEFINES ---------- */
#define SEMANTIC_CODE 0
#define ZERO_FILL 0
#define INCREASE_FILL 1
#define RANDOM_FILL 2

/* ---------- STRUCTS ---------- */
typedef struct MATRIX_ {
  uint32_t row;  // Number of row
  uint32_t col;  // Number of column
  int *elements;
} MATRIX;

/* ---------- PROTOTYPES ---------- */
MATRIX *initMatrix(uint32_t row, uint32_t col);
void deleteMatrix(MATRIX *matrix);
void fillMatrix(MATRIX *matrix, uint32_t fillmode);
void printMatrix(MATRIX matrix);

void setElement(MATRIX *matrix, uint32_t row, uint32_t col, int val);
int getElement(MATRIX matrix, uint32_t row, uint32_t col);

MATRIX *addMatrix(MATRIX matrix_a, MATRIX matrix_b);
MATRIX *mulMatrix(MATRIX matrix_a, MATRIX matrix_b);

/* ---------- MAIN ---------- */
int main(int argc, char *argv[]) {
  MATRIX *matrix_1 = initMatrix(4, 6);
  MATRIX *matrix_2 = initMatrix(6, 2);

  fillMatrix(matrix_1, RANDOM_FILL);
  puts("Matrix_1");
  puts("-------------------------------------------------");
  printMatrix(*matrix_1);
  putchar('\n');

  fillMatrix(matrix_2, RANDOM_FILL);
  puts("Matrix_2");
  puts("-------------------------------------------------");
  printMatrix(*matrix_2);
  putchar('\n');

  // MATRIX *matrix_3 = addMatrix(*matrix_1, *matrix_2);
  // puts("Matrix_1 + Matrix_2 = Matrix_3");
  // puts("-------------------------------------------------");
  // printMatrix(*matrix_3);
  // putchar('\n');

  MATRIX *matrix_3 = mulMatrix(*matrix_1, *matrix_2);
  puts("Matrix_1 * Matrix_2 = Matrix_3");
  puts("-------------------------------------------------");
  printMatrix(*matrix_3);
  putchar('\n');

  deleteMatrix(matrix_1);
  deleteMatrix(matrix_2);
  deleteMatrix(matrix_3);
  return 0;
}

/* ---------- FUNCTIONS ---------- */
MATRIX *initMatrix(uint32_t row, uint32_t col) {
  // check size
  MATRIX *matrix = (MATRIX *)malloc(sizeof(MATRIX));
  // if ((matrix->row * matrix->col) > MAX_SIZE) exit(EXIT_FAILURE);

  matrix->row = row;
  matrix->col = col;

  matrix->elements = (int *)malloc(row * col * sizeof(int));
  fillMatrix(matrix, ZERO_FILL);

  return matrix;
}

void deleteMatrix(MATRIX *matrix) {
  free(matrix->elements);
  free(matrix);
}

void fillMatrix(MATRIX *matrix, uint32_t fillmode) {
  uint32_t i;
  uint32_t size = matrix->row * matrix->col;
  int *ptr = matrix->elements;

  switch (fillmode) {
    case ZERO_FILL:
      for (i = 0; i < size; i++) *(matrix->elements + i) = 0;
      break;
    case INCREASE_FILL:
      for (i = 0; i < size; i++) *(matrix->elements + i) = i + 1;
      break;
    case RANDOM_FILL:
      for (i = 0; i < size; i++) *(matrix->elements + i) = (rand() % 900) + 100;
      break;
  }
}

void setElement(MATRIX *matrix, uint32_t row, uint32_t col, int val) {
  // if (!(matrix->row > row && matrix->col > col)) exit(EXIT_FAILURE);
  *(matrix->elements + (matrix->col * row + col)) = val;
}

int getElement(MATRIX matrix, uint32_t row, uint32_t col) {
  // if (!(matrix.row > row && matrix.col > col)) exit(EXIT_FAILURE);
  return *(matrix.elements + (matrix.col * row + col));
}

MATRIX *addMatrix(MATRIX matrix_a, MATRIX matrix_b) {
  if (!((matrix_a.row == matrix_b.row) && (matrix_a.col == matrix_b.col)))
    exit(EXIT_FAILURE);
  MATRIX *matrix_y = initMatrix(matrix_a.row, matrix_a.col);

#if SEMANTIC_CODE
  // Sementic code
  uint32_t m, n;
  for (m = 0; m < matrix_y->row; m++)
    for (n = 0; n < matrix_y->col; n++)
      setElement(matrix_y, m, n,
                 getElement(matrix_a, m, n) + getElement(matrix_b, m, n));
#else
  // Simple code
  uint32_t i;
  for (i = 0; i < matrix_y->row * matrix_y->col; i++)
    *(matrix_y->elements + i) =
        *(matrix_a.elements + i) + *(matrix_b.elements + i);

#endif
  return matrix_y;
}

MATRIX *mulMatrix(MATRIX matrix_a, MATRIX matrix_b) {
  uint32_t tmp;
  int acc;

  // (m*n) x (n*p) = m*p
  if (!(matrix_a.col == matrix_b.row)) exit(EXIT_FAILURE);

  tmp = matrix_a.col;
  MATRIX *matrix_y = initMatrix(matrix_a.row, matrix_b.col);

#if SEMANTIC_CODE
  // Sementic code
  uint32_t m, n, p;
  for (m = 0; m < matrix_y->row; m++) {
    for (p = 0; p < matrix_y->col; p++) {
      acc = 0;
      for (n = 0; n < tmp; n++) {
        acc += getElement(matrix_a, m, n) * getElement(matrix_b, n, p);
      }
      setElement(matrix_y, m, p, acc);
    }
  }
#else
  // Simple code
  int i, j;
  for (i = 0; i < matrix_y->row * matrix_y->col; i++) {
    acc = 0;
    for (j = 0; j < tmp; j++) {
      acc += *(matrix_a.elements + (i / matrix_y->col * matrix_a.col + j)) *
             *(matrix_b.elements + (j * matrix_b.col + i % matrix_y->col));
    }
    *(matrix_y->elements + i) = acc;
  }
#endif
  return matrix_y;
}

void printMatrix(MATRIX matrix) {
#if SEMANTIC_CODE
  uint32_t m, n;
  for (m = 0; m < matrix.row; m++) {
    for (n = 0; n < matrix.col; n++) {
      printf("%4d%c", *(matrix.elements + (matrix.col * m + n)),
             n == matrix.col - 1 ? '\n' : ' ');
    }
  }
#else
  uint32_t i;
  for (i = 0; i < matrix.row * matrix.col; i++) {
    printf("%4d%c", *(matrix.elements + i),
           (i + 1) % matrix.col == 0 && (i + 1) > 0 ? '\n' : ' ');
  }
#endif
}