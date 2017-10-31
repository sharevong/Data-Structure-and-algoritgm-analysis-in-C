/***********************************************
 * 3.21 使用一个数组实现两个栈
 * 两个栈: 一个栈从数组头向后增长
 *         一个栈从数组尾向前增长
 *         当两个栈的栈顶相遇时，数组被填满
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#define MAX_STACK_SIZE 10

struct twoStack
{
   int pos1 ;   // 第一个栈的栈顶，初始值为-1
   int pos2 ;   // 第二个栈的栈顶，初始值为arrSize
   int arr[ 2 * MAX_STACK_SIZE ] ;
} ;
typedef struct twoStack* TwoStack ;

TwoStack createTwoStack()
{
   TwoStack ts = (TwoStack)malloc( sizeof( struct twoStack ) ) ;
   assert( ts ) ;
   ts->pos1 = -1 ;
   ts->pos2 = 2 * MAX_STACK_SIZE ;
   memset( ts->arr, 0, 2 * MAX_STACK_SIZE ) ;
   return ts ;
}

int isFull( TwoStack ts )
{
   // 当两个栈的栈顶相邻时，数组被填满，不能再执行push
   return ts->pos1 == ts->pos2 - 1 ;
}

// 第一个栈的push: 栈顶加1再赋值
void push1( TwoStack ts, int x )
{
   assert( !isFull( ts ) ) ;
   ts->pos1++ ;
   ts->arr[ts->pos1] = x ;
}

// 第二个栈的push: 栈顶减1再赋值
void push2( TwoStack ts, int x )
{
   assert( !isFull( ts ) ) ;
   ts->pos2-- ;
   ts->arr[ts->pos2] = x ;
}

int isEmpty1( TwoStack ts )
{
   return ts->pos1 == -1 ;
}

int isEmpty2( TwoStack ts )
{
   return ts->pos2 == 2 * MAX_STACK_SIZE ;
}

int pop1( TwoStack ts )
{
   assert( !isEmpty1( ts ) ) ;
   int ret = ts->arr[ts->pos1] ;
   ts->pos1-- ;
   return ret ;
}

int pop2( TwoStack ts )
{
   assert( !isEmpty2( ts ) ) ;
   int ret = ts->arr[ts->pos2] ;
   ts->pos2++ ;
   return ret ;
}

int top1( TwoStack ts )
{
   assert( !isEmpty1( ts ) ) ;
   return ts->arr[ts->pos1] ;
}

int top2( TwoStack ts )
{
   assert( !isEmpty2( ts ) ) ;
   return ts->arr[ts->pos2] ;
}

void deleteTwoStack( TwoStack ts )
{
   if( ts )
   {
      free( ts ) ;
   }
}

int main( int argc, char** argv )
{
   TwoStack ts = createTwoStack() ;
   int i ;
   for( i = 0;i < 10;i++ )
   {
      push1( ts, i ) ;
   }
   for( i = 100;i > 90;i-- )
   {
      push2( ts, i ) ;
   }
   printf( "full? %d\n", isFull( ts ) ) ;
   printf( "Stack1: " ) ;
   for( i = 0;i < 10;i++ )
   {
      printf( "%d ", pop1( ts ) ) ;
   }
   printf( "\n" ) ;
   printf( "Stack2: " ) ;
   for( i = 0;i < 10;i++ )
   {
      printf( "%d ", pop2( ts ) ) ;
   }
   printf( "\n" ) ;
   deleteTwoStack( ts ) ;
}
