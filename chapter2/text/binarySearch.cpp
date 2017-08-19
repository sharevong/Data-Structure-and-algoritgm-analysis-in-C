/***********************************************
* 使用对分查找在有序数组中查找元素
*
***********************************************/
#include <stdio.h>

// 假设数组有序且按增序排列，返回元素在数组中的下标
// 元素在数组中不存在时，返回-1
int binarySearch( int arr[], int size, int x )
{
	int left = 0 ;
	int right = size-1 ;
	while( left <= right )
	{
		int mid = (left+right) / 2 ;
		if( x > arr[mid] )
			left = mid+1 ;
		else if( x < arr[mid] )
			right = mid-1 ;
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
	int arr[] = { 1, 3, 7, 9, 11, 17, 29, 67 } ;
	int size = sizeof(arr) / sizeof(arr[0]) ;

	printf( "the arr is: " ) ;
	printArr( arr, size ) ;
	printf( "\n" ) ;

	int x1 = 11 ;
	int idx1 = binarySearch( arr, size, x1 ) ;
	printf( "the number %d is arr[%d]\n", x1, idx1 ) ;
	int x2 = 14 ;
	int idx2 = binarySearch( arr, size, x2 ) ;
	printf( "the number %d is arr[%d]\n", x2, idx2 ) ;		
}
