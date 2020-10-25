#pragma once

#include "DoublyLinkedList.h"

template<class T>
class Heap{
private:
    DoublyLinkedList<T> heap;
    int size;
    void downSort(int index);
    void swap(int a, int b);
public:
    Heap();
    Heap(DoublyLinkedList<T> list);
    T remove();
    void insert(T data);
    bool isEmpty();
    void print();
};

template<class T>
Heap<T>::Heap() {
    size = 0;
}

template<class T>
void Heap<T>::downSort(int index){
    while (index >= 1) {
        int pos = index;
        while (pos*2 <= size) {
            int s1 = pos*2;
            int s2 = pos*2+1;
            int max;
            if (s2 > size) {
                max = s1;
            } else {
                heap[s1] > heap[s2] ? max = s1 : max = s2;
            }
            if (heap[max] > heap[pos]) {
                swap(pos, max);
                pos = max;
            } else {
                pos = size;
            }
        }
        index--;
    }
}

template<class T>
Heap<T>::Heap(DoublyLinkedList<T> list) {
    if(!list.isEmpty()){
        heap = list;
        size = list.getSize();
        int index = size / 2;
        downSort(index);
    }
}

template<class T>
void Heap<T>::swap(int a, int b){
    T aux = heap[a];
    heap[a] = heap[b];
    heap[b] = aux;
}

template<class T>
T Heap<T>::remove(){
    if (!isEmpty()) {
        T aux = heap[1];
        swap(1,size);
        heap.deleteAt(size);
        size--;
        downSort(1);
        return aux;
    } else {
        throw runtime_error("The heap is empty");
    }
}

template<class T>
void Heap<T>::insert(T data){
    heap.addLast(data);
    size++;
    int index = size / 2;
    downSort(index);
}

template<class T>
bool Heap<T>::isEmpty(){
    return size == 0;
}

template<class T>
void Heap<T>::print(){
    heap.print();
}