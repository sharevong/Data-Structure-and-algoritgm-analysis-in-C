/**********************************
 * 3.17 懒惰删除
 *
 **********************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node
{
   int no ;
   int isDeleted ;
   struct node* next ;
} ;
typedef struct node* Node ;

struct list
{
   Node head ;
   int delNum ;
   int savNum ;
} ;
typedef struct list* List ;

List createList()
{
   List l = (List)malloc( sizeof(struct list) ) ;
   assert( l ) ;
   l->head = (Node)malloc( sizeof(struct node) ) ;
   assert( l->head ) ;
   l->head->no = -1 ;
   l->head->isDeleted = 0 ;
   l->head->next = NULL ;
   l->delNum = 0 ;
   l->savNum = 0 ;
   return l ;
}

void insertList( List l, int number )
{
   assert( l ) ;
   assert( l->head ) ;
   Node n = (Node)malloc( sizeof(struct node) ) ;
   assert( n ) ;
   n->no = number ;
   n->isDeleted = 0 ;
   n->next = l->head->next ;
   l->head->next = n ;
   l->savNum++ ;  
}

void deleteReal( List l )
{
   assert( l ) ;
   assert( l->head ) ;
   Node pre = l->head ;
   Node n = l->head->next ;
   while( n )
   {
      if( n->isDeleted )
      {
         Node tmp = n ;
         pre->next = n->next ;
         n = n->next ;
         free( tmp ) ;
         l->delNum-- ;
      }
      else
      {
         pre = pre->next ;
         n = n->next ;
      }
   }
}

void deleteElement( List l, int number )
{
   assert( l ) ;
   assert( l->head ) ;
   Node n = l->head->next ;
   while( n && n->no != number )
      n = n->next ;
   if( n == NULL )
      return ;
   n->isDeleted = 1 ;
   l->savNum-- ;
   l->delNum++ ;
   if( l->delNum >= l->savNum )
      deleteReal( l ) ;
}

void printList( List l )
{
   assert( l ) ;
   assert( l->head ) ;
   Node n = l->head->next ;
   while( n )
   {
      printf( "%d", n->no ) ;
      if( n->isDeleted )
         printf( "(Del)" ) ;
      printf( " " ) ;
      n = n->next ;
   }
   printf( "\n" ) ;
}

void deleteList( List l )
{
   if( l == NULL )
      return ;
   Node n = l->head ;
   while( n )
   {
      Node tmp = n ;
      n = n->next ;
      free( tmp ) ;
   }
   free( l ) ;
}

int main( int argc, char** argv )
{
   List l = createList() ;
   int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
   int size = sizeof(arr) / sizeof(arr[0]) ;
   for( int i = 0;i < size;i++ )
      insertList( l, arr[i] ) ;
   printList( l ) ;

   for( int i = 0;i < size;i++ )
   {
      deleteElement( l, arr[i] ) ;
      printList( l ) ;
   }
   deleteList( l ) ;
}

