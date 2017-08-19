/******************************************
* 2.14 素数筛法计算整数N内的所有素数
*
******************************************/
#include <stdio.h>
#include <stdlib.h>

// 素数筛法 
// 打印一个素数i，然后将i 2i 3i ....清除
// 时间复杂度：O( NloglogN )
void printPrime( unsigned int n )
{
	int* arr = (int*)malloc( (n+1) * sizeof(int) ) ;
	for( int i = 0;i <=n;i++ )
		arr[i] = i ;
	for( int i = 2;i <=n;i++ )
	{
		if( arr[i] != 0 )
			printf( "%d ", arr[i] ) ;
		for( int j = 1;j*i <= n;j++ )
		{
			if( arr[j*i] != 0 )  // 判断是否已经被置为0，避免重复置0
				arr[j*i] = 0 ;				
		}
	}
	printf( "\n" ) ;
	free( arr ) ;
}

int main( int argc, char** argv )
{
	unsigned int n = 100 ;
	printPrime( n ) ;
}
