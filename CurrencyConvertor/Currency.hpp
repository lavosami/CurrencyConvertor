//
//  Currency.hpp
//  CurrencyConvertor
//
//  Created by Егор Парамонов on 19.05.2023.
//

#ifndef Currency_hpp
#define Currency_hpp

#include <stdio.h>
#include <iostream>
#include <map>
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
    Currency() {
        balance.currency = "RUB";
        balance.value = 0;
        parse();
    }
    
    Currency(std::string currency, double value) {
        balance.currency = currency;
        balance.value = value;
        parse();
    }
    
private:
    void parse();
    void getResponse();
    
public:
    void convert(std::string curr);
    void print();
    
public:
    Currency operator+(Currency& other);
    Currency operator-(Currency& other);
    Currency operator*(Currency& other);
    Currency operator/(Currency& other);
    bool operator>(Currency& other);
    bool operator>=(Currency& other);
    bool operator<(Currency& other);
    bool operator<=(Currency& other);
    
    Currency operator*(double num);
    Currency operator/(double num);
    bool operator>(double num);
    bool operator>=(double num);
    bool operator<(double num);
    bool operator<=(double num);
};

#endif /* Currency_hpp */
