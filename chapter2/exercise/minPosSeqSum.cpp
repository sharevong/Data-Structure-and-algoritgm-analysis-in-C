/*******************************************
* 2.12.b 最小正子序列和
* 
*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 算法1：枚举所有可能的子序列，找出最小的正子序列和
// 时间复杂度：O( N^2 )
int getMinPosSeqSum1( int arr[], int n )
{
	int sum = 0 ;
	int tmp = 0 ;
	for( int i = 0;i < n;i++ )
	{
		tmp = 0 ;
		for( int j = i;j < n;j++ )
		{
			tmp += arr[j] ;
			if( (sum == 0 && tmp > sum) ||
				(tmp < sum && tmp > 0) )
				sum = tmp ;
		}
	}
	return sum ;
}

/* 算法2：分别求出a0到a0 a1 ... an的子序列和，再加上0值
*  产生最小正子序列和的值是其中的两个最接近的值之差
*  将这些值排序后，从0值开始向后检查相邻的元素是否能相减（即两个序列是否能相减产生新序列）
*  找出相减能产生的最小值
*  eg: 序列  4 -1  5 -2 -1  2  6 -2 
*子序列和 0  4  3  8  6  5  7 13 11 
*    下标-1  0  1  2  3  4  5  6  7
*  排序后 0  3  4  5  6  7  8 11 13  (使用快排提高效率)  
*    下标-1  1  0  4  3  5  2  7  6
*  0 3能够相减，相减产生的子序列为 4 -1 
*  3 4不能相减，因为3的子序列为4 -1，4的子序列为4
*  通过检查下标来判断是否能够相减，0的下标-1 3的下标1
*  时间复杂度：O( NlogN )
*/
typedef struct item
{
	int sum ;  // 子序列和
	int idx ;  // 产生子序列和对应的下标 a[0] .. a[idx]
} item ;

/***************************************************************
* 快速排序：
* 以数组中的第一个元素作为基准，分别从后向前和从前向后遍历数组，
* 将小于该元素的值移动到左边，大于该元素的值移动到右边，直到两
* 个遍历相遇，然后将该元素填入相遇位置，再递归作左右部分的排序
* 直到子数组中只剩下一个元素left == right
*
***************************************************************/
void quickSortItems( item* items, int left, int right )
{
	if( left < right )   // 这个判断用于终止递归
	{
		item tmp ;
		int i = left, j = right ; // 使用i j分别从前向后 从后向前遍历
		tmp = items[i] ;  // 保存第一个元素的值
		while( i < j )  // 遍历直到i j相遇
		{
			while( i < j && items[j].sum >= tmp.sum ) // 从后向前遍历直到找到一个较小的值或者找不到
				j-- ;
			if( i < j ) // 判断是否找到符合条件的值
				items[i++] = items[j] ;  // 找到后赋值给第一个元素，i向前推进一个元素
			while( i < j && items[i].sum <= tmp.sum )  // 原理同上
				i++ ;
			if( i < j ) 
				items[j--] = items[i] ;
		}
		items[i] = tmp ;  // 退出循环时i == j，将第一个元素插入该位置，以该位置为边界将数组分为两部分
						  // 左边部分的值都小于该元素，右边部分的值都大于该元素
		quickSortItems( items, left, i-1 ) ;  // 递归处理左右部分
		quickSortItems( items, i+1, right ) ;
	}	
}

int getMinPosSeqSum2( int arr[], int n )
{
	item* items = (item*)malloc( (n+1) * sizeof(item) ) ; // 保存n个子序列和以及一个0值
	items[0].sum = 0 ;
	items[0].idx = -1 ;

	int tmp = 0 ;
	for( int i = 0;i < n;i++ )
	{
		tmp += arr[i] ;
		items[i+1].sum = tmp ;  // 保存每个子序列的和及下标
		items[i+1].idx = i ;		
	}
	
	quickSortItems( items, 0, n ) ;  // 排序

	int sum = 0 ;
	for( int i = 0;i < n;i++ )
	{
		if( items[i].sum < 0 )
			continue ;

		if( sum == 0 )   // 赋给sum一个初始的正值
			sum = items[i+1].sum - items[i].sum ;  

		if( items[i+1].idx > items[i].idx &&  // 当相邻子序列和能够相减，且差值小于sum并大于0时，更新sum值
            items[i+1].sum - items[i].sum < sum &&
			items[i+1].sum - items[i].sum > 0 )
			sum = items[i+1].sum - items[i].sum ;	
	}
		
	free( items ) ;
	return sum ;
}

void printArr( int arr[], int size )
{
    for( int i = 0;i < size;i++ )
        printf( "%d ", arr[i] ) ;
}

int main( int argc, char** argv )
{
	int arr[] = { 4, -1, 6, -2, -1, 3, 6, -2 } ;
	int n = sizeof(arr) / sizeof(arr[0]) ;
	printf( "arr: " ) ;
	printArr( arr, n ) ;
	printf( "\n" ) ;

	// int result = getMinPosSeqSum1( arr, n ) ;
	int result = getMinPosSeqSum2( arr, n ) ;	

	printf( "the minest postitive sequence sum is %d\n", result ) ;		
}
