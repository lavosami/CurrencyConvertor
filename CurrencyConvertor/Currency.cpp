//
//  Currency.cpp
//  CurrencyConvertor
//
//  Created by Егор Парамонов on 19.05.2023.
//

#include "Currency.hpp"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <map>
#include <string>

#include <curl/curl.h>

#include "json.hpp"
using json = nlohmann::json;


void Currency::parse() {
    getResponse();
    
    std::ifstream ifs("/Users/lavosami/Downloads/daily_json.js");
    
    json j = json::parse(ifs);
    
    for (auto curr : j["Valute"]) {
        currencies.insert(std::make_pair(std::string(curr["CharCode"]), (double)curr["Value"]/((double)curr["Nominal"])));
    }
    
    ifs.close();
}


size_t  writeData(void* buffer, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(buffer, size, nmemb, stream);
    return written;
}

void Currency::getResponse() {
    const char* url = "https://www.cbr-xml-daily.ru/daily_json.js";
    const char* fileName = "/Users/lavosami/Downloads/daily_json.js";

    CURL* curl = curl_easy_init();
    if (curl) {
        FILE* file = fopen(fileName, "w");
        if (file) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Failed to download file: " << curl_easy_strerror(res) << std::endl;
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


Currency Currency::operator=(Currency& other) {
    return Currency(other.balance.currency, other.balance.value);
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

Currency Currency::operator*(Currency& other) {
    if (balance.currency != other.balance.currency) {
        other.convert(balance.currency);
    }
    
    return Currency(balance.currency, balance.value * other.balance.value);
}

Currency Currency::operator/(Currency& other) {
    if (balance.currency != other.balance.currency) {
        other.convert(balance.currency);
    }
    
    return Currency(balance.currency, balance.value / other.balance.value);
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


Currency Currency::operator=(double num) {
    return Currency(balance.currency, num);
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

bool Currency::operator>(double num) {
    return (balance.value > num);
}

bool Currency::operator>=(double num) {
    return (balance.value >= num);
}

bool Currency::operator<(double num) {
    return (balance.value < num);
}

bool Currency::operator<=(double num) {
    return (balance.value <= num);
}

bool Currency::operator==(double num) {
    return (balance.value == num);
}
