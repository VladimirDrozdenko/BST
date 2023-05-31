#include <assert.h>
#include <memory.h>

#include "bst.h"


void testInsert() {
    Tree tree;
    memset(&tree, 0, sizeof(tree));

    Insert(&tree, 10);
    assert(Size(&tree) == 1);
    assert(Height(&tree) == 1);

    Insert(&tree, 10);
    assert(Size(&tree) == 1);
    assert(Height(&tree) == 1);

    Insert(&tree, 11);
    assert(Size(&tree) == 2);
    assert(Height(&tree) == 2);

    Insert(&tree, 8);
    assert(Size(&tree) == 3);
    assert(Height(&tree) == 2);

    Insert(&tree, 9);
    assert(Size(&tree) == 4);
    assert(Height(&tree) == 3);

    Print(&tree);

    Delete(&tree, 10);

    Print(&tree);

    Clean(&tree);
}


int main() {
    testInsert();

}