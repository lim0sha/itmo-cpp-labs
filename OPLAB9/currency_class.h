#pragma once

namespace fs = std::filesystem;

struct XmlCurrency {
 private:
  std::string num_code;
  std::string char_code;
  int nominal{};
  std::string name;
  long double value{};
  std::vector<XmlCurrency> parsed_data;
 public:
  void ParseXml(const std::string &xml_data) {
    pugi::xml_document doc;
    if (!doc.load_string(xml_data.c_str())) {
      std::cerr << "Failed to load XML data.";
      return;
    }
    pugi::xml_node val_curs = doc.child("ValCurs");
    for (pugi::xml_node v_currency = val_curs.child("Valute"); v_currency;
         v_currency = v_currency.next_sibling("Valute")) {
      XmlCurrency curr;
      curr.num_code = v_currency.child_value("NumCode");
      curr.char_code = v_currency.child_value("CharCode");
      curr.nominal = std::stoi(v_currency.child_value("Nominal"));
      curr.name = v_currency.child_value("Name");
      std::string str_value = v_currency.child_value("Value");
      std::replace(str_value.begin(), str_value.end(), ',', '.');
      curr.value = std::stold(str_value);
      parsed_data.push_back(curr);
    }
  }

  static void ColorDraw(const std::string &message) {
    if (message.empty()) {
      std::cerr << "Non-existing request.";
      return;
    }
    system("Color 02");
    std::vector<std::string> words;
    std::istringstream iss(message);
    std::string word;
    while (iss >> word) {
      words.push_back(word);
    }
    for (const auto &kWord : words) {
      std::cout << kWord << " ";
    }
    std::cout << "\n";
  }

  void Display(ParseArguments &Parser, Request &Req) {
    std::string result_str;
    std::string v_name = Parser.get_v_name();
    std::string v_nominal = Parser.get_v_nominal();
    for (auto &c : parsed_data) {
      if (c.char_code == v_name) {
        result_str += c.char_code + " ";
        long double value_res = (stold(v_nominal) / c.nominal) * c.value;
        std::stringstream ss_value_res;
        ss_value_res << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << value_res;
        std::string str_value = ss_value_res.str();
        result_str += v_nominal + " " + Req.get_curr_date() + " " + ss_value_res.str();
        // std::replace(result_str.begin(), result_str.end(), '/', '.');
        break;
      }
    }
    if (!Parser.filename_exists()) {
      XmlCurrency::ColorDraw(result_str);
    } else {
      fs::path project_dir = "D:/ITMO/2_SEM/OP/OPLAB9";
      fs::path file_path = project_dir / Parser.get_filename();
      if (!fs::exists(project_dir)) {
        std::cerr << "No existing directory for the file.";
        return;
      }
      std::ofstream outFile(file_path, std::ios::app);
      if (!outFile.is_open()) {
        std::cerr << "Can not open the file.";
        return;
      }
      outFile << result_str << "\n";
      outFile.close();
    }
  }
};
