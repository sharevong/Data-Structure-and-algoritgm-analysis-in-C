/***************************************
 * 3.16 删除链表中的重复项
 *
 ***************************************/
#include "common.h"

void rmRepeat( List l )
{
   assert( l ) ;
   Position p = l->next ;
   while( p )
   {
      Position prep = p ;
      Position q = p->next ;
      while( q )
      {
         if( q->no == p->no )
         {
            Position tmp = q ;
            prep->next = q->next ;
            q = q->next ;
            free( tmp ) ;
         }
         else
         {
            prep = prep->next ;
            q = q->next ;
         }
      }
      p = p->next ;
   }
}

int main( int argc, char** argv )
{
   int arr[] = { 4, 8, 2, 1, 4, 7, 2, 5, 5 } ;
   int size = sizeof(arr) / sizeof(arr[0]) ;
   List l = createList() ;
   for( int i = size-1;i >= 0;i-- )
   {
      insertList( l, arr[i] ) ;
   }
   printList( l ) ;
   rmRepeat( l ) ;
   printList( l ) ;
   deleteList( l ) ;
}
