//
//  main.cpp
//  CurrencyConvertor
//
//  Created by Егор Парамонов on 19.05.2023.
//

#include <iostream>
#include "Currency.hpp"

int main(int argc, const char * argv[]) {
    Currency currency = Currency("BYN", 5.23);
    Currency currenc2 = Currency("BYN", 5.23);
    
    
    currency.convert("RUB");
    
    currency = currency + currenc2;
    
    currency.print();
    
    currency = currency / 2;
    
    currency.print();
    
    return 0;
}
