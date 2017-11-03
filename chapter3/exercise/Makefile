Programs=printList printLots swap1 swap2 intersection union addPoly multiPoly \
			compute joseph joseph2 findElement reverseList radixSort adjoinList \
			adjustList rmRepeat lazyDelete balanceSymbol computePostfix infixPostfix postfixInfix twoStack minStack threeStack fibnacci queue deque

all:$(Programs)

%:%.cpp
	g++ -g -O0 -o $@ $^

clean:
	rm -rf $(Programs)
	rm -rf *.dSYM
