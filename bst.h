#ifndef __BST_H__
#define __BST_H__

#include <stdbool.h>

typedef struct __node {
    int value;
    struct __node* left;
    struct __node* right;
} Node;


typedef struct {
    Node* root;
} Tree;


void Insert(Tree* tree, int value);
void Delete(Tree* tree, int value);
void Clean(Tree* tree);

void Print(const Tree* tree);
bool Find(const Tree* tree, int value);
unsigned int Size(const Tree* tree);
unsigned int Height(const Tree* tree);

#endif //__BST_H__
