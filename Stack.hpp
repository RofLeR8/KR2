#ifndef STACK_HPP
#define STACK_HPP
#include <exception>
#include <iostream>
template <class T> class Stack {
public:
  virtual ~Stack() {}
  virtual void push(const T &e) = 0; // Добавление элемента в стек
  virtual T pop() = 0; // Удаление верхнего элемента
  virtual bool isEmpty() = 0; // Проверка стека на пустоту
};

template <typename T> class StackArray : public Stack<T> {
private:
  int size_;
  T *dataArray_{nullptr};
  int top_;

public:
  StackArray(const StackArray<T> &src) = delete;
  StackArray(StackArray<T> &&src) = delete;
  StackArray &operator=(const StackArray<T> &src) = delete;
  StackArray &operator=(StackArray<T> &&src) = delete;
  StackArray(int size = 20);
  T top();
  virtual ~StackArray() override;
  virtual void push(const T &e) override;
  virtual T pop() override;
  virtual bool isEmpty() override;
};

// exception StackUnderflow
class StackUnderflow : public std::exception {
public:
  StackUnderflow() : reason_("Stack Underflow") {}
  const char *what() const throw() { return reason_; }

private:
  const char *reason_;
};

// exception WrongStackSize
class WrongStackSize : public std::exception {
public:
  WrongStackSize() : reason_("Wrong Stack Size") {}
  const char *what() const throw() { return reason_; }

private:
  const char *reason_;
};

// exception StackOverflow
class StackOverflow : public std::exception {
public:
  StackOverflow() : reason_("Stack Overflow") {}
  const char *what() const throw() { return reason_; }

private:
  const char *reason_;
};

// Default constructor
template <class T> StackArray<T>::StackArray(int size) : size_(size), top_(-1) {
  try {
    dataArray_ = new T[size_];
  } catch (std::exception &ex) {
    throw WrongStackSize();
  }
}

// Destructor
template <typename T> StackArray<T>::~StackArray<T>() { delete[] dataArray_; }

// push
template <class T> void StackArray<T>::push(const T &element) {
  if (top_ == size_ - 1) {
    throw StackOverflow();
  } else {
    top_++;
    dataArray_[top_] = element;
  }
  std::cout << "Element(" << element << ") was inserted into stack\n";
}

// pop
template <typename T> T StackArray<T>::pop() {
  if (isEmpty()) {
    throw StackUnderflow();
  } else {
    T element = dataArray_[top_];
    top_--;
    std::cout << "Element(" << element << ") was removed from stack\n";
    return element;
  }
}

// isEmpty
template <typename T> bool StackArray<T>::isEmpty() {
  if (top_ == -1) {
    return true;
  } else {
    return false;
  }
}

// top
template <typename T> T StackArray<T>::top() { return dataArray_[top_]; }

#endif