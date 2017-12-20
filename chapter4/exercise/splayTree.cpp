/********************************
 * 自顶向下伸展树的实现例程
 *
 *
 ********************************/ 
#include "splayTree.hpp"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void makeEmpty( splayTree t )
{
   if( t == NULL )
      return ;
   makeEmpty( t->left ) ;
   makeEmpty( t->right ) ;
}

splayTree insertTree( splayTree t, int x )
{
   if( t == NULL )
   {
      t = (splayTree)malloc( sizeof(struct splayNode) ) ;
      assert( t ) ;
      t->element = x ;
      t->left = t->right = NULL ;
      return t ;
   }
   else
   {
      t = splay( t, x ) ;  // 伸展树伸展，使最接近或等于x的值为根
      if( x < t->element ) 
      {
         // 如果根节点的值小于x，则新建节点作为根。
         // 将原根及其左右子树放入新根的左右子树中
         splayTree tmp = (splayTree)malloc( sizeof(struct splayNode) ) ;
         assert( tmp ) ;
         tmp->element = x ;  
         tmp->left = t->left ;
         tmp->right = t ;
         t->left = NULL ;
         t = tmp ;
         return t ;
      }
      else if( x > t->element )
      {
         splayTree tmp = (splayTree)malloc( sizeof(struct splayNode) ) ;
         assert( tmp ) ;
         tmp->element = x ;
         tmp->left = t ;
         tmp->right = t->right ;
         t->right = NULL ;
         t = tmp ;
         return t ;
      }
      else
      {
         // 已存在插入值时，不做操作
         return t ;
      }
   }
}

splayTree findTree( splayTree t, int x )
{
   if( t == NULL )
   {
      printf( "Tree is Null\n" ) ;
      return t ;
   }
   t = splay( t, x ) ;  // 查找值时将最接近或等于x的值作为根
   if( t->element != x )
   {
      printf( "No element %d in tree\n", x ) ;
   }
   return t ;
}

splayTree deleteTree( splayTree t, int x )
{
   if( t == NULL )
   {
      printf( "Tree is Null\n" ) ;
      return t ;
   }
   t = splay( t, x ) ;
   if( t->element == x ) // 当存在值时
   {
      splayTree tmp = t ;
      if( t->left == NULL )
      {
         t = t->right ;
      }
      else
      {
         t = t->left ;
         t = splay( t, x ) ;     // 这一步和下一步的顺序不能调换，伸展前t->right不一定为空
         t->right = tmp->right ; // 由于t为原根的左子树，所有值都小于x
                                 // 伸展后的t的值为最接近且小于x的值，它的右子树为空，
                                 // 可以安全赋值t->right
      }
      free( tmp ) ;
   }
   else
   {
      printf( "No element %d in tree\n", x ) ;
   }
   return t ;
}

void printTree( splayTree t, int tab )
{
   if( t == NULL )
      return ;
   for( int i = 0;i < 3*tab;i++ )
      printf( " " ) ;
   printf( "%d\n", t->element ) ;
   printTree( t->left, tab+1 ) ;
   printTree( t->right, tab+1 ) ;
}

splayTree splay( splayTree t, int x )
{
   struct splayNode head ;  // 头节点的两个指针分别作为L R，将树分为三部分 L T R
   head.left = head.right = NULL ;  // L 除t树以外的左边节点 R 除t树以为的右边节点
   splayTree leftMax = &head ;
   splayTree rightMin = &head ;
   
   while( t->element != x )  // 从根节点开始遍历直到叶节点或找到值为止
   {
      if( x < t->element )  // 每遍历一个节点时，依据与x的大小关系分别加入L R
      {
         if( t->left == NULL )
            break ;
         if( x < t->left->element )  // 当出现一字形时，需要单旋转更新节点
            t = singleRotateWithLeft( t ) ;
         rightMin->left = t ;  // 第一次执行时 header.left指向R初始位置
         rightMin = t ;      // 将节点放入R中，并且新加入的节点是R中最小的
         t = t->left ;   // 继续向下遍历
      }
      else
      {
         if( t->right == NULL )
            break ;
         if( x > t->right->element )
            t = singleRotateWithRight( t ) ;
         leftMax->right = t ;  // 第一次执行时 header.right指向L初始位置
         leftMax = t ;
         t = t->right ;
      }
   }
   leftMax->right = t->left ;  // 遍历完成后 L T R连接成一棵以T为根的树
   rightMin->left = t->right ;
   t->left = head.right ;
   t->right = head.left ;
   return t ;
}

splayTree singleRotateWithLeft( splayTree k1 )
{
   splayTree k2 = k1->left ;
   k1->left = k2->right ;
   k2->right = k1 ;
   return k2 ;
}

splayTree singleRotateWithRight( splayTree k1 )
{
   splayTree k2 = k1->right ;
   k1->right = k2->left ;
   k2->left = k1 ;
   return k2 ;
}
