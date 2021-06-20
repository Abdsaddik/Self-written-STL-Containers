#pragma once

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <new>

using namespace std;

class Exception : public std::out_of_range
{
public:
    Exception(const char* str) : std::out_of_range(str) {}
};

template<typename T>
class Container{
    protected:
    int maxSize_ = 10000;
    int top_=-1;
    int size_;
    int dynamic_size;
    T * stackPtr_ = nullptr;
    virtual bool IsFull() = 0;
    virtual void shrink() = 0;
    virtual void relocate();

    public:
    /*default Constructor*/
    Container(int Size = 100);
    /*copy Constructor*/
    Container (const Container& rhs);
    /*move Constructor*/
    Container (Container && rhs) noexcept;
    /*assignment operator*/
    virtual ~Container();
    virtual void push(const T & value) = 0;
    virtual int dynamic() const;
    virtual void pop() = 0;
    /*return the current size*/
    virtual int size() = 0;
    virtual bool empty() = 0;
    /*assignment operator*/
    Container& operator=(const Container& rhs);
};

template<typename T>
Container<T>::Container(int Size): 
size_(Size), top_{-1}, stackPtr_{new T[size_]}, dynamic_size{size_} 
{
}

template<typename T>
Container<T>::Container(const Container<T>& rhs) : 
top_{rhs.top_}, size_{rhs.size_}, stackPtr_{new T[size_]}, dynamic_size{size_} {
    if(rhs.stackPtr_==nullptr) throw Exception("Exception: no allocated dynamic memory");
    memcpy(stackPtr_, rhs.stackPtr_, size_*sizeof(T));
}

template<typename T>
Container<T>::Container (Container<T> && rhs) noexcept : top_{std::move(rhs.top_)}, size_{std::move(rhs.size_)}, stackPtr_{rhs.stackPtr_}, dynamic_size{size_} {
    stackPtr_ = rhs.stackPtr_;
    rhs.stackPtr_ = nullptr;
    rhs.size_ = 0;
    rhs.top_ = -1; 
}

template<typename T>
Container<T>::~Container(){
    delete[] stackPtr_;
    stackPtr_ = nullptr;
}

template<typename T>
int Container<T>::dynamic() const{
    return dynamic_size;
}

template<typename T>
void Container<T>::relocate(){
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
    tmp_stackPtr = nullptr;
    size_ += val;
    dynamic_size = size_;
}

/*assignment operator*/
template<typename T>
Container<T>& Container<T>::operator=(const Container<T>& rhs) {
    if(this != &rhs){
        top_ = rhs.top_;
        size_ = rhs.size_;
        dynamic_size = rhs.dynamic_size;
        // deep copy
        delete[] stackPtr_;
        stackPtr_ = new T[size_];
        memcpy(stackPtr_, rhs.stackPtr_, rhs.size_*sizeof(T));
    }  
    return *this;
}