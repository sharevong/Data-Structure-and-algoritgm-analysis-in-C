/******************************************
* 2.16 不使用递归求幂
*
******************************************/
#include <stdio.h>

// 算法：3^7 = 3^(4 + 2 + 1) = 3^4 * 3^2 * 3^1
// 7的二进制表示111 最左边的1乘以3(3^1) 中间的1乘以9(3^2) 最右边的1乘以27(3^4)
// 因此，随着i不断从低到高，乘以的值是x的值不断平方产生的值
int pow( unsigned int x, unsigned int n )
{	
	int ret = 1 ;
	while( n )
	{
		if( n & 1 )  // 如果在该位上不是1，不需要作乘法
			ret *= x ;  // 实际是 ret = ret * ( 1 * x ) 
		x *= x ;  // 每右移一位，x作一次平方操作（2进制）
		n >>= 1 ;	
	}
	return ret ;	
}

int main( int argc, char** argv )
{
	unsigned int x = 3 ;
	unsigned int n = 7 ;
	printf( "%d ^ %d = %d\n", x, n, pow(x, n) ) ;
}
