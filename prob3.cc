#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

long largestPrime(const long target);
bool hasFactors(const long target);
std::vector<long> getFactors(const long target);

int main() {
  const long TARGET = 600851475143;

  std::cout << largestPrime(TARGET) << std::endl;
}

//keep a running total, since we might have a stack overflow with recursion
long largestPrime(const long target){
  long result = 0;
//get factors
  for(long i = 2; i < target/2; ++i){
    if(target % i == 0){
      if(!hasFactors(target / i)){
        return target / i;
      }
    }
  }
  return -1;// nothing found
}

bool hasFactors(const long target){
  for(int i=2; i < target; ++i){
    if(target % i == 0){
      return true;
    }
  }
  return false;
}
