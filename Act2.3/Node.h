#ifndef NODE_H
#define NODE_H

template<class T>
struct Node {
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node(T data);
    Node(T data, Node<T> *prev, Node<T> *next);
};

template<class T>
Node<T>::Node(T data){
    this->data = data;
    this->prev = NULL;
    this->next = NULL;
}

template<class T>
Node<T>::Node(T data, Node<T>* prev, Node<T>* next){
    this->data = data;
    this->prev = prev;
    this->next = next;
}

#endif