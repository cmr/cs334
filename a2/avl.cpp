#define A(v) (dynamic_cast<AVL<T>*>(v))

template<typename T>
AVL<T> *AVL<T>::search(const T &v) {
    cout << "looking for " << v;
    if (v == this->value) {
        cout << "found " << v;
        return this;
    } else if (v < this->value) {
        if (this->left == NULL) {
            return NULL;
        } else {
            return A(this->left)->search(v);
        }
    } else {
        if (this->right == NULL) {
            return NULL;
        } else {
            return A(this->right)->search(v);
        }
    }
}

template<typename T>
AVL<T> *AVL<T>::insert(const T &v) {
    if (v <= this->value) {
        if (this->left == NULL) {
            return A(this->left = new AVL<T>(v));
        } else {
            return A(this->left)->insert(v);
        }
    } else /* if (v > this->value) */ {
        if (this->right == NULL) {
            return dynamic_cast<AVL<T>*>(this->right = new AVL<T>(v));
        } else {
            return dynamic_cast<AVL<T>*>(this->right)->insert(v);
        }
    }
}

template<typename T>
AVL<T> *bst_transplant(AVL<T> *u, AVL<T> *v) {
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
AVL<T> *bst_minimum(AVL<T> *n) {
    while (n->getLeft() != NULL) {
        n = B(n->getLeft());
    }
    return n;
}

template<typename T>
AVL<T> *AVL<T>::remove(const T &v) {
    AVL<T> *node = this->search(v);
    if (node == NULL) {
        return NULL;
    }
    if (node->left == NULL) {
        return bst_transplant(node, B(node->right));
    } else if (node->right == NULL) {
        return bst_transplant(node, B(node->left));
    } else {
        AVL<T> *y = bst_minimum(B(this->right));
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
