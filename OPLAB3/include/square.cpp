#include "square.h"

namespace sqr {
  void Square::multiply(size_t value) {
    this->side_ *= value;
  }
  void Square::vectorize(sqr::VectorXY v) {
    this->point_.x += v.x;
    this->point_.y += v.y;
  }
  bool Square::operator==(const Square& other) const {
    return this->side_ == other.side_;
  }
  bool Square::operator!=(const sqr::Square &other) const {
    return this->side_ != other.side_;
  }
  bool Square::operator>(const Square& other) const {
    return this->side_ > other.side_;
  }
  bool Square::operator<(const Square& other) const {
    return this->side_ < other.side_;
  }
}