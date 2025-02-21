#include "vector.h"
#include <iostream>

using namespace std;

int main() {
  Vector vector1(5);
  vector1.push_back(1);
  vector1.push_back(2);
  vector1.push_back(3);
  vector1.push_back(4);
  vector1.push_back(5);
  vector1.print();

  vector1.right_rotate();
  vector1.print();
  vector1.left_rotate();
  vector1.print();
  vector1.right_rotate_steps(3);
  vector1.print();

  cout << vector1.pop(2) << endl;
  cout << vector1.pop(3) << endl;
  vector1.print();

  return 0;
}
