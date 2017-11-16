/********************************************************
 * 4.13 分别使用三种方式执行二叉查找树的删除
 *      删除同时具有左右子树的节点
 *      检查哪种方式给出最好的平衡
 * a。用左子树最大值x代替，然后在左子树递归删除x
 * b。交替用左子树最大值和右子树最小值代替，递归删除
 * c。随机用左子树最大值和右子树最小值代替，递归删除
 * b给出最好平衡，a时间最短
 ********************************************************/
#include "binarySearchTree.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <memory.h>

#define N 100
typedef Tree (*funcType)( Tree, int ) ;

static int flag = 0 ;

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

// 使用左子树的最大值代替
Tree deleteTree1( Tree t, int x )
{
   if( t == NULL )
      return t ;
   if( x > t->element )
   {
      t->right = deleteTree1( t->right, x ) ;
   }
   else if( x < t->element )
   {
      t->left = deleteTree1( t->left, x ) ;
   }
   else
   {
      if( t->left && t->right )
      {
         int tmp = findMax( t->left ) ;
         t->left = deleteTree1( t->left, tmp ) ;
         t->element = tmp ;
      }
      else
      {
         Tree tmp = t ;
         if( t->left == NULL )
            t = t->right ;
         else if( t->right == NULL )
            t = t->left ;
         free( tmp ) ;
      }
   }
   return t ;
}

// 交替使用左子树最大值和右子树最小值代替
Tree deleteTree2( Tree t, int x )
{
   if( t == NULL )
      return t ;
   if( x > t->element )
   {
      t->right = deleteTree2( t->right, x ) ;
   }
   else if( x < t->element )
   {
      t->left = deleteTree2( t->left, x ) ;
   }
   else
   {
      if( t->left && t->right )
      {
         if( flag )
         {
            int tmp = findMax( t->left ) ;
            t->left = deleteTree2( t->left, tmp ) ;
            t->element = tmp ;
            flag = 0 ;
         }
         else
         {
            int tmp = findMin( t->right ) ;
            t->right = deleteTree2( t->right, tmp ) ;
            t->element = tmp ;
            flag = 1 ;
         }
      }
      else
      {
         Tree tmp = t ;
         if( t->left == NULL )
            t = t->right ;
         else if( t->right == NULL )
            t = t->left ;
         free( tmp ) ;
      }
   }
   return t ;
}

// 随机使用左子树最大值和右子树最小值代替
Tree deleteTree3( Tree t, int x )
{
   if( t == NULL )
      return t ;
   if( x > t->element )
   {
      t->right = deleteTree2( t->right, x ) ;
   }
   else if( x < t->element )
   {
      t->left = deleteTree2( t->left, x ) ;
   }
   else
   {
      if( t->left && t->right )
      {
         int s = getRandomInt( 0, 1 ) ;
         if( s == 0 )
         {
            int tmp = findMax( t->left ) ;
            t->left = deleteTree2( t->left, tmp ) ;
            t->element = tmp ;
            flag = 0 ;
         }
         else
         {
            int tmp = findMin( t->right ) ;
            t->right = deleteTree2( t->right, tmp ) ;
            t->element = tmp ;
            flag = 1 ;
         }
      }
      else
      {
         Tree tmp = t ;
         if( t->left == NULL )
            t = t->right ;
         else if( t->right == NULL )
            t = t->left ;
         free( tmp ) ;
      }
   }
   return t ;
}

void checkBalance( funcType func_delete )
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
      t = (*func_delete)( t, y ) ;
      arr[y] = 0 ;
   }

   // 操作完成后，获取根节点左子树右子树的高度
   printf( "left height: %d, right height: %d\n", 
           height(t->left), height(t->right) ) ;

   // printTree1( t, 0 ) ;

   makeEmpty( t ) ;
   free( arr ) ;
}

int main( int argc, char** argv )
{
   time_t begin, end ;

   printf( "delete use left max:\n" ) ;
   begin = time( NULL ) ;
   checkBalance( &deleteTree1 ) ;
   end = time( NULL ) ;
   printf( "takes %lds\n", end-begin ) ;
   
   printf( "delete use left max and right min alternately:\n" ) ;
   begin = time( NULL ) ;
   checkBalance( &deleteTree2 ) ;
   end = time( NULL ) ;
   printf( "takes %lds\n", end-begin ) ;

   printf( "delete use left max and right min randomly:\n" ) ;
   begin = time( NULL ) ;
   checkBalance( &deleteTree3 ) ;
   end = time( NULL ) ;
   printf( "takes %lds\n", end-begin ) ;
}
