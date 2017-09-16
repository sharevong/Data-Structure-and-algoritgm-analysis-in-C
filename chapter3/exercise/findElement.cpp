/*********************************************
* 3.11 查找单链表特定元素
*  
*********************************************/
#include "list.hpp"
#include <stdlib.h>
#include <stdio.h>

// 查找链表中是否包含某个元素
// 不能使用递归查找（链表非常大时会产生很多临时栈）
bool findElement( List l, int x )
{
    bool found = false ;
    if( l == NULL ) return false ;
    Position p = l->next ;
    while( p )
    {
        if( p->element == x )
        {
            found = true ;
            break ;
        }
        p = p->next ;
    }
    return found ;
}

int main( int argc, char** argv )
{
    List l = NULL ;       // l需要初始化为NULL,否则在makeEmpty时会core
    l = makeEmpty( l ) ;  // 需要获取返回值，否则l会保持为NULL
    Position p = l ;
    for( int i = 0;i < 10;i++ )
        insert( i, l, p ) ;
    printList( l ) ;

    printf( "is 5 in list: %d\n", findElement( l, 5 ) ) ;
    printf( "is -2 in list: %d\n", findElement( l, -2 ) ) ;
    
    deleteList( l ) ;
}
