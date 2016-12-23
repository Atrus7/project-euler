#include <cmath>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

long largestPal(const int digits);

int main() {
  const int DIGITS = 3;

  std::cout << largestPal(DIGITS) << std::endl;
}
bool isPal(int n){
  string s = to_string(n);
  for(int i=0; i < ceil(s.size()/2.0); ++i){
    if(s[i] != s[s.size() - 1 - i]){
      return false;
    }
  }
  return true;
}

long largestPal(const int d) {
  int LARGEST_NUMBER = pow(10, d) -1; // highest number with d digits

  for(int i=LARGEST_NUMBER; i > 1; --i){
    for(int j=LARGEST_NUMBER; j >= i; --i){
      if(isPal(i * j)){
        std::cout << i << std::endl;
        std::cout << j << std::endl;
        return i*j;
      }
    }
  }
  return -1;
}
