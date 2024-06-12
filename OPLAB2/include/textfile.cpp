#include "textfile.h"

#include <utility>

namespace fs = std::filesystem;

namespace tfl {
  // constructors
  TextFile::TextFile() = default;
  [[maybe_unused]] TextFile::TextFile(std::string name) {
    this->filename_ = std::move(name);
    fs::path currentPath = fs::current_path();
    if (currentPath.has_filename() && currentPath.filename() == "bin" &&
        currentPath.parent_path().has_filename() && currentPath.parent_path().filename() == "cmake-build-debug") {
      currentPath.remove_filename();
      currentPath.remove_filename();
    }
    this->filepath_ = currentPath;
  }
  [[maybe_unused]] TextFile::TextFile(std::string name, const std::string &path) {
    this->filename_ = std::move(name);
    this->filepath_ = path;
    this->fileformat = ".txt";
    this->filesize_ = 0;
    this->CorrectFormat();
  }
  TextFile::TextFile(const TextFile &other) {
    this->filename_ = other.filename_;
    this->filepath_ = other.filepath_;
    this->fileformat = other.fileformat;
    this->filesize_ = other.filesize_;
    this->CorrectFormat();
  }

  // get method's
  [[nodiscard]] std::string TextFile::get_filename() const {
    return this->filename_;
  }
  [[nodiscard]] std::string TextFile::get_extension() const {
    return this->fileformat;
  }
  [[nodiscard]] std::filesystem::path TextFile::get_filepath() const {
    return this->filepath_;
  }
  [[nodiscard]] long TextFile::get_filesize() const {
    return this->filesize_;
  }
  [[nodiscard]] std::filesystem::path TextFile::get_absolutepath() const {
    return this->absolutepath_;
  }

  // initial functions
  void TextFile::CorrectFormat() {
    if (!(this->filename_.substr(this->filename_.size() - 4, 4) == ".txt")) {
      this->filename_ = this->filename_ + ".txt";
    }
    this->absolutepath_ = this->filepath_ / this->filename_;
  }
  void TextFile::Create() {
    this->CorrectFormat();
    std::ofstream file;
    file.open(this->absolutepath_, std::ios::out);
    if (!file.is_open()) {
      std::cerr << "Error: Couldn't create file\n";
    } else {
      std::cout << "File " << this->filename_ << " was created\n";
    }
    file.close();
  }
  void TextFile::Delete() {
    if (IsDeleted()) {
      std::cerr << "Error: file was already deleted\n";
      exit(0);
    }
    std::error_code error_code;
    std::filesystem::remove(this->absolutepath_, error_code);
    if (error_code) {
      std::cerr << "Error: Couldn't delete file " << error_code.message() << "\n";
    } else {
      std::cout << "File " << this->filename_ << " was deleted\n";
    }
    this->filename_ = "!del";
    this->filepath_ = "!del";
    this->filesize_ = 0;
    this->absolutepath_ = "!del";
  }
  void TextFile::PrintName() const {
    std::cout << "Name: " << this->get_filename() << "\n";
  }
  void TextFile::PrintPath() const {
    std::cout << "Path of " << this->get_filename() << " is " << this->get_filepath() << "\n";
  }
  void TextFile::PrintAbsolutePath() const {
    std::cout << "Absolute path of " << this->get_filename() << " is " << this->get_absolutepath() << "\n";
  }
  void TextFile::PrintSize() const {
    std::cout << "Size of " << this->get_filename() << " is " << this->get_filesize() << " bytes\n";
  }
  void TextFile::PrintExtension() const {
    std::cout << "Extension of " << this->get_filename() << " is " << this->get_extension() << "\n";
  }
  void TextFile::PrintInfo() const {
    std::cout << "File info:\n";
    this->PrintName();
    this->PrintPath();
    this->PrintAbsolutePath();
    this->PrintSize();
    this->PrintExtension();
  }
  [[nodiscard]] bool TextFile::IsOpen() const {
    return std::filesystem::exists(this->absolutepath_);
  }
  [[nodiscard]] bool TextFile::IsDeleted() const {
    return (this->filename_ == "!del" && this->filepath_ == "!del" and this->absolutepath_ == "!del");
  }
  void TextFile::UpdateSize() {
    std::ifstream file(this->absolutepath_, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
      std::cerr << "Error: Couldn't open file for reading\n";
      return;
    } else {
      this->filesize_ = file.tellg();
    }
  }
  void TextFile::Init(const std::string& path) {
    if (!std::filesystem::exists(path)) {
      std::cerr << "Error: File does not exist\n";
      return;
    }
    std::filesystem::path filepath(path);

    this->filename_ = filepath.filename().string();
    this->fileformat = filepath.extension().string();
    this->filepath_ = filepath.parent_path();
    this->absolutepath_ = path;
    std::filesystem::path absolute_path = std::filesystem::absolute(filepath);

    std::ifstream file_stream(absolute_path, std::ios::binary);
    if (file_stream.is_open()) {
      file_stream.seekg(0, std::ios::end);
      filesize_ = file_stream.tellg();
      file_stream.close();
    } else {
      std::cerr << "Error: Couldn't open file for reading\n";
      filesize_ = -1;
    }
  }
  [[nodiscard]] bool TextFile::HasNotEnded() const {
    std::ifstream file_(this->absolutepath_);
    return !file_.eof();
  }

