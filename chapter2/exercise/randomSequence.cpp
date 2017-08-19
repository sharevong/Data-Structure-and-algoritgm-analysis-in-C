/***********************************************
* 2.7 生成前n个自然数的随机序列（值不重复）
*
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

// make a random int in range [min, max)
int getRandomInt( const int min, const int max )
{
	static bool inited = false ;
	if( !inited )
	{
		srand( time(NULL) ) ;
		inited = true ;
	}
	int range = max - min ;
	return rand() % range + min ;
}

void printArr( const int arr[], const int size )
{
    for( int i = 0;i < size;i++ )
        printf( "%d ", arr[i] ) ;
}

// 算法1：生成数组中的每个元素并与前面的值比较，当与前面的值都不相同时插入
// 时间复杂度：O( N^2 * logN )  ?
void makeArr1( int arr[], const int n )
{
	int i, j, tmp ;
	bool success ;
	for( int i = 0;i < n;i++ )
	{
	retry:
		tmp = getRandomInt( 1, n+1 ) ;
		for( j = i-1;j >= 0;j-- )
			if( tmp == arr[j] )
				goto retry ;
		arr[i] = tmp ;			
	}			
}

// 算法2：使用附加数组，每生成一个自然数时，标记该自然数被使用过
// 生成自然数后，检查标记，如果已经被使用过，重新生成，直到生成的自然数未被标记
// 时间复杂度：O( NlogN )  ?
void makeArr2( int arr[], const int n )
{
	int* used = (int*)malloc( n * sizeof(int) ) ;
	memset( used, 0, n * sizeof(int) ) ;  // 这里不能使用 int used[n] = { 0 }
	int i ;
	for( i = 0;i < n;i++ )
	{
		int tmp = getRandomInt( 1, n+1 ) ;
		while( used[tmp] == 1 )
			tmp = getRandomInt( 1, n+1 ) ;
		used[tmp] = 1 ;
		arr[i] = tmp ;
	}
	free( used ) ;
}

// 算法3：首先按顺序给数组赋值，然后随机两两交换
// 时间复杂度：O( N )
void makeArr3( int arr[], const int n )
{
	int i, j, tmp ;
	for( i = 0;i < n;i++ )
		arr[i] = i+1 ;
	for( i = 0;i < n;i++ )
	{
		tmp = arr[i] ;
		j = getRandomInt( 0, n ) ;
		arr[i] = arr[j] ;
		arr[j] = tmp ;
	}	
}

int main( int argc, char** argv )
{
	const int n = 10 ;
	int arr[n] = { 0 } ;

	// makeArr1( arr, n ) ;
	// makeArr2( arr, n ) ;
	makeArr3( arr, n ) ;

	printf( "arr: " ) ;
	printArr( arr, n ) ;
	printf( "\n" ) ;			
}
