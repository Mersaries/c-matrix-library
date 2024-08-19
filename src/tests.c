#include <check.h>
#include <time.h>

#include "s21_matrix.h"

START_TEST(s21_create_matrix_1) {
  srand(time(NULL));
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(rand() % 100, rand() % 100, &A), S21_SUC);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  srand(time(NULL));
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(-rand() % 100, rand() % 100, &A), S21_INC);
}
END_TEST

START_TEST(s21_create_matrix_3) {
  srand(time(NULL));
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(rand() % 100, -rand() % 100, &A), S21_INC);
}
END_TEST

START_TEST(s21_create_matrix_4) {
  srand(time(NULL));
  ck_assert_int_eq(s21_create_matrix(-rand() % 100, rand() % 100, NULL),
                   S21_INC);
}
END_TEST

START_TEST(s21_eq_matrix_1) {
  srand(time(NULL));
  matrix_t A;
  s21_create_matrix(10, 10, &A);
  matrix_t B;
  s21_create_matrix(10, 10, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
      B.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  srand(time(NULL));
  matrix_t A;
  s21_create_matrix(10, 10, &A);
  matrix_t B;
  s21_create_matrix(10, 10, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
      B.matrix[i][j] = A.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_3) {
  srand(time(NULL));
  matrix_t A;
  s21_create_matrix(10, 10, &A);
  matrix_t B;
  s21_create_matrix(5, 5, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_1) {
  matrix_t A, B, RES, REAL;
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &B);
  s21_create_matrix(10, 10, &REAL);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
      B.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
      REAL.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &RES), S21_SUC);
  ck_assert_int_eq(s21_eq_matrix(&RES, &REAL), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&RES);
  s21_remove_matrix(&REAL);
}
END_TEST

START_TEST(s21_sum_matrix_2) {
  matrix_t A, B, RES, REAL;
  s21_create_matrix(10, 20, &A);
  s21_create_matrix(10, 20, &B);
  s21_create_matrix(10, 20, &REAL);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = (rand() % 10 < 5 ? 1 : -1) * rand() % 100 +
                       (rand() % 10000) / 1000000;
      B.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
      REAL.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &RES), S21_SUC);
  ck_assert_int_eq(s21_eq_matrix(&RES, &REAL), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&RES);
  s21_remove_matrix(&REAL);
}
END_TEST

START_TEST(s21_sum_matrix_3) {
  matrix_t A, B, RES, REAL;
  s21_create_matrix(10, 1, &A);
  s21_create_matrix(10, 1, &B);
  s21_create_matrix(10, 1, &REAL);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = (rand() % 10 < 5 ? 1 : -1) * rand() % 100 +
                       (rand() % 10000) / 1000000;
      B.matrix[i][j] = (rand() % 10 < 5 ? 1 : -1) * rand() % 100 +
                       (rand() % 10000) / 1000000;
      REAL.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &RES), S21_SUC);
  ck_assert_int_eq(s21_eq_matrix(&RES, &REAL), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&RES);
  s21_remove_matrix(&REAL);
}
END_TEST

START_TEST(s21_sum_matrix_4) {
  matrix_t A, B, RES;
  s21_create_matrix(10, 1, &A);
  s21_create_matrix(10, 2, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &RES), S21_CALC);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_5) {
  matrix_t A, B, RES;
  s21_create_matrix(10, 50, &A);
  s21_create_matrix(1, 50, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &RES), S21_CALC);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_6) {
  matrix_t B, RES;
  s21_create_matrix(1, 50, &B);
  ck_assert_int_eq(s21_sum_matrix(NULL, &B, &RES), S21_INC);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_7) {
  matrix_t A, B;
  s21_create_matrix(10, 50, &A);
  s21_create_matrix(10, 50, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), S21_INC);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_1) {
  matrix_t A, B, RES, REAL;
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &B);
  s21_create_matrix(10, 10, &REAL);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
      B.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
      REAL.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &RES), S21_SUC);
  ck_assert_int_eq(s21_eq_matrix(&RES, &REAL), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&RES);
  s21_remove_matrix(&REAL);
}
END_TEST

