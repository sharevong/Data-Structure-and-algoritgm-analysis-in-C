Programs=testBSTree testInsertDelete checkBalance leastNodes testAvlTree insertAvlTreeNonRecursive deleteAvlTree doubleRotateReal testSplayTree testSplayTree1

all:$(Programs)

%:%.cpp binarySearchTree.cpp avlTree.cpp splayTree.cpp splayTree1.cpp
	g++ -g -O0 -o $@ $^

clean:
	rm -rf $(Programs)
	rm -rf *.dSYM
