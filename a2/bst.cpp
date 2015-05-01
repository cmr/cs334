#define B(v) (dynamic_cast<BST<T>*>(v))

template<typename T>
BST<T> *BST<T>::search(const T &v) {
    cout << "looking for " << v;
    if (v == this->value) {
        cout << "found " << v;
        return this;
    } else if (v < this->value) {
        if (this->left == NULL) {
            return NULL;
        } else {
            return dynamic_cast<BST<T>*>(this->left)->search(v);
        }
    } else {
        if (this->right == NULL) {
            return NULL;
        } else {
            return dynamic_cast<BST<T>*>(this->right)->search(v);
        }
    }
}

template<typename T>
BST<T> *BST<T>::insert(const T &v) {
    if (v <= this->value) {
        if (this->left == NULL) {
            return dynamic_cast<BST<T>*>(this->left = new BST<T>(v));
        } else {
            return dynamic_cast<BST<T>*>(this->left)->insert(v);
        }
    } else /* if (v > this->value) */ {
        if (this->right == NULL) {
            return dynamic_cast<BST<T>*>(this->right = new BST<T>(v));
        } else {
            return dynamic_cast<BST<T>*>(this->right)->insert(v);
        }
    }
}

template<typename T>
BST<T> *bst_transplant(BST<T> *u, BST<T> *v) {
    if (u->getParent() == NULL) {
        return v;
    } else if (u == u->getParent()->getLeft()) {
        u->getParent()->setLeft(v);
    } else {
        u->getParent()->setRight(v);
    }
    if (v != NULL) {
        v->setParent(u->getParent());
    }
    return u;
}

template<typename T>
BST<T> *bst_minimum(BST<T> *n) {
    while (n->getLeft() != NULL) {
        n = B(n->getLeft());
    }
    return n;
}

template<typename T>
BST<T> *BST<T>::remove(const T &v) {
    BST<T> *node = this->search(v);
    if (node == NULL) {
        return NULL;
    }
    if (node->left == NULL) {
        return bst_transplant(node, B(node->right));
    } else if (node->right == NULL) {
        return bst_transplant(node, B(node->left));
    } else {
        BST<T> *y = bst_minimum(B(this->right));
        if (y->parent != this) {
            bst_transplant(y, B(y->right));
            B(y)->right = this->right;
            B(y->right)->parent = y;
        }
        bst_transplant(this, y);
        B(y)->left = this->left;
        B(y->left)->parent = y;
        return y;
    }

}

#undef B
