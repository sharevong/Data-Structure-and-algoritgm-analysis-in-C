/***************************************
* 使用递归作幂运算
*
***************************************/
#include <stdio.h>

// 假设计算结果不超过long long表示范围
long long pow( long long x, unsigned int n )
{
	if( n == 0 )
		return 1 ;
	// if( n == 1 ) 可以省略
	// 	return x ;
	if( n % 2 == 0 )
		return pow( x*x, n/2 ) ;
	else
		return pow( x*x, n/2 ) * x ;	
}

int main( int argc, char** argv )
{
	long long x = 3 ;
	unsigned int n = 3 ;
	long long result = pow( x, n ) ;
	printf( "%lld ^ %d = %lld\n", x, n, result ) ;	
	// long long输出需要使用lld%，使用ld%会输出错误的值	
}
