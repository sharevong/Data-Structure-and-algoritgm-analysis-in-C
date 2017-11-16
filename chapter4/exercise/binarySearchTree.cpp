/***************************************
 * 二叉查找树的实现例程
 * 
 ***************************************/
#include "binarySearchTree.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 插入数据
Tree insertTree( Tree t, int x )
{
   if( t == NULL )
   {
      t = (Tree)malloc( sizeof(struct node) ) ;
      assert( t ) ;
      t->element = x ;
      t->left = t->right = NULL ;
   }
   else if( x > t->element )
   {
      t->right = insertTree( t->right, x ) ;
   }
   else if( x < t->element )
   {
      t->left = insertTree( t->left, x ) ;
   }
   return t ;
}

// 最小值
int findMin( Tree t )
{
   assert( t ) ;
   while( t->left )
      t = t->left ;
   return t->element ;
}

// 最大值
int findMax( Tree t )
{
   assert( t ) ;
   if( t->right == NULL )
      return t->element ;
   return findMax( t->right ) ;
}

// 删除数据
Tree deleteTree( Tree t, int x )
{
   if( t == NULL )
   {
      printf( "element %d not found\n", x ) ;
      return t ;
   }
   else if( x > t->element )
   {
      t->right = deleteTree( t->right, x ) ;
   }
   else if( x < t->element )
   {
      t->left = deleteTree( t->left, x ) ;
   }
   else
   {
      if( t->left && t->right ) // 删除有左右子树的节点时
      {
         int tmp = findMin( t->right ) ;  // 取右子树的最小值作为新值
         t->right = deleteTree( t->right, tmp ) ; // 再递归删除右子树的最小值
         t->element = tmp ;
      }
      else // 删除只有左子树或右子树的节点或者删除无子树的节点
      {
         Node tmp = t ;
         if( t->left == NULL )  // 将节点设置为左子树或右子树
            t = t->right ;
         else if( t->right == NULL )
            t = t->left ;
         free( tmp ) ;
      }
   }
   return t ;
}

// 从小到大的顺序打印树
void printTree( Tree t )
{
   if( t != NULL )
   {
      printTree( t->left ) ;
      printf( "%d ", t->element ) ;
      printTree( t->right ) ;
   }
}

// 删除树
void makeEmpty( Tree t )
{
   if( t != NULL )
   {
      makeEmpty( t->left ) ;
      makeEmpty( t->right ) ;
      free( t ) ;
   }
}
