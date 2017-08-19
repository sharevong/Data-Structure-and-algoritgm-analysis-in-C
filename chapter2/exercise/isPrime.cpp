/*********************************************
* 2.13 判断一个数是否是质数
*
*********************************************/
#include <stdio.h>

void checkPrime( unsigned int n )
{
	bool isPrime = true ;
	for( int i = 2;i*i <= n;i++ )
	{
		if( n % i == 0 )
		{
			isPrime = false ;
			break ;
		}
	}
	if( isPrime )
		printf( "%d is a prime\n", n ) ;
	else
		printf( "%d is not a prime\n", n ) ;
}

// 获取一个数二进制位中1的个数
void getbits( unsigned int n )
{
	int count = 0 ;
	unsigned int tmp = n ;
	while( tmp )
	{
		if( tmp & 1 )
			count++ ;
		tmp >>= 1 ;
	}	
	printf( "%d have %d 1s in binary\n", n, count ) ;
}

int main( int argc, char** argv )
{
	unsigned int x1 = 17 ;
	unsigned int x2 = 1989 ;
	checkPrime( x1 ) ;
	getbits( x1 ) ;
	checkPrime( x2 ) ;
	getbits( x2 ) ;
}
