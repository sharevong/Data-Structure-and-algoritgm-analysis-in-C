/****************************************
* 2.12 a. 最小子序列和
* 假设所有数都为正数时，最小子序列和为0
*
****************************************/
#include <stdio.h>

// 与求解最大子序列和原理一致
// 遍历数组不断累加求和，出现正数时，截断前面的序列并置0，然后继续向后遍历
int getMinSeqSum( int arr[], int n )
{
	int sum = 0 ;
	int tmp = 0 ;
	for( int i = 0;i < n;i++ )
	{
		tmp += arr[i] ;
		if( tmp < sum )
			sum = tmp ;
		if( tmp > 0 )
			tmp = 0 ;
	}
	return sum ;
}

void printArr( int arr[], int size )
{
    for( int i = 0;i < size;i++ )
        printf( "%d ", arr[i] ) ;
}

int main( int argc, char** argv )
{
	int arr[] = { -1, -3, 2, -5, 6, -7 } ;
	int n = sizeof(arr) / sizeof(arr[0]) ;
	
	printf( "arr: " ) ;
	printArr( arr, n ) ;
	printf( "\n" ) ;
	
	int minSeqSum = getMinSeqSum( arr, n ) ;
	printf( "the minest sequence sum is %d\n", minSeqSum ) ; 
}
