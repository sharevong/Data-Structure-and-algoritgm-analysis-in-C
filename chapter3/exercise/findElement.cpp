/*********************************************
* 3.11 查找单链表特定元素
*  
*********************************************/
#include "common.h"

// 查找链表中是否包含某个元素
// 不能使用递归查找（链表非常大时会产生很多临时栈）
bool findElement( List l, int x )
{
    bool found = false ;
    if( l == NULL ) return false ;
    Position p = l->next ;
    while( p )
    {
        if( p->no == x )
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
    List l = createList() ;
    for( int i = 0;i < 10;i++ )
        insertList( l, i ) ;
    printList( l ) ;

    printf( "is 5 in list: %d\n", findElement( l, 5 ) ) ;
    printf( "is -2 in list: %d\n", findElement( l, -2 ) ) ;
    
    deleteList( l ) ;
}