  // active functions
  void TextFile::WriteInt(int value) {
    std::ofstream file;
    file.open(this->absolutepath_, std::ios_base::app);
    if (!file.is_open()) {
      std::cerr << "Error: Couldn't open file for writing\n";
      return;
    }
    file << value;
    if (file.fail()) {
      std::cerr << "Error: Failed to write integer to file\n";
    }
    file.close();
    this->UpdateSize();
  }
  void TextFile::WriteString(std::string& text) {
    std::ofstream file;
    file.open(this->absolutepath_, std::ios_base::app);
    if (!file.is_open()) {
      std::cerr << "Error: Couldn't open file for writing\n";
      return;
    }
    file << text;
    if (file.fail()) {
      std::cerr << "Error: Failed to write integer to file\n";
    }
    file.close();
    this->UpdateSize();
  }
  void TextFile::WriteFloat(float value) {
    std::ofstream file;
    file.open(this->absolutepath_, std::ios_base::app);
    if (!file.is_open()) {
      std::cerr << "Error: Couldn't open file for writing\n";
      return;
    }
    file << value;
    if (file.fail()) {
      std::cerr << "Error: Failed to write integer to file\n";
    }
    file.close();
    this->UpdateSize();
  }
  [[nodiscard]] std::string TextFile::Copy() const {
    std::string new_filename = filename_;
    std::filesystem::path new_filepath = absolutepath_;
    std::string::size_type dot_pos = new_filename.find_last_of('.');
    if (dot_pos != std::string::npos) {
      new_filename.insert(dot_pos, "1");
      new_filepath.replace_filename(new_filename);
    }

    tfl::TextFile newfile(new_filename, new_filepath.string());
    std::ifstream source_file(absolutepath_, std::ios::binary);
    if (!source_file.is_open()) {
      std::cerr << "Error: Couldn't open source file for reading\n";
      exit(0);
    }
    std::ofstream dest_file(new_filepath, std::ios::binary);
    if (!dest_file.is_open()) {
      std::cerr << "Error: Couldn't open destination file for writing\n";
      exit(0);
    }
    dest_file << source_file.rdbuf();
    source_file.close();
    dest_file.close();
    std::string copy_path = this->filepath_.string() + "\\" + new_filename;
    std::cout << "File " << this->filename_ << " was copied and saved as " << new_filename << "\n";
    return copy_path;
  }
  void TextFile::CopyFrom(TextFile& other) {
    std::ifstream source_file(this->absolutepath_, std::ios::binary);
    if (!source_file.is_open()) {
      std::cerr << "Error: Couldn't open source file for reading\n";
      return;
    }

    std::ifstream other_source_file(other.absolutepath_, std::ios::binary);
    if (!other_source_file.is_open()) {
      std::cerr << "Error: Couldn't open source file for reading\n";
      return;
    }

    std::ofstream dest_file(this->absolutepath_, std::ios::binary | std::ios::app);
    if (!dest_file.is_open()) {
      std::cerr << "Error: Couldn't open destination file for writing\n";
      return;
    }
    std::cout << "Data of " << other.filename_ << " was copied to " << this->filename_ << "\n";
    dest_file << other_source_file.rdbuf();
    source_file.close();
    other_source_file.close();
    dest_file.close();
  }
  std::pair<size_t, size_t> TextFile::CountCharactersAndLines() const {
    std::ifstream file(this->absolutepath_);
    if (!file.is_open()) {
      std::cerr << "Error: Couldn't open file for reading\n";
      return {0, 0};
    }
    size_t char_count = 0;
    size_t line_count = 0;
    std::string line;
    while (std::getline(file, line)) {
      char_count += line.size();
      ++line_count;
    }
    file.close();
    return {char_count, line_count};
  }
  void TextFile::PrintFileContents() const {
    std::ifstream file(this->absolutepath_);
    if (!file.is_open()) {
      std::cerr << "Error: Couldn't open file for reading." << std::endl;
      return;
    }
    std::string line;
    while (std::getline(file, line) && this->HasNotEnded()) {
      std::cout << line << std::endl;
    }
    file.close();
  }
  void TextFile::Reverse() {
    std::ifstream file(this->absolutepath_);
    if (!file.is_open()) {
      std::cerr << "Error: Couldn't open file for reading\n";
      return;
    }

    std::string content;
    char ch;
    while (file.get(ch)) {
      content.push_back(ch);
    }
    std::reverse(content.begin(), content.end());
    file.close();

    std::ofstream outfile(this->absolutepath_);
    if (!outfile.is_open()) {
      std::cerr << "Error: Couldn't open file for writing\n";
      return;
    }
    outfile << content;
    outfile.close();
  }

  // operators
  bool TextFile::operator==(const tfl::TextFile& file_to_compare) const {
    return (this->filesize_ == file_to_compare.filesize_);
  }
  bool TextFile::operator>(const tfl::TextFile& file_to_compare) const {
    return (this->filesize_ > file_to_compare.filesize_);
  }
  bool TextFile::operator<(const tfl::TextFile& file_to_compare) const {
    return (this->filesize_ < file_to_compare.filesize_);
  }
}
