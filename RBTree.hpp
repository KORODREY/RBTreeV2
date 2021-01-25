#pragma once

#include <iostream>

template <typename T>
class RBTree {
    const bool red = true;
    const bool black = false;

    struct Node {
        T value; // значение элемента
        bool color; // бит цвета

        Node *left; // указатель на левое поддерево
        Node *right; // указатель на правое поддерево

        Node *parent; // родитель
    };

    Node *root; // корень дерева

    Node *Sibling(Node *node) const;

    void RotateLeft(Node *node);
    void RotateRight(Node *node);

    void FixInsertion(Node *node);
    void FixRemoving(Node *node);

    Node *FindNode(const T& value) const;
    void RemoveNode(Node *node);

    void Copy(Node *node, Node* &newNode);
    void Clear(Node* &node);

    int GetSize(Node *node) const;

    void PreOrder(std::ostream &os, Node *node) const;
    void InOrder(std::ostream &os, Node *node) const;
    void PostOrder(std::ostream &os, Node *node) const;

public:
    RBTree();
    RBTree(const RBTree& tree);

    RBTree& operator=(const RBTree& tree);

    void Insert(const T& value);
    bool Remove(const T& value);
    bool Find(const T& value) const;

    int GetSize() const;

    void PreOrder(std::ostream &os) const;
    void InOrder(std::ostream &os) const;
    void PostOrder(std::ostream &os) const;

    ~RBTree();

    template <typename T1>
    friend std::ostream& operator<<(std::ostream &os, const RBTree<T1>& tree);

    template <typename T1>
    friend std::istream& operator>>(std::istream &is, RBTree<T1>& tree);
};

template <typename T>
typename RBTree<T>::Node* RBTree<T>::Sibling(Node *node) const {
    if (node->parent == nullptr) 
        return nullptr; 

    Node *parent = node->parent;

    return node == parent->left ? parent->right : parent->left; 
}

template <typename T>
void RBTree<T>::RotateLeft(Node *node) {
    Node *right = node->right;
    node->right = right->left;

    if (node->right != nullptr)
        node->right->parent = node;

    right->parent = node->parent;

    if (node->parent == nullptr) {
        root = right;
    }
    else if (node == node->parent->left) {
        node->parent->left = right;
    }
    else {
        node->parent->right = right;
    }

    right->left = node;
    node->parent = right;
}

template <typename T>
void RBTree<T>::RotateRight(Node *node) {
    Node *left = node->left;
    node->left = left->right;

    if (node->left)
        node->left->parent = node;

    left->parent = node->parent;

    if (node->parent == nullptr) {
        root = left;
    }
    else if (node == node->parent->left) {
        node->parent->left = left;
    }
    else {
        node->parent->right = left;
    }

    left->right = node;
    node->parent = left;
}

template <typename T>
void RBTree<T>::FixInsertion(Node *node) {
    while (node != root && node->color != black && node->parent->color == red) {
        Node *parent = node->parent;
        Node *grandparent = node->parent->parent;
        Node *uncle = parent == grandparent->left ? grandparent->right : grandparent->left;

        if (uncle && uncle->color == red) {
            grandparent->color = red;
            parent->color = black;
            uncle->color = black;

            node = grandparent;
        }
        else {
            if (parent == grandparent->left) {                      
                if (node == parent->right) {
                    RotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }

                RotateRight(grandparent);
            }
            else {
                if (node == parent->left) {
                    RotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }

                RotateLeft(grandparent);
            }
            
            std::swap(parent->color, grandparent->color);

            node = parent;
        }       
    }

    root->color = black;
}

template <typename T>
void RBTree<T>::FixRemoving(Node *node) {
    if (node == root)
        return; 

    Node *sibling = Sibling(node);
    Node *parent = node->parent;

    if (sibling == nullptr) {
        FixRemoving(parent); 
    }
    else { 
        if (sibling->color == red) {
            parent->color = red; 
            sibling->color = black; 

            if (sibling == sibling->parent->left) { 
                RotateRight(parent); 
            }
            else {
                RotateLeft(parent); 
            }

            FixRemoving(node); 
        } else {
            if ((sibling->left && sibling->left->color == red) || (sibling->right && sibling->right->color == red)) {
                if (sibling->left && sibling->left->color == red) { 
                    if (sibling == sibling->parent->left) {
                        sibling->left->color = sibling->color; 
                        sibling->color = parent->color; 
                        
                        RotateRight(parent); 
                    }
                    else { 
                        sibling->left->color = parent->color; 
                        
                        RotateRight(sibling); 
                        RotateLeft(parent); 
                    } 
                }
                else { 
                    if (sibling == sibling->parent->left) {
                        sibling->right->color = parent->color; 
                        
                        RotateLeft(sibling); 
                        RotateRight(parent); 
                    }
                    else {
                        sibling->right->color = sibling->color; 
                        sibling->color = parent->color; 
                        
                        RotateLeft(parent); 
                    } 
                } 
            
                parent->color = black; 
            }
            else {
                sibling->color = red; 
                
                if (parent->color == black) {
                    FixRemoving(parent); 
                }
                else {
                    parent->color = black; 
                }
            } 
        } 
    } 
}

