//
//  Currency.hpp
//  CurrencyConvertor
//
//  Created by Егор Парамонов on 19.05.2023.
//

#ifndef Currency_hpp
#define Currency_hpp

#include <iostream>
#include <map>
#include <stdio.h>
#include <string>

struct Balance {
  std::string currency;
  double value;
};

class Currency {
private:
  std::map<std::string, double> currencies;
  Balance balance;

public:
  Currency();
  Currency(std::string currency, double value);

private:
  void parse();
  void getResponse();

public:
  void convert(std::string curr);
  void print();

public:
  Currency& operator=(const Currency& other);
  Currency operator+(Currency& other);
  Currency operator-(Currency& other);
  bool operator>(Currency& other);
  bool operator>=(Currency& other);
  bool operator<(Currency& other);
  bool operator<=(Currency& other);
  bool operator==(Currency& other);

  Currency& operator=(double num);
  Currency operator+(double num);
  Currency operator-(double num);
  Currency operator*(double num);
  Currency operator/(double num);
  bool operator>(double num);
  bool operator>=(double num);
  bool operator<(double num);
  bool operator<=(double num);
  bool operator==(double num);

  friend Currency operator+(double num, Currency& other);
  friend Currency operator-(double num, Currency& other);
  friend Currency operator*(double num, Currency& other);
  friend bool operator>(double num, Currency& other);
  friend bool operator>=(double num, Currency& other);
  friend bool operator<(double num, Currency& other);
  friend bool operator<=(double num, Currency& other);
  friend bool operator==(double num, Currency& other);
};

#endif /* Currency_hpp */
