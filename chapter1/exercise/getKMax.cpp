/******************************************************
* in an arr of n number, get the kth max number in arr 
* 
******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <climits>

// get random int in [min, max)
int getRandomInt( int min, int max )
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

// generate arr with n random int
void generateArr( int** arr, int n )
{
	for( int i = 0;i < n;i++ )
	{
		// (*arr)[i] = getRandomInt( 0, 100 ) ;
		(*arr)[i] = getRandomInt( 0, INT_MAX ) ;		
	}	
}

// print arr
void printArr( int arr[], int n )
{
	for( int i = 0;i < n;i++ )
	{
		printf( "%d ", arr[i] ) ;		
	}
	printf( "\n" ) ;
}

int getKthMax( int arr[], int n, int k )
{
	int i, j ;
	for( i = 0;i < n;i++ )
	{
		if( i == k ) break ;
		int max = i ;    // store index in max
		for( j = i+1;j < n;j++ )
		{
			if( arr[j] > arr[max] )
			{
				max = j ;  // update max with new index
			}
		}
		if( max != i )
		{
			int temp = arr[i] ;
			arr[i] = arr[max] ;
			arr[max] = temp ;
		}	
	}
	return arr[k-1] ;
}

int main( int argc, char** argv )
{	
	// seconds takes: 0 0 0 0 14 1812 
	int num[] = { 10, 100, 1000, 10000, 100000, 1000000 } ;
	int size = sizeof(num) / sizeof(num[0]) ;
	int i ;
	time_t begin, end ;
	for( i = 0;i < size;i++ )
	{
		int n = num[i] ;
		int k = n/2 ;
		int* arr = 	(int*)malloc( n * sizeof(int) ) ;
		generateArr( &arr, n ) ;
		// printArr( arr, n ) ;
		time( &begin ) ;
		int result = getKthMax( arr, n, k ) ;
		time( &end ) ;
		double diff = difftime( end, begin ) ;
		printf( "the %dth max number in arr is %d\n", k, result ) ;
		printf( "get the number takes %.2f seconds\n", diff ) ;
		free( arr ) ;														
	}				
}