START_TEST(s21_sub_matrix_2) {
  matrix_t A, B, RES, REAL;
  s21_create_matrix(10, 20, &A);
  s21_create_matrix(10, 20, &B);
  s21_create_matrix(10, 20, &REAL);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = (rand() % 10 < 5 ? 1 : -1) * rand() % 100 +
                       (rand() % 10000) / 1000000;
      B.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
      REAL.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &RES), S21_SUC);
  ck_assert_int_eq(s21_eq_matrix(&RES, &REAL), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&RES);
  s21_remove_matrix(&REAL);
}
END_TEST

START_TEST(s21_sub_matrix_3) {
  matrix_t A, B, RES, REAL;
  s21_create_matrix(10, 1, &A);
  s21_create_matrix(10, 1, &B);
  s21_create_matrix(10, 1, &REAL);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = (rand() % 10 < 5 ? 1 : -1) * rand() % 100 +
                       (rand() % 10000) / 1000000;
      B.matrix[i][j] = (rand() % 10 < 5 ? 1 : -1) * rand() % 100 +
                       (rand() % 10000) / 1000000;
      REAL.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &RES), S21_SUC);
  ck_assert_int_eq(s21_eq_matrix(&RES, &REAL), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&RES);
  s21_remove_matrix(&REAL);
}
END_TEST

START_TEST(s21_sub_matrix_4) {
  matrix_t A, B, RES;
  s21_create_matrix(10, 1, &A);
  s21_create_matrix(10, 2, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &RES), S21_CALC);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_5) {
  matrix_t A, B, RES;
  s21_create_matrix(10, 50, &A);
  s21_create_matrix(1, 50, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &RES), S21_CALC);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_6) {
  matrix_t B, RES;
  s21_create_matrix(1, 50, &B);
  ck_assert_int_eq(s21_sub_matrix(NULL, &B, &RES), S21_INC);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_7) {
  matrix_t A, B;
  s21_create_matrix(10, 50, &A);
  s21_create_matrix(10, 50, &B);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), S21_INC);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_mult_number_1) {
  matrix_t A, RES, REAL;
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &REAL);
  double n = (rand() % 1000 + 100) * 2;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
      REAL.matrix[i][j] = A.matrix[i][j] * n;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, n, &RES), S21_SUC);
  ck_assert_int_eq(s21_eq_matrix(&RES, &REAL), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&RES);
  s21_remove_matrix(&REAL);
}
END_TEST

START_TEST(s21_mult_number_2) {
  matrix_t A, RES, REAL;
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &REAL);
  double n = 0;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = rand() % 100 + (rand() % 10000) / 1000000;
      REAL.matrix[i][j] = A.matrix[i][j] * n;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, n, &RES), S21_SUC);
  ck_assert_int_eq(s21_eq_matrix(&RES, &REAL), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&RES);
  s21_remove_matrix(&REAL);
}
END_TEST

START_TEST(s21_mult_matrix_1) {
  matrix_t A, B, RES, REAL;

  ck_assert_int_eq(s21_create_matrix(3, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 3, &B), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &REAL), 0);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = (rand() % 10 < 5 ? 1 : -1) * rand() % 100;
    }
  }
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = (rand() % 10 < 5 ? 1 : -1) * rand() % 100;
    }
  }
  for (int i = 0; i < REAL.rows; i++) {
    for (int j = 0; j < REAL.columns; j++) {
      REAL.matrix[i][j] = 0;
      for (int m = 0; m < B.rows; m++)
        REAL.matrix[i][j] += A.matrix[i][m] * B.matrix[m][j];
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &RES), S21_SUC);
  ck_assert_int_eq(s21_eq_matrix(&RES, &REAL), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&RES);
  s21_remove_matrix(&REAL);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  matrix_t *res = {0}, *A = {0};
  ck_assert_int_eq(s21_mult_matrix(NULL, NULL, NULL), S21_INC);
  ck_assert_int_eq(s21_mult_matrix(NULL, NULL, res), S21_INC);
  ck_assert_int_eq(s21_mult_matrix(A, NULL, NULL), S21_INC);
}
END_TEST

START_TEST(s21_transpose_1) {
  matrix_t A, RES, REAL;

  ck_assert_int_eq(s21_create_matrix(3, 2, &A), 0);
  ck_assert_int_eq(s21_create_matrix(2, 3, &REAL), 0);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = (rand() % 10 < 5 ? 1 : -1) * rand() % 100;
      REAL.matrix[j][i] = A.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &RES), S21_SUC);
  ck_assert_int_eq(s21_eq_matrix(&RES, &REAL), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&RES);
  s21_remove_matrix(&REAL);
}
END_TEST

