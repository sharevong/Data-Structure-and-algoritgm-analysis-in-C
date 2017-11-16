Programs=testBSTree testInsertDelete checkBalance leastNodes

all:$(Programs)

%:%.cpp binarySearchTree.cpp
	g++ -g -O0 -o $@ $^

clean:
	rm -rf $(Programs)
	rm -rf *.dSYM
