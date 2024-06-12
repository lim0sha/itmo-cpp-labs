#include "../include/textfile.h"
#include "../include/menu.h"

#define ndl std::cout << "\n"

int main(int argc, char* argv[]) {
  std::string main_path = R"(D:\ITMO\2_SEM\OP\OPLAB2)";
  //std::cout << main_path << "\n" << " - project build directory";
  if (argc > 1 && strcmp(argv[1], "autotest") == 0 || argc > 1 && strcmp(argv[1], "Autotest") == 0) {
    tfl::TextFile file1("testfile");
    tfl::TextFile file3("testfile3", main_path);
    file1.Create();
    file3.Create();
    ndl;

    if (file1.IsOpen() && file3.IsOpen()) {
      file1.WriteInt(12);
      file1.WriteInt(34);
      file1.PrintInfo();
      ndl;

      std::cout << "Let's compare file1 and file3:\n";
      file3.WriteInt(56);
      file3.WriteInt(67);
      if (file1 == file3) {
        std::cout << "Files are the same size\n";
      }
      ndl;

      std::cout << "File contents are:\n";
      file1.PrintFileContents();
      ndl;

      file1.Reverse();
      std::cout << "File reversed contents are:\n";
      file1.PrintFileContents();
      ndl;

      std::string copy_path = file1.Copy();
      tfl::TextFile file2;
      file2.Init(copy_path);
      ndl;
      file2.PrintInfo();
      ndl;

      std::string text = "\nHello! I'm Sasha\n";
      file1.WriteString(text);
      file1.WriteFloat(123.4567);

      std::cout << "Let's compare file1 and file2:\n";
      if (file1 > file2) {
        std::cout << "File1 is bigger than file2\n";
      } else if (file1 < file2) {
        std::cout << "File2 is bigger than file1\n";
      }
      ndl;

      file2.CopyFrom(file1);
      ndl;
      file2.PrintInfo();
      ndl;

      std::cout << file2.get_filename() << " has " << file2.CountCharactersAndLines().first << " symbols\n";
      std::cout << file2.get_filename() << " has " << file2.CountCharactersAndLines().second << " lines\n";
      ndl;

      file1.Delete();
      file2.Delete();
      file3.Delete();
      ndl;

      if (file1.IsDeleted() && file2.IsDeleted() && file3.IsDeleted()) {
        std::cout << "Congrats! It works!\n";
      }
    }
  } else {
    tfl::TextFile FileToCopy("testfile");
    FileToCopy.Create();
    tfl::TextFile File("menu_testfile");
    File.Create();
    FileToCopy.WriteInt(100500);

    menu::Menu File_Menu;
    File_Menu.set_file(File);
    File_Menu.set_int_arg(1234);
    File_Menu.set_str_arg("\nHello! I'm Sasha\n");
    File_Menu.set_float_arg(567.89);
    File_Menu.set_copy_from(FileToCopy);

    File_Menu.menu_action();

    File.Delete();
    FileToCopy.Delete();
    if (!File_Menu.get_copy_path().empty()) {
      tfl::TextFile Copy;
      Copy.Init(File_Menu.get_copy_path());
      Copy.Delete();
    }
  }
  return 0;
}
