/*************************************************
 * 3.24 斐波那契递归计算到50时，栈空间是否用完？
 * 不会用完
 * 递归调用次数 C(n) = C(n-2) + C(n-1) + 1
 *              C(0) = C(1) = 1
 *************************************************/
#include <stdio.h>
#include <time.h>

unsigned long long fib( unsigned int n )
{
   if( n == 0 || n == 1 )
      return 1 ;
   return fib( n-2 ) + fib( n-1 ) ;
}

int main( int argc, char** argv )
{
   for( int i = 0;i <= 50;i++ )
   {
      time_t start = time( NULL ) ;
      unsigned long long result = fib( i ) ;
      time_t stop = time( NULL ) ;
      printf( "%d: %llu, takes %lds\n", i, result, stop-start ) ;
   }
}
