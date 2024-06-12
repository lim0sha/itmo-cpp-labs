#include "menu.h"

enum class MenuAction {
  Exit,
  WriteInt,
  WriteString,
  WriteFloat,
  PrintFileContents,
  CopyFile,
  CopyFromFileByPath,
  ReverseFileContents,
};

namespace menu {
  // action functions
  void Menu::menu_action() {
    int input;
    std::cout << "Here's a active functions menu for the Textfile objects:\n";
    std::cout << "1 - write int argument\n2 - write string argument\n3 - write float argument\n4"
                 " - print file contents\n5 - copy file\n6 - copy from file by path\n7 - reverse file contents\n0 - exit menu\n\n";
    std::cin >> input;
    auto action = static_cast<MenuAction>(input);
    while (action != MenuAction::Exit) {
      switch (action) {
        case MenuAction::WriteInt:
          this->file_.WriteInt(this->int_arg_);
          break;
        case MenuAction::WriteString:
          this->file_.WriteString(this->str_arg_);
          break;
        case MenuAction::WriteFloat:
          this->file_.WriteFloat(this->float_arg_);
          break;
        case MenuAction::PrintFileContents:
          this->file_.PrintFileContents();
          break;
        case MenuAction::CopyFile:
          this->copy_path_ = file_.Copy();
          break;
        case MenuAction::CopyFromFileByPath:
          this->file_.CopyFrom(this->copy_from_);
          break;
        case MenuAction::ReverseFileContents:
          this->file_.Reverse();
          break;
        default:
          std::cout << "Invalid input. Please try again.\n";
      }
      std::cin >> input;
      action = static_cast<MenuAction>(input);
    }
  }
  // getters
  std::string Menu::get_copy_path() {
    return this->copy_path_;
  }

  // setters
  void Menu::set_file(const tfl::TextFile& other) {
    this->file_ = other;
  }
  void Menu::set_copy_from(const tfl::TextFile& other) {
    this->copy_from_ = other;
  }
  void Menu::set_int_arg(int value) {
    this->int_arg_ = value;
  }
  void Menu::set_str_arg(std::string value) {
    this->str_arg_ = std::move(value);
  }
  void Menu::set_float_arg(float value) {
    this->float_arg_ = value;
  }
}
