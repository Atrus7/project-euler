#include <cmath>
#include <iostream>

int fibonacci_evens(const int upTo);

int main() {
  const int LIMIT = 4000000;

  std::cout << fibonacci_evens(LIMIT) << std::endl;
}

//keep a running total, since we might have a stack overflow with recursion
int fibonacci_evens(const int upTo){
  int result = 0;
  int first = 1;
  int second = 2;

  while(second <= upTo){
    if(second % 2 == 0){
      result += second;
    }

    //next seq
    int temp = second;
    second = second+first;
    first = temp;
  }

  return result;
}
