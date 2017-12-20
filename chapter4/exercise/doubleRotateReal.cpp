/*************************************************
 * 4.22 执行双旋转的函数，效率超过执行两个单旋转
 *
 *************************************************/
#include "avlTree.hpp"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/*
        k1                      k3
       /  \                    / \
      k2   a    ----->        k2  k1
     / \                     / \  / \
    b   k3                  b   c d  a
       /  \
      c    d 
*/
AvlTree doubleRotateWithLeft1( AvlTree k1 )
{
   AvlTree k2 = k1->left ;
   AvlTree k3 = k2->right ;
   k2->right = k3->left ;
   k1->left = k3->right ;
   k3->left = k2 ;
   k3->right = k1 ;
   k2->height = max( getHeight(k2->left), getHeight(k2->right) ) + 1 ;
   k1->height = max( getHeight(k1->left), getHeight(k1->right) ) + 1 ;
   k3->height = max( getHeight(k1), getHeight(k2) ) + 1 ;
   return k3 ;
}

/*
       k1                               k3
      /  \                             /  \
     a    k2           ----->         k1  k2
         /  \                        / \  / \
        k3   b                      a  c  d  b
       / \
      c   d
*/
AvlTree doubleRotateWithRight1( AvlTree k1 )
{
   AvlTree k2 = k1->right ;
   AvlTree k3 = k2->left ;
   k1->right = k3->left ;
   k2->left = k3->right ;
   k3->left = k1 ;
   k3->right = k2 ;
   k1->height = max( getHeight(k1->left), getHeight(k1->right) ) + 1 ;
   k2->height = max( getHeight(k2->left), getHeight(k2->right) ) + 1 ;
   k3->height = max( getHeight(k1), getHeight(k2) ) + 1 ;
   return k3 ;
}

AvlTree insertTree1( AvlTree t, int x )
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
            t = doubleRotateWithRight1( t ) ;
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
            t = doubleRotateWithLeft1( t ) ;
      }
   }
   t->height = max( getHeight(t->left), getHeight(t->right) ) + 1 ;
   return t ;
}

int main( int argc, char** argv )
{
   AvlTree t = NULL ;
   int arr[] = { 2, 1, 4, 5, 9, 3, 6, 7 } ;
   int size = sizeof( arr ) / sizeof( arr[0] ) ;
   for( int i = 0;i < size;i++ )
   {
      t = insertTree1( t, arr[i] ) ;
   }
   printTree1( t, 0 ) ;
   makeEmpty( t ) ;
}
