/********************************************************
 * 4.12 插入1到2n之间的随机n个树构造二叉查找树
 *      然后执行n^2次先插入后删除的操作，检查树的平衡性
 *
 ********************************************************/
#include "binarySearchTree.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <memory.h>

#define N 10

int max( int a, int b )
{
   return a > b ? a : b ;
}

// 获取树的高度
int height( Tree t )
{
   if( t == NULL )
      return -1 ;
   else if( t->left == NULL && t->right == NULL )
      return 0 ;
   else
      return max( height(t->left), height(t->right) ) + 1 ;
}

// 打印树
void printTree1( Tree t, int tab )
{
   if( t == NULL )
      return ;
   for( int i = 0;i < tab*3;i++ )
      printf( " " ) ;
   printf( "%d\n", t->element ) ;
   printTree1( t->left, tab+1 ) ;
   printTree1( t->right, tab+1 ) ;
}

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

int main( int argc, char** argv )
{
   // 标识数组，初始化为0，每当数字插入树中标记为1
   // 从树中删除标记为0
   int* arr = (int*)malloc( (2*N+1) * sizeof(int) ) ;
   assert( arr ) ;
   memset( arr, 0, 2*N+1 ) ;

   Tree t = NULL ;
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

   // 操作完成后，获取根节点左子树右子树的高度
   printf( "left height: %d, right height: %d\n", 
           height(t->left), height(t->right) ) ;

   printTree1( t, 0 ) ;

   makeEmpty( t ) ;
   free( arr ) ;
}
