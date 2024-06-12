#include "../include/set.h"
#include "../include/square.h"

int main(int argc, char* argv[]) {
  int response;
  if (argc > 1 && strcmp(argv[1], "autotest") == 0 || argc > 1 && strcmp(argv[1], "Autotest") == 0) {
    std::cout << "Here's an example of working Set class:\n";
    set::NumberSet set_1;
    set::NumberSet set_2;
    set::NumberSet set_3;
    std::cout << "Formed two sets\n";
    set_1 += 1;
    set_1 += 2;
    set_1 += 2;
    set_1 += 4;

    set_2 += 2;
    set_2 += 3;

    set_3 += 1;
    set_3 += 2;
    set_3 += 4;

    if (set_1 == set_3 and set_1 != set_2) {
      std::cout << "Overloaded operators for Set class work!\n";
    } else {
      std::cout << "\n";
    }
    std::cout << "Summed two sets\n";
    set_1 + set_2;
    std::cout << "Printed set_1: " << set_1;
    set_1 -= 4;
    std::cout << "Printed set_1 after deleting element '4': " << set_1;
    std::cout << "\nHere's an example of working Square class:\n";
    sqr::Point x_1(1, 2);
    sqr::Point x_2(3, 4);
    sqr::VectorXY v_1(5, 7);
    sqr::Square Square_1(x_1, 10, 60);
    sqr::Square Square_2(x_2, 20, 30);

    if (Square_1 == Square_2) {
      std::cout << "Squares have same area\n";
    } else {
      std::cout << "Squares do not have same area\n";
    }
    std::cout << "We multiplied Square_1 by 2 and moved it by vector v_1\n";
    Square_1.multiply(2);
    Square_1.vectorize(v_1);
    if (Square_1 == Square_2) {
      std::cout << "Squares have same area\n";
    } else {
      std::cout << "Squares do not have same area\n";
    }
  } else {
    std::cout << "Enter 1 to see Set class functionality\nEnter 2 to see Square class functionality\n";
    std::cin >> response;
    if (response == 1) {
      set::NumberSet set_1;
      set::NumberSet set_2;
      set::NumberSet set_3;
      std::cout << "Formed two sets\n";
      set_1 += 1;
      set_1 += 2;
      set_1 += 2;
      set_1 += 4;

      set_2 += 2;
      set_2 += 3;

      set_3 += 1;
      set_3 += 2;
      set_3 += 4;

      if (set_1 == set_3 and set_1 != set_2) {
        std::cout << "Overloaded operators for Set class work!\n";
      }
      std::cout << "Summed two sets\n";
      set_1 + set_2;
      std::cout << "Printed set_1: " << set_1;
      set_1 -= 4;
      std::cout << "Printed set_1 after deleting element '4': " << set_1;
    } else if (response == 2) {
      sqr::Point x_1(1, 2);
      sqr::Point x_2(3, 4);
      sqr::VectorXY v_1(5, 7);
      sqr::Square Square_1(x_1, 10, 60);
      sqr::Square Square_2(x_2, 20, 30);

      if (Square_1 == Square_2) {
        std::cout << "Squares have same area\n";
      } else {
        std::cout << "Squares do not have same area\n";
      }
      std::cout << "We multiplied Square_1 by 2 and moved it by vector v_1\n";
      Square_1.multiply(2);
      Square_1.vectorize(v_1);
      if (Square_1 == Square_2) {
        std::cout << "Squares have same area\n";
      } else {
        std::cout << "Squares do not have same area\n";
      }
    }
  }
  return 0;
}
