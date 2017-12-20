/***********************************
 * 4.20 avl树的非懒惰删除
 *      删除后检查平衡情况并调整
 *
 ***********************************/
#include "avlTree.hpp"
#include <stdlib.h>
#include <stdio.h>

AvlTree deleteTreeReal( AvlTree t, int x )
{
   if( t == NULL )   // 未找到删除元素，直接返回
   {
      printf( "Element %d not found in tree.\n", x ) ;
      return t ;
   }
   else if( x > t->element )  // 递归删除
   {
      t->right = deleteTreeReal( t->right, x ) ;
   }
   else if( x < t->element )
   {
      t->left = deleteTreeReal( t->left, x ) ;
   }
   else
   {
      if( t->left && t->right )  // 有左右儿子时选择右子树的最小值替换
      {
         int min = findMin( t->right ) ;
         t->element = min ;
         t->right = deleteTreeReal( t->right, min ) ;
      }
      else  // 只有一个儿子或叶子节点时，删除节点，更新为儿子节点或NULL
      {
         AvlTree tmp = t ;
         if( t->left == NULL )
            t = t->right ;
         else if( t->right == NULL )
            t = t->left ;
         free( tmp ) ;
      }
   }

   // 删除完成后，检查平衡，注意t可能为NULL(删除叶子节点时出现)
   if( t != NULL )
   {
      // 考虑不做旋转的情况，需要更新节点高度(旋转操作中会更新节点高度)
      t->height = max( getHeight( t->left ), getHeight( t->right ) ) + 1 ;
      // 左子树高于右子树
      if( getHeight( t->left ) - getHeight( t->right ) == 2 )
      {
         // 检查左子树的左儿子是否高于右儿子，需要加等号
         // 左子树的左儿子高时，左单旋转，其他情形类似处理
         if( getHeight( t->left->left ) >= getHeight( t->left->right ) )
            t = singleRotateWithLeft( t ) ;
         else
            t = doubleRotateWithLeft( t ) ;
      }
      else if( getHeight( t->right ) - getHeight( t->left ) == 2 )
      {
         if( getHeight( t->right->right ) >= getHeight( t->right->left ) )
            t = singleRotateWithRight( t ) ;
         else
            t = doubleRotateWithRight( t ) ;
      }
   }
   return t ;
}

int main( int argc, char** argv )
{
   AvlTree t = NULL ;
   /*
   int arr[] = { 2, 1, 4, 5, 9, 3, 6, 7 } ;
   int size = sizeof( arr ) / sizeof( arr[0] ) ;
   for( int i = 0;i < size;i++ )
   {
      t = insertTree( t, arr[i] ) ;
   }
   printTree1( t, 0 ) ;

   t = deleteTreeReal( t, 5 ) ;
   printTree1( t, 0 ) ;

   t = deleteTreeReal( t, 2 ) ;
   printTree1( t, 0 ) ;
   */

   int arr[] = { 4, 3, 6, 2, 5, 7, 9 } ;
   int size = sizeof( arr ) / sizeof( arr[0] ) ;
   for( int i = 0;i < size;i++ )
   {
      t = insertTree( t, arr[i] ) ;
   }
   printTree1( t, 0 ) ;

   t = deleteTreeReal( t, 2 ) ;
   printTree1( t, 0 ) ;

   makeEmpty( t ) ;
}
