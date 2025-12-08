//
// Created by khaled-sawaid on 05/12/2025.
//

#ifndef DS_WET1_WINTER_2026_AVLTREE_H
#define DS_WET1_WINTER_2026_AVLTREE_H


template <typename Key, typename Value>
class AVLTree {
private:
    struct AVLNode {
        Key key;
        Value value;
        int height;
        AVLNode* left;
        AVLNode* right;

        AVLNode(const Key& k, const Value& v)
        : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
    };
    AVLNode* root;

    static int height(AVLNode* node) {
        return node != nullptr ? node->height : 0;
    }

    static int getBalance(AVLNode* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    static int max(int a, int b) {
        return a > b ? a : b;
    }
    static void updateHeight(AVLNode* node) {
        if (node == nullptr) return;
        node->height = 1 + max(height(node->left), height(node->right));
    }

    static AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    static AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    static AVLNode* rebalance(AVLNode* node) {
        updateHeight(node);
        int balance = getBalance(node);

        // left side heavy
        if (balance > 1){
            if (getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        // right side heavy
        if (balance < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    static AVLNode* insertNode(AVLNode* node, const Key& key, const Value& value, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new AVLNode(key, value);
        }

        if (key < node->key) {
            node->left = insertNode(node->left, key, value, inserted);
        } else if (key > node->key) {
            node->right = insertNode(node->right, key, value, inserted);
        } else {
            inserted = false;
            return node;
        }

        return rebalance(node);
    }

    static AVLNode* minNode(AVLNode* node) {
        if (node == nullptr) return nullptr;
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    static AVLNode* removeNode(AVLNode* node, const Key& key, bool& removed) {
        if (node == nullptr) {
            removed = false;
            return nullptr;
        }

        if (key < node->key) {
            node->left = removeNode(node->left, key, removed);
        }
        else if (key > node->key) {
            node->right = removeNode(node->right, key, removed);
        }
        else {
            removed = true;

            // Node with only one child or no child
            if (!node->left || !node->right) {
                AVLNode* child = node->left ? node->left : node->right;
                delete node;
                return child;

            } else {
                AVLNode* successor = minNode(node->right);
                Key tempKey = successor->key;

                node->key = tempKey;
                node->value = successor->value;

                node->right = removeNode(node->right, tempKey, removed);
            }
        }
        return rebalance(node);
    }

    static AVLNode* findNode(AVLNode* node, const Key& key) {
        while (node) {
            if (key < node->key) {
                node = node->left;
            } else if (key > node->key) {
                node = node->right;
            } else {
                return node;
            }
        }
        return nullptr;
    }

    static void destroyTree(AVLNode* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    AVLTree(): root(nullptr) {}

    ~AVLTree() {
        destroyTree(root);
        root = nullptr;
    }

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    bool insert(const Key& key, const Value& value) {
        bool inserted = false;
        root = insertNode(root, key, value, inserted);
        return inserted;
    }

    bool remove(const Key& key) {
        bool removed = false;
        root = removeNode(root, key, removed);
        return removed;
    }

    Value* find(const Key& key) {
        AVLNode* node = findNode(root, key);
        return node ? &node->value : nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

};


#endif //DS_WET1_WINTER_2026_AVLTREE_H