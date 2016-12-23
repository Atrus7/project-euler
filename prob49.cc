#include <cmath>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cassert>
using namespace std;

vector<int> otherSeq(const int digits);
bool isPerm(int n1, int n2);

bool isPrime(const int target){
  for(int i=2; i < target; ++i){
    if(target % i == 0){
      return false;
    }
  }
  return true;
}

int main() {
  const int DIGITS = 4;
  vector<int> seq = otherSeq(DIGITS);
  assert(seq.size() <= 100);
  std::cout << seq[0] << " " << seq[1]<< " " << seq[2] << std::endl;

  assert(isPerm(seq[0], seq[1]));
  assert(isPerm(seq[2], seq[1]));
}

bool isPerm(int n1, int n2){
  string s1 = to_string(n1);
  string s2 = to_string(n2);
  long hash1 = 0;
  long hash2 = 0;
  for(int i=0; i < 4; ++i){
    hash1 += pow(10, s1[i] - 48);
    hash2 += pow(10, s2[i] - 48);
  }
  return hash2 == hash1;
}

vector<int> otherSeq(const int d) {
  vector<int> prime_nums;
  int LARGEST_NUMBER = pow(10, d) -1; // highest number with d digits
  int SMALLEST_NUMBER = pow(10, d-1); // lowest number with d digits

  std::cout << LARGEST_NUMBER  << std::endl;
  std::cout << SMALLEST_NUMBER  << std::endl;
  for(int i=SMALLEST_NUMBER; i <= LARGEST_NUMBER; i++){
    if(isPrime(i)){
      prime_nums.push_back(i);
    }
  }

  for(int i=0; i < prime_nums.size(); ++i){
    int prev_dist = 0;
    vector<int> need_three;
    need_three.push_back(prime_nums[i]);

    for(int j=i+1; j < prime_nums.size(); ++j){
      if(isPerm(prime_nums[i], prime_nums[j]) ){
        if(prev_dist == 0 || need_three.back() - prime_nums[j]  == prev_dist){
          prev_dist =  need_three.back() - prime_nums[j];
          need_three.push_back(prime_nums[j]);
        }
      }
    }

    if(need_three.size() >= 3){
      return need_three;
    }

  }
  return prime_nums;
}
