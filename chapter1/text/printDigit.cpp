/*************************************************
* print out a unsigned int number with recursive
* 递归的四条重要法则：
* 1. 基准情形：必须具有无需递归就能解出的基准情形
* 2. 不断推进：每一次递归向基准情形推进
* 3. 设计法则：假设所有递归都能运行
* 4. 合成效益法则：不做重复性工作
*
*************************************************/
#include <stdio.h>
#include <assert.h>

// print digit 0-9
void PrintDigit( unsigned int n )
{
	assert( n < 10 ) ;				
	printf( "%d", n ) ;	
}

// print unsigned number
void PrintOut( unsigned int N )
{
	if( N >= 10 )
		PrintOut( N/10 ) ;
	// PrintDigit( N%10 ) ;   // N%10 --> N-N/10*10
	PrintDigit( N-N/10*10 ) ;
}

int main( int argc, char** argv )
{
	unsigned int N = 76234 ;
	PrintOut( N ) ;	
	printf( "\n" ) ;
}
