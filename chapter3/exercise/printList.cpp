/*********************************************
* 3.1 打印单链表的所有元素
*  
*********************************************/
#include "common.h"

int main( int argc, char** argv )
{
    List l = createList() ;
    for( int i = 0;i < 10;i++ )
        insertList( l, i ) ;
    printList( l ) ;
    deleteList( l ) ;
}
