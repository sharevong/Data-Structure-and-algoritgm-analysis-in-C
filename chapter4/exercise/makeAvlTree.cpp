/***************************************
 * 4.30 生成具有最少节点/高度为h的avl树
 *      左右子树高度分别为h-1/h-2
 * 4.31 生成高度为h的理想二叉树
 *      左右子树的高度都为h-1
 *
 ***************************************/
#include "avlTree.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define HEIGHT 3

AvlTree makeMinAvlTree( int height, int* element )
{
   AvlTree t = NULL ;
   if( height >= 0 )
   {
      t = (AvlTree)malloc( sizeof(*t) ) ;
      assert( t ) ;
      t->left = makeMinAvlTree( height-1, element ) ;  // 左子树一直递归到叶节点再赋值
      t->element = ++(*element) ;   // element的值不断向上增长
      t->right = makeMinAvlTree( height-2, element ) ;
   }
   return t ;
}

AvlTree makeMaxAvlTree( int height, int* element )
{
   AvlTree t = NULL ;
   if( height >= 0 )
   {
      t = (AvlTree)malloc( sizeof(*t) ) ;
      assert( t ) ;
      t->left = makeMaxAvlTree( height-1, element ) ;
      t->element = ++(*element) ;
      t->right = makeMaxAvlTree( height-1, element ) ;
   }
   return t ;
}

AvlTree minAvlTree( int height )
{
   int lastElement = 0 ;
   return makeMinAvlTree( height, &lastElement ) ;
}

AvlTree maxAvlTree( int height )
{
   int lastElement = 0 ;
   return makeMaxAvlTree( height, &lastElement ) ;
}

int main( int argc, char** argv )
{
   AvlTree t = NULL ;
   t = minAvlTree( HEIGHT ) ;
   printTree1( t, 0 ) ;
   makeEmpty( t ) ;
   
   t = NULL ;
   t = maxAvlTree( HEIGHT ) ;
   printTree1( t, 0 ) ;
   makeEmpty( t ) ;
}
