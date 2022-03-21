#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    
private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    /* TODO */
    this -> head = NULL;
    this -> size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    /* TODO */
    Node<T> *curr1, *curr2 = obj.head;
    int i;

    if(obj.size == 0 || obj.head == NULL)
    {
        this -> size = 0;
        this -> head = NULL;
        return;
    }

    curr1 = new Node<T>(curr2 -> data);
    head = curr1;
    curr2 = curr2 -> next;
    this -> size = obj.size;

    for(i = 1; i < this -> size; i++)
    {
        curr1 -> next = new Node<T>(curr2 -> data);
        curr1 -> next -> prev = curr1;
        curr1 = curr1 -> next;
        curr2 = curr2 -> next;
    }

    curr1 -> next = this -> head;
    this -> head -> prev = curr1;
}

template<class T>
LinkedList<T>::~LinkedList() {
    /* TODO */

    this -> removeAllNodes();
}

template<class T>
int LinkedList<T>::getSize() const {
    /* TODO */
    return this -> size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    /* TODO */
    if(this -> size == 0 || this -> head == NULL) return true;
    
    return false;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    /* TODO */
    Node<T> *curr = this -> head;
    if (curr == NULL) return false;

    do
    {
        if(curr -> data == node -> data && curr -> next == node -> next && curr -> prev == node -> prev) return true;

        curr = curr -> next;
    }
    while(curr != this -> head);

    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    /* TODO */
    return this -> head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    /* TODO */
    if(this -> head == NULL) return NULL;

    return this -> head -> prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    /* TODO */
    Node<T> *curr = this -> head;

    if(curr == NULL) return NULL;

    do
    {
        if(curr -> data == data) return curr;
        curr = curr -> next;
    }while(curr != this -> head);

    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    /* TODO */
    if(index >= this -> size || index < 0 || this -> head == NULL) return NULL;

    Node<T> *curr = this -> head;
    int i;

    for(i = 0; i < index; i++) curr = curr -> next;

    return curr;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    /* TODO */
    Node<T> *tmp = new Node<T>(data);
    tmp -> prev = tmp;
    tmp -> next = tmp;

    if(this -> head == NULL)
    {
        this -> head = tmp;
        size++;
        return;
    }

    tmp -> prev = this -> head -> prev;
    tmp -> next = this -> head;
    this -> head -> prev -> next = tmp;
    this -> head -> prev = tmp;

    this -> head = tmp;
    this -> size++;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    /* TODO */
    Node<T> *tmp = new Node<T>(data);
    tmp -> prev = tmp;
    tmp -> next = tmp;

    if(this -> head == NULL)
    {
        this -> head = tmp;
        size++;
        return;
    }

    tmp -> prev = this -> head -> prev;
    tmp -> next = this -> head;
    this -> head -> prev -> next = tmp;
    this -> head -> prev = tmp;

    this -> size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    /* TODO */
    Node<T> *curr = this -> head;
    bool inList = false;

    if(this -> head == NULL) return;

    do
    {
        if(curr == node)
        {
            inList = true;
            break;
        }

        curr = curr -> next;
    }while(curr != head);

    if(not inList) return;

    Node<T> *tmp = new Node<T>(data, curr, curr -> next);

    curr -> next -> prev = tmp;
    curr -> next = tmp;

    this -> size++;
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    /* TODO */
    Node<T> *curr = this -> head;
    int count, mod = k - 1, copy_size = this -> size;

    if(curr == NULL) return;

    for(count = 1; count <= copy_size; count++)
    {
        if(count % mod == 0)
        {
            Node<T> *temp = new Node<T>(data, curr, curr -> next);
            curr -> next = temp;
            curr = temp -> next;
            curr -> prev = temp;
            this -> size++;

        }

        else curr = curr -> next;
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    /* TODO */
    Node<T> *curr = this -> head;
    bool notIn = true;

    if(curr == NULL) return;

    do
    {
        if(curr == node)
        {
            notIn = false;
            break;
        }
        curr = curr -> next;
    }while(curr != head);

    if(notIn) return;

    curr -> prev -> next = curr -> next;
    curr -> next -> prev = curr -> prev;

    if(curr == this -> head)
    {
        if(curr -> next == curr) this -> head = NULL;

        else this -> head = curr -> next;
    }

    delete curr;
    this -> size--;
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    /* TODO */
    Node<T> *curr = this -> head, *temp;

    if(curr == NULL) return;

    do
    {
        temp = curr -> next;

        if(curr -> data == data)
        {
            curr -> prev -> next = curr -> next;
            curr -> next -> prev = curr -> prev;

            if(curr == this -> head)
            {
                if(curr -> next == curr) this -> head = NULL;

                else this -> head = curr -> next;
            }

            delete curr;
            this -> size--;
        }

        curr = temp;
    }while(curr != this -> head && this -> head != NULL);
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
    Node<T> *curr = this -> head, *temp;
    int i;

    if(curr == NULL) return;

    for(i = 0; i < this -> size; i++)
    {
        temp = curr -> next;
        delete curr;
        curr = temp;
    }

    this -> head = NULL;
    this -> size = 0;
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    /* TODO */
    Node<T> *curr = this -> head, *temp;
    int copy_size = this -> size, count;

    if(curr == NULL) return;

    if(k == 1)
    {
        this -> removeAllNodes();
        return;
    }

    for(count = 1; count <= copy_size; count++)
    {
        if(count % k == 0)
        {
            temp = curr -> next;
            curr -> prev -> next = curr -> next;
            curr -> next -> prev = curr -> prev;
            delete curr;
            curr = temp;
            this -> size--;
        }

        else curr = curr -> next;
    }
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    /* TODO */
    bool notIn1 = true, notIn2 = true;
    Node<T> *curr1 = this -> head, *curr2 = head, *item1, *item2, *temp;

    if(this -> head == NULL) return;

    do
    {
        if(curr1 == node1)
        {
            notIn1 = false;
            item1 = curr1;
        }

        if(curr2 == node2)
        {
            notIn2 = false;
            item2 = curr2;
        }

        curr1 = curr1 -> next;
        curr2 = curr2 -> next;
    }while(curr1 != this -> head && curr2 != this -> head);

    if(notIn1 or notIn2) return;

    if(item1 -> next == item2)
    {
        item1 -> prev -> next = item2;
        item2 -> next -> prev = item1;

        temp = item1 -> prev;
        item1 -> prev = item2;
        item2 -> prev = temp;

        temp = item2 -> next;
        item2 -> next = item1;
        item1 -> next = temp;
    }

    else if(item2 -> next == item1)
    {
        item2 -> prev -> next = item1;
        item1 -> next -> prev = item2;

        temp = item2 -> prev;
        item2 -> prev = item1;
        item1 -> prev = temp;

        temp = item1 -> next;
        item1 -> next = item2;
        item2 -> next = temp;
    }

    else
    {
        item1 -> next -> prev = item2;
        item1 -> prev -> next = item2;
        item2 -> next -> prev = item1;
        item2 -> prev -> next = item1;

        temp = item1 -> next;
        item1 -> next = item2 -> next;
        item2 -> next = temp;

        temp = item1 -> prev;
        item1 -> prev = item2 -> prev;
        item2 -> prev = temp;
    }

    if(this -> head == item1) this -> head = item2;

    else if(this -> head == item2) this -> head = item1;
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    /* TODO */
    int i;

    for(i = 0; i < size; i++) (*this).swap((*this).getNodeAtIndex(i), (*this).getNodeAtIndex((i * i + seed) % size));
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    /* TODO */
    int i;
    
    if(rhs.head == NULL || rhs.size == 0)
    {
        this -> size = 0;
        this -> head = NULL;
        return *this;
    }


    (*this).removeAllNodes();

    for(i = 0; i < rhs.size; i++) (*this).insertAtTheEnd(rhs.getNodeAtIndex(i) -> data);

    return *this;
}

#endif //LINKEDLIST_H
