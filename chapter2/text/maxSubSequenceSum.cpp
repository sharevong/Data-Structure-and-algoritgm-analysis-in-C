/***********************************************************
* 最大子序列和问题：
* 给定整数A1 A2 .... An（可能有负数），找出其中的一个子序列
* 使得该子序列在所有子序列中和最大，假设所有整数都是负数时，
* 最大子序列和为0
*
***********************************************************/
#include <stdio.h>

// 算法1：穷举所有可能的子序列，找出最大的子序列和
// 时间复杂度：O( N^3 )
int getMaxSequenceSum1( int arr[], int size )
{
	int i, j, k ;
	int max = 0 ;
	for( i = 0;i < size;i++ )
		for( j = i;j < size;j++ )
	{
		int tmp = 0 ;
		for( k = i;k <= j;k++ )
			tmp += arr[k] ;
		if( tmp > max )
			max = tmp ;
	}
	return max ;
}

// 算法2：在算法1的基础上去除一个for循环
// 时间复杂度：O( N^2 )
int getMaxSequenceSum2( int arr[], int size )
{
	int i, j ;
	int max = 0 ;
	for( i = 0;i < size;i++ )
	{
		int tmp = 0 ;
		for( j = i;j < size;j++ )
		{
			tmp += arr[j] ;
			if( tmp > max )
				max = tmp ;
		}
	}
	return max ;
}

// 算法3：使用递归，将数组拆分成两个更小的数组，分别计算左边数组的最大子序列和，
// 右边数组的最大子序列和，跨越中间值的最大子序列和，三个值中的最大值为结果
// 时间复杂度：O( NlogN )
int getMaxSequenceSum3( int arr[], int left, int right )
{
	int maxLeftSum = 0 ;  // 左边数组的最大子序列和
	int maxRightSum = 0 ; // 右边数组的最大子序列和
	int maxLeftBorderSum = 0 ; // 跨越中间值时，左半部分的最大值
	int maxRightBorderSum = 0 ;  // 跨越中间值时，右半部分的最大值
	int center = (left+right) / 2 ;

	if( left == right )    // 基准情形
	{
		if( arr[left] > 0 )
			return arr[left] ;
		return 0 ; 
	}

	maxLeftSum = getMaxSequenceSum3( arr, left, center ) ;  // 使用递归计算左右子数组的最大子序列和

	maxRightSum = getMaxSequenceSum3( arr, center+1, right ) ;

	// 计算跨越中间值时的最大子序列和
	// 分别从中间值遍历到左右边界，找出两部分的最大值，再相加
	int tmp = 0 ;
	for( int i = center;i >= left;i-- )  
	{
		tmp += arr[i] ;
		if( tmp > maxLeftBorderSum )
			maxLeftBorderSum = tmp ;
	}
	tmp = 0 ;
	for( int i = center+1;i <= right;i++ )  // i取值为center+1而不是center，防止重复计算
	{
		tmp += arr[i] ;
		if( tmp > maxRightBorderSum )
			maxRightBorderSum = tmp ;
	}
	int maxMiddleSum = maxLeftBorderSum + maxRightBorderSum ;

	int result = maxLeftSum > maxRightSum ? maxLeftSum : maxRightSum ;
	result = result > maxMiddleSum ? result : maxMiddleSum ;
	return result ;	
}

// 算法4：遍历数组中的元素进行累加，
// 当出现负数时，直接截断前面的序列，重新从0开始计算，继续向后遍历，不需要再从头开始遍历
// 时间复杂度：O( N )
int getMaxSequenceSum4( int arr[], int size )
{
	int i ;
	int max = 0 ;
	int tmp = 0 ;
	for( i = 0;i < size;i++ )
	{
		tmp += arr[i] ;
		if( tmp > max )
			max = tmp ;
		else if( tmp < 0 )
			tmp = 0 ;
	}
	return max ;
}

void printArr( int arr[], int size )
{
	for( int i = 0;i < size;i++ )
		printf( "%d ", arr[i] ) ;
}

int main( int argc, char** argv )
{
	int arr[] = { -2, 11, -4, 13, -5, -2 } ; // 最大子序列和为20，对应子序列为11 -4 13
	int size = sizeof(arr) / sizeof(arr[0]) ;
	int result = 0 ;

	printf( "the arr is: " ) ;
	printArr( arr, size ) ;
	printf( "\n" ) ;

	// result = getMaxSequenceSum1( arr, size ) ;
	// result = getMaxSequenceSum2( arr, size ) ;
	// result = getMaxSequenceSum3( arr, 0, size-1 ) ;
	result = getMaxSequenceSum4( arr, size ) ;

	printf( "the max sequence sum is %d\n", result ) ;	
}
