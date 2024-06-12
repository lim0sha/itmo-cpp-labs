#include "functions.h"
#include <cstring>

using namespace std;

void encrease_r_ref(size_t &v1, size_t &v2) {
  size_t maximum = std::max(v1, v2);
  size_t minimum = std::min(v1, v2);
  size_t reminder = maximum % minimum;
  if (v1 == maximum) {
    v1 += reminder;
  } else {
    v2 += reminder;
  }
}
void encrease_r_ptr(size_t *v1, size_t *v2) {
  size_t maximum = std::max(*v1, *v2);
  size_t minimum = std::min(*v1, *v2);
  size_t reminder = maximum % minimum;
  if (*v1 == maximum) {
    *v1 += reminder;
  } else {
    *v2 += reminder;
  }
}

void invert_rational_ref(double &value) {
  value = 1 / value;
}
void invert_rational_ptr(double *value) {
  *value = 1 / *value;
}

void decrease_ref(circle_t &circle, size_t &key) {
  circle.radius -= key;
}
void decrease_ptr(circle_t *circle, size_t *key) {
  circle->radius -= *key;
}

void swap_lines_ref(matrix3x3_t &matrix, size_t &line1, size_t &line2) {
  for (int i = 0; i < 3; ++i) {
    swap(matrix.data[line1 - 1][i], matrix.data[line2 - 1][i]);
  }
}

void swap_lines_ptr(matrix3x3_t *matrix, size_t *line1, size_t *line2) {
  for (size_t i = 0; i < 3; ++i) {
    float temp = matrix->data[*line1 - 1][i];
    matrix->data[*line1 - 1][i] = matrix->data[*line2 - 1][i];
    matrix->data[*line2 - 1][i] = temp;
  }
}

void make_default_matrix(matrix3x3_t &matrix) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      matrix.data[i][j] = 3 * i + j + 1;
    }
  }
}

void print_matrix(matrix3x3_t &matrix) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      cout << matrix.data[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

int main(int argc, char *argv[]) {
  if (argc > 1 && strcmp(argv[1], "autotest") == 0) {
    //const int& ref =
    // encrease_r demo
    cout << "ENCREASING A NUMBER BY REMINDER TEST\n";
    size_t a = 6;
    size_t b = 5;
    size_t *a_ptr = &a;
    size_t *b_ptr = &b;
    cout << a << " " << b << " - before ref swap\n";
    encrease_r_ref(a, b);
    cout << a << " " << b << " - after ref swap\n";
    encrease_r_ptr(a_ptr, b_ptr);
    cout << a << " " << b << " - after ptr swap\n\n";

    // invert_rational demo
    cout << "INVERTING RATIONAL NUMBER TEST\n";
    double value = 5;
    double *value_ptr = &value;
    cout << value << " - default value before function has worked\n";
    invert_rational_ref(value);
    cout << value << " - value after ref function has worked\n";
    invert_rational_ptr(value_ptr);
    cout << value << " - value after ptr function has worked\n\n";

    // decrease demo
    cout << "DECREASING CIRCLE RADIUS TEST\n";
    circle_t circle{};
    circle.center.x = 10;
    circle.center.y = 10;
    circle.radius = 10;
    size_t key = 2;
    circle_t *circle_ptr = &circle;
    size_t *key_ptr = &key;
    decrease_ref(circle, key);
    cout << circle.radius << " - radius before decreasing\n";
    decrease_ptr(circle_ptr, key_ptr);
    cout << circle.radius << " - radius after decreasing\n\n";

    // swap_lines demo
    cout << "MATRIX SWAP LINES TEST\n";
    matrix3x3_t matrix{};
    matrix3x3_t *matrix_ptr = &matrix;
    size_t line1 = 1;
    size_t line2 = 3;
    size_t *line1_ptr = &line1;
    size_t *line2_ptr = &line2;
    make_default_matrix(matrix);
    cout << "Matrix before lines swap:\n";
    print_matrix(matrix);
    swap_lines_ref(matrix, line1, line2);
    cout << "Matrix after 1st lines swap:\n";
    print_matrix(matrix);
    swap_lines_ptr(matrix_ptr, line1_ptr, line2_ptr);
    cout << "Matrix after 2nd lines swap:\n";
    print_matrix(matrix);

  } else {
    cout << "Enter a type of function you want to demonstrate\n";
    cout << "1 - for 'Encrease_r' functions\n";
    cout << "2 - for 'Invert_rational' function\n";
    cout << "3 - for 'Decrease' function\n";
    cout << "4 - for 'Swap_lines' function\n";
    cout << "0 - to finish executing\n";
    int input;
    while (true) {
      cin >> input;
      switch (input) {
        case 1: {
          // encrease_r demo
          size_t a = 6;
          size_t b = 5;
          size_t *a_ptr = &a;
          size_t *b_ptr = &b;
          cout << a << " " << b << " - before ref swap\n";
          encrease_r_ref(a, b);
          cout << a << " " << b << " - after ref swap\n";
          encrease_r_ptr(a_ptr, b_ptr);
          cout << a << " " << b << " - after ptr swap\n\n";
          break;
        }
        case 2: {
          // invert_rational demo
          double value = 5;
          double *value_ptr = &value;
          cout << value << " - default value before function has worked\n";
          invert_rational_ref(value);
          cout << value << " - value after ref function has worked\n";
          invert_rational_ptr(value_ptr);
          cout << value << " - value after ptr function has worked\n\n";
          break;
        }
        case 3: {
          // decrease demo
          circle_t circle{};
          circle.center.x = 10;
          circle.center.y = 10;
          circle.radius = 10;
          size_t key = 2;
          circle_t *circle_ptr = &circle;
          size_t *key_ptr = &key;
          decrease_ref(circle, key);
          cout << circle.radius << " - radius before decreasing\n";
          decrease_ptr(circle_ptr, key_ptr);
          cout << circle.radius << " - radius after decreasing\n\n";
          break;
        }
        case 4: {
          // swap_lines demo
          matrix3x3_t matrix{};
          matrix3x3_t *matrix_ptr = &matrix;
          size_t line1 = 1;
          size_t line2 = 3;
          size_t *line1_ptr = &line1;
          size_t *line2_ptr = &line2;
          make_default_matrix(matrix);
          cout << "Matrix before lines swap:\n";
          print_matrix(matrix);
          swap_lines_ref(matrix, line1, line2);
          cout << "Matrix after 1st lines swap:\n";
          print_matrix(matrix);
          swap_lines_ptr(matrix_ptr, line1_ptr, line2_ptr);
          cout << "Matrix after 2nd lines swap:\n";
          print_matrix(matrix);
          break;
        }
        case 0: {
          cerr << "Program executing is finished";
          exit(-1);
        }
        default:break;
      }
    }
  }
}
