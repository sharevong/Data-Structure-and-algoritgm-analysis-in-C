/***********************************************************
 * 3.23 使用数组实现三个栈
 * 算法：
 *   第一个栈从数组头部向尾部增长
 *   第二个栈从数组尾部向头部增长
 *   第三个栈从数组中间位置向尾部增长
 *   当入栈发生冲突时（如第一个栈已增长到数组中间位置时）
 *   移动第三个栈使第三个栈中的中间元素位于第一个栈和
 *   第三个栈之间的中间位置
 *   A->    B->   <-C
 *
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#define MAX_STACK_SIZE 3

struct threeStack
{
   int topOfStack1 ;   // 第一个栈的栈顶 -1
   int topOfStack2 ;   // 第二栈栈的栈顶 3 * MAX_STACK_SIZE
   int topOfStack3 ;   // 第三个栈的栈顶 MAX_STACK_SIZE - 1
   int bottomOfStack3 ;  // 第三个栈的栈底 MAX_STACK_SIZE 
                         // 使用栈底和栈顶标记第三个栈的范围，方便移动
   int arr[ 3 * MAX_STACK_SIZE ] ;
} ;
typedef struct threeStack* ThreeStack ;

ThreeStack createThreeStack()
{
   ThreeStack ts = (ThreeStack)malloc( sizeof( struct threeStack ) ) ;
   assert( ts ) ;
   ts->topOfStack1 = -1 ;
   ts->topOfStack2 = 3 * MAX_STACK_SIZE ;
   ts->topOfStack3 = MAX_STACK_SIZE - 1 ;
   ts->bottomOfStack3 = MAX_STACK_SIZE ;
   memset( ts->arr, 0, 3 * MAX_STACK_SIZE ) ;
   return ts ;
}

int isEmpty1( ThreeStack ts )
{
   assert( ts ) ;
   return ts->topOfStack1 == -1 ;
}

int isEmpty2( ThreeStack ts )
{
   assert( ts ) ;
   return ts->topOfStack2 == 3 * MAX_STACK_SIZE - 1 ;
}

// 第三个栈为空时，栈顶在栈底前一个位置
int isEmpty3( ThreeStack ts )
{
   assert( ts ) ;
   return ts->topOfStack3 == ts->bottomOfStack3 - 1 ;
}

// 判断数组是否被填满，push时检查
int isFull( ThreeStack ts )
{
   assert( ts ) ;
   if( isEmpty3( ts ) )
   {
      // 第三个栈为空时，检查第一个栈的栈顶是否与第二个栈的栈顶相邻
      return ts->topOfStack1 == ts->topOfStack2 - 1 ;
   }
   else
   {
      // 第三个栈不为空时，检查第一个栈的栈顶与第三个栈的栈底相邻且
      // 第二个栈的栈顶与第三个栈的栈顶相邻
      return ( ts->topOfStack1 == ts->bottomOfStack3 - 1 ) &&
             ( ts->topOfStack2 == ts->topOfStack3 + 1 ) ;
   }
}

// 移动第三个栈，使第三个栈的中间元素位于第一个栈和第二个栈的中间位置
void move( ThreeStack ts )
{
   // 第三个栈的中间元素位置
   int centerOfStack3 = ( ts->bottomOfStack3 + ts->topOfStack3 ) / 2 ;
   // 第一个栈和第二个栈之间的中间位置
   int centerOfStack1_2 = ( ts->topOfStack1 + ts->topOfStack2 ) / 2 ;

   if( centerOfStack3 > centerOfStack1_2 )
   {
      // 向左移动时从栈底开始移动直到栈顶，移动距离为两个中间位置之差
      for( int i = ts->bottomOfStack3;i <= ts->topOfStack3;i++ )
      {
         ts->arr[ i - ( centerOfStack3 - centerOfStack1_2 ) ] 
            = ts->arr[i] ;
      }
      ts->bottomOfStack3 -= ( centerOfStack3 - centerOfStack1_2 ) ;
      ts->topOfStack3 -= ( centerOfStack3 - centerOfStack1_2 ) ;
   }
   else if( centerOfStack3 < centerOfStack1_2 )
   {
      // 向右移动时从栈顶开始移动直到栈底
      for( int i = ts->topOfStack3;i >= ts->bottomOfStack3;i-- )
      {
         ts->arr[ i + ( centerOfStack1_2 - centerOfStack3 ) ] 
            = ts->arr[i] ;
      }
      ts->bottomOfStack3 += ( centerOfStack1_2 - centerOfStack3 ) ;
      ts->topOfStack3 += ( centerOfStack1_2 - centerOfStack3 ) ;
   }
}

// 第一个栈入栈
void push1( ThreeStack ts, int x )
{
   assert( ts ) ;
   assert( !isFull( ts ) ) ;

   ts->topOfStack1++ ;
   // 更新第一个栈的栈顶后检查是否与第三个栈的栈底发生冲突
   // 发生冲突时移动第三个栈
   if( ts->topOfStack1 == ts->bottomOfStack3 )
   {
      move( ts ) ;
   }
   ts->arr[ ts->topOfStack1 ] = x ;
}

// 第三个栈入栈
void push3( ThreeStack ts, int x )
{
   assert( ts ) ;
   assert( !isFull( ts ) ) ;

   // 检查如果入栈（栈顶加1）是否会与第二个栈发生冲突
   // 发生冲突时移动第三个栈（不能直接更新栈顶，可能移动）
   if( ts->topOfStack3 + 1 == ts->topOfStack2 )
   {
      move( ts ) ;
   }
   ts->topOfStack3++ ;
   ts->arr[ ts->topOfStack3 ] = x ;
}

// 第二个栈入栈
void push2( ThreeStack ts, int x )
{
   assert( ts ) ;
   assert( !isFull( ts ) ) ;

   ts->topOfStack2-- ;
   // 更新第二个栈的栈顶后检查是否与第三个栈的栈顶发生冲突
   // 发生冲突时移动第三个栈
   if( ts->topOfStack2 == ts->topOfStack3 )
   {
      move( ts ) ;
   }
   ts->arr[ ts->topOfStack2 ] = x ;
}

int pop1( ThreeStack ts )
{
   assert( ts ) ;
   assert( !isEmpty1( ts ) ) ;
   int ret = ts->arr[ ts->topOfStack1 ] ;
   ts->topOfStack1-- ;
   return ret ;
}

int pop2( ThreeStack ts )
{
   assert( ts ) ;
   assert( !isEmpty2( ts ) ) ;
   int ret = ts->arr[ ts->topOfStack2 ] ;
   ts->topOfStack2++ ;
   return ret ;
}

int pop3( ThreeStack ts )
{
   assert( ts ) ;
   assert( !isEmpty3( ts ) ) ;
   int ret = ts->arr[ ts->topOfStack3 ] ;
   ts->topOfStack3-- ;
   return ret ;
}

int top1( ThreeStack ts )
{
   assert( ts ) ;
   assert( !isEmpty1( ts ) ) ;
   return ts->arr[ ts->topOfStack1 ] ;
}

int top2( ThreeStack ts )
{
   assert( ts ) ;
   assert( !isEmpty2( ts ) ) ;
   return ts->arr[ ts->topOfStack2 ] ;
}

int top3( ThreeStack ts )
{
   assert( ts ) ;
   assert( !isEmpty3( ts ) ) ;
   return ts->arr[ ts->topOfStack3 ] ;
}

void printThreeStack( ThreeStack ts )
{
   if( !ts )
      return ;
   printf( "Stack1: " ) ;
   for( int i = 0;i <= ts->topOfStack1;i++ )
   {
      printf( "%d ", ts->arr[i] ) ;
   }
   printf( "\n" ) ;
   printf( "Stack3: " ) ;
   for( int i = ts->bottomOfStack3;i <= ts->topOfStack3;i++ )
   {
      printf( "%d ", ts->arr[i] ) ;
   }
   printf( "\n" ) ;
   printf( "Stack2: " ) ;
   for( int i = ts->topOfStack2;i < 3 * MAX_STACK_SIZE;i++ )
   {
      printf( "%d ", ts->arr[i] ) ;
   }
   printf( "\n" ) ;
}

void deleteThreeStack( ThreeStack ts )
{
   if( ts )
      free( ts ) ;
}

int main( int argc, char** argv )
{
   ThreeStack ts = createThreeStack() ;
   int a[] = { 1, 2, 3, 4 } ;
   int b[] = { 5, 6 } ;
   int c[] = { 7, 8, 9 } ;
   for( int i = 0;i < sizeof(a)/sizeof(a[0]);i++ )
      push1( ts, a[i] ) ;
   for( int i = 0;i < sizeof(b)/sizeof(b[0]);i++ )
      push3( ts, b[i] ) ;
   for( int i = 0;i < sizeof(c)/sizeof(c[0]);i++ )
      push2( ts, c[i] ) ;
   printThreeStack( ts ) ;
   deleteThreeStack( ts ) ;
}
