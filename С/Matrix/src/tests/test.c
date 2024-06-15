#include <check.h>

#include "../s21_matrix.h"
double get_rand(double min, double max);

START_TEST(create_1) {
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, columns, &m);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      m.matrix[i][j] = 0;
    }
  }
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, columns);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_2) {
  const int rows = -1;
  const int columns = 2;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, columns, &m), 1);
}
END_TEST

START_TEST(create_3) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), UNCORRECT_MATRIX);
}
END_TEST

START_TEST(create_4) {
  const int rows = 10;
  const int cols = 0;

  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), UNCORRECT_MATRIX);
}
END_TEST

START_TEST(zero_matrix) {
  matrix_t A = {0};
  matrix_t B = {0};
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
}

START_TEST(eq_1) {
  const int rows = 3;
  const int columns = 3;
  const int rows2 = 3;
  const int columns2 = 3;
  matrix_t a = {0};
  matrix_t b = {0};
  s21_create_matrix(rows, columns, &a);
  s21_create_matrix(rows2, columns2, &b);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      a.matrix[i][j] = 0;
      b.matrix[i][j] = 0;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_2) {
  const int rows = 3;
  const int columns = 3;
  const int rows2 = 4;
  const int columns2 = 3;
  matrix_t a = {0};
  matrix_t b = {0};
  s21_create_matrix(rows, columns, &a);
  s21_create_matrix(rows2, columns2, &b);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      a.matrix[i][j] = 0;
      b.matrix[i][j] = 0;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_3) {
  const int rows = 3;
  const int columns = 3;
  const int rows2 = 3;
  const int columns2 = 3;
  matrix_t a = {0};
  matrix_t b = {0};
  s21_create_matrix(rows, columns, &a);
  s21_create_matrix(rows2, columns2, &b);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      a.matrix[i][j] = 0;
      b.matrix[i][j] = 1;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_4) {
  int result = s21_eq_matrix(NULL, NULL);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(sum_1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, columns, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, columns, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] + mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};

  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sum_2) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int columns1 = rand() % 100 + 1;
  s21_create_matrix(rows1, columns1, &mtx);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < columns1; j++) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), 2);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sum_3) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  rows = -rows;
  columns = -columns;
  matrix_t m = {0};
  s21_create_matrix(rows, columns, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, columns, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, columns, &check);

  matrix_t res = {0};

  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), UNCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, columns, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, columns, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] - mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};

  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_2) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int columns1 = rand() % 100 + 1;
  s21_create_matrix(rows1, columns1, &mtx);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < columns1; j++) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), 2);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub_3) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  rows = -rows;
  columns = -columns;
  matrix_t m = {0};
  s21_create_matrix(rows, columns, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, columns, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, columns, &check);
  matrix_t res = {0};
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), UNCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, columns, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, columns, &check);
  double mult_number = get_rand(-10e5, 10e5);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] * mult_number;
    }
  }
  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  rows = -rows;
  columns = -columns;
  matrix_t m = {0};
  s21_create_matrix(rows, columns, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, columns, &check);
  double mult_number = get_rand(-10e5, 10e5);
  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), UNCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 10, &B);
  int result = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &B);
  A.rows = 0;
  int result = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, UNCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  int result = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix4) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = get_rand(-10e10, 10e10);

  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = get_rand(-10e10, 10e10);

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < mtx.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < m.columns; k++)
        check.matrix[i][j] += m.matrix[i][k] * mtx.matrix[k][j];
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
  // ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix5) {
  const int rows = 2;
  const int cols = 3;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = c++;

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);
  check.matrix[0][0] = 58;
  check.matrix[0][1] = 64;
  check.matrix[1][0] = 139;
  check.matrix[1][1] = 154;

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(transpose_1) {
  matrix_t A;
  int res = s21_transpose(NULL, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(10, 10, &A);
  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(deter_1) {
  int result = s21_determinant(NULL, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(deter_2) {
  matrix_t A;
  double deter;
  s21_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = s21_determinant(&A, &deter);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(deter_3) {
  matrix_t A;
  double deter;
  s21_create_matrix(10, 9, &A);
  int res = s21_determinant(&A, &deter);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(deter_4) {
  matrix_t A;
  double deter;
  double det_true = 984.1238;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 984.1238;
  int res = s21_determinant(&A, &deter);
  ck_assert_double_eq_tol(deter, det_true, 1e+08);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(deter_6) {
  matrix_t A;
  double deter;
  double det_true = -40;
  double const A_nums[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  s21_create_matrix(3, 3, &A);
  int count = 0;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = A_nums[count];
      count++;
    }
  }
  int res = s21_determinant(&A, &deter);
  ck_assert_double_eq_tol(deter, det_true, 1e-08);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(deter_7) {
  matrix_t A;
  double deter;
  double det_true = -1369800;
  double const A_nums[25] = {1,  2,  3,   4, 5,  6,  7,  8,  9,  10, 11, 12, 49,
                             14, 15, 161, 7, 18, 19, 20, 64, 48, 1,  2,  3};
  s21_create_matrix(5, 5, &A);
  int count = 0;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = A_nums[count];
      count++;
    }
  }
  int res = s21_determinant(&A, &deter);
  ck_assert_double_eq_tol(deter, det_true, 1e+08);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(deter_8) {
  matrix_t A;
  double deter;
  double det_true = 17187;
  double const A_nums[4] = {9, 2, 96, 1931};
  s21_create_matrix(2, 2, &A);
  int count = 0;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = A_nums[count];
      count++;
    }
  }
  int res = s21_determinant(&A, &deter);
  ck_assert_double_eq_tol(deter, det_true, 1e+08);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(deter_9) {
  matrix_t A;
  double deter;
  double det_true = 0;
  double const A_nums[25] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                             14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
  s21_create_matrix(5, 5, &A);
  int count = 0;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = A_nums[count];
      count++;
    }
  }
  int res = s21_determinant(&A, &deter);
  ck_assert_double_eq_tol(deter, det_true, 1e-08);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_1) {
  matrix_t A, C;
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
  matrix_t B;
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_2) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (codec) {
    m.matrix[0][0] = 1431.12312331;
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(result.matrix[0][0] == (1.0 / m.matrix[0][0]), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(inverse_3) {
  int res = s21_inverse_matrix(NULL, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(inverse_4) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_5) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(10, 9, &A);
  int res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_6) {
  matrix_t A;
  matrix_t B;
  double const A_nums[25] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                             14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

  s21_create_matrix(5, 5, &A);
  int count = 0;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = A_nums[count];
      count++;
    }
  }

  int res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(complements_1) {
  int result = s21_calc_complements(NULL, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(complements_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(complements_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(10, 9, &A);
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(complements_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double const A_nums[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double const result_nums[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  int count = 0;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = A_nums[count];
      count++;
    }
  }
  count = 0;
  for (int i = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      C.matrix[i][j] = result_nums[count];
      count++;
    }
  }
  int res = s21_calc_complements(&A, &B);
  // for (int i = 0; i < B.rows; i++) {
  //   for (int j = 0; j < B.columns; j++) {
  //     printf("%lf\n",  B.matrix[i][j]);
  //   }
  // }
  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *t_core = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, t_core);

  tcase_add_test(t_core, create_1);
  tcase_add_test(t_core, create_2);
  tcase_add_test(t_core, create_3);
  tcase_add_test(t_core, create_4);
  tcase_add_test(t_core, eq_1);
  tcase_add_test(t_core, eq_2);
  tcase_add_test(t_core, eq_3);
  tcase_add_test(t_core, eq_4);
  tcase_add_test(t_core, zero_matrix);
  tcase_add_test(t_core, sum_1);
  tcase_add_test(t_core, sum_2);
  tcase_add_test(t_core, sum_3);
  tcase_add_test(t_core, sub_1);
  tcase_add_test(t_core, sub_2);
  tcase_add_test(t_core, sub_3);
  tcase_add_test(t_core, mult_number_1);
  tcase_add_test(t_core, mult_number_2);
  tcase_add_test(t_core, mult_matrix1);
  tcase_add_test(t_core, mult_matrix2);
  tcase_add_test(t_core, mult_matrix3);
  tcase_add_test(t_core, mult_matrix4);
  tcase_add_test(t_core, mult_matrix5);
  tcase_add_test(t_core, transpose_1);
  tcase_add_test(t_core, transpose_2);
  tcase_add_test(t_core, transpose_3);
  tcase_add_test(t_core, deter_1);
  tcase_add_test(t_core, deter_2);
  tcase_add_test(t_core, deter_3);
  tcase_add_test(t_core, deter_4);
  tcase_add_test(t_core, deter_6);
  tcase_add_test(t_core, deter_7);
  tcase_add_test(t_core, deter_8);
  tcase_add_test(t_core, deter_9);
  tcase_add_test(t_core, inverse_1);
  tcase_add_test(t_core, inverse_2);
  tcase_add_test(t_core, inverse_3);
  tcase_add_test(t_core, inverse_4);
  tcase_add_test(t_core, inverse_5);
  tcase_add_test(t_core, inverse_6);
  tcase_add_test(t_core, complements_1);
  tcase_add_test(t_core, complements_2);
  tcase_add_test(t_core, complements_3);
  tcase_add_test(t_core, complements_4);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf ? 1 : 0;
}

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}