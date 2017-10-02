/*********************************************
* 3.2 给定两个包含升序整数的链表L P
* 假设L的元素为 1 2 3 4 5 6 7 8 9 10
*     P的元素为 1 3 4 6
* 则打印L中的P中元素指定位置的元素，
* 即打印L中的第 1 3 4 6个元素
*
*********************************************/
#include "common.h"

void printLots( List l, List p )
{
    Position pos1 = l ;
    Position pos2 = p->next ;  
    int count = 0 ;
    while( pos1 )
    {
        pos1 = pos1->next ;
        if( pos2 && ++count == pos2->no )
        {
            printf( "%d ", pos1->no ) ;
            pos2 = pos2->next ;
        }
    }
    printf( "\n" ) ;
}

int main( int argc, char** argv )
{
    List l = createList() ;
    for( int i = 10;i >= 1;i-- )
        insertList( l, i ) ;
    printList( l ) ;
    
    List p = createList() ;
    int arr[] = { 19, 6, 4, 3, 1 } ;
    int size = sizeof(arr) / sizeof(arr[0]) ;
    for( int i = 0;i < size;i++ )
       insertList( p, arr[i] ) ;
    printList( p ) ;

    printLots( l, p ) ;    

    deleteList( l ) ;
    deleteList( p ) ;            
}