template <typename T>
typename RBTree<T>::Node* RBTree<T>::FindNode(const T& value) const {
    Node *node = root;

    while (node) {
        if (node->value == value)
            return node;

        if (value < node->value) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    return nullptr;
}

template <typename T>
void RBTree<T>::RemoveNode(Node *node) {
    Node *u = nullptr;

    if (node->left && node->right) {
        Node *tmp = node->right; 

        while (tmp->left) 
            tmp = tmp->left; 

        u = tmp; 
    }
    else {
        if (node->left) {
            u = node->left; 
        }
        else if (node->right) {
            u = node->right; 
        }
    }

    bool uvBlack = (u == nullptr || u->color == black) && (node->color == black);
    Node *parent = node->parent; 

    if (u == nullptr) { 
        if (node == root) { 
            root = nullptr;
        }
        else { 
            if (uvBlack) {
                FixRemoving(node); 
            }
            else {
                Node *sibling = Sibling(node);
                
                if (sibling) {
                    sibling->color = red;
                }
            } 

            if (node == node->parent->left) { 
                parent->left = nullptr; 
            } else { 
                parent->right = nullptr; 
            } 
        } 

        delete node; 
        return; 
    } 

    // если узла один ребёнок
    if (node->left == nullptr || node->right == nullptr) { 
        if (node == root) { // node - корень, присваиваем узлу его значение и удаляем u
            node->value = u->value; 
            node->left = nullptr;
            node->right = nullptr; 
            
            delete u; 
        } else { 
            // отсоединяем узел от дерева и перемещаем его вверх 
            if (node == node->parent->left) { 
                parent->left = u; 
            } else { 
                parent->right = u; 
            } 

            delete node; 
            
            u->parent = parent; 
            
            if (uvBlack) {
                FixRemoving(u);
            } else {
                u->color = black; 
            } 
        } 

        return; 
    } 

    std::swap(u->value, node->value);
    RemoveNode(u);
}

template <typename T>
void RBTree<T>::Copy(Node *node, Node* &newNode) {
    if (node == nullptr)
        return;

    newNode = new Node;
    
    newNode->value = node->value;
    newNode->color = node->color;
    newNode->left = nullptr;
    newNode->right = nullptr;

    Copy(node->left, newNode->left);
    Copy(node->right, newNode->right);
}

template <typename T>
void RBTree<T>::Clear(Node* &node) {
    if (node == nullptr)
        return;

    Clear(node->left);
    Clear(node->right);

    delete node;
    node = nullptr;
}

template <typename T>
int RBTree<T>::GetSize(Node *node) const {
    if (node == nullptr)
        return 0;

    int leftSize = GetSize(node->left);
    int rightSize = GetSize(node->right);

    return 1 + leftSize + rightSize;
}

template <typename T>
void RBTree<T>::PreOrder(std::ostream &os, Node *node) const {
    if (node == nullptr)
        return;

    os << node->value << " ";
    PreOrder(os, node->left);
    PreOrder(os, node->right);
}

template <typename T>
void RBTree<T>::InOrder(std::ostream &os, Node *node) const {
   if (node == nullptr)
        return;

    InOrder(os, node->left);
    os << node->value << " ";
    InOrder(os, node->right);
}

template <typename T>
void RBTree<T>::PostOrder(std::ostream &os, Node *node) const {
    if (node == nullptr)
        return;

    PostOrder(os, node->left);
    PostOrder(os, node->right);
    os << node->value << " ";
}

template <typename T>
RBTree<T>::RBTree() {
    root = nullptr;
}

template <typename T>
RBTree<T>::RBTree(const RBTree& tree) {
    Copy(tree.root, root);
}

template <typename T>
RBTree<T>& RBTree<T>::operator=(const RBTree& tree) {
    if (this == &tree)
        return *this;

    Clear(root);
    Copy(tree.root, root);

    return *this;
}

template <typename T>
void RBTree<T>::Insert(const T& value) {
    Node *current = root;
    Node *parent = nullptr;

    while (current != nullptr) {
        parent = current;

        if (value < current->value) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    Node *node = new Node;

    node->value = value;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = red;

    if (parent) {
        if (value < parent->value) {
            parent->left = node;
        }
        else {
            parent->right = node;
        }
    }
    else {
        root = node;
    }

    FixInsertion(node);
}

template <typename T>
bool RBTree<T>::Remove(const T& value) {
    Node *node = FindNode(value);

    // если нет нужного элемента
    if (node == nullptr)
        return false; // удаления не было

    RemoveNode(node);
    return true; // удаление было
}

template <typename T>
bool RBTree<T>::Find(const T& value) const {
    return FindNode(value) != nullptr;
}

template <typename T>
int RBTree<T>::GetSize() const {
    return GetSize(root);
}

template <typename T>
void RBTree<T>::PreOrder(std::ostream &os) const {
    PreOrder(os, root);
}

template <typename T>
void RBTree<T>::InOrder(std::ostream &os) const {
    InOrder(os, root);
}

template <typename T>
void RBTree<T>::PostOrder(std::ostream &os) const {
    PostOrder(os, root);
}

template <typename T>
RBTree<T>::~RBTree() {
    Clear(root);
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const RBTree<T>& tree) {
    tree.InOrder(os, tree.root);

    return os;
}

template <typename T>
std::istream& operator>>(std::istream &is, RBTree<T>& tree) {
    T value;
    tree.Clear(tree.root);

    while (is >> value) {
        tree.Insert(value);
    }

    return is;
}