/*********************************************
 * 3.15 自调整表的链表实现 
 *      自调整表：插入在表头进行
 *                查询时查询项移动到表头
 *********************************************/
#include "common.h"

Position findElement( List l, int element )
{
   assert( l ) ;
   Position pre = l ;
   Position p = l->next ;
   while( p && p->no != element )
   {
      pre = pre->next ;
      p = p->next ;
   }
   if( p )
   {
      pre->next = p->next ;
      p->next = l->next ;
      l->next = p ;
      return p ;
   }
   else
   {
      printf( "can't find %d in list\n", element ) ;
      return NULL ;
   }
}

int main( int argc, char** argv )
{
   int arr[] = { 4, 8, 1, 7, 2, 5 } ;
   int size = sizeof(arr) / sizeof(arr[0]) ;
   List l = createList() ;
   for( int i = size-1;i >= 0;i-- )
   {
      insertList( l, arr[i] ) ;
   }
   printList( l ) ;
   findElement( l, 7 ) ;
   printList( l ) ;
   findElement( l, 7 ) ;
   printList( l ) ;
   findElement( l, 11 ) ;
   deleteList( l ) ;
}
