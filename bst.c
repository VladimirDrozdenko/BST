
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

static int _max(int a, int b) {
    return (a < b) ? b : a;
}

static void _insert(Node* parent, Node* newNode) {
    Node* p = parent;
    while (p) {
        if (p->value == newNode->value) {
            free(newNode);
            return; // no duplicates
        }

        if (p->value > newNode->value) {
            if (p->left != 0) {
                p = p->left;
            } else {
                parent->left = newNode;
                return;
            }
        } else {
            if (p->right != 0) {
                p = p->right;
            } else {
                p->right = newNode;
                return;
            }
        }
    }
}

static unsigned int _size(const Node* p) {
    if (p == 0) {
        return 0;
    }
    return 1 + _size(p->left) + _size(p->right);
}

static unsigned int _height(const Node* p) {
    if (p == 0) {
        return 0;
    }
    return 1 + _max(_height(p->left), _height(p->right));
}

static void _clean(Node* p) {
    if (p != 0) {
        _clean(p->left);
        _clean(p->right);
        free(p);
    }
}

static bool _find(const Node* p, int value) {
    if (p == 0) {
        return false;
    }

    if (p->value == value) {
        return true;
    }

    if (p->value > value) {
        return _find(p->left, value);
    }

    return _find(p->right, value);
}

static void _print(const Node* p, unsigned int level) {
    const unsigned int buffer_size = 255;
    char buffer[buffer_size];

    if (p == 0) {
        snprintf(buffer, buffer_size, "%*s", level+4, "<null>");
        printf("%s\n", buffer);
        return;
    }

    snprintf(buffer, buffer_size, "%*d", level, p->value);
    printf("%s\n", buffer);

    _print(p->left, level+2);
    _print(p->right, level+2);
}

static Node* _findMin(Node* pn) {
    Node* p = pn;
    while (p && p->left) {
        p = p->left;
    }
    return p;
}

static Node* _delete(Node* pn, int value) {
    if (pn) {
        if (pn->value > value) {
            pn->left = _delete(pn->left, value);
        } else if (pn->value < value) {
            pn->right = _delete(pn->right, value);
        } else {
            // found the node to delete
            if (!pn->left && !pn->right) { // no children
                free(pn);
                pn = 0;
            } else if (pn->left && pn->right) { // two children
                Node* p = _findMin(pn->right);
                pn->value = p->value;
                pn->right = _delete(p, p->value);
            } else if (pn->left) { // only left child
                Node* p = pn->left;
                free(pn);
                pn = p;
            } else { // only right child
                Node* p = pn->right;
                free(pn);
                pn = p;
            }
        }
    }

    return pn;
}

void Insert(Tree* tree, int value) {
    Node* pnode = malloc(sizeof(Node));
    pnode->value = value;
    pnode->left = pnode->right = 0;

    if (tree->root == 0) {
        tree->root = pnode;
        return;
    }

    _insert(tree->root, pnode);
}

void Delete(Tree* tree, int value) {
    tree->root = _delete(tree->root, value);
}

void Clean(Tree* tree) {
    _clean(tree->root);
}

void Print(const Tree* tree) {
    printf("\n");
    _print(tree->root, 0);
}

bool Find(const Tree* tree, int value) {
    return _find(tree->root, value);
}

unsigned int Size(const Tree* tree) {
    return _size(tree->root);
}

unsigned int Height(const Tree* tree) {
    return _height(tree->root);
}
