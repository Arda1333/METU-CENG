#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    void treeCopy(BSTNode<T> *&r, BSTNode<T> *object);
    void treeDelete(BSTNode<T> *r);
    bool containsHelper(BSTNode<T> *r,BSTNode<T> *node) const;
    void insertHelper(BSTNode<T> *r, BSTNode<T> *node);
    void removeHelper(BSTNode<T> *&r, T value);
    T getMin(BSTNode<T> *r);
    BSTNode<T> *searchHelper(BSTNode<T> *r, T value) const;
    int getSize(BSTNode<T> *r) const;
    void inorderTraversal(BSTNode<T> *r, BSTNode<T> **list, int &i) const;
    void preorderTraversal(BSTNode<T> *r, BSTNode<T> **list, int &i) const;
    void postorderTraversal(BSTNode<T> *r, BSTNode<T> **list, int &i) const;

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    /* TODO */
    root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    /* TODO */
    if(obj.root == NULL)
    {
        this -> root = NULL;
        return;
    }

    this -> treeCopy(this -> root, obj.root);
}

template<class T>
BST<T>::~BST() {
    /* TODO */
    this -> treeDelete(this -> root);
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    /* TODO */
    return this -> root;
}

template<class T>
bool BST<T>::isEmpty() const {
    /* TODO */
    return this -> root == NULL;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    /* TODO */
    return containsHelper(this -> root, node);
}

template<class T>
void BST<T>::insert(const T &data) {
    /* TODO */
    BSTNode<T> *temp = new BSTNode<T>(data, NULL, NULL);

    if(this -> root == NULL) root = temp;

    else this -> insertHelper(this -> root, temp);
}

template<class T>
void BST<T>::remove(const T &data) {
    /* TODO */
    this -> removeHelper(this -> root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    /* TODO */
    this -> treeDelete(this -> root);
    root = NULL;
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    /* TODO */
    return this -> searchHelper(this -> root, data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {
    int size = this -> getSize(this -> root), i = 0;

    BSTNode<T> **list = new BSTNode<T> *[size], *temp;

    if (tp == inorder) {
        /* TODO */
        this -> inorderTraversal(this -> root, list, i);

        for(i = 0; i < size; i++)
        {
            if(list[i] == node && i != size - 1)
            {
                temp = list[i + 1];
                delete[] list;
                return temp;
            }
        }

        delete[] list;
        return NULL;
    } else if (tp == preorder) {
        /* TODO */
        i = 0;
        this -> preorderTraversal(this -> root, list, i);

        for(i = 0; i < size; i++)
        {
            if(list[i] == node && i != size - 1)
            {
                temp = list[i + 1];
                delete[] list;
                return temp;
            }
        }

        delete[] list;
        return NULL;
    } else if (tp == postorder) {
        /* TODO */
        i = 0;
        this -> postorderTraversal(this -> root, list, i);

        for(i = 0; i < size; i++)
        {
            if(list[i] == node && i != size - 1)
            {
                temp = list[i + 1];
                delete[] list;
                return temp;
            }
        }

        delete[] list;
        return NULL;
    }
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */
    if(rhs.root == NULL) this -> root = NULL;
    
    else this -> treeCopy(this -> root, rhs.root);

    return *this;
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        /* TODO */
        std::cout << "\t" << node->data;

        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);

        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    } else if (tp == postorder) {
        /* TODO */
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }

        std::cout << "\t" << node->data;
    }
}




//Helper functions

template<class T>
void BST<T>::treeCopy(BSTNode<T> *&r, BSTNode<T> *object)
{
    /* TODO */
    if(object == NULL) return;

    r = new BSTNode<T>(object -> data, NULL, NULL);
    this -> treeCopy(r -> left, object -> left);
    this -> treeCopy(r -> right, object -> right);
}

template<class T>
void BST<T>::treeDelete(BSTNode<T> *r)
{
    if(r == NULL) return;

    this -> treeDelete(r -> left);
    this -> treeDelete(r -> right);
    delete r;
}

template<class T>
bool BST<T>::containsHelper(BSTNode<T> *r, BSTNode<T> *node) const
{
    if(r == NULL) return false;

    else if(r == node) return true;

    return (this -> containsHelper(r -> left, node) || this -> containsHelper(r -> right, node));
}

template<class T>
void BST<T>::insertHelper(BSTNode<T> *r, BSTNode<T> *node)
{
    if(r -> data > node -> data)
    {
        if(r -> left == NULL) r -> left = node;

        else this -> insertHelper(r -> left, node);
    }

    else if(r -> data < node -> data)
    {
        if(r -> right == NULL) r -> right = node;

        else this -> insertHelper(r -> right, node);
    }
}

template<class T>
void BST<T>::removeHelper(BSTNode<T> *&r, T value)
{
    if(r == NULL) return;

    else if(r -> data > value) this -> removeHelper(r -> left, value);

    else if(r -> data < value) this -> removeHelper(r -> right, value);

    else
    {
        if(r -> right && r -> left)
        {
            r -> data = this -> getMin(r -> right);

            this -> removeHelper(r -> right, r -> data);
        }

        else
        {
            BSTNode<T> *oldNode = r;

            if(r -> right) r = r -> right;

            else r = r -> left;

            delete oldNode;
        }
    }
}

template<class T>
T BST<T>::getMin(BSTNode<T> *r)
{
    while(r -> left) r = r -> left;

    return r -> data;
}

template<class T>
BSTNode<T> *BST<T>::searchHelper(BSTNode<T> *r, T value) const
{
    if(r == NULL) return NULL;

    if(r -> data == value) return r;

    if(r -> data < value) return this -> searchHelper(r -> right, value);

    else return this -> searchHelper(r -> left, value);
}

template<class T>
int BST<T>::getSize(BSTNode<T> *r) const
{
    if(r == NULL) return 0;

    return 1 + this -> getSize(r -> left) + this -> getSize(r -> right);
}

template<class T>
void BST<T>::inorderTraversal(BSTNode<T> *r, BSTNode<T> **list, int &i) const
{
    if(r == NULL) return;

    inorderTraversal(r -> left, list, i);

    list[i] = r;
    i++;

    inorderTraversal(r -> right, list, i);
}

template<class T>
void BST<T>::preorderTraversal(BSTNode<T> *r, BSTNode<T> **list, int &i) const
{
    if(r == NULL) return;

    list[i] = r;
    i++;

    preorderTraversal(r -> left, list, i);

    preorderTraversal(r -> right, list, i);
}

template<class T>
void BST<T>::postorderTraversal(BSTNode<T> *r, BSTNode<T> **list, int &i) const
{
    if(r == NULL) return;

    postorderTraversal(r -> left, list, i);

    postorderTraversal(r -> right, list, i);

    list[i] = r;
    i++;
}