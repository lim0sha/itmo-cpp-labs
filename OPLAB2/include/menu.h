#pragma once
#include "textfile.h"

namespace menu {

class Menu {
 private:
  tfl::TextFile file_;
  tfl::TextFile copy_from_;
  int int_arg_;
  std::string str_arg_;
  float float_arg_;
  std::string copy_path_;
 public:
  // getters
  std::string get_copy_path();

  // setters
  void set_file(const tfl::TextFile& other);
  void set_copy_from(const tfl::TextFile& other);
  void set_int_arg(int value);
  void set_str_arg(std::string value);
  void set_float_arg(float value);

  // action functions
  void menu_action();
};
}