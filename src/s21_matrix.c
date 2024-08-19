#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int code = S21_SUC;
  if (result) {
    if (rows > 0 && columns > 0) {
      // s21_remove_matrix(result);
      result->rows = rows;
      result->columns = columns;
      result->matrix = calloc(rows, sizeof(double *));
      if (result->matrix == NULL) code = S21_INC;
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(sizeof(double), columns);
        if (result->matrix[i] == NULL) code = S21_INC;
      }
    } else {
      code = S21_INC;
    }
  } else {
    code = S21_INC;
  }

  return code;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      int rows = A->rows;
      for (int i = 0; i < rows; i++) {
        if (A->matrix[i] != NULL) free(A->matrix[i]);
      }
      free(A->matrix);
      A->rows = 0;
      A->columns = 0;
    }
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int code = FAILURE;
  if (eq_params_matrix(*A, *B)) {
    int flag = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
          flag = 1;
        }
      }
    }
    if (flag == 0) code = SUCCESS;
  }

  return code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = S21_SUC;
  if (A == NULL || B == NULL || result == NULL) code = S21_INC;
  if (code == S21_SUC)
    if (!eq_params_matrix(*A, *B)) code = S21_CALC;
  if (code == S21_SUC) code = s21_create_matrix(A->rows, A->columns, result);
  if (code == S21_SUC) {
    result->rows = A->rows;
    result->columns = A->columns;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = S21_SUC;
  if (A == NULL || B == NULL || result == NULL) code = S21_INC;
  if (code == S21_SUC)
    if (!eq_params_matrix(*A, *B)) code = S21_CALC;
  if (code == S21_SUC) code = s21_create_matrix(A->rows, A->columns, result);
  if (code == S21_SUC) {
    result->rows = A->rows;
    result->columns = A->columns;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }

  return code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int code = S21_SUC;
  if (A == NULL || result == NULL) code = S21_INC;
  if (code == S21_SUC) code = s21_create_matrix(A->rows, A->columns, result);
  if (code == S21_SUC) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = number * A->matrix[i][j];
      }
    }
  }

  return code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = S21_SUC;
  if (A == NULL || B == NULL || result == NULL) code = S21_INC;
  if (code == S21_SUC)
    if (A->columns != B->rows) code = S21_CALC;
  if (code == S21_SUC) code = s21_create_matrix(A->rows, B->columns, result);
  if (code == S21_SUC) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        double sum = 0;
        for (int k = 0; k < A->columns; k++) {
          sum += A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = sum;
      }
    }
  }

  return code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int code = S21_SUC;
  if (A == NULL || result == NULL) code = S21_INC;
  if (code == S21_SUC) code = s21_create_matrix(A->columns, A->rows, result);
  if (code == S21_SUC) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int code = S21_SUC;
  if (A == NULL || result == NULL) code = S21_INC;
  if (code == S21_SUC) {
    if (A->columns == 0 || A->rows == 0) code = S21_INC;
  }
  if (code == S21_SUC) {
    if (A->rows != A->columns || (A->rows < 2 && A->columns < 2))
      code = S21_CALC;
  }
  if (code == S21_SUC) code = s21_create_matrix(A->rows, A->columns, result);
  if (code == S21_SUC) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = pow(-1, i + j) * get_minor(*A, i, j);
      }
    }
  }

  return code;
}

int s21_determinant(matrix_t *A, double *result) {
  int code = S21_SUC;
  if (A == NULL || result == NULL) code = S21_INC;
  if (A->rows != A->columns) code = S21_CALC;
  if (code == S21_SUC) {
    *result = 0;
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows > 1) {
      matrix_t ALG;
      code = s21_calc_complements(A, &ALG);
      if (code == S21_SUC) {
        for (int i = 0; i < A->rows; i++) {
          *result += A->matrix[i][0] * ALG.matrix[i][0];
        }
        s21_remove_matrix(&ALG);
      }
    } else {
      code = S21_INC;
    }
  }

  return code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int code = S21_SUC;
  double delt = 0;
  matrix_t M, AT;
  if (A == NULL || result == NULL) code = S21_INC;
  if (A->rows != A->columns) code = S21_CALC;
  if (code == S21_SUC) code = s21_create_matrix(A->columns, A->rows, result);
  if (code == S21_SUC) {
    code = s21_determinant(A, &delt);
    if (code == S21_SUC && fabs(delt) < 1e-6) code = S21_CALC;
  }
  if (code == S21_SUC) code = s21_transpose(A, &AT);
  if (code == S21_SUC) {
    if (A->rows == 1) {
      result->matrix[0][0] = 1 / A->matrix[0][0];
    } else {
      code = s21_calc_complements(&AT, &M);
      if (code == S21_SUC) {
        s21_remove_matrix(result);
        code = s21_mult_number(&M, 1.0 / delt, result);
        s21_remove_matrix(&M);
      }
    }
    s21_remove_matrix(&AT);
  }

  return code;
}