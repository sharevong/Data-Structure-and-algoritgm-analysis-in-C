#include "hashQuad.h"

enum KindOfEntry { Legitimate, Empty, Deleted } ;

struct HashEntry
{
	ElementType Element ;
	enum KindOfEntry Info ;
} ;

typedef struct HashEntry Cell ;

struct HashTbl
{
	int TableSize ;
	Cell* TheCells ;
} ;

HashTable InitializeTable( int TableSize )
{
	if( TableSize < MinTableSize )
	{
		Error( "Table size too small" ) ;
		return NULL ;
	}
	HashTable H = malloc( sizeof( struct HashTbl ) ) ;
	if( H == NULL )
		FatalError( "Out of space!!!" ) ;
	H->TableSize = NextPrime( TableSize ) ;
	H->TheCells = malloc( sizeof( Cell ) * H->TableSize ) ;
	if( H->TheCells == NULL )
		FatalError( "Out of space!!!" ) ;
	for( int i = 0;i < H->TableSize;i++ )
	{
		H->TheCells[i].Info = Empty ;
	}
	return H ;
}

void DestroyTable( HashTable H )

Position Find( ElementType Key, HashTable H ) ;
{
	Position CurrentPos = Hash( Key, H->TableSize ) ;
	int CollisonNum = 0 ;
	while( H->TheCells[ CurrentPos ].Info != Empty &&   // 关键字为字符串时应使用strcmp
		   H->TheCells[ CurrentPos ].Element != Key )   // 判断顺序不能改变，否则散列表中无值时死循环
	{
		CurrentPos += 2 * ++CollisonNum - 1 ;  // F(i) = i^2, 则F(i) = F(i-1) + 2i - 1
		if( CurrentPos >= H->TableSize )
			CurrentPos -= H->TableSize ;
	}
	return CurrentPos ;
}

void Insert( ElementType Key, HashTable H )
{
	Position Pos = Find( Key, H ) ;
	if( H->TheCells[ Pos ].Info != Legitimate )
	{
		H->TheCells[ Pos ].Info = Legitimate ;
		H->TheCells[ Pos ].Element = Key ;  // 关键字为字符串时应使用strcpy
	}
}

ElementType Retrieve( Position P, HashTable H ) ;

HashTable Rehash( HashTable H )
{
	int i, OldSize ;
	Cell* OldCells ;
	
	OldCells = H->TheCells ;
	OldSize = H->TableSize ;
	
	H = InitializeTable( 2 * OldSize ) ;
	for( i = 0;i < OldSize;i++ )
	{
		if( OldCells[i].Info == Legitimate )
			Insert( OldCells[i].Element, H ) ;
	}
	free( OldCells ) ;
	return H ;
} 