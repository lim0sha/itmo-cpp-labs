#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include <filesystem>
#include <algorithm>

namespace tfl {

class TextFile {
 private:
  // file parameters
  std::string filename_;
  std::string fileformat;
  std::filesystem::path filepath_;
  std::filesystem::path absolutepath_;

  long filesize_{};
 public:
  // constructors
  TextFile();
  [[maybe_unused]] TextFile(std::string name);
  [[maybe_unused]] TextFile(std::string name, const std::string &path);
  TextFile(const TextFile &other);

  // get method's
  [[nodiscard]] std::string get_filename() const;
  [[nodiscard]] std::string get_extension() const;
  [[nodiscard]] std::filesystem::path get_filepath() const;
  [[nodiscard]] std::filesystem::path get_absolutepath() const;
  [[nodiscard]] long get_filesize() const;

  // initial functions
  void CorrectFormat();
  void Init(const std::string& path);
  void PrintName() const;
  void PrintPath() const;
  void PrintAbsolutePath() const;
  void PrintSize() const;
  void PrintExtension() const;
  void PrintInfo() const;
  [[nodiscard]] bool IsOpen() const;
  [[nodiscard]] bool IsDeleted() const;
  [[nodiscard]] bool HasNotEnded() const;
  void UpdateSize();

  // active functions
  void Create();
  void Delete();
  void WriteInt(int value);
  void WriteString(std::string& text);
  void WriteFloat(float value);
  void PrintFileContents() const;
  [[nodiscard]] std::pair<size_t, size_t> CountCharactersAndLines() const;
  [[nodiscard]] std::string Copy() const;
  void CopyFrom(TextFile& other);
  void Reverse();

  // operators
  bool operator==(const tfl::TextFile& file_to_compare) const;
  bool operator>(const tfl::TextFile& file_to_compare) const;
  bool operator<(const tfl::TextFile& file_to_compare) const;
};
}