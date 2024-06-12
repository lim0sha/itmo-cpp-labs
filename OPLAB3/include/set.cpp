#include "set.h"

namespace set {
  // constructors
  NumberSet::NumberSet() = default;

  // getters
  std::vector<size_t> NumberSet::get_numbers() const {
    return this->numbers_;
  }
[[maybe_unused]] size_t NumberSet::front() const {
    if (!this->numbers_.empty()) {
      return this->numbers_[0];
    } else {
      std::cerr << "Error: the set is empty";
      return -1;
    }
  }
[[maybe_unused]] size_t NumberSet::back() const {
    if (!this->numbers_.empty()) {
      return this->numbers_[numbers_.size() - 1];
    } else {
      std::cerr << "Error: the set is empty";
      return -1;
    }
  }

  // functions
  [[maybe_unused]] void NumberSet::set_default() {
    for (int i = 0; i < this->Kmax_size_; ++i) {
      this->numbers_.push_back(i);
    }
  }
  void NumberSet::remove_duplicates() {
    std::set<size_t> s(this->numbers_.begin(), this->numbers_.end() );
    numbers_.assign(s.begin(),s.end() );
  }

  // operators
  NumberSet& NumberSet::operator+(const set::NumberSet &other) {
    for (unsigned long long number : other.numbers_) {
      this->numbers_.push_back(number);
    }
    this->remove_duplicates();
    return *this;
  }
  NumberSet &NumberSet::operator+=(size_t value) {
    this->numbers_.push_back(value);
    this->remove_duplicates();
    return *this;
  }
  NumberSet &NumberSet::operator-=(size_t value) {
    if (std::binary_search(this->numbers_.begin(), this->numbers_.end(), value)) {
      this->numbers_.erase(std::remove(this->numbers_.begin(), this->numbers_.end(), value), this->numbers_.end());
    }
    return *this;
  }
  bool NumberSet::operator==(const set::NumberSet &other) {
    if (this->numbers_.size() == other.numbers_.size()) {
      for (int i = 0; i < numbers_.size(); ++i) {
        if (this->numbers_[i] != other.numbers_[i]) {
          return false;
        }
      }
      return true;
    } else {
      return false;
    }
  }
  bool NumberSet::operator!=(const set::NumberSet &other) {
    return !(*this==other);
  }
}

std::ostream& operator<<(std::ostream& basic_ostream, const set::NumberSet& set) {
  for (int i = 0; i < set.get_numbers().size(); ++i) {
    basic_ostream << set.get_numbers()[i] << " ";
  }
  basic_ostream << "\n";
  return basic_ostream;
}

