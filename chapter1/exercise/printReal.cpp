/*************************************************
* print real number like -xx.yy with PrintDigit
* 打印实数，由于浮点数在计算机中存储不精确，输出
* 结果位数较多
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

// 打印正整数
void PrintOut( unsigned int n )
{
	if( n >= 10 )
		PrintOut( n/10 ) ;
	PrintDigit( n - n/10*10 ) ;
}

// 打印实数
void PrintReal( double x )
{
	if( x < 0 )
		printf( "-" ) ;  // 负数时打印负号

	x = x >=0 ? x : -x ; // 去除负号
	int integer = x ;    // 整数部分
	double decimal = x - integer ;  // 小数部分

	PrintOut( integer ) ;  // 整数部分使用打印正整数函数

	if( decimal == 0.0 )  // 检查是否存在小数部分
		return ;
	printf( "." ) ;

	while( decimal != 0.0 )  // 小数部分不断乘10，将最高位转为一个个位数打印
	{
		int tmp = decimal * 10 ;
		PrintDigit( tmp ) ;
		decimal = decimal*10 - tmp ;
	}	
}

int main( int argc, char** argv )
{
	PrintReal( -146.98 ) ;
	printf( "\n" ) ;
	PrintReal( -13 ) ;
	printf( "\n" ) ;
	PrintReal( 245 ) ;
	printf( "\n" ) ;
	PrintReal( 0.47 ) ;
	printf( "\n" ) ;
}
