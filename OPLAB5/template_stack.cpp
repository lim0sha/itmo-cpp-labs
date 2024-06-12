#include "template_stack.h"

template<int n, class T>
TStack<n, T>::TStack() = default;

template<int n, class T>
[[nodiscard]] bool TStack<n, T>::empty() noexcept {
  return this->data.empty();
}

template<int n, class T>
void TStack<n, T>::push(T element) {
  try {
    if (size + 1 <= max_size) {
      this->data.push_back(element);
      size++;
    } else {
      throw std::overflow_error("Stack has reached size limit, no pushes are available now.");
    }
  }
  catch (const std::exception &e) {
    std::cerr << "Exception caught: " << e.what() << "\n";
  }
}

template<int n, class T>
T TStack<n, T>::pop() {
  try {
    if (!this->empty()) {
      T element = data.back();
      this->data.pop_back();
      size--;
      return element;
    } else {
      throw std::underflow_error("Stack is empty, no elements are stored.");
    }
  }
  catch (const std::exception &e) {
    std::cerr << "Exception caught: " << e.what() << "\n";
    return T();
  }
}

template<int n, class T>
bool TStack<n, T>::find(T element) noexcept {
  if (this->empty()) {
    return false;
  }
  for (int i = data.size() - 1; i >= 0; --i) {
    if (data[i] == element) {
      return true;
    }
  }
  return false;
}

template<int n, class T>
T TStack<n, T>::peek() noexcept {
  return this->data.back();
}

template
class TStack<4, int>;
template
class TStack<3, std::string>;
template
class TStack<2, std::pair<int, long>>;
template
class TStack<1, std::tuple<char, int>>;