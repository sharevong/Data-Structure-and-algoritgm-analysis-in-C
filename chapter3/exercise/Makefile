LinkList_Dir=../text/linkedList

all:printList printLots swap1 swap2 intersection union addPoly multiPoly \
	compute

printList:printList.cpp ../text/linkedList/list.cpp
	g++ -g -O0 -o printList -I${LinkList_Dir} $^

printLots:printLots.cpp ../text/linkedList/list.cpp
	g++ -g -O0 -o printLots -I${LinkList_Dir} $^

swap1:swap1.cpp ../text/linkedList/list.cpp
	g++ -g -O0 -o swap1 -I${LinkList_Dir} $^

swap2:swap2.cpp
	g++ -g -O0 -o swap2 $^

intersection:intersection.cpp ../text/linkedList/list.cpp
	g++ -g -O0 -o intersection -I${LinkList_Dir} $^

union:union.cpp ../text/linkedList/list.cpp 
	g++ -g -O0 -o union -I${LinkList_Dir} $^

addPoly:addPoly.cpp
	g++ -g -O0 -o addPoly $^

multiPoly:multiPoly.cpp
	g++ -g -O0 -o multiPoly $^

compute:compute.cpp
	g++ -g -O0 -o compute $^

clean:
	rm -rf printList
	rm -rf printLots
	rm -rf swap1
	rm -rf swap2
	rm -rf intersection
	rm -rf union
	rm -rf addPoly
	rm -rf multiPoly
	rm -rf compute
