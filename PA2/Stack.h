#pragma once
#include "List.h"

//My Vector
template <typename T> 
class MyStack: public List<T>{
public:
    void push(T const &e){
        this->InsertBegin(e); 
    } 
    T pop(){ 
        T tem = (*this)[0];
        this->Remove(0);
        return tem; 
        } 
    T top(){
        return (*this)[0]; 
    }
    bool empty(){
        if(this->GetSize() > 0) return false;
        else return true;
    }
};