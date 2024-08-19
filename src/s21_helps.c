#include "s21_matrix.h"

int eq_params_matrix(matrix_t A, matrix_t B) {
  int code = 0;
  if (A.columns == B.columns && A.rows == B.rows) code = 1;

  return code;
}

double get_minor(matrix_t A, int row, int column) {
  double minor = 0;

  if (A.rows == 2 && A.columns == 2) {
    if (row == 0 && column == 0) minor = A.matrix[1][1];
    if (row == 0 && column == 1) minor = A.matrix[1][0];
    if (row == 1 && column == 0) minor = A.matrix[0][1];
    if (row == 1 && column == 1) minor = A.matrix[0][0];
  } else {
    matrix_t B;
    s21_create_matrix(A.rows - 1, A.columns - 1, &B);
    int arow = 0, acol = 0;
    for (int i = 0; i < B.rows; i++) {
      for (int j = 0; j < B.columns; j++) {
        arow = i;
        acol = j;
        if (arow >= row) arow++;
        if (acol >= column) acol++;
        B.matrix[i][j] = A.matrix[arow][acol];
      }
    }
    for (int i = 0; i < B.rows; i++) {
      minor += pow(-1, i) * B.matrix[i][0] * get_minor(B, i, 0);
    }
    s21_remove_matrix(&B);
  }

  return minor;
}
