#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <cstdint>
#include <set>
#include <cmath>
#include <cstring>

namespace sqr {

struct Point {
  int x;
  int y;
};

struct VectorXY {
  int x;
  int y;
};

class Square {
 private:
  Point point_;
  uint16_t side_;
  [[maybe_unused]] float angle_;
 public:
  Square() = default;
  Square(Point p, uint16_t s, float a) : point_(p), side_(s), angle_(a) {};
  void multiply(size_t value);
  void vectorize(VectorXY v);
  bool operator==(const Square& other) const;
  bool operator!=(const Square& other) const;
  bool operator<(const Square& other) const;
  bool operator>(const Square& other) const;
};
}