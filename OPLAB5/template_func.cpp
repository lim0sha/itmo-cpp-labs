#include "template_func.h"

template<typename T_power, typename T_type>
T_type power(T_type n, T_power pow) {
  try {
    if (pow != (int) pow) {
      throw std::invalid_argument("Exponents should be an integer value.");
    }
    T_type result = 1;
    bool negative_power = false;
    if (pow < 0) {
      pow = -pow;
      negative_power = true;
    }
    while (pow) {
      if ((int) pow % 2 == 0) {
        pow /= 2;
        n *= n;
      } else {
        --pow;
        result *= n;
      }
    }
    if (negative_power) {
      return static_cast<T_type>(1.0) / result;
    } else {
      return result;
    }
  }
  catch (std::exception &e) {
    std::cerr << "Exception caught: " << e.what() << "\n";
    return T_type();
  }
}

template int power<int, int>(int, int);
template float power<float, float>(float, float);
template double power<double, double>(double, double);
template double power<int, double>(double, int);
template int power<double, int>(int, double);


