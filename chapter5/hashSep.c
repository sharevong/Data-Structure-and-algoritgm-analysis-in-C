#include "hashSep.h"

struct ListNode
{
	ElementType Element ;
	Position Next ;
} ;
typedef Position List ;

struct HashTbl
{
	int TableSize ;
	List* TheLists ;
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
	H->TableSize = NextPrime( TableSize ) ;  // 获取不小于TableSize的最小质数，作为散列表的大小
	H->TheLists = malloc( sizeof( List ) * H->TableSize ) ;
	if( H->TheLists == NULL )
		FatalError( "Out of space!!!" ) ;
	for( int i = 0;i < H->TableSize;i++ )
	{
		H->TheLists[i] = malloc( sizeof( struct ListNode ) ) ;
		if( H->TheLists[i] == NULL )
			FatalError( "Out of space!!!" ) ;
		else
			H->TheLists[i]->Next = NULL ;  // 创建表头
	}
	return H ;
}

void DestroyTable( HashTable H ) ;

Position Find( ElementKey Key, HashTable H )
{
	Position P ;
	List L ;
	L = H->TheLists[ Hash( Key, H->TableSize ) ] ;
	P = L->Next ;
	while( P && P->Element != Key )  // 对于字符串类型的关键字，应使用strcmp
		P = P->Next ;
	return P ;
}

void Insert( ElementKey Key, HashTable H )
{
	List L ;
	Position Pos, NewCell ;
	Pos = Find( Key, H ) ;
	if( Pos == NULL )
	{
		NewCell = malloc( sizeof( struct ListNode ) ) ;
		if( NewCell == NULL )
			FatalError( "Out of space!!!" ) ;
		else
		{
			L = H->TheLists[ Hash( Key, H->TableSize ) ] ;
			NewCell->Element = Key ;   // 新关键字插入表头
			NewCell->Next = L->Next ;
			L->Next = NewCell ;
		}
	}
}

ElementKey Retrieve( Position P ) ;