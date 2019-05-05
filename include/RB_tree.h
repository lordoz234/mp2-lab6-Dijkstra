#ifndef _INCLUDE_RB_TREE_H
#define _INCLUDE_RB_TREE_H

enum Color {RED, BLACK, DOUBLE_BLACK};

template <class T>
struct Node
{
    T data;
    int color;
    Node *left, *right, *parent;
    explicit Node(T);
};

template <class T>
class RBTree
{
private:
    Node <T> *root;
protected:
    void rotateLeft(Node<T> *&);
    void rotateRight(Node<T> *&);
    void fixInsertRBTree(Node<T> *&);
    void fixDeleteRBTree(Node<T> *&);
    int getColor(Node<T> *&);
    void setColor(Node<T> *&, int);
    Node<T> *minValueNode(Node<T> *&);
    Node<T>* insertBST(Node<T> *&, Node<T> *&);
    Node<T>* deleteBST(Node<T> *&, T);
    int getBlackHeight(Node<T> *);
public:
    int size;
    RBTree();
    Node <T>* get_root();
    T minimum();
    void insert(T);
    void erase(T);
    bool empty();
};


template<class T>
Node<T>::Node(T data) {
    this->data = data;
    color = RED;
    left = right = parent = nullptr;
}

template<class T>
RBTree<T>::RBTree() {
    size = 0;
    root = nullptr;
}

template <class T>
bool RBTree<T>::empty() {
    return ((!root) ? true : false);
}

template<class T>
int RBTree<T>::getColor(Node<T> *&node) {
    if (node == nullptr)
        return BLACK;

    return node->color;
}

template<class T>
void RBTree<T>::setColor(Node<T> *&node, int color) {
    if (node == nullptr)
        return;

    node->color = color;
}

template<class T>
Node<T>* RBTree<T>::insertBST(Node<T> *&root, Node <T>*&ptr) {
    if (root == nullptr)
        return ptr;
    if (ptr->data < root->data) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }
    return root;
}

template<class T>
void RBTree<T>::insert(T n) {
    Node<T> *node = new Node<T>(n);
    root = insertBST(root, node);
    fixInsertRBTree(node);
    ++size;
}

template<class T>
void RBTree<T>::rotateLeft(Node<T> *&ptr) {
    Node<T> *right_child = ptr->right;
    ptr->right = right_child->left;
    if (ptr->right != nullptr)
        ptr->right->parent = ptr;
    right_child->parent = ptr->parent;
    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;
    right_child->left = ptr;
    ptr->parent = right_child;
}

template<class T>
void RBTree<T>::rotateRight(Node<T>*&ptr) {
    Node<T> *left_child = ptr->left;
    ptr->left = left_child->right;
    if (ptr->left != nullptr)
        ptr->left->parent = ptr;
    left_child->parent = ptr->parent;
    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;
    left_child->right = ptr;
    ptr->parent = left_child;
}

template<class T>
void RBTree<T>::fixInsertRBTree(Node<T> *&ptr) {
    Node<T> *parent = nullptr;
    Node<T> *grandparent = nullptr;
    while (ptr != root && ptr -> parent != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node<T> *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node<T> *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}


template <class T>
void RBTree<T>::fixDeleteRBTree(Node<T> *&node) {
    if (node == nullptr)
        return;

    if (node == root) {
        if (node -> left != nullptr) {
            Node<T> *temp = minValueNode(root);
            if (root->left == temp) {
                temp->left = nullptr;
            }
            temp->right = node->right;
            root = temp;
            delete (node);
        }
        else {
            root = node -> right;
            delete (node);
        }
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node<T> *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node<T> *sibling = nullptr;
        Node<T> *parent = nullptr;
        Node<T> *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}
template<class T>
Node<T> *RBTree<T>::minValueNode(Node<T> *&node) {
    Node<T> *ptr = node;
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;
}

template<class T>
Node<T>* RBTree<T>::deleteBST(Node<T> *&root, T data) {
    if (root == nullptr)
        return root;
    if (data < root->data)
        return deleteBST(root->left, data);
    if (data > root->data)
        return deleteBST(root->right, data);
    if (root->left == nullptr || root->right == nullptr)
        return root;
    Node<T> *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}

template<class T>
void RBTree<T>::erase(T data) {
    Node<T> *node = deleteBST(root, data);
    fixDeleteRBTree(node);
    --size;
}

template <class T>
Node<T>* RBTree<T>::get_root() {
    return root;
}

template <class T>
T RBTree<T>::minimum() {
	return minValueNode(root) -> data;
}

#endif //_INCLUDE_RB_TREE_H