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

namespace set {

class NumberSet {
 private:
  std::vector<size_t> numbers_;
  const uint8_t Kmax_size_ = 10;
  void remove_duplicates();
 public:
  // constructor
  NumberSet();

  // getters
  [[nodiscard]] std::vector<size_t> get_numbers() const;
  [[maybe_unused]] [[nodiscard]] size_t front() const;
  [[maybe_unused]] [[nodiscard]] size_t back() const;

  // functions
  [[maybe_unused]] void set_default();

  // operators
  NumberSet& operator+(const NumberSet& other);
  NumberSet& operator+=(size_t value);
  NumberSet& operator-=(size_t value);
  bool operator==(const NumberSet& other);
  bool operator!=(const NumberSet& other);

};
}

std::ostream& operator<<(std::ostream& basic_ostream, const set::NumberSet& set);