#include "stl_functions.h"
#include "c_types.h"

template<typename T>
bool is_positive_int(const T &val) {
  return val > 0;
}

bool compare_CPoint(const CPoint &p1, const CPoint &p2) {
  return (p1.getX() < p2.getX()) || (p1.getX() == p2.getX() && p1.getY() < p2.getY());
}

bool compare_CRational(const CRational &r1, const CRational &r2) {
  return (r1.getNumerator() * r2.getDenominator()) < (r2.getNumerator() * r1.getDenominator());
}

bool isEven(int x) { return x % 2 == 0; }
bool ascending(int x, int y) { return x < y; }
bool descending(int x, int y) { return x > y; }
bool check(char a, char b) { return std::tolower(a) == std::tolower(b); }

int main(int argc, char *argv[]) {
  if (argc > 1 && strcmp(argv[1], "autotest") == 0 || argc > 1 && strcmp(argv[1], "Autotest") == 0) {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::list<int> vec2 = {5, 6, -9, 2, 4};
    std::cout << "All elements of vec1 are positive integers: " << std::boolalpha
              << my_all_of(vec1.begin(), vec1.end(), is_positive_int<int>) << "\n";
    std::cout << "All elements of vec2 are positive integers: " << std::boolalpha
              << my_all_of(vec2.begin(), vec2.end(), is_positive_int<int>) << "\n\n";

    std::vector<int> v1 = {1, 3, 5, 4, 9};
    std::vector<char> v2 = {'s', '2', 'g'};
    std::cout << (my_all_of(v1.begin(), v1.end(), isEven) ? "All the numbers in v1 are even\n"
                                                          : "Not all the numbers in v1 are even\n");
    std::cout << (my_all_of(v2.begin(), v2.end(), isdigit) ? "All the elements in v2 are digits\n\n"
                                                           : "Not all the elements in v2 are digits\n\n");

    std::list<int> list1 = {1, 2, 3, 4, 5};
    std::list<int> list2 = {5, 4, 3, 2, 1};
    std::cout << (my_is_sorted(list1.begin(), list1.end(), ascending) ? "List1 is sorted in ascending order\n"
                                                                      : "List1 is not sorted\n");
    std::cout << (my_is_sorted(list2.begin(), list2.end(), descending) ? "List2 is sorted in descending order\n\n"
                                                                       : "List2 is not sorted\n\n");

    std::string container1 = "level";
    std::vector<int> container2 = {1, 2, 3, 2, 1};
    std::cout
        << (my_is_palindrome(container1.begin(), container1.end() - 1, check) ? "The container1 is a palindrome\n"
                                                                              : "The container1 is not a palindrome\n");
    std::cout
        << (my_is_palindrome(container2.begin(), container2.end() - 1, check) ? "The container2 is a palindrome\n\n"
                                                                              : "The container2 is not a palindrome\n\n");

    std::vector<CPoint> points = {CPoint(1, 2), CPoint(3, 4), CPoint(2, 5)};
    std::cout << "Is points sorted: " << std::boolalpha << my_is_sorted(points.begin(), points.end(), compare_CPoint)
              << "\n";
    std::list<CRational> rationals = {CRational(1, 2), CRational(2, 3), CRational(3, 4)};
    std::cout << "Is rationals sorted: " << std::boolalpha
              << my_is_sorted(rationals.begin(), rationals.end(), compare_CRational) << "\n";
  } else {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::list<int> vec2 = {5, 6, -9, 2, 4};
    std::cout << "All elements of vec1 are positive integers: " << std::boolalpha
              << my_all_of(vec1.begin(), vec1.end(), is_positive_int<int>) << "\n";
    std::cout << "All elements of vec2 are positive integers: " << std::boolalpha
              << my_all_of(vec2.begin(), vec2.end(), is_positive_int<int>) << "\n\n";

    std::vector<int> v1 = {1, 3, 5, 4, 9};
    std::vector<char> v2 = {'s', '2', 'g'};
    std::cout << (my_all_of(v1.begin(), v1.end(), isEven) ? "All the numbers in v1 are even\n"
                                                          : "Not all the numbers in v1 are even\n");
    std::cout << (my_all_of(v2.begin(), v2.end(), isdigit) ? "All the elements in v2 are digits\n\n"
                                                           : "Not all the elements in v2 are digits\n\n");

    std::list<int> list1 = {1, 2, 3, 4, 5};
    std::list<int> list2 = {5, 4, 3, 2, 1};
    std::cout << (my_is_sorted(list1.begin(), list1.end(), ascending) ? "List1 is sorted in ascending order\n"
                                                                      : "List1 is not sorted\n");
    std::cout << (my_is_sorted(list2.begin(), list2.end(), descending) ? "List2 is sorted in descending order\n\n"
                                                                       : "List2 is not sorted\n\n");

    std::string container1 = "level";
    std::vector<int> container2 = {1, 2, 3, 2, 1};
    std::cout
        << (my_is_palindrome(container1.begin(), container1.end() - 1, check) ? "The container1 is a palindrome\n"
                                                                              : "The container1 is not a palindrome\n");
    std::cout
        << (my_is_palindrome(container2.begin(), container2.end() - 1, check) ? "The container2 is a palindrome\n\n"
                                                                              : "The container2 is not a palindrome\n\n");

    std::vector<CPoint> points = {CPoint(1, 2), CPoint(3, 4), CPoint(2, 5)};
    std::cout << "Is points sorted: " << std::boolalpha << my_is_sorted(points.begin(), points.end(), compare_CPoint)
              << "\n";
    std::list<CRational> rationals = {CRational(1, 2), CRational(2, 3), CRational(3, 4)};
    std::cout << "Is rationals sorted: " << std::boolalpha
              << my_is_sorted(rationals.begin(), rationals.end(), compare_CRational) << "\n";
  }
  return 0;
}
