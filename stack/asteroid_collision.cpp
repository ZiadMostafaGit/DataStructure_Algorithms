#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

vector<int> asteroid_collision(vector<int> &asteroids) {
  vector<int> stack;

  int top = -1;
  bool flag = true;
  for (int i = 0; i < asteroids.size(); i++) {
    if (stack.empty()) {
      stack.push_back(asteroids[i]);
      top++;
    } else {
      if (stack[top] > 0 && asteroids[i] < 0) {
        while (!stack.empty() && stack[top] > 0) {
          if (abs(stack[top]) > abs(asteroids[i])) {
            flag = false;
            break;
          } else if (abs(stack[top]) < abs(asteroids[i])) {
            stack.pop_back();
            top--;
          } else if (abs(stack[top]) == abs(asteroids[i])) {
            stack.pop_back();
            top--;
            flag = false;
            break;
          }
        }
        if (flag) {
          stack.push_back(asteroids[i]);
          top++;
        }
      } else {
        stack.push_back(asteroids[i]);
        top++;
      }
    }
  }
  return stack;
}
