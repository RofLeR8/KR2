#ifndef STACK_HPP
#define STACK_HPP
template <class T> class Stack {
public:
  virtual ~Stack() {}
  virtual void push(const T &e) = 0; // Добавление элемента в стек
  virtual T pop() = 0; // Удаление верхнего элемента
  virtual bool isEmpty() = 0; // Проверка стека на пустоту
};

#endif