CC = clang++ -std=c++11

# choose one of three tree flavors
TREE_FLAVOR = -DTEST_BST
#TREE_FLAVOR = -DTEST_AVL
#TREE_FLAVOR = -DTEST_SPLAY

DEBUG_FLAG = -DMAIN_ECHO #-DDEBUG_ECHO

SRC = main.cpp

all: test_me test_bst test_avl test_splay

test_me: $(SRC)
	$(CC) -g $(DEBUG_FLAG) -DTEST_INTERACTIVE $(TREE_FLAVOR) -o test_me main.cpp

test_bst: $(SRC)
	$(CC) -g $(DEBUG_FLAG) -DTEST_COMPLEXITY -DTEST_BST -o test_bst main.cpp

test_avl: $(SRC)
	$(CC) -g $(DEBUG_FLAG) -DTEST_COMPLEXITY -DTEST_AVL -o test_avl main.cpp

test_splay: $(SRC)
	$(CC) -g $(DEBUG_FLAG) -DTEST_COMPLEXITY -DTEST_SPLAY -o test_splay main.cpp

clean:
	rm -f test_me test_bst test_avl test_splay

