/********************************************
 * common head file for exercise
 *
 ********************************************/
#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node
{
   int no ;
   struct Node* next ;
} ;
typedef struct Node* Position ;
typedef struct Node* List ;

List createList()
{
   List l = (List)malloc( sizeof(struct Node) ) ;
   assert( l ) ;
   l->no = -1 ;
   l->next = NULL ;
   return l ;   
}

void insertList( List l, int number )
{
   assert( l ) ;
   Position first = l->next ;
   Position p = (Position)malloc( sizeof(struct Node) ) ;
   assert( p ) ;
   p->no = number ;
   p->next = first ;
   l->next = p ;
}

void insertPosition( List l, Position p, int number )
{
   assert( l ) ;
   assert( p ) ;
   Position tmp = (Position)malloc( sizeof(struct Node) ) ;
   assert( tmp ) ;
   tmp->no = number ;
   tmp->next = p->next ;
   p->next = tmp ;
}

void printList( List l )
{
   assert( l ) ;
   Position p = l->next ;
   while( p )
   {
      printf( "%d ", p->no ) ;
      p = p->next ;
   }
   printf( "\n" ) ;
}

void deleteList( List l )
{
   if( l == NULL ) return ;
   Position p = l->next ;
   while( p )
   {
      Position tmp = p ;
      p = p->next ;
      free( tmp ) ;
   }
   free( l ) ;
}

#endif
