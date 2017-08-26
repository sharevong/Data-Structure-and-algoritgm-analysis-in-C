/**************************************************
* 3.3 通过调整指针交换单链表中的相邻元素
*
**************************************************/
#include "list.hpp"
#include <stdlib.h>

// prep -> p -> nextp
// prep -> nextp -> p
// 交换p和nextp
void swap1( Position prep, Position p )
{
	Position tmp = p->next ;  // 在更新之前保留p的下一个位置
	prep->next = tmp ;
	p->next = tmp->next ;
	tmp->next = p ;
}

int main( int argc, char** argv )
{
	List l = NULL ;
	l = makeEmpty( l ) ;
	for( int i = 10;i >= 1;i-- )
		insert( i, l, l ) ;
	printList( l ) ;

	Position prep = advance( l ) ;
	Position p = advance( prep ) ;
	swap1( prep, p ) ;

	printList( l ) ;

	deleteList( l ) ;
}
