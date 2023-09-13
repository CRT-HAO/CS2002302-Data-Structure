#include <iostream>

using namespace std;

bool isPalindrome(int num) {
  if (num < 0)
    return false;

  int originalNum = num;
  int reservedNum = 0;

  while (num > 0) {
    int remainder = num % 10;
    reservedNum = reservedNum * 10 + remainder;
    num /= 10;
  }

  return originalNum == reservedNum;
}

int main() {
  int num;
  cin >> num;

  cout << num << " "
       << (isPalindrome(num) ? "is a palindrome number."
                             : "is not a palindrome number.")
       << endl;

  return 0;
}