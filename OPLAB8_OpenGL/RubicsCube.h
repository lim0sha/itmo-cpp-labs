#pragma once
#include "lib/glew-cmake/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include <cstdint>
#include <iostream>
#include <utility>
#include <cstdio>
#include <memory>
#include <cmath>
#include <array>
#include <tuple>
#include <queue>
#include <tuple>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
#include <fstream>

struct CubeInits {
  // цвета граней куба в палитре RGB
  GLfloat Gl_colors[7][3] = {
      {0.0f, 0.8f, 0.0f}, {0.2f, 0.2f, 1.0f}, {1.0f, 0.2f, 0.2f}, {1.0f, 0.6f, 0.0f}, {1.0f, 1.0f, 0.0f},
      {0.8f, 0.8f, 0.8f}, {0.3f, 0.3f, 0.3f}
  };

  // 6 видов вращения. Move_C {a, b, c, d} -> при вращении "Move_C" меняют положение углы a, b, c и d
  std::vector<std::vector<std::vector<int>>> Map_CROT = {
      {{4, 5, 6, 7}, {3, 2, 1, 0}, {7, 6, 2, 3}, {5, 4, 0, 1}, {4, 7, 3, 0}, {6, 5, 1, 2}},
      {{7, 6, 5, 4}, {0, 1, 2, 3}, {7, 3, 2, 6}, {5, 1, 0, 4}, {4, 0, 3, 7}, {6, 2, 1, 5}}
  };

  // 6 видов вращения. Move_E {a, b, c, d} -> при вращении "Move_E" меняют положение ребра a, b, c и d
  std::vector<std::vector<std::vector<int>>> Map_EROT = {
      {{4, 5, 6, 7}, {11, 10, 9, 8}, {6, 2, 10, 3}, {4, 0, 8, 1}, {7, 3, 11, 0}, {5, 1, 9, 2}},
      {{7, 6, 5, 4}, {8, 9, 10, 11}, {3, 10, 2, 6}, {1, 8, 0, 4}, {0, 11, 3, 7}, {2, 9, 1, 5}}
  };

  // corner {a, b, c} -> угол между гранями a, b и c
  // 0: Верхняя (Top)
  // 1 Нижняя (Bottom)
  // 2: Передняя (Front)
  // 3: Задняя (Back)
  // 4: Левая (Left)
  // 5: Правая (Right)
  int8_t Map_CORI[8][3] = {{1, 3, 4}, {1, 5, 3}, {1, 2, 5}, {1, 4, 2}, {0, 4, 3}, {0, 3, 5}, {0, 5, 2}, {0, 2, 4}};

  // edge {a, b} -> ребро между гранями a и b
  // 0: Верхняя (Top)
  // 1 Нижняя (Bottom)
  // 2: Передняя (Front)
  // 3: Задняя (Back)
  // 4: Левая (Left)
  // 5: Правая (Right)
  int8_t Map_EORI[12][2] = {{4, 3}, {5, 3}, {5, 2}, {4, 2}, {0, 3}, {0, 5}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {1, 2}, {1, 4},};

  // Индексация реберных кубиков в кубике Рубика. Значение -1 означает, что в данной позиции нет реберного кубика
  int8_t Map_EINDEX[27] = {-1, 8, -1, 11, -1, 9, -1, 10, -1, 0, -1, 1, -1, -1, -1, 3, -1, 2, -1, 4, -1, 7, -1, 5, -1, 6, -1};

  // Индексация центральных кубиков. Значение -1 означает, что в данной позиции нет центрального кубика
  int8_t Map_CNTRINDEX[27] = {-1, -1, -1, -1, 1, -1, -1, -1, -1, -1, 3, -1, 4, -1, 5, -1, 2, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1,};
};

class Plate {
 public:
  enum Side {T, BT, F, BC, L, R};
  int8_t SideBlocksC[9];
};

class Margin {
 public:
  int8_t top_, bottom_, front_, back_, left_, right_;
};

class RubicsCube {
 public:
  // Изначальная разметка ребер и углов куба по индексам. По этим массивам сохраняется и считывается состояние куба
  RubicsCube() : corners_padding_{0, 1, 2, 3, 4, 5, 6, 7}, corners_init_{0, 0, 0, 0, 0, 0, 0, 0},
                 edges_padding_{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, edges_init_{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} {}
  [[nodiscard]] Margin get_margin(int position, int x, int y) const;
  void do_rotate(Plate::Side side_type, int value_count = 1);
  void save_state(const std::string &filename) const;
  void load_state(const std::string &filename);
  void print_state() const;
  void generate_random_state();
  [[nodiscard]] bool is_valid_state() const;
 private:
  int8_t corners_padding_[8]{}, corners_init_[8]{};
  int8_t edges_padding_[12]{}, edges_init_[12]{};
};

class MovesSequence {
 public:
  [[nodiscard]] bool isActive() const {
    return is_running_;
  }
 private:
  bool is_running_;
};

struct Vector {
  long double x_axis, y_axis, z_axis;
  long double operator*(const Vector &r) const { return x_axis * r.x_axis + y_axis * r.y_axis + z_axis * r.z_axis; }
  [[nodiscard]] Vector intersection(const Vector &other) const {return {y_axis * other.z_axis - z_axis * other.y_axis, x_axis * other.z_axis - z_axis * other.x_axis, y_axis * other.x_axis - x_axis * other.y_axis};}
};

class VirtualOrb {
 public:
  VirtualOrb();
  void init_rotation_vector(long double angle, Vector v_pos);
  void do_rotate();
 private:
  double radius_, angle_{};
  Vector init_axis_{};
  GLfloat buffer_[16]{};
  void erase_initialization();
};

class GlMonitor {
 public:
  GlMonitor();
  bool init();
  void run();
  void init_cube(const RubicsCube &rubics_cube);
  void queue_push_rotation(Plate::Side c_side, int d_param, int value);
 private:
  void display(const RubicsCube &rubics_cube);
  static void draw_margin_side(GLfloat X_ax, GLfloat Y_ax, GLfloat Z_ax, GLfloat GL_value, Margin color, GLenum type);
  void process_rotations();
  static void init_color(int color_code);
  static void keyboard_response(GLFWwindow *glf_wwindow, int key_pushed, int _act, int action, int _mode);
  std::queue<std::tuple<Plate::Side, int, int>> queue_moves_;
  int rotation_type_buffer_[3]{};
  GLfloat rotation_vector_;
  MovesSequence MvSqs_;
  VirtualOrb virtual_orb_;
  RubicsCube cube_template_;
  GLFWwindow *gl_window_;
};

GlMonitor *createOpenglViewer();
