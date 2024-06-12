#include "template_func.h"
#include "template_stack.h"

int main(int argc, char *argv[]) {
  if (argc > 1 && (strcmp(argv[1], "autotest") == 0 || strcmp(argv[1], "Autotest") == 0)) {
    std::cout << "Template functions action:";
    ndl
    std::cout << power(2, 3);
    ndl
    std::cout << power(0.2342, 3);
    ndl
    std::cout << power(0.764578265345353, 2);
    ndl
    std::cout << power(2.0, -3);
    ndl
    //std::cout << power(2, 3.9);
    //ndl
    ndl
    std::cout << "Template class actions:";
    ndl
    TStack<4, int> stack1;
    TStack<3, std::string> stack2;
    TStack<2, std::pair<int, long>> stack3;
    TStack<1, std::tuple<char, int>> stack4;

    stack1.push(52);
    stack1.push(100500);
    std::cout << stack1.pop();
    ndl
    std::cout << stack1.pop();
    ndl
    // std::cout << stack1.pop();

    stack2.push("hello!");
    stack2.push("my name");
    stack2.push("is Sasha");
    // stack2.push("I guess this one wouldn't fit in :(");

    stack3.push(std::pair(239, 30));
    stack3.push(std::pair(30, 239));
    if (stack3.find(std::pair(30, 239))) {
      stack3.pop();
      std::cout << "Find method for Stack works!";
    }
    ndl

    stack4.push(std::tuple('w', 23));
    std::cout << std::get<0>(stack4.peek()) << " " << std::get<1>(stack4.peek());
    ndl
  } else {
    std::cout << "Template functions action:";
    ndl
    std::cout << power(2, 3);
    ndl
    std::cout << power(0.2342, 3);
    ndl
    std::cout << power(0.764578265345353, 2);
    ndl
    std::cout << power(2.0, -3);
    ndl
    std::cout << power(2, 3.9);
    ndl
        ndl
    std::cout << "Template class actions:";
    ndl
    TStack<4, int> stack1;
    TStack<3, std::string> stack2;
    TStack<2, std::pair<int, long>> stack3;
    TStack<1, std::tuple<char, int>> stack4;

    stack1.push(52);
    stack1.push(100500);
    std::cout << stack1.pop();
    ndl
    std::cout << stack1.pop();
    ndl
    std::cout << stack1.pop();
    ndl

    stack2.push("hello!");
    stack2.push("my name");
    stack2.push("is Sasha");
    stack2.push("I guess this one wouldn't fit in :(");

    stack3.push(std::pair(239, 30));
    stack3.push(std::pair(30, 239));
    if (stack3.find(std::pair(30, 239))) {
      stack3.pop();
      std::cout << "Find method for Stack works!";
    }
    ndl

    stack4.push(std::tuple('w', 23));
    std::cout << std::get<0>(stack4.peek()) << " " << std::get<1>(stack4.peek());
    ndl
  }
  return 0;
}
