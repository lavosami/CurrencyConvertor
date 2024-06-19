//
//  Currency.cpp
//  CurrencyConvertor
//
//  Created by Егор Парамонов on 19.05.2023.
//

#include "Currency.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>

#include <curl/curl.h>

#include "json.hpp"
using json = nlohmann::json;

Currency::Currency() {
  balance.currency = "RUB";
  balance.value = 0;
  parse();
}

Currency::Currency(std::string currency, double value) {
  balance.currency = currency;
  balance.value = value;
  parse();
}

void Currency::parse() {
  getResponse();

  std::ifstream ifs("daily_json.js");

  json j = json::parse(ifs);

  for (auto curr : j["Valute"]) {
    currencies.insert(
        std::make_pair(std::string(curr["CharCode"]),
                       (double)curr["Value"] / ((double)curr["Nominal"])));
  }

  ifs.close();
}

size_t writeData(void* buffer, size_t size, size_t nmemb, FILE* stream) {
  size_t written = fwrite(buffer, size, nmemb, stream);
  return written;
}

void Currency::getResponse() {
  const char* url = "https://www.cbr-xml-daily.ru/daily_json.js";
  const char* fileName = "daily_json.js";

  CURL* curl = curl_easy_init();
  if (curl) {
    FILE* file = fopen(fileName, "w");
    if (file) {
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
      CURLcode res = curl_easy_perform(curl);
      if (res != CURLE_OK) {
        std::cerr << "Failed to download file: " << curl_easy_strerror(res)
                  << std::endl;
      }

      fclose(file);
    } else {
      std::cerr << "Failed to open file for writing." << std::endl;
    }

    curl_easy_cleanup(curl);
  } else {
    std::cerr << "Failed to initialize libcurl." << std::endl;
  }
}

void Currency::convert(std::string curr) {
  if (balance.currency == curr) {
    return;
  } else if (curr == "RUB") {
    balance.value = balance.value * currencies[balance.currency];
    balance.currency = "RUB";
  } else {
    if (balance.currency != "RUB") {
      balance.value = balance.value * currencies[balance.currency];
      balance.currency = "RUB";
    }
    balance.value = balance.value / currencies[curr];
    balance.currency = curr;
  }
}

void Currency::print() {
  std::cout << balance.currency << ": " << balance.value << '\n';
}

Currency& Currency::operator=(const Currency& other) {
  if (this == &other) {
    return *this;
  }

  balance.currency = other.balance.currency;
  balance.value = other.balance.value;

  return *this;
}

Currency Currency::operator+(Currency& other) {
  if (balance.currency != other.balance.currency) {
    other.convert(balance.currency);
  }

  return Currency(balance.currency, balance.value + other.balance.value);
}

Currency Currency::operator-(Currency& other) {
  if (balance.currency != other.balance.currency) {
    other.convert(balance.currency);
  }

  return Currency(balance.currency, balance.value - other.balance.value);
}

bool Currency::operator>(Currency& other) {
  if (balance.currency != other.balance.currency) {
    other.convert(balance.currency);
  }

  return (balance.value > other.balance.value);
}

bool Currency::operator>=(Currency& other) {
  if (balance.currency != other.balance.currency) {
    other.convert(balance.currency);
  }

  return (balance.value >= other.balance.value);
}

bool Currency::operator<(Currency& other) {
  if (balance.currency != other.balance.currency) {
    other.convert(balance.currency);
  }

  return (balance.value < other.balance.value);
}

bool Currency::operator<=(Currency& other) {
  if (balance.currency != other.balance.currency) {
    other.convert(balance.currency);
  }

  return (balance.value <= other.balance.value);
}

bool Currency::operator==(Currency& other) {
  if (balance.currency != other.balance.currency) {
    other.convert(balance.currency);
  }

  return (balance.value == other.balance.value);
}

Currency& Currency::operator=(double num) {
  if (this->balance.value == num) {
    return *this;
  }

  balance.value = num;

  return *this;
}

Currency Currency::operator+(double num) {
  return Currency(balance.currency, balance.value + num);
}

Currency Currency::operator-(double num) {
  return Currency(balance.currency, balance.value - num);
}

Currency Currency::operator*(double num) {
  return Currency(balance.currency, balance.value * num);
}

Currency Currency::operator/(double num) {
  return Currency(balance.currency, balance.value / num);
}

bool Currency::operator>(double num) { return (balance.value > num); }

bool Currency::operator>=(double num) { return (balance.value >= num); }

bool Currency::operator<(double num) { return (balance.value < num); }

bool Currency::operator<=(double num) { return (balance.value <= num); }

bool Currency::operator==(double num) { return (balance.value == num); }

Currency operator+(double num, Currency& other) {
  return Currency(other.balance.currency, other.balance.value + num);
}

Currency operator-(double num, Currency& other) {
  return Currency(other.balance.currency, other.balance.value - num);
}

Currency operator*(double num, Currency& other) {
  return Currency(other.balance.currency, other.balance.value * num);
}

bool operator>(double num, Currency& other) {
  return (num > other.balance.value);
}

bool operator>=(double num, Currency& other) {
  return (num >= other.balance.value);
}

bool operator<(double num, Currency& other) {
  return (num < other.balance.value);
}

bool operator<=(double num, Currency& other) {
  return (num <= other.balance.value);
}

bool operator==(double num, Currency& other) {
  return (num == other.balance.value);
}
