#pragma once

class Request {
 private:
  std::string url;
  std::string current_date;
  const std::string url_template = "www.cbr.ru/scripts/XML_daily.asp?date_req=";
  void MakeURL(const ParseArguments &Parser) {
    url = url_template + Parser.get_date();
  }
 public:
  explicit Request(const ParseArguments &Parser) {
    current_date = Parser.get_date();
    MakeURL(Parser);
  }
  void MakeURLByDate(const std::string &date) {
    current_date = date;
    url = url_template + date;
  }
  [[nodiscard]] std::string get_url() const {
    return this->url;
  }
  [[nodiscard]] std::string get_curr_date() const {
    return this->current_date;
  }
};

static size_t CollectData(char *p, size_t s, size_t n, std::string *d) {
  d->append(p, s * n);
  return s * n;
}