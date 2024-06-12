#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <string_view>
#include <cmath>
#include <ctime>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include "pugixml-1.14/src/pugixml.hpp"
#include "curl/curl.h"

class ParseArguments {
 private:
  std::string v_name;
  std::string v_nominal;
  const char *date_format = "%d.%m.%Y";
  static std::string GetCurrentDate(const char *format) {
    time_t now = time(nullptr);
    tm *tmPtr = localtime(&now);
    char arr[80];
    strftime(arr, sizeof(arr), format, tmPtr);
    std::string return_str = std::string(arr);
    return return_str;
  }
  std::string date;
  std::string date_date;
  std::string date_date_start;
  std::string date_date_finish;
  std::string filename;

  bool have_filename = false;
  bool have_date = false;
  bool have_v_nom = false;
  bool have_v_name = false;
  bool have_date_date = false;
  std::vector<std::string> dates{};

  void FormatDate() {
    std::replace(date.begin(), date.end(), '.', '/');
    std::replace(date_date.begin(), date_date.end(), '.', '/');
    std::replace(date_date_start.begin(), date_date_start.end(), '.', '/');
    std::replace(date_date_finish.begin(), date_date_finish.end(), '.', '/');
  }

  static std::vector<std::string> SplitDate(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      elems.push_back(item);
    }
    return elems;
  }

 public:
  ParseArguments() = default;
  [[nodiscard]] std::string get_v_name() const {
    return this->v_name;
  }
  [[nodiscard]] std::string get_v_nominal() const {
    return this->v_nominal;
  }
  [[nodiscard]] std::string get_date() const {
    return this->date;
  }
  [[nodiscard]] std::string get_date_date_start() const {
    return this->date_date_start;
  }
  [[nodiscard]] std::string get_date_date_finish() const {
    return this->date_date_finish;
  }
  [[nodiscard]] bool date_date_exists() const {
    return this->have_date_date;
  }
  [[nodiscard]] std::vector<std::string> get_dates() const {
    return this->dates;
  }
  [[nodiscard]] size_t get_dates_size() const {
    return this->dates.size();
  }
  [[nodiscard]] std::string get_filename() const {
    return this->filename;
  }
  [[nodiscard]] bool filename_exists() const {
    return this->have_filename;
  }

  void Parse(int argc, char *argv[]) {
    std::string argument;
    for (int i = 1; i < argc; ++i) {
      argument = argv[i];
      if (argument.starts_with("--Vname=")) {
        have_v_name = true;
        for (int j = 8; j < argument.size(); ++j) {
          v_name += argument[j];
        }
      } else if (argument.starts_with("--Vnom=")) {
        have_v_nom = true;
        for (int j = 7; j < argument.size(); ++j) {
          v_nominal += argument[j];
        }
      } else if (argument.starts_with("--Date=")) {
        have_date = true;
        for (int j = 7; j < argument.size(); ++j) {
          date += argument[j];
        }
      } else if (argument.starts_with("--DateDate=")) {
        have_date_date = true;
        for (int j = 11; j < argument.size(); ++j) {
          date_date += argument[j];
        }
      } else if (argument.starts_with("--Filename=")) {
        have_filename = true;
        for (int j = 11; j < argument.size(); ++j) {
          filename += argument[j];
        }
      }
    }
    if (!have_date && !have_date_date) {
      date = GetCurrentDate(date_format);
    }
    if (!have_date && have_date_date) {
      SeparateDateDate('-');
    }
    FormatDate();
    if (!have_v_nom || !have_v_name) {
      std::cerr << "Parsing failed. No required arguments.";
      exit(EXIT_FAILURE);
    }
  }

  void SeparateDateDate(const char delim) {
    std::vector<std::string> out;
    size_t start;
    size_t end = 0;
    while ((start = date_date.find_first_not_of(delim, end)) != std::string::npos) {
      end = date_date.find(delim, start);
      out.push_back(date_date.substr(start, end - start));
    }
    date_date_start = out.front();
    date_date_finish = out.back();
  }

  void DatesBetween(const std::string &startDate, const std::string &endDate) {
    std::vector<std::string> startParts = SplitDate(startDate, '/');
    std::vector<std::string> endParts = SplitDate(endDate, '/');
    int startDay = std::stoi(startParts[0]);
    int startMonth = std::stoi(startParts[1]);
    int startYear = std::stoi(startParts[2]);
    int endDay = std::stoi(endParts[0]);
    int endMonth = std::stoi(endParts[1]);
    int endYear = std::stoi(endParts[2]);
    for (int year = startYear; year <= endYear; ++year) {
      int monthStart = (year == startYear) ? startMonth : 1;
      int monthEnd = (year == endYear) ? endMonth : 12;
      for (int month = monthStart; month <= monthEnd; ++month) {
        int dayStart = (year == startYear && month == startMonth) ? startDay : 1;
        int dayEnd = (year == endYear && month == endMonth) ? endDay : 31;
        for (int day = dayStart; day <= dayEnd; ++day) {
          std::string single_date = (day < 10 ? "0" : "") + std::to_string(day) + "/" +
              (month < 10 ? "0" : "") + std::to_string(month) + "/" +
              std::to_string(year);
          dates.push_back(single_date);
        }
      }
    }
  }
};