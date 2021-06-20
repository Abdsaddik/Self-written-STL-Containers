
#pragma once

#include "Container.hpp"

template <typename T>
class Stack : public Container<T>{
    private:
    bool IsFull();
    void shrink();

    public:
    using BaseClass = Container<T>;
    /*default Constructor*/
    Stack(int Size = 100);
    /*copy Constructor*/
    Stack (const Stack& rhs);
    /*move Constructor*/
    Stack (Stack && rhs) noexcept;
    /*assignment operator*/
    ~Stack();
    void push(const T & value);
    void pop();
    void swap(Stack& rhs);
    const T & top();
    /*return the current size*/
    int size();
    bool empty(); 
    /*assignment operator*/
    Stack<T>& operator = (const Stack& rhs);
    template<typename T1>
    friend ostream& operator<<(ostream& out, Stack<T1>& s); 
};

template<typename T>
Stack<T>::Stack(int Size) : BaseClass(Size)
{
}

template<typename T>
Stack<T>::Stack (const Stack<T>& rhs) : BaseClass(rhs) 
{
}

template<typename T>
Stack<T>::Stack (Stack<T> && rhs) noexcept : BaseClass{move(rhs)} 
{
}

template<typename T>
Stack<T>::~Stack(){
    BaseClass::~Container();
}

template<typename T>
bool Stack<T>::IsFull(){
    if(BaseClass::top_<(BaseClass::size_-1)) return false;
    else BaseClass::relocate();
    if(BaseClass::top_ == BaseClass::size_-1) return true;
    return false;
}

template<typename T>
void Stack<T>::push(const T & value){
    if(BaseClass::stackPtr_ == nullptr) throw Exception("Exception: stack is no more allocated");
    if(IsFull()) throw Exception("Exception: stack is full"); 
    BaseClass::stackPtr_[++BaseClass::top_] = value;
}

template<typename T>
void Stack<T>::shrink(){
    BaseClass::size_ -= 100;
    T* stackPtr_tmp = new T[BaseClass::size_];
    memcpy(stackPtr_tmp, BaseClass::stackPtr_, BaseClass::size_*sizeof(T));
    delete[] BaseClass::stackPtr_;
    BaseClass::stackPtr_ = new T[BaseClass::size_];
    BaseClass::dynamic_size = BaseClass::size_;
    memcpy(BaseClass::stackPtr_, stackPtr_tmp, BaseClass::size_*sizeof(T));
    delete[] stackPtr_tmp;
    stackPtr_tmp = nullptr;
}

template<typename T>
void Stack<T>::pop(){
    if(BaseClass::stackPtr_ == nullptr) throw Exception("Exception: stack is no more allocated");
    if(empty()) throw Exception("Exception: stack is empty");
    BaseClass::top_--;
    if(BaseClass::size_-(BaseClass::top_+1)>99) shrink();
}
template<typename T>
void Stack<T>::swap(Stack<T>& rhs){
    std::swap(*this, rhs);
}

template<typename T>
const T & Stack<T>::top() {
    if(BaseClass::stackPtr_ == nullptr) throw Exception("Exception: stack is no more allocated");
    if(empty()) throw Exception("Exception: stack is empty");
    return BaseClass::stackPtr_[BaseClass::top_];
}

template<typename T>
/*return the current size*/
int Stack<T>::size(){
    return BaseClass::top_+1;
}

/*assignment operator*/
template<typename T>
Stack<T>& Stack<T>::operator = (const Stack<T>& rhs) {
    BaseClass::operator=(rhs);
}

template<typename T>
bool Stack<T>::empty(){
    return BaseClass::top_<0;
}

template<typename T>
ostream& operator<<(ostream& out, Stack<T>& s){
    if(s.empty()) return out << "Stack is empty!\n";
    while (s.size())
    {   
        out << s.top() << "  ";
        s.pop();
    }
    return out << endl;
}
