/**********************************************
* 使用欧几里德算法求解最大公约数
* 并估计在一定数字范围内两个数互质的概率
*
**********************************************/
#include <stdio.h>

unsigned int gcd( unsigned int m, unsigned int n )
{
	unsigned int rem = 0 ;
	while( n > 0 )  // this is n > 0, not n >= 0
	{
		rem = m % n ;
		m = n ;
		n = rem ;	
	}
	return m ;
}

void relativePrime( unsigned int n )
{
	int prime = 0 ;
	int total = 0 ;
	for( int i = 1;i <= n;i++ )
		for( int j = i+1;j <= n;j++ )
	{
		total++ ;
		if( gcd( i, j ) == 1 )
			prime++ ;	
	}
	printf( "int %d range, two number relative prime chance is %.2f\n",
			n, (double)prime/total ) ;  // 随着n的增大，概率趋向于6/(pi^2)
}

int main( int argc, char** argv )
{
	unsigned int m = 1989 ;
	unsigned int n = 1590 ;
	unsigned int result = gcd( m, n ) ;
	printf( "%d and %d has max greatest common mesure: %d\n", m, n, result ) ;	

	relativePrime( 1000 ) ;	
}
