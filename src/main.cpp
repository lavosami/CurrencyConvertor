#include "Currency.hpp"
#include <iostream>

int main(int argc, const char* argv[]) {
  Currency curr = Currency("USD", 1);

  curr.convert("RUB");

  curr.print();
  return 0;
}
