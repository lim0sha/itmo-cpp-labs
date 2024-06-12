#include <iostream>
#include "buffer.h"
#include <algorithm>
#include <cstring>

#define ndl std::cout << "\n"

int main(int argc, char *argv[]) {
  if (argc > 1 && strcmp(argv[1], "autotest") == 0 || argc > 1 && strcmp(argv[1], "Autotest") == 0) {
    CircularBuffer<int> circular_buffer(3);
    circular_buffer.push_back(1);
    circular_buffer.push_back(2);
    circular_buffer.push_back(3);
    for (auto x : circular_buffer) {
      std::cout << x << ' ';
    }
    ndl;
    circular_buffer.push_front(52);
    for (auto x : circular_buffer) {
      std::cout << x << ' ';
    }
    ndl;
    std::cout << *circular_buffer.begin();
    ndl;
    circular_buffer.pop_back();
    for (auto x : circular_buffer) {
      std::cout << x << ' ';
    }
    ndl;
    circular_buffer.pop_back();
    for (auto x : circular_buffer) {
      std::cout << x << ' ';
    }
    ndl;
    circular_buffer.recap(5);
    circular_buffer.push_front(239);
    circular_buffer.push_front(78);
    circular_buffer.push_back(345);
    circular_buffer.push_back(795);
    std::sort(circular_buffer.begin(), circular_buffer.end());
    for (auto x : circular_buffer) {
      std::cout << x << ' ';
    }
    ndl;
    const std::string word = "I_LOVE_IS/SWE";
    CircularBuffer<std::string> buffer(7, word) ;
    for (const auto& x : buffer) {
      std::cout << x << ' ';
    }
    ndl;
    std::cout << "All tests passed successfully!";
  } else {
    CircularBuffer<int> v(3);
    v.push_back(501);
    v.push_back(2);
    CircularBuffer<int>::ConstIterator it(v.c_begin() + 1);
    std::cout << "before insert\n";
    for (auto x : v) {
      std::cout << x << ' ';
    }
    std::cout << "\nafter insert [1] 800\n";
    v.insert(it, 800);
    for (auto x : v) {
      std::cout << x << ' ';
    }
    std::cout << "\nv.front " << v.front();
    std::cout << "\nv.back " << v.back() << '\n';
    std::cout << "sort:\n";
    std::sort(v.begin(), v.end());
    for (auto x : v) {
      std::cout << x << ' ';
    }
    std::cout << "\nv.front " << v.front();
    std::cout << '\n';
    v.push_front(99999);
    for (auto x : v) {
      std::cout << x << ' ';
    }
    std::cout << '\n';
    std::cout << "v.front " << v.front();
    v.pop_front();
    std::cout << '\n';
    for (auto x : v) {
      std::cout << x << ' ';
    }
    std::cout << "\ncapacity = " << v.capacity() << "\nsize = " << v.size();
    v.clear();
    std::cout << '\n';
    for (size_t i = 0; i < 3; i++) {
      if (!v.empty()) {
        std::cout << v[i] << ' ';
      } else {
        std::cout << "empty";
        break;
      }
    }
    std::cout << "\n\n";
    CircularBuffer<int> bbb(5, 0);
    for (int i = 0; i < bbb.size(); ++i) {
      bbb.push_back(i);
    }
    for (auto i : bbb) {
      std::cout << i << " ";
    }
    std::cout << "\n17-th element during capacity = 5: " << bbb[17];
  }
  return 0;
}