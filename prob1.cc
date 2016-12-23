#include <cmath>
#include <iostream>

int main() {
  const int LIMIT = 1000;
  const int multiples[]  = {3, 5}; // must be in non-decreasing order

  int sum = 0;

  for(int i = 0; i < LIMIT; ++i){
    if(multiples[0] * i < LIMIT) {
      int three_mul = multiples[0] * i;
      sum += multiples[0] * i;
      if(three_mul % multiples[1] == 0){
        sum -= three_mul;
      }
    }
    if(multiples[1] * i < LIMIT) {
      sum += multiples[1] * i;
    }
  }
  std::cout << sum << std::endl;
}
