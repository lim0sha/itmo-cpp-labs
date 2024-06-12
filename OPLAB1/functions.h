#pragma once
#include <iostream>
using namespace std;

struct point_t {
  float x;
  float y;
};

struct circle_t {
  point_t center;
  float radius;
};

struct matrix3x3_t {
  float data[3][3];
};

void encrease_r_ref(size_t &v1, size_t &v2);
void encrease_r_ptr(size_t *v1, size_t *v2);

void invert_rational_ref(double &value);
void invert_rational_ptr(double *value);

void decrease_ref(circle_t &circle, size_t &key);
void decrease_ptr(circle_t *circle, size_t *key);

void swap_lines_ref(matrix3x3_t &matrix, size_t &line1, size_t &line2);
void swap_lines_ptr(matrix3x3_t *matrix, size_t *line1, size_t *line2);

void make_default_matrix(matrix3x3_t& matrix);
void print_matrix(matrix3x3_t& matrix);