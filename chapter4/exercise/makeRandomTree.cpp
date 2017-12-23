/*********************************
 * 4.29 生成随机N节点二叉树
 *
 *********************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "binarySearchTree.hpp"

#define N 10

int getRandomInt( int min, int max )
{
   static int inited = 0 ;
   if( !inited )
   {
      srand( time(NULL) ) ;
      inited = 1 ;
   }
   return min + rand() % ( max - min + 1 ) ; 
}

Tree makeRandomTree( int m, int n )
{
   Tree t = NULL ;
   if( m <= n )
   {
      t = (Tree)malloc( sizeof(struct node) ) ;
      assert( t ) ;
      int x = getRandomInt( m, n ) ;
      t->element = x ;
      t->left = makeRandomTree( m, x-1 ) ;
      t->right = makeRandomTree( x+1, n ) ;
   }
   return t ;
}

int main( int argc, char** argv )
{
   Tree t = NULL ;
   t = makeRandomTree( 1, N ) ;
   printTree( t ) ;
   printf( "\n" ) ;
   makeEmpty( t ) ;
}
