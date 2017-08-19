/*******************************************
* 2.12.c 浮点数序列求解最大子序列乘积
*
*******************************************/
#include <stdio.h>
#include <stdlib.h>

/* 动态规划
* 假设以元素a[i]结尾的序列中最大子序列乘积为max[i]，最小子序列乘积为min[i]（考虑负负得正需要保存最小值）
* 状态转移方程
* max[i] = arr[0]  i == 0
*		   MAX( arr[i], max[i-1]*arr[i], min[i-1]*arr[i] )
* min[i] = arr[0]  i == 0
*          MIN( arr[i], max[i-1]*arr[i], min[i-1]*arr[i] ) 
* 计算出以a[i]结尾的最大子序列乘积后，更新结果
*/
double MAX( double d1, double d2, double d3 )
{
	double ret = d1 > d2 ? d1 : d2 ;
	return ret > d3 ? ret : d3 ;
}

double MIN( double d1, double d2, double d3 )
{
	double ret = d1 < d2 ? d1 : d2 ;
	return ret < d3 ? ret : d3 ;
}

double getMaxSeqPro( double arr[], int n )
{
	double ret = 0.0 ;
	 // 可以不使用数组，只保留上一轮产生的最大子序列乘积 最小子序列乘积即可
	double* max = (double*)malloc( n * sizeof(double) ) ;  
	double* min = (double*)malloc( n * sizeof(double) ) ;
	for( int i = 0;i < n;i++ )
	{
		if( i == 0 )
			max[i] = min[i] = arr[i] ;
		else
		{
			max[i] = MAX( arr[i], max[i-1]*arr[i], min[i-1]*arr[i] ) ;
			min[i] = MIN( arr[i], max[i-1]*arr[i], min[i-1]*arr[i] ) ;
		}
		if( max[i] > ret )
			ret = max[i] ;				
	}
	free( max ) ;
	free( min ) ;
	return ret ;
}

void printArr( double arr[], int size )
{
    for( int i = 0;i < size;i++ )
        printf( "%.2f ", arr[i] ) ;
}

int main( int argc, char** argv )
{
	double arr[] = { -2.5, 4, 0, 3, 0.5, 8, -1 } ;
	int n = sizeof(arr) / sizeof(arr[0]) ;
	printf( "arr: " ) ;
	printArr( arr, n ) ;
	printf( "\n" ) ;

	double result = getMaxSeqPro( arr, n ) ;
	printf( "max sequence product is %.2f\n", result ) ;	
}
