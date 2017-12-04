/**************************************************
 * 4.19 avl树的非递归插入
 *      使用栈存储从根节点到插入节点的路径
 *      插入完成后，从插入节点向上遍历直到根节点
 *      检查路径上节点的平衡情况
 **************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <stack>
#include "avlTree.hpp"

using std::stack ;

AvlTree insertTreeNonRecursive( AvlTree t, int x )
{
   stack<AvlTree> s ;
   AvlTree root = t ;

   while( true )
   {
      if( t == NULL )  // 找到插入位置
      {
         t = (AvlTree)malloc( sizeof( struct AvlNode ) ) ;
         assert( t ) ;
         t->element = x ;
         t->left = t->right = NULL ;
         t->height = 0 ;
         s.push( t ) ;  // 将插入节点放入栈中，注意插入节点此时未与其父节点连接
         break ;
      }
      else if( x > t->element )
      {
         s.push( t ) ;   // 将插入路径上经过的节点放入栈
         t = t->right ;
      }
      else if( x < t->element )
      {
         s.push( t ) ;
         t = t->left ;
      }
      else   // 已存在元素时，不做插入，直接退出
      {
         return root ;
      }
   }
   
   AvlTree son, father ;
   while( !s.empty() )  // 遍历栈直到栈为空
   {
      son = s.top() ;
      s.pop() ;
      if( s.empty() ) break ;   // 栈为空，说明遍历到根节点，此时son为根节点
      father = s.top() ;
      s.pop() ;
      if( son->element > father->element )
      {
         father->right = son ;  // 连接父子节点，使新插入节点与父节点能连接上
         // 更新父节点的高度，考虑不旋转时的情况
         father->height = max( getHeight( father->left ), getHeight( son ) ) + 1 ;
         if( getHeight( father->right ) - getHeight( father->left ) == 2 )
         {
            // 产生不平衡时检查新插入元素插入位置，插入右儿子的右子树使用右单旋转
            if( x > father->right->element )
               father = singleRotateWithRight( father ) ;
            else
               father = doubleRotateWithRight( father ) ;
         }
      }
      else if( son->element < father->element )
      {
         father->left = son ;
         father->height = max( getHeight( son ), getHeight( father->right ) ) + 1 ;
         if( getHeight( father->left ) - getHeight( father->right ) == 2 )
         {
            if( x < father->left->element )
               father = singleRotateWithLeft( father ) ;
            else
               father = doubleRotateWithRight( father ) ;
         }
      }
      s.push( father ) ;  // 将父节点重新放入栈，作为下一轮循环的子节点
   }

   return son ;
}

int main( int argc, char** argv )
{
   AvlTree t = NULL ;
   int arr[] = { 2, 1, 4, 5, 9, 3, 6, 7 } ;
   int size = sizeof( arr ) / sizeof( arr[0] ) ;
   for( int i = 0;i < size;i++ )
   {
      t = insertTreeNonRecursive( t, arr[i] ) ;
   }
   printTree1( t, 0 ) ;
   makeEmpty( t ) ;
}
