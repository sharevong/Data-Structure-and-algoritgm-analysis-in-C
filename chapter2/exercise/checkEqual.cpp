/***************************************************
* 2.11 确定在整数A1 < A2 < ... < An中是否存在Ai = i
*
***************************************************/
#include <stdio.h>

// 使用二分查找算法找出值与下标相等的数
// 时间复杂度：O( logN )
int getEqual( int arr[], int n )
{
	int left = 1 ;  // 不计数组中的第0个元素
	int right = n-1 ;
	while( left <= right )
	{
		int mid = (left+right) / 2 ;
		if( arr[mid] > mid )  // 如果中间值大于它的下标，则它右边的数都会大于对应的下标
			right = mid - 1 ;
		else if( arr[mid] < mid )  // 如果中间值小于它的下标，则它左边的数都会小于对应的下标
			left = mid + 1 ;
		else
			return mid ;
	}
	return -1 ;	
}

void printArr( int arr[], int size )
{
    for( int i = 0;i < size;i++ )
        printf( "%d ", arr[i] ) ;
}

int main( int argc, char** argv )
{
	int arr1[] = { 0, 2, 3, 4, 5, 6 } ;
	int n = sizeof(arr1) / sizeof(arr1[0]) ;
	int idx = getEqual( arr1, n ) ;
	printf( "arr1: " ) ;
	printArr( arr1, n ) ;
	printf( "\n" ) ;
	if( idx == -1 )
		printf( "arr1 has no number equal to it's index\n" ) ;
	else
		printf( "arr1[%d] = %d\n", idx, arr1[idx] ) ;

	int arr2[] = { 0, -1, 2, 4, 7, 8 } ;
	n = sizeof(arr2) / sizeof(arr2[0]) ;
    idx = getEqual( arr2, n ) ;
    printf( "arr2: " ) ;
    printArr( arr2, n ) ;      
    printf( "\n" ) ;                   
    if( idx == -1 )                    
        printf( "arr2 has no number equal to it's index\n" ) ;
    else                                    
        printf( "arr2[%d] = %d\n", idx, arr2[idx] ) ;	
}
