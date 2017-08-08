/*****************************************
* get the word int the puzzle
* 字谜游戏：从正方形中找出隐藏的单词
*
*****************************************/
#include <stdio.h>
#include <string.h>

#define WORD_MAX_SIZE 15

// 检查单词是否存在单词表中
void checkWord( const char* word, const char** words, int n )
{
	for( int i = 0;i < n;i++ )
	{
		if( strcmp( word, words[i] ) == 0 )
		{
			printf( "word: %s\n", word ) ;
			break ;
		}
	}
}

// 从正方形中的每个字符开始，向不同方向遍历直到超出边界，检查过程中产生的每个单词
// 二维数组作为函数参数时必须指定第二维的大小，不使用指针（与声明保持一致）
void getWordsInPuzzle( const char puzzle[][4], int row, int col, 
					   const char** words, int n )
{
	char temp[ WORD_MAX_SIZE ] = { 0 } ;
	enum direction {
		NORTH, SOUTH, WEST, EAST, NORTHWEST, NORTHEAST, SOUTHWEST, SOUTHEAST
	} ;  // 遍历方向
	for( int i = 0;i < row;i++ )
	{
		for( int j = 0;j < col;j++ )
		{
			for( int direct = 0;direct != 7;direct = direct+1 )  // 不能直接使用enum类型遍历
			{
				int rowid = i ;
            	int colid = j ;

				memset( temp, 0, WORD_MAX_SIZE ) ;
            	int k = 0 ;  
            	temp[k++] = puzzle[rowid][colid] ;  // 假设单独一个字母不是单词，不检查
				switch( direct )
				{
				case NORTH: while( --rowid >= 0 )  // 按遍历方向遍历直到边界行或列
							{	temp[k++] = puzzle[rowid][colid];
								checkWord(temp, words, n); }  // 每产生一个新单词，检查是否在单词表中
							break ;
				case SOUTH: while( ++rowid < row ) 
							{ 	temp[k++] = puzzle[rowid][colid];
								checkWord(temp, words, n); }
							break ;
				case WEST:  while( --colid >= 0 ) 
							{ 	temp[k++] = puzzle[rowid][colid];
								checkWord(temp, words, n); }
							break ;	
				case EAST:  while( ++colid < col ) 
							{ 	temp[k++] = puzzle[rowid][colid];
								checkWord(temp, words, n); }
							break ;
				case NORTHWEST: while( --rowid >= 0 && --colid >= 0 ) 
							{   temp[k++] = puzzle[rowid][colid];
								checkWord(temp, words, n); }
                            break ;
				case NORTHEAST: while( --rowid >= 0 && ++colid < col )
							{   temp[k++] = puzzle[rowid][colid];
								checkWord(temp, words, n); }
                            break ;
				case SOUTHWEST: while( ++rowid < row && --colid >= 0 )
							{   temp[k++] = puzzle[rowid][colid];
								checkWord(temp, words, n); }
                            break ;
				case SOUTHEAST: while( ++rowid < row && ++colid < col )
							{   temp[k++] = puzzle[rowid][colid];
								checkWord(temp, words, n); }
                            break ;
				}				
			}
		}
	}					
}

int main( int argc, char** argv )
{
	const char puzzle[][4] = {   // 二维数组声明时需要指定第二维的大小
		{ 't', 'h', 'i', 's' } ,
		{ 'w', 'a', 't', 's' } ,
		{ 'o', 'a', 'h', 'g' } ,
		{ 'f', 'g', 'd', 't' }     // 正方形中存在 this two fat that 四个单词
	} ;
	const char* words[] = { "this", "two", "fat", "that" } ;  // 单词表
	int rownum = 4 ;
	int colnum = 4 ;
	int n = 4 ;
	getWordsInPuzzle( puzzle, rownum, colnum, words, n ) ;  // 获取正方形中的单词并打印
}
