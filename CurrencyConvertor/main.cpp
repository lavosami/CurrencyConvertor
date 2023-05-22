//
//  main.cpp
//  CurrencyConvertor
//
//  Created by Егор Парамонов on 19.05.2023.
//

#include <iostream>
#include "Currency.hpp"

int main(int argc, const char * argv[]) {
    Currency curr = Currency("EUR", 1);
    
    curr.convert("USD");
    
    curr.print();
    return 0;
}
