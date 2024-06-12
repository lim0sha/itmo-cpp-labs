#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <stdexcept>
#include <tuple>
#include <string>

template<int n, class T>
class TStack {
 private:
  unsigned int max_size{n};
  unsigned int size{};
  std::vector<T> data{};
  [[nodiscard]] bool empty() noexcept;
 public:
  TStack();
  void push(T element);
  T pop();
  bool find(T element) noexcept;
  T peek() noexcept;
};
