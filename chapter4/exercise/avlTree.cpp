/*************************************
 * avl树的实现例程
 *
 *
 *************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avlTree.hpp"

void makeEmpty( AvlTree t )
{
   if( t == NULL )
      return ;
   makeEmpty( t->left ) ;
   makeEmpty( t->right ) ;
   free( t ) ;
}

int max( int a, int b )
{
   return a > b ? a : b ;
}

AvlTree singleRotateWithLeft( AvlTree k1 )
{
   AvlTree k2 = k1->left ;
   k1->left = k2->right ;
   k2->right = k1 ;
   k1->height = max( getHeight(k1->left), getHeight(k1->right) ) + 1 ;
   k2->height = max( getHeight(k2->left), k1->height ) + 1 ;
   return k2 ;
}

AvlTree singleRotateWithRight( AvlTree k1 )
{
   AvlTree k2 = k1->right ;
   k1->right = k2->left ;
   k2->left = k1 ;
   k1->height = max( getHeight(k1->left), getHeight(k1->right) ) + 1 ;
   k2->height = max( k1->height, getHeight(k2->right) ) + 1 ;
   return k2 ;
}

AvlTree doubleRotateWithLeft( AvlTree k1 )
{
   k1->left = singleRotateWithRight( k1->left ) ;
   return singleRotateWithLeft( k1 ) ;
}

AvlTree doubleRotateWithRight( AvlTree k1 )
{
   k1->right = singleRotateWithLeft( k1->right ) ;
   return singleRotateWithRight( k1 ) ;
}

AvlTree insertTree( AvlTree t, int x )
{
   if( t == NULL )
   {
      t = (AvlTree)malloc( sizeof(struct AvlNode) ) ;
      assert( t ) ;
      t->left = t->right = NULL ;
      t->element = x ;
      t->height = 0 ;
   }
   else if( x > t->element )
   {
      t->right = insertTree( t->right, x ) ;
      if( getHeight(t->right) - getHeight(t->left) == 2 )
      {
         if( x > t->right->element )
            t = singleRotateWithRight( t ) ;
         else
            t = doubleRotateWithRight( t ) ;
      }
   }
   else if( x < t->element )
   {
      t->left = insertTree( t->left, x ) ;
      if( getHeight(t->left) - getHeight(t->right) == 2 )
      {
         if( x < t->left->element )
            t = singleRotateWithLeft( t ) ;
         else
            t = doubleRotateWithLeft( t ) ;
      }
   }
   t->height = max( getHeight(t->left), getHeight(t->right) ) + 1 ;
   return t ;
}

AvlTree deleteTree( AvlTree t, int x )
{
   // ToDo: delete
   return t ;
}

Position findTree( AvlTree t, int x )
{
   if( t == NULL )
   {
      return NULL ;
   }
   else if( x > t->element )
   {
      return findTree( t->right, x ) ;
   }
   else if( x < t->element )
   {
      return findTree( t->left, x ) ;
   }
   else
   {
      return t ;
   }
}

int findMin( AvlTree t )
{
   assert( t ) ;
   while( t->left )
      t = t->left ;
   return t->element ;
}

int findMax( AvlTree t )
{
   assert( t ) ;
   while( t->right )
      t = t->right ;
   return t->element ;
}

int getHeight( AvlTree t )
{
   if( t == NULL )
      return -1 ;
   return t->height ;
}

int getElement( Position p )
{
   assert( p ) ;
   return p->element ;
}

void printTree1( AvlTree t, int tab )
{
   if( t == NULL )
      return ;
   for( int i = 0;i < 3*tab;i++ )
      printf( " " ) ;
   printf( "%d\n", t->element ) ;
   printTree1( t->left, tab+1 ) ;
   printTree1( t->right, tab+1 ) ;
}

void printTree( AvlTree t )
{
   printTree1( t, 0 ) ;
}