START_TEST(s21_transpose_2) {
  matrix_t *res = {0}, *A = {0};
  ck_assert_int_eq(s21_transpose(NULL, NULL), S21_INC);
  ck_assert_int_eq(s21_transpose(NULL, res), S21_INC);
  ck_assert_int_eq(s21_transpose(A, NULL), S21_INC);
}
END_TEST

START_TEST(s21_calc_complements_1) {
  matrix_t A = {0}, B = {0}, C = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &C);
  A.matrix[0][0] = 1.0;
  s21_calc_complements(&A, &B);
  C.matrix[0][0] = 0.0;
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  matrix_t A = {0}, B = {0}, C = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &C);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  s21_calc_complements(&A, &B);
  C.matrix[0][0] = 0.0;
  C.matrix[0][1] = 10.0;
  C.matrix[1][0] = 4.0;
  C.matrix[1][1] = -14.0;
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  matrix_t A = {0}, B = {0}, C = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &C);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  s21_calc_complements(&A, &B);
  C.matrix[0][0] = 0.0;
  C.matrix[0][1] = 10.0;
  C.matrix[1][0] = 4.0;
  C.matrix[1][1] = -14.0;
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_complements_4) {
  matrix_t A = {0}, B = {0}, C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  s21_calc_complements(&A, &B);
  C.matrix[0][0] = 0.0;
  C.matrix[0][1] = 10.0;
  C.matrix[0][2] = -20.0;
  C.matrix[1][0] = 4.0;
  C.matrix[1][1] = -14.0;
  C.matrix[1][2] = 8.0;
  C.matrix[2][0] = -8.0;
  C.matrix[2][1] = -2.0;
  C.matrix[2][2] = 4.0;
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_complements_5) {
  matrix_t a = {0};
  matrix_t b = {0};
  ck_assert_int_eq(s21_calc_complements(&a, &b), S21_INC);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(s21_calc_complements_6) {
  matrix_t a = {0};
  matrix_t b = {0};
  s21_create_matrix(1, 2, &a);
  ck_assert_int_eq(s21_calc_complements(&a, &b), S21_CALC);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(s21_calc_complements_7) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;
  matrix_t res = {0};
  s21_calc_complements(&m, &res);
  ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(s21_calc_complements_8) {
  matrix_t a = {0};
  matrix_t b = {0};
  s21_create_matrix(1, 2, &a);
  ck_assert_int_eq(s21_calc_complements(&a, &b), S21_CALC);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(s21_calc_complements_9) {
  matrix_t *res = {0}, *A = {0};
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), S21_INC);
  ck_assert_int_eq(s21_calc_complements(NULL, res), S21_INC);
  ck_assert_int_eq(s21_calc_complements(A, NULL), S21_INC);
}
END_TEST

START_TEST(s21_inverse_matrix_1) {
  matrix_t A = {0}, B = {0}, C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 44300.0 / 367429.0;
  C.matrix[0][1] = -236300.0 / 367429.0;
  C.matrix[0][2] = 200360.0 / 367429.0;
  C.matrix[1][0] = 20600.0 / 367429.0;
  C.matrix[1][1] = 56000.0 / 367429.0;
  C.matrix[1][2] = -156483.0 / 367429.0;
  C.matrix[2][0] = 30900.0 / 367429.0;
  C.matrix[2][1] = 84000.0 / 367429.0;
  C.matrix[2][2] = -51010.0 / 367429.0;
  A.matrix[0][0] = 2.8;
  A.matrix[0][1] = 1.3;
  A.matrix[0][2] = 7.01;
  A.matrix[1][0] = -1.03;
  A.matrix[1][1] = -2.3;
  A.matrix[1][2] = 3.01;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = -3;
  A.matrix[2][2] = 2;
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  matrix_t A = {0}, C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  matrix_t B = {0};
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    m.matrix[0][0] = 1431.12312331;
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_double_eq_tol(result.matrix[0][0], 1.0 / m.matrix[0][0], 1e-6);
    ck_assert_int_eq(code, S21_SUC);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(s21_inverse_matrix_4) {
  matrix_t *res = {0}, *A = {0};
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), S21_INC);
  ck_assert_int_eq(s21_calc_complements(NULL, res), S21_INC);
  ck_assert_int_eq(s21_calc_complements(A, NULL), S21_INC);
}
END_TEST

