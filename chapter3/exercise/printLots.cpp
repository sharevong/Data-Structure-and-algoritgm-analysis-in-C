/*********************************************
* 3.2 给定两个包含升序整数的链表L P
* 假设L的元素为 1 2 3 4 5 6 7 8 9 10
*     P的元素为 1 3 4 6
* 则打印L中的P中元素指定位置的元素，
* 即打印L中的第 1 3 4 6个元素
*
*********************************************/
#include "list.hpp"
#include <stdio.h>
#include <stdlib.h>

void printLots( List l, List p )
{
    Position pos1 = l ;
    Position pos2 = p->next ;  
    int count = 0 ;
    while( pos1 )
    {
        pos1 = pos1->next ;
        if( pos2 && ++count == pos2->element )
        {
            printf( "%d ", pos1->element ) ;
            pos2 = pos2->next ;
        }
    }
    printf( "\n" ) ;
}

int main( int argc, char** argv )
{
    List l = NULL ;
    l = makeEmpty( l ) ;
    Position pos = l ;
    for( int i = 10;i >= 1;i-- )  // 头插法，按降序插入，链表才会是升序
        insert( i, l, pos ) ;
    printList( l ) ;
    
    List p = NULL ;
    p = makeEmpty( p ) ;
    pos = p ;
    insert( 19, p, pos ) ;   // 该值超过了链表L的长度，不会打印任何值
    insert( 6, p, pos ) ;
    insert( 4, p, pos ) ;
    insert( 3, p, pos ) ;
    insert( 1, p, pos ) ;
    printList( p ) ;

    printLots( l, p ) ;    

    deleteList( l ) ;
    deleteList( p ) ;            
}
