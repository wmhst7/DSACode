#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

//List Implementation Begin
#define LIST_NODE_DEFAULT_DATA 0

template <typename T>
class ListNode{
public:
    T data;
    ListNode<T> * next;
    ListNode(T d = LIST_NODE_DEFAULT_DATA, ListNode<T>* n = nullptr)
    :data(d), next(n){}
};

template <typename T>
class MyList{
private:
    ListNode<T> *head, *tail;
    int size;
public:
    List(){
        head = new ListNode<T>();
        tail = new ListNode<T>();
        head->next = tail;
        size = 0;
    }
    void InsertBegin(T d){
        ListNode<T> * p = head->next;
        head->next = new ListNode<T>(d,p);
        size++;
    }
    void InsertEnd(T d){
        ListNode<T> * p = head;
        while(p->next != tail){
            p = p->next;
        }
        p->next = new ListNode<T>(d,tail);
        size++;
    }
    bool Remove(int k){
        if(k < 0 || k >= size) return false;
        ListNode<T> *p = head, *q = head->next;
        int position = 0;
        while(position < k){
            p = p->next;
            q = q->next;
            position++;
        }
        p->next = q->next;
        size--;
        delete q;
        return true;
    }
    void Print(){
        ListNode<T> *p= head;
        p = p->next;
        while(p != tail){
            std::cout<<p->data->data<<' ';
            p = p->next;
        }
        std::cout<<std::endl;
    }
    T operator[](int k){
        if(k < 0 || k >= size) return LIST_NODE_DEFAULT_DATA;
        ListNode<T> *p = head;
        int position = -1;
        while(position < k){
            p = p->next;
            position++;
        }
        return p->data;
    }
    
    int GetSize(){
        return size;
    }
};
//List Implementaion End