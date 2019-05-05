#ifndef _INCLUDE_AVL_TREE
#define _INCLUDE_AVL_TREE

#include <queue>
#include <iostream>
#include <algorithm>

template <class T>
struct node {
    node<T> *left;
    node<T> *right;
    unsigned char height;
    T data;
};

template <class T>
class avl_tree {
private:
    node<T> *root;
    node<T>* inserts(node<T>*p, T k);
    node<T>* erases(node<T>*p, T k);
	node<T>* minimum(node<T> *p);
public:    
    avl_tree();
    node<T>* creates(T x);
    node<T> *rotateRight(node<T> *p);
    node<T> *rotateLeft(node<T>* q);
    void newheight (node<T> *p);
    unsigned char height(node<T> *p);
    int bfactor(node<T> *p);
    node<T> *balance(node<T>* p);
    void insert(T x);
    void erase(T x);
    T minimum();
    bool finds (T k);
    void print ();
    void bfs();
    bool empty();
};

template <class T>
avl_tree<T>::avl_tree() {
    root = nullptr;
}

template <class T>
node<T>* avl_tree<T>::creates(T x) {
    node<T> *temp = new node<T>();
    temp -> data = x;
    temp -> left = nullptr;
    temp -> right = nullptr;
    temp -> height = 1;
    return temp;
}

template <class T>
void avl_tree<T>::newheight (node<T> *p) {
    if (p) {
        unsigned char h1 = (p->left ? height(p->left) : 0);
        unsigned char h2 = (p->left ? height(p->right) : 0);
        p->height = std::max(h1, h2) + 1;
    }
}

template <class T>
unsigned char avl_tree<T>::height (node<T> *p) {
    if (p == nullptr) return 0;
    else return p -> height;
}

template <class T>
int avl_tree<T>::bfactor (node<T> *p) {
    if (p) {
        return height(p->right) - height(p->left);
    }
}

template <class T>
node<T>* avl_tree<T>::rotateRight (node<T> *p) {
    node<T> *q = p -> left;
    if (p == root) {
        root = q;
    }
    p -> left = q -> right;
    q -> right = p;
    newheight(p);
    newheight(q);
    newheight(root);
    return q;
}

template <class T>
node<T>* avl_tree<T>::rotateLeft (node<T> *q) {
    node<T> *p = q -> right;
    if (q == root) {
        root = p;
    }
    q -> right = p -> left;
    if (p -> left != nullptr) {
    }
    p -> left = q;
    newheight(q);
    newheight(p);
    newheight(root);
    return p;
}

template <class T>
node<T>* avl_tree<T>::minimum(node<T> *v) {
    if (v -> left == nullptr) {
        return v;
    }
    return minimum(v -> left);
}

template <class T>
node<T>* avl_tree<T>::balance (node<T>* p) {
    newheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p -> right) < 0) {
            p -> right = rotateRight(p -> right);
        }
        return rotateLeft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p -> left) > 0) {
            p -> left = rotateLeft(p -> left);
        }
        return rotateRight(p);
    }
    return p;
}

template <class T>
node<T>* avl_tree<T>::inserts(node<T>* p, T x) {
    if (root == nullptr) root = creates(x);
    else if (p == nullptr) return creates(x);
    else {
        if (x < p -> data) {
            p -> left = inserts(p -> left, x);
        }
        else {
            p -> right = inserts(p -> right, x);
        }
    }
    if (p != nullptr) {
        return balance(p);
    }
}

template <class T>
node<T>* avl_tree<T>::erases (node<T> *r, T x) {
    if (r == nullptr) return r;
    if (x < r -> data) {
        r -> left = erases (r -> left, x);
    }
    else if (x > r -> data) {
        r -> right = erases (r -> right, x);
    }
    else if (r -> left != nullptr && r -> right != nullptr) {
        r -> data = minimum(r -> right) -> data;
        r -> right = erases(r -> right, r -> data);
    }
    else {
        if (r -> left != nullptr) {
            r = r -> left;
        }
        else {
            if (r == root) {
                root = nullptr;
            }
            r = r -> right;
        }
    }
    return balance(r);
}

template <class T>
bool avl_tree<T>::finds (T x) {
    node<T> *s = root;
    while (s != nullptr) {
        if (s -> data > x) {
            if (s -> left == nullptr) {
                return false;
            }
            s = s -> left;
        } else if (s -> data < x) {
            if (s -> right == nullptr) {
                return false;
            }
            s = s -> right;
        } else {
            return true;
        }
    }
    return false;
}

template <class T>
void avl_tree<T>::bfs () {
    std::queue <node<T> *> q;
    q.push(root);
    while (!q.empty()) {
        node<T> *v = q.front();
        std::cout << v -> data << " ";
        q.pop();
        if (v -> left != nullptr) {
            q.push(v -> left);
        }
        if (v -> right != nullptr) {
            q.push(v -> right);
        }
    }
}

template <class T>
void avl_tree<T>::insert(T x) {
	inserts(root, x);
}

template <class T>
void avl_tree<T>::erase(T x) {
	erases(root, x);
}

template <class T>
T avl_tree<T>::minimum() {
	return minimum(root) -> data;
}

template <class T>
bool avl_tree<T>::empty() {
	return (!root ? true : false);
}

#endif //_INCLUDE_AVL_TREE