//Hunter Harbison
//CSIII
//2/8/2022

#ifndef Collection_HPP_
#define Collection_HPP_
#include <iostream>
#include "list.hpp"

template <typename T>
class Collection;

template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T>
class Collection {
public:
    Collection();
     // head_ (nullptr); // <- example given in class not sure if its right
    void add(const T& item);
    void remove(const T& item);
    T last();
    void print();
    friend bool equal<T>(const Collection<T>& c1, const Collection<T>& c2);

private:
    node<T>* head;
};

template <typename T>
Collection<T>::Collection(){
    head=nullptr;
}

//add function
template <typename T>
void Collection<T>::add(const T& item){
    node<T> *newnode;
    newnode = new node<T>;
    newnode -> setData(item);
    newnode -> setNext(head);
    head = newnode;
}

//remove function
template <typename T>
void Collection<T>::remove(const T& item){
    node<T> *last = nullptr;
    node<T> *ptr = head;
    while (ptr != nullptr){
        auto next = ptr -> getNext();
        if (ptr -> getData() == item){
            if (last !=nullptr)
                last -> setNext(ptr -> getNext());
            delete ptr;    
        }
        if (ptr != nullptr){
            last = ptr;
        }
        ptr = next;
    }
}

//last function
template <typename T>
T Collection<T>::last(){
    return head -> getData();
}

//print function
template <typename T>
void Collection<T>::print(){
    auto print = head;
    while(print != nullptr){                 //while loop interates until nullptr
        auto e = print -> getData();
        std::cout << e << " ";
        print = print -> getNext();
    }
}

template <typename T>
bool equal (const Collection<T>& c1, const Collection<T>& c2){
    auto list1 = c1.head;
    auto list2 = c2.head;
    while (list1 != nullptr && list2 != nullptr){
        if (list1 -> getData() != list2 -> getData()){      //while loop iterates through until either list reaches nullptr
            return false;
        }
        list1 = list1 -> getNext();
        list2 = list2 -> getNext();
    }
    return true;
}

#endif