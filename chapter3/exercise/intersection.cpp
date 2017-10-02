/**********************************************
* 3.4 给定两个已排序的表L1 L2，计算交集
*     ? core dump in deleteList
**********************************************/
#include "common.h"

// 求两个已排序链表的交集
List intersection( List l1, List l2 )
{
    List l = createList() ;
    Position p = l ;
    Position p1 = l1->next ;
    Position p2 = l2->next ;
    while( p1 && p2 )
    {
        if( p1->no > p2->no )
        {
            insertPosition( l, p, p2->no ) ;    
            p2 = p2->next ;    
        }
        else if( p1->no < p2->no )
        {
            insertPosition( l, p, p1->no ) ;
            p1 = p1->next ;
        }
        else
        {
            insertPosition( l, p, p1->no ) ;
            p1 = p1->next ;
            p2 = p2->next ;    
        }
        p = p->next ;
    }
    while( p1 )
    {
       insertPosition( l, p, p1->no ) ;
       p1 = p1->next ;
       p = p->next ;
    }
    while( p2 )
    {
       insertPosition( l, p, p2->no ) ;
       p2 = p2->next ;
       p = p->next ;
    }   
    return l ;   
}

int main( int argc, char** argv )
{
    List l1 = createList() ;
    List l2 = createList() ;
    
    int arr1[] = { 9, 7, 5, 3, 2, 1 } ;
    int size1 = sizeof(arr1) / sizeof(arr1[0]) ;
    for( int i = 0;i < size1;i++ )
       insertList( l1, arr1[i] ) ;
    printList( l1 ) ;   // l1: 1 2 3 5 7 9

    int arr2[] = { 11, 10, 8, 6, 5, 4, 2 } ;
    int size2 = sizeof(arr2) / sizeof(arr2[0]) ;
    for( int i = 0;i < size2;i++ )
       insertList( l2, arr2[i] ) ;
    printList( l2 ) ;  // l2: 2 4 5 6 8 10 11

    List inter = intersection( l1, l2 ) ;
    printList( inter ) ;   // inter: 1 2 3 4 5 6 7 8 9 10 11                

    deleteList( l1 ) ;
    deleteList( l2 ) ;
    deleteList( inter ) ;
}
