#include "Stack.hpp"
#include <iostream>

bool checkOperations(char &operation) {
  if (operation == '(' || operation == ')' || operation == '+' ||
      operation == '-' || operation == '*' || operation == '/') {
    return true;
  } else {
    return false;
  }
}

// bool checkBalanceBrackets(const std::string &expression, const int maxDeep) { // take from Task#2_Stack
//   StackArray<char> stack(maxDeep);
//   for (auto it : expression) {
//     if (stack.isEmpty() && (it == '(' || it == '{' ||  it == '[')) {
//       stack.push(it);
//     } else {
//       if ((stack.top() == '(' && it == ')') ||
//           (stack.top() == '{' && it == '}') ||
//           (stack.top() == '[' && it == ']')) {
//         stack.pop();
//       } else {if(){}
//       }
//     }
//   }
//   // std::cout << "result: " << stack.isEmpty() << "\n";
//   return stack.isEmpty();
// }

bool checkBalanceBrackets(const std::string &expression) {
  StackArray<char> stack;
  for (char c : expression) {
    if (c == '(' || c == '{' || c == '[') {
      stack.push(c);
    } else if (c == ')' || c == '}' || c == ']') {
      if (stack.isEmpty()) {
        return false;
      }
      char top = stack.top();
      stack.pop();
      if ((c == ')' && top != '(') || (c == '}' && top != '{') ||
          (c == ']' && top != '[')) {
        return false;
      }
    }
  }
  return stack.isEmpty();
}

void getPostfixFromInfix(const std::string &infix, std::string &postfix,
                         const std::size_t stackSize) {
  if(!checkBalanceBrackets(infix)) {
    throw std::runtime_error("Error! Expression has unbalanced brackets.");
  }
  StackArray<char> operations(stackSize);
  for (auto it : infix) {
    if (isdigit(it)) { // if it is digit then push into postfix string
      postfix += it;
      continue;
    }
    if (operations.isEmpty()) {  // if stack is empty then push first operation
      if (checkOperations(it)) { // check that it is operation
        operations.push(it);
        continue;
      } else {
        throw std::invalid_argument("Invalid input"); // if not throw exception
      }
    } else {
      if (it == '+' || it == '-') { // if it == '+'  or '-' add all operation
                                    // with higher priority to postfix
        while ((operations.top() != '(') && !operations.isEmpty()) {
          postfix += operations.pop();
        }
        operations.push(it); // then push current operation into stack
        continue;
      }
      if (it == '*' || it == '/') { // if it == '*' or '/' simply  push in stack
                                    // because it has the highest priority
        operations.push(it);
        continue;
      }
      if (it == '(') { // if it == '(' simply push into stack
        operations.push(it);
      }
      if (it == ')') { // if it == ')' add to postfix all operation from stack
                       // before the '('
        while (operations.top() != '(' && !operations.isEmpty()) {
          postfix += operations.pop();
        }
        operations.pop(); // remove the '('
      }
    }
  }
  while (!operations.isEmpty()) {
    postfix += operations.pop();
  }
}
int main() {
  std::string infix = "3*6+1*(4+5/2-7)-8";
  std::string postfix;
  getPostfixFromInfix(infix, postfix, 50);
  std::cout << postfix;
  return 0;
}