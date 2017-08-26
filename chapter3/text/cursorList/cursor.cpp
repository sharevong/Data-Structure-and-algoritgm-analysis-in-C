#include "cursor.hpp"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define MAX_SIZE 1024

struct Node
{
	ElementType element ;  // int
	Position next ;
} ;

// 使用数组存储所有节点
struct Node cursorSpace[ MAX_SIZE ] ;  

// 初始化数组 数组的每个元素指向下一个元素 最后一个元素指向第一个元素 元素值初始化为0
// a[0].next = 1  a[1].next = 2 .... a[end-1].next = 0
// a[0]作为NULL使用 a[0].next是数组中空闲列表的第一个位置 链表的尾节点指向a[0]
// List Position的值不能为0
void initCursorSpace()
{
	int i ;
	for( i = 0;i < MAX_SIZE;i++ )
	{
		cursorSpace[i].element = 0 ;
		cursorSpace[i].next = (i+1) % MAX_SIZE ;
	}
}

// 分配一个新的空闲位置 即获取a[0].next指向的位置 并更新a[0].next
// 当所有空闲位置都已分配时，返回0
static Position cursorAlloc()
{
	Position p = cursorSpace[0].next ;
	cursorSpace[0].next = cursorSpace[p].next ;
	return p ;	
}

// 将一个位置置为空闲 将该位置的next置为a[0].next 将a[0].next置为该位置
// 即将该位置加入空闲列表，并作为空闲列表中的第一个
static Position cursorFree( Position p )
{
	cursorSpace[p].next = cursorSpace[0].next ;
	cursorSpace[0].next = p ;
}

// 创建空链表 创建头节点 
List makeEmpty( List l )
{
	deleteList( l ) ;  // 创建空链表时，l应为0或者一个已创建的链表，l未初始化指向随机位置时会coredump
	l = cursorAlloc() ;  // 从数组中分配一个空闲位置
	if( l == 0 )  // 检查是否有空闲位置
		return l ;
	cursorSpace[l].element = 0 ;  
	cursorSpace[l].next = 0 ;  // 将头节点指向a[0]，使链表为空
	return l ;
}

// 检查链表是否为空 检查头节点是否指向a[0]
int isEmpty( List l )
{
	assert( l ) ;
	return cursorSpace[l].next == 0 ;	
}

// 检查尾节点 尾节点指向a[0]
int isLast( Position p, List l )
{
	assert( p ) ;
	return cursorSpace[p].next == 0 ;	
}


Position find( ElementType x, List l )
{
	assert( l ) ;
	Position p = cursorSpace[l].next ;
	while( p && cursorSpace[p].element != x )
		p = cursorSpace[p].next ;
	return p ;		
}

// 删除元素时，获取元素在链表中位置的前一个位置，然后更新指针并删除
void deleteElement( ElementType x, List l )
{
	Position p = findPrevious( x, l ) ;
	if( isLast( p, l ) )
		return ;
	Position tmp = cursorSpace[p].next ;
	cursorSpace[p].next = cursorSpace[tmp].next ;
	cursorFree( tmp ) ;
	return ;
}

Position findPrevious( ElementType x, List l )
{
	assert( l ) ;
	Position p = l ;
	Position tmp ;
	while( (tmp = cursorSpace[p].next) && (cursorSpace[tmp].element != x) )
		p = tmp ;
	return p ;
}

void insert( ElementType x, List l, Position p )
{
	Position tmp = cursorAlloc() ;
	assert( tmp ) ;
	cursorSpace[tmp].element = x ;
	cursorSpace[tmp].next = cursorSpace[p].next ;
	cursorSpace[p].next = tmp ;
}

// 删除链表时，从第一个节点遍历到尾节点删除，最后删除头节点
void deleteList( List l )
{
	if( l == 0 )
		return ;
	Position p = cursorSpace[l].next ;
	Position tmp ;
	while( p )
	{
		tmp = p ;    // 更新p前保存，方便后续的删除
		p = cursorSpace[p].next ;
		cursorFree( tmp ) ;	
	}		
	cursorFree( l ) ;
}

Position header( List l )
{
	return l ;
}

Position first( List l )
{
	return cursorSpace[l].next ;	
}

Position advance( Position p )
{
	return cursorSpace[p].next ;
}

ElementType retrieve( Position p )
{
	return cursorSpace[p].element ;
}

void printList( List l )
{
	if( l == 0 ) 
		return ;
	Position p = cursorSpace[l].next ;
	while( p )
	{
		printf( "%d ", cursorSpace[p].element ) ;
		p = cursorSpace[p].next ;
	}		
	printf( "\n" ) ;
}
