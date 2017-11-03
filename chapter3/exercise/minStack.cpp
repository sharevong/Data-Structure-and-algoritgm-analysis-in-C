/****************************************
 * 3.22.a 支持push pop findMin的栈
 * 算法：
 *    使用两个栈
 *    一个栈用于保存数据
 *    一个栈用于保存最小值
 ****************************************/
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_STACK_SIZE 1024

struct minStack
{
   int pos1 ;
   int pos2 ;
   int arr1[ MAX_STACK_SIZE ] ;  // 数据栈
   int arr2[ MAX_STACK_SIZE ] ;  // 最小值栈
} ;
typedef struct minStack* MinStack ;

MinStack createMinStack()
{
   MinStack ms = (MinStack)malloc( sizeof( struct minStack ) ) ;
   assert( ms ) ;
   ms->pos1 = -1 ;
   ms->pos2 = -1 ;
   memset( ms->arr1, 0, MAX_STACK_SIZE ) ;
   memset( ms->arr2, 0, MAX_STACK_SIZE ) ;
   return ms ;
}

int isFull( MinStack ms )
{
   assert( ms ) ;
   return ms->pos1 == MAX_STACK_SIZE - 1 ;
}

int isEmpty( MinStack ms )
{
   assert( ms ) ;
   return ms->pos1 == -1 ;
}

// 入栈
void push( MinStack ms, int x )
{
   assert( ms ) ;
   assert( !isFull( ms ) ) ;
   ms->pos1++ ;
   ms->arr1[ms->pos1] = x ;
   // 如果是第一个元素，即也是数据栈当前的最小值，最小值栈入栈
   // 否则与最小值栈栈顶值比较，如果小于等于原最小值，入栈
   // 保证最小值栈栈顶值一直是数据栈中的最小值
   if( ms->pos2 == -1 )
   {
      ms->pos2++ ;
      ms->arr2[ms->pos2] = x ;
   }
   // 判断使用小于等于，因为同样的最小值可能出现多次
   // 可以考虑所有数据相同的情况，
   // push多次可以防止一次pop使得整个最小值栈变空，从而无法获取最小值
   else if( x <= ms->arr2[ms->pos2] )
   {
      ms->pos2++ ;
      ms->arr2[ms->pos2] = x ;
   }
}

// 出栈
int pop( MinStack ms )
{
   assert( ms ) ;
   assert( !isEmpty( ms ) ) ;
   int ret = ms->arr1[ms->pos1] ;
   ms->pos1-- ;
   // 出栈时判断出栈的值是否为最小值，如果是，最小值栈出栈
   if( ret == ms->arr2[ms->pos2] )
   {
      ms->pos2-- ;
   }
   return ret ;
}

int top( MinStack ms )
{
   assert( ms ) ;
   assert( !isEmpty( ms ) ) ;
   return ms->arr1[ms->pos1] ;
}

// 查找最小值，获取最小值栈的栈顶值即可
int findMin( MinStack ms )
{
   assert( ms ) ;
   assert( !isEmpty( ms ) ) ;
   return ms->arr2[ms->pos2] ;
}

void deleteMinStack( MinStack ms )
{
   if( ms )
      free( ms ) ;
}

int main( int argc, char** argv )
{
   MinStack ms = createMinStack() ;
   push( ms, 5 ) ;
   push( ms, 4 ) ;
   push( ms, 1 ) ;
   push( ms, 3 ) ;
   push( ms, 1 ) ;
   printf( "stack min: %d\n", findMin( ms ) ) ;
   for( int i = 0;i < 4;i++ )
   {
      pop( ms ) ;
      printf( "pop %d, min: %d\n", i, findMin( ms ) ) ;
   }

   deleteMinStack( ms ) ;
}
