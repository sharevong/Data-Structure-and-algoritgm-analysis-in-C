/********************************************************
 * 4.27 插入1到2n之间的随机n个树构造树
 *      然后执行n^2次先插入后删除的操作
 *      分别测试二叉树 avl树 伸展树的执行时间
 *
 ********************************************************/
#include "binarySearchTree.hpp"
#include "avlTree.hpp"
#include "splayTree.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <memory.h>

#define N 100

// get random int in [ min, max ]
int getRandomInt( int min, int max )
{
   static int inited = false ;
   if( !inited )
   {
      srand( time( NULL ) ) ;
   }
   return min + rand() % ( max - min + 1 ) ;
}

template<typename T>
long long testTreeTime( T t )
{
   // 标识数组，初始化为0，每当数字插入树中标记为1
   // 从树中删除标记为0
   int* arr = (int*)malloc( (2*N+1) * sizeof(int) ) ;
   assert( arr ) ;
   memset( arr, 0, 2*N+1 ) ;
      
   for( int i = 0;i < N;i++ )
   {
      int x ;  // 从1到2n范围随机取n个数插入树中
      do
      {
         x = getRandomInt( 1, 2*N ) ;
      } while( arr[x] == 1 ) ;
      t = insertTree( t, x ) ;
      arr[x] = 1 ;  // 插入后标记为1
   }

   time_t begin = time( NULL ) ;
   for( int i = 0;i < N*N;i++ )
   {
      int x ;  // 执行n^2次随机插入／删除对
      do
      {
         x = getRandomInt( 1, 2*N ) ;
      } while( arr[x] == 1 ) ;
      t = insertTree( t, x ) ;
      arr[x] = 1 ;
      int y ;
      do
      {
         y = getRandomInt( 1, 2*N ) ;
      } while( arr[y] == 0 ) ;
      t = deleteTree( t, y ) ;
      arr[y] = 0 ;
   }
   time_t end = time( NULL ) ;

   makeEmpty( t ) ;
   free( arr ) ;

   return end-begin ;
}

int main( int argc, char** argv )
{
   Tree t = NULL ;
   long long time = testTreeTime( t ) ;
   printf( "binary tree takes %llds\n", time ) ;

   AvlTree at = NULL ;
   time = testTreeTime( at ) ;
   printf( "avl tree takes %llds\n", time ) ;
   
   splayTree st = NULL ;
   time = testTreeTime( st ) ;
   printf( "splay tree takes %llds\n", time ) ;
}
