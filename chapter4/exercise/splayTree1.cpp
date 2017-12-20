/********************************
 * 自底向上伸展树的实现例程
 *
 *
 ********************************/ 
#include "splayTree1.hpp"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stack>

using std::stack ;

void makeEmpty( splayTree1 t )
{
   if( t == NULL )
      return ;
   makeEmpty( t->left ) ;
   makeEmpty( t->right ) ;
}

splayTree1 insertTree( splayTree1 t, int x )
{
   if( t == NULL )
   {
      t = (splayTree1)malloc( sizeof(struct splayNode1) ) ;
      assert( t ) ;
      t->element = x ;
      t->left = t->right = NULL ;
      return t ;
   }
   else
   {
      t = splay( t, x ) ;
      if( t->element > x )
      {
         splayTree1 tmp = (splayTree1)malloc( sizeof(struct splayNode1) ) ;
         assert( tmp ) ;
         tmp->element = x ;
         tmp->left = t->left ;
         tmp->right = t ;
         t->left = NULL ;
         t = tmp ;
      }
      else if( t->element < x )
      {
         splayTree1 tmp = (splayTree1)malloc( sizeof(struct splayNode1) ) ;
         assert( tmp ) ;
         tmp->element = x ;
         tmp->left = t ;
         tmp->right = t->right ;
         t->right = NULL ;
         t = tmp ;
      }
      else
      {
      }
      return t ;
   }
}

splayTree1 findTree( splayTree1 t, int x )
{
   if( t == NULL )
   {
      printf( "Tree is Null\n" ) ;
      return t ;
   }
   t = splay( t, x ) ;
   if( t->element != x )
   {
      printf( "No element %d in tree\n", x ) ;
   }
   return t ;
}

splayTree1 deleteTree( splayTree1 t, int x )
{
   if( t == NULL )
   {
      printf( "Tree is Null\n" ) ;
      return t ;
   }
   t = splay( t, x ) ;
   splayTree1 tmp = t ;
   if( t->element == x )
   {
      if( t->left == NULL )
      {
         t = t->right ;
      }
      else
      {
         t = t->left ;
         t = splay( t, x ) ;
         t->right = tmp->right ;
      }
      free( tmp ) ;
   }
   return t ;
}

void printTree( splayTree1 t, int tab )
{
   if( t == NULL )
      return ;
   for( int i = 0;i < 3*tab;i++ )
      printf( " " ) ;
   printf( "%d\n", t->element ) ;
   printTree( t->left, tab+1 ) ;
   printTree( t->right, tab+1 ) ;
}

splayTree1 splay( splayTree1 t, int x )
{
   stack<splayTree1> s ; // 使用栈存储根节点到目标节点之间的所有节点
   while( t )
   {
      if( x < t->element )
      {
         s.push( t ) ;
         t = t->left ;
      }
      else if( x > t->element )
      {
         s.push( t ) ;
         t = t->right ;
      }
      else
      {
         s.push( t ) ;
         break ;
      }
   }
   splayTree1 son, parent, grand ;
   while( !s.empty() )  // 遍历栈直到栈为空
   {
      son = s.top() ;
      s.pop() ;
      if( s.empty() ) break ;
      parent = s.top() ;
      s.pop() ;
      if( son->element < parent->element )
      {
         parent->left = son ;  // 这一步是必须的，上一次循环可能改变了树，需要重新连接
         if( s.empty() )  // 当父节点为根节点时，只需要执行一次单旋转即可
         {
            parent = singleRotateWithLeft( parent ) ;
            s.push( parent ) ;
         }
         else
         {
            grand = s.top() ;   
            s.pop() ;
            // 一字形结构，从祖父节点开始做两次单旋转
            if( parent->element < grand->element )
            {
               grand = singleRotateWithLeft( grand ) ;
               grand = singleRotateWithLeft( grand ) ;
               s.push( grand ) ;
            }
            // 之字形结构，先父节点后祖父节点做两次方向不同的单旋转
            else
            {
               parent = singleRotateWithLeft( parent ) ;
               grand->right = parent ;   // 父节点更新后，需要重新连接
               grand = singleRotateWithRight( grand ) ;
               s.push( grand ) ;
            }
         }
      }
      else
      {
         parent->right = son ;
         if( s.empty() )
         {
            parent = singleRotateWithRight( parent ) ;
            s.push( parent ) ;
         }
         else
         {
            grand = s.top() ;
            s.pop() ;
            if( parent->element > grand->element )
            {
               grand = singleRotateWithRight( grand ) ;
               grand = singleRotateWithRight( grand ) ;
               s.push( grand ) ;
            }
            else
            {
               parent = singleRotateWithRight( parent ) ;
               grand->left = parent ;
               grand = singleRotateWithLeft( grand ) ;
               s.push( grand ) ;
            }
         }
      }
   }
   return son ;
}

splayTree1 singleRotateWithLeft( splayTree1 k1 )
{
   splayTree1 k2 = k1->left ;
   k1->left = k2->right ;
   k2->right = k1 ;
   return k2 ;
}

splayTree1 singleRotateWithRight( splayTree1 k1 )
{
   splayTree1 k2 = k1->right ;
   k1->right = k2->left ;
   k2->left = k1 ;
   return k2 ;
}
