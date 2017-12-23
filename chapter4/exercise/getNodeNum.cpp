/***********************************
 * 4.28 获取树中节点个树 树叶个树
 *      满节点个树
 *
 ***********************************/
#include "binarySearchTree.hpp"
#include <stdio.h>

int getNodeNum( Tree t )
{
   if( t == NULL )
      return 0 ;
   return 1 + getNodeNum( t->left ) +
              getNodeNum( t->right ) ;
}

int getLeavesNum( Tree t )
{
   if( t == NULL )
      return 0 ;
   return (t->left == NULL && t->right == NULL) +
          getLeavesNum( t->left ) +
          getLeavesNum( t->right ) ;
}

int getFullNum( Tree t )
{
   if( t == NULL )
      return 0 ;
   return (t->left && t->right) +
          getFullNum( t->left ) +
          getFullNum( t->right ) ;
}

int main( int argc, char** argv )
{
   int arr[] = { 3, 1, 4, 6, 9, 2, 5, 7 } ;
   int size = sizeof(arr) / sizeof(arr[0]) ;
   Tree t = NULL ;
   for( int i = 0;i < size;i++ )
   {
      t = insertTree( t, arr[i] ) ;
   }
   printTree( t ) ;
   printf( "\n" ) ; 
   printf( "node num: %d\n", getNodeNum( t ) ) ;
   printf( "leaves num: %d\n", getLeavesNum( t ) ) ;
   printf( "full node num: %d\n", getFullNum( t ) ) ;
}
