LinkList_Dir=../text/linkedList

all:printList printLots swap1 swap2

printList:printList.cpp ../text/linkedList/list.cpp
	g++ -g -O0 -o printList -I${LinkList_Dir} $^

printLots:printLots.cpp ../text/linkedList/list.cpp
	g++ -g -O0 -o printLots -I${LinkList_Dir} $^

swap1:swap1.cpp ../text/linkedList/list.cpp
	g++ -g -O0 -o swap1 -I${LinkList_Dir} $^

swap2:swap2.cpp
	g++ -g -O0 -o swap2 $^

clean:
	rm -rf printList
	rm -rf printLots
	rm -rf swap1
	rm -rf swap2
