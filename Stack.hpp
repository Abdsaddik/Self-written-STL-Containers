#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <new>



class Exception : public std::out_of_range
{
public:
    Exception(const char* str) : std::out_of_range(str) {}
};

template <typename T = int>
class Stack{
    private:
    int maxSize_ = 10000;
    int top_;
    int size_;
    T * stackPtr_ = nullptr;
    bool IsFull();
    void relocate();

    public:
    /*default Constructor*/
    Stack(int Size = 10);
    /*copy Constructor*/
    Stack (const Stack<T>& rhs);
    /*move Constructor*/
    Stack (Stack<T> && rhs) noexcept;
    ~Stack();
    void push(const T & value);
    void pop();
    void swap(Stack<T>& rhs);
    const T & top();
    /*return the current size*/
    int size() const;
    // copy assignment
    Stack<T>& operator = (const Stack<T>& rhs);
    bool empty();
    
};

template<typename T>
Stack<T>::Stack(int Size) : size_(Size){
    top_ = -1;
    stackPtr_ = new T[size_];
}

template<typename T>
Stack<T>::Stack (const Stack<T>& rhs) : top_{rhs.top_}, size_{rhs.size_} {
    if(rhs.stackPtr_==nullptr) throw Exception("Exception: no allocated dynamic memory");
    stackPtr_ = new T[size_];
    for(int cnt = 0; cnt <= top_; cnt++) stackPtr_[cnt] = rhs.stackPtr_[cnt];
}

template<typename T>
Stack<T>::Stack (Stack<T> && rhs) noexcept : top_{std::move(rhs.top_)}, size_{std::move(rhs.size_)}, stackPtr_{rhs.stackPtr_} {
    stackPtr_ = rhs.stackPtr_;
    rhs.stackPtr_ = nullptr;
    rhs.size_ = 0;
    rhs.top_ = -1;   
}

template<typename T>
Stack<T>::~Stack(){
    delete[] stackPtr_;
    stackPtr_ = nullptr;
}

template<typename T>
bool Stack<T>::IsFull(){
    if(top_<(size_-1)) return false;
    else relocate();
    if(top_ == size_-1) return true;
    return false;
}
template<typename T>
void Stack<T>::relocate(){
    int val = 100;
    while ((size_+val)>maxSize_) { val /= 2;} 
    T * tmp_stackPtr = new T[size_+val];
    if(tmp_stackPtr==nullptr) throw std::bad_alloc();
    memcpy(tmp_stackPtr, stackPtr_, size_*sizeof(T));  
    delete[] stackPtr_;
    stackPtr_ = new T[size_+val];
    if(stackPtr_==nullptr) throw std::bad_alloc();
    memcpy(stackPtr_, tmp_stackPtr, size_*sizeof(T));
    delete[] tmp_stackPtr; 
    size_ += val;
}

template<typename T>
void Stack<T>::push(const T & value){
    if(stackPtr_ == nullptr) throw Exception("Exception: stack is no more allocated");
    if(IsFull()) throw Exception("Exception: stack is full"); 
    stackPtr_[++top_] = value;
}

template<typename T>
void Stack<T>::pop(){
    if(stackPtr_ == nullptr) throw Exception("Exception: stack is no more allocated");
    if(empty()) throw Exception("Exception: stack is empty");
    top_--;
}
template<typename T>
void Stack<T>::swap(Stack<T>& rhs){
    std::swap(*this, rhs);
}

template<typename T>
const T & Stack<T>::top() {
    if(stackPtr_ == nullptr) throw Exception("Exception: stack is no more allocated");
    if(empty()) throw Exception("Exception: stack is empty");
    return stackPtr_[top_];
}

template<typename T>
/*return the current size*/
int Stack<T>::size() const{
    return top_+1;
}

// copy assignment
template<typename T>
Stack<T>& Stack<T>::operator = (const Stack<T>& rhs) {
    top_ = rhs.top_;
    size_ = rhs.size_;
    stackPtr_ = new T[size_];
    for(int cnt = 0; cnt <= top_; cnt++) stackPtr_[cnt] = rhs.stackPtr_[cnt];
    return *this;
}

template<typename T>
bool Stack<T>::empty(){
    return top_<0;
}