START_TEST(s21_determinant_1) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, S21_SUC);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(s21_determinant_2) {
  const int size = 4;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j + i;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, S21_SUC);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(s21_determinant_3) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][1] = 6;
  m.matrix[0][2] = -2;
  m.matrix[0][3] = -1;
  m.matrix[0][4] = 5;
  m.matrix[1][3] = -9;
  m.matrix[1][4] = -7;
  m.matrix[2][1] = 15;
  m.matrix[2][2] = 35;
  m.matrix[3][1] = -1;
  m.matrix[3][2] = -11;
  m.matrix[3][3] = -2;
  m.matrix[3][4] = 1;
  m.matrix[4][0] = -2;
  m.matrix[4][1] = -2;
  m.matrix[4][2] = 3;
  m.matrix[4][4] = -2;

  double res = 0;
  ck_assert_int_eq(s21_determinant(&m, &res), S21_SUC);
  ck_assert_double_eq_tol(res, 2480, 1e-6);

  s21_remove_matrix(&m);
}
END_TEST

int main() {
  Suite *suite_case = suite_create("s21_matrix");
  TCase *test_case = tcase_create("s21_matrix_tests");

  SRunner *runner = srunner_create(suite_case);
  suite_add_tcase(suite_case, test_case);
  tcase_add_loop_test(test_case, s21_create_matrix_1, 0, 10);
  tcase_add_test(test_case, s21_create_matrix_2);
  tcase_add_test(test_case, s21_create_matrix_3);
  tcase_add_test(test_case, s21_create_matrix_4);
  tcase_add_test(test_case, s21_eq_matrix_1);
  tcase_add_test(test_case, s21_eq_matrix_2);
  tcase_add_test(test_case, s21_eq_matrix_3);
  tcase_add_test(test_case, s21_sum_matrix_1);
  tcase_add_test(test_case, s21_sum_matrix_2);
  tcase_add_test(test_case, s21_sum_matrix_3);
  tcase_add_test(test_case, s21_sum_matrix_4);
  tcase_add_test(test_case, s21_sum_matrix_5);
  tcase_add_test(test_case, s21_sum_matrix_6);
  tcase_add_test(test_case, s21_sum_matrix_7);
  tcase_add_test(test_case, s21_sub_matrix_1);
  tcase_add_test(test_case, s21_sub_matrix_2);
  tcase_add_test(test_case, s21_sub_matrix_3);
  tcase_add_test(test_case, s21_sub_matrix_4);
  tcase_add_test(test_case, s21_sub_matrix_5);
  tcase_add_test(test_case, s21_sub_matrix_6);
  tcase_add_test(test_case, s21_sub_matrix_7);
  tcase_add_loop_test(test_case, s21_mult_number_1, 0, 20);
  tcase_add_loop_test(test_case, s21_mult_number_2, 0, 20);
  tcase_add_loop_test(test_case, s21_mult_matrix_1, 0, 20);
  tcase_add_test(test_case, s21_mult_matrix_2);
  tcase_add_test(test_case, s21_calc_complements_1);
  tcase_add_test(test_case, s21_calc_complements_2);
  tcase_add_test(test_case, s21_calc_complements_3);
  tcase_add_test(test_case, s21_calc_complements_4);
  tcase_add_test(test_case, s21_calc_complements_5);
  tcase_add_test(test_case, s21_calc_complements_6);
  tcase_add_test(test_case, s21_calc_complements_7);
  tcase_add_test(test_case, s21_calc_complements_8);
  tcase_add_test(test_case, s21_calc_complements_9);
  tcase_add_test(test_case, s21_inverse_matrix_1);
  tcase_add_test(test_case, s21_inverse_matrix_2);
  tcase_add_test(test_case, s21_inverse_matrix_3);
  tcase_add_test(test_case, s21_inverse_matrix_4);
  tcase_add_test(test_case, s21_determinant_1);
  tcase_add_test(test_case, s21_determinant_2);
  tcase_add_test(test_case, s21_determinant_3);
  tcase_add_loop_test(test_case, s21_transpose_1, 0, 10);
  tcase_add_test(test_case, s21_transpose_2);

  srunner_run_all(runner, CK_ENV);
  srunner_free(runner);
}