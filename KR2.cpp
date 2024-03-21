#include "StackArray.hpp"
#include <iostream>
#include <stdexcept>

bool checkOperations(
    char &operation) { // func for check is char operation or not
  if (operation == '(' || operation == ')' || operation == '+' ||
      operation == '-' || operation == '*' || operation == '/') {
    return true;
  } else {
    return false;
  }
}

bool checkBalanceBrackets(
    const std::string &expression,
    int maxDeep) { // updated version of func from Task#2_Stack
  StackArray<char> stack(maxDeep);
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
  if (!checkBalanceBrackets(infix, infix.length())) {
    throw std::runtime_error("Error! Expression has unbalanced brackets.");
  }
  int doubleOpearation = 0;
  StackArray<char> operations(stackSize);
  for (auto it : infix) {
    if (doubleOpearation > 1) {
      throw std::invalid_argument("Invalid input");
      return;
    }
    if (isdigit(it)) { // if it is digit then push into postfix string
      postfix += it;
      doubleOpearation = 0;
      continue;
    }
    if (operations.isEmpty()) {  // if stack is empty then push first operation
      if (checkOperations(it)) { // check that it is operation
        operations.push(it);
        doubleOpearation++;
        continue;
      } else {
        throw std::invalid_argument("Invalid input"); // if not throw exception
      }
    } else {
      if (it == '+' || it == '-') { // if it == '+'  or '-' add all operation
        doubleOpearation++;         // with higher priority to postfix
        while ((operations.top() != '(') && !operations.isEmpty()) {
          postfix += operations.pop();
        }
        operations.push(it); // then push current operation into stack
        continue;
      }
      if (it == '*' || it == '/') { // if it == '*' or '/' simply  push in stack
        doubleOpearation++;         // because it has the highest priority
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
  while (
      !operations
           .isEmpty()) { // add to postfix all remaining operations from stack
    postfix += operations.pop();
  }
}

int evaluatePostfix(const std::string &infix, const std::size_t stackSize) {
  StackArray<int> numbers(stackSize);
  for (auto it : infix) {
    if (isdigit(it)) { // if it is number then push it into stack
      numbers.push(int(it - '0'));
    } else { // if it isn`t number, we take two numbers from stack and do
             // operation 'it' with 'a' and 'b'
      int a = numbers.pop();
      int b = numbers.pop();
      switch (it) {
      case '+':
        numbers.push(b + a);
        break;
      case '-':
        numbers.push(b - a);
        break;
      case '*':
        numbers.push(b * a);
        break;
      case '/':
        if (a == 0) {
          throw std::runtime_error("Devision  by zero");
        }
        numbers.push(b / a);
        break;
      default:
        throw std::invalid_argument("Invalid input");
      }
    }
  }
  return numbers.pop();
}
int main() {
  try {
    std::cout << "Enter the expression(enter '0' to stop): \n";
    std::string infix;
    while (std::cin >> infix && infix != "0") {
      std::string postfix;
      getPostfixFromInfix(infix, postfix, 50);
      std::cout << "Postfix version of expression: \n";
      std::cout << postfix << "\n";
      std::cout << "Result: \n"
                << infix << " = " << evaluatePostfix(postfix, 50) << "\n";
      std::cout << "Enter the expression(enter '0' to stop): \n";
    }
    return 0;
  } catch (std::exception &ex) {
    std::cerr << ex.what();
  }
}