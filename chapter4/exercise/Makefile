Programs=testBSTree testInsertDelete checkBalance leastNodes testAvlTree insertAvlTreeNonRecursive

all:$(Programs)

%:%.cpp binarySearchTree.cpp avlTree.cpp
	g++ -g -O0 -o $@ $^

clean:
	rm -rf $(Programs)
	rm -rf *.dSYM
