#pragma once
#include "parser_class.h"
#include "request_class.h"
#include "currency_class.h"
#include "curl/curl.h"

void GetCurlRequest(ParseArguments& Parser, Request& Req) {
  CURL *curl;
  CURLcode c;
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if (curl) {
    if (!Parser.date_date_exists()) {
      std::string xml_s_request;
      curl_easy_setopt(curl, CURLOPT_URL, Req.get_url().data());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CollectData);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &xml_s_request);
      c = curl_easy_perform(curl);
      if (c != CURLE_OK) {
        std::cerr << "Curl parsing failed.";
        return;
      } else {
        XmlCurrency XmlCrc;
        XmlCrc.ParseXml(xml_s_request);
        XmlCrc.Display(Parser, Req);
      }
    } else {
      Parser.DatesBetween(Parser.get_date_date_start(), Parser.get_date_date_finish());
      for (int i = 0; i < Parser.get_dates_size(); ++i) {
        std::string xml_s_request;
        Req.MakeURLByDate(Parser.get_dates()[i]);
        curl_easy_setopt(curl, CURLOPT_URL, Req.get_url().data());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CollectData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &xml_s_request);
        c = curl_easy_perform(curl);
        if (c != CURLE_OK) {
          std::cerr << "Curl parsing failed.";
          return;
        } else {
          XmlCurrency XmlCrc;
          XmlCrc.ParseXml(xml_s_request);
          XmlCrc.Display(Parser, Req);
        }
      }
    }
  } else {
    curl_easy_cleanup(curl);
    std::cerr << "No parsing was enabled.";
    return;
  }
}
