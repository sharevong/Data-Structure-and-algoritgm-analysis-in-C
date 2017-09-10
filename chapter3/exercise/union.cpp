/**********************************************
* 3.5 给定两个已排序的表L1 L2，计算并集
*
**********************************************/
#include "list.hpp"
#include <stdlib.h>
#include <assert.h>

// 求两个已排序链表的并集
List unionList( List l1, List l2 )
{
    List l = NULL ;
    l = makeEmpty( l ) ;
    Position p1 = l1->next ;
    Position p2 = l2->next ;
    Position p = l ;
    while( p1 && p2 )
    {
        if( p1->element > p2->element )
        {
            insert( p2->element, l, p ) ;    
            p2 = p2->next ;    
            p = p->next ;
        }
        else if( p1->element < p2->element )
        {
            insert( p1->element, l, p ) ;
            p1 = p1->next ;
            p = p->next ;
        }
        else
        {
            insert( p1->element, l, p ) ;
            p = p->next ;
            insert( p2->element, l, p ) ;
            p1 = p1->next ;
            p2 = p2->next ;    
            p = p->next ;
        }
    }
    if( p1 ) p->next = p1 ;
    else if( p2 ) p->next = p2 ;    
    return l ;                
}

int main( int argc, char** argv )
{
    List l1 = NULL ;
    List l2 = NULL ;
    l1 = makeEmpty( l1 ) ;
    l2 = makeEmpty( l2 ) ;
    
    insert( 9, l1, l1 ) ;
    insert( 7, l1, l1 ) ;
    insert( 5, l1, l1 ) ;
    insert( 3, l1, l1 ) ;
    insert( 2, l1, l1 ) ;
    insert( 1, l1, l1 ) ;
    printList( l1 ) ;   // l1: 1 2 3 5 7 9

    insert( 11, l2, l2 ) ;
    insert( 10, l2, l2 ) ;
    insert( 8, l2, l2 ) ;
    insert( 6, l2, l2 ) ;
    insert( 5, l2, l2 ) ;
    insert( 4, l2, l2 ) ;
    insert( 2, l2, l2 ) ;
    printList( l2 ) ;  // l2: 2 4 5 6 8 10 11

    List un = unionList( l1, l2 ) ;
    printList( un ) ;  // un: 1 2 2 3 4 5 5 6 7 8 9 10 11
 
    deleteList( l1 ) ;
    deleteList( l2 ) ;
    deleteList( un ) ;        
}
