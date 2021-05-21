#include<iostream>
using namespace std;

template <typename T> 
class Stack {
    private:

    T* stack;
    int top;
    int capacity;
    
    public :

    Stack(int stackCapacity = 10);
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& item);
    void Pop();
};

template <typename T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize) {
    if (newSize < 0)
        throw "New length must be >=0";
    
    T* temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete[] a;
    a = temp;
}

template <typename T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity) {
  if (capacity < 1) 
    throw "Stack capacity must be >0"; 
  stack = new T[capacity];
  top = -1;
}

template <typename T>
inline bool Stack<T>::IsEmpty() const { 
  return top == -1; 
}

template <typename T>
inline T& Stack<T>::Top() const {
  if (IsEmpty())
    throw "Stack is empty"; 
  return stack[top];
}

template <typename T>
void Stack<T>::Push(const T& item) {
  if (top == capacity - 1) {
    ChangeSize1D(stack, capacity, 2 * capacity); 
    capacity *= 2;
  }
  stack[++top] = item;
}

template <typename T> void Stack<T>::Pop(){
  if (IsEmpty()) 
    throw "Stack is empty. Cannot delete"; 
  stack[top--].~T();
}
