
#pragma once

#include"Container.hpp"

template <typename T>
class Queue : public Container<T>{
    
    private:
    int front_;
    bool IsFull();
    /*reduce memory size to fit the actual number elments plus size for 100X elements */
    void shrink();

    public:
    using BaseClass = Container<T>;
    /*default Constructor*/
    Queue(int Size = 100);
    /*copy Constructor*/
    Queue (const Queue& rhs);
    /*move Constructor*/
    Queue (Queue&& rhs) noexcept;
    ~Queue();
    void push(const T & value);
    T back();
    T front();
    void pop();
    void swap(Queue& rhs);
    /*return the current size*/
    int size();
    bool empty();
    /*assignment operator*/
    Queue& operator=(const Queue& rhs);
    template<typename T1>
    friend ostream& operator<<(ostream& out, Queue<T1>& q);
};

template<typename T>
Queue<T>::Queue(int Size) : front_{0}, BaseClass(Size)
{
}

template<typename T>
Queue<T>::Queue(const Queue& rhs) : front_{rhs.front_}, BaseClass{rhs} {
}

template<typename T>
Queue<T>::Queue(Queue&& rhs) noexcept : front_{move(rhs.front_)}, BaseClass{move(rhs)} {
    rhs.front_ = 0;  
}

template<typename T>
Queue<T>::~Queue(){
    BaseClass::~Container();
}

template<typename T>
bool Queue<T>::IsFull(){ 
    if((BaseClass::top_+1-front_)<(BaseClass::size_-1)) return false;
    else BaseClass::relocate();
    if((BaseClass::top_+1-front_) == BaseClass::size_-1) return true;
    return false;
}

template<typename T>
void Queue<T>::push(const T & value){
    if(BaseClass::stackPtr_ == nullptr) throw Exception("Exception: stack is no more allocated");
    if(IsFull()) throw Exception("Exception: stack is full"); 
    BaseClass::stackPtr_[++BaseClass::top_] = value;
}

template<typename T>
T Queue<T>::back(){
    if(empty()) throw Exception("Exception: stack is empty");
    return BaseClass::stackPtr_[BaseClass::top_];
}

template<typename T>
T Queue<T>::front(){
    if(empty()) throw Exception("Exception: stack is empty");
    return BaseClass::stackPtr_[front_];
}

template<typename T>
void Queue<T>::pop(){
    if(BaseClass::stackPtr_ == nullptr) {throw Exception("Exception: stack is no more allocated");}
    if(empty() == true) throw Exception("Exception: stack is empty");
    front_++;
    if(front_>99) shrink();
}

template<typename T>
void Queue<T>::swap(Queue& rhs){
    std::swap(*this, rhs);
}


template<typename T>
/*return the current size*/
int Queue<T>::size(){
    return BaseClass::size_ = (BaseClass::top_+1- front_);
}

template<typename T>
void Queue<T>::shrink(){
    T* stackPtr_tmp = new T[size()];
    memcpy(stackPtr_tmp, BaseClass::stackPtr_+front_, size()*sizeof(T));
    delete[] BaseClass::stackPtr_;
    BaseClass::stackPtr_ = new T[size()+100];
    BaseClass::dynamic_size = size()+100;
    memcpy(BaseClass::stackPtr_, stackPtr_tmp, size()*sizeof(T));
    delete[] stackPtr_tmp;
    stackPtr_tmp = nullptr;
    BaseClass::top_ = size()-1;
    front_ = 0;
}

template<typename T>
bool Queue<T>::empty(){
    return (front_>BaseClass::top_);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& rhs){
    front_ = rhs.front_;
    BaseClass::operator=(rhs);
}

template<typename T>
ostream& operator<<(ostream& out, Queue<T>& q){
    if(q.empty()) return out << "Queue is empty!\n";
    while (q.size())
    {   
        out << q.front() << "  ";
        q.pop();
    }
    return out << endl;
}
