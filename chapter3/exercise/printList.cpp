/*********************************************
* 3.1 打印单链表的所有元素
* 
*********************************************/
#include "list.hpp"
#include <stdlib.h>

/**************************************** 
该方法在链表实现文件中已存在
void printList( List l )
{
    if( l == NULL ) return ;
    Position p = l->next ;
    while( p )
    {
        printf( "%d ", p->element ) ;
        p = p->next ;
    }
    printf( "\n" ) ;
}
****************************************/

int main( int argc, char** argv )
{
	List l = NULL ;       // l需要初始化为NULL,否则在makeEmpty时会core
	l = makeEmpty( l ) ;  // 需要获取返回值，否则l会保持为NULL
	Position p = l ;
	for( int i = 0;i < 10;i++ )
		insert( i, l, p ) ;
	printList( l ) ;
	deleteList( l ) ;
}
