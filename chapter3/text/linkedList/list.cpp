#include "list.hpp"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

List makeEmpty( List l )
{
	deleteList( l ) ;  // 创建空链表时，l应为NULL或者一个已创建的链表，l未初始化指向随机位置时会coredump
	l = (List)malloc( sizeof(struct Node) ) ;  // 不能使用sizeof(*List)
	if( l == NULL )
		return NULL ;
	l->element = 0 ;
	l->next = NULL ;
	return l ;
}

int isEmpty( List l )
{
	return l->next == NULL ;	
}

int isLast( Position p, List l )
{
	return p->next == NULL ;	
}

Position find( ElementType x, List l )
{
	Position p = l->next ;
	while( p && p->element != x )
		p = p->next ;
	return p ;		
}

// 删除元素时，需获取元素在链表中位置的前一个位置，然后更新指针并删除
void deleteElement( ElementType x, List l )
{
	Position p = findPrevious( x, l ) ;
	if( isLast( p, l ) )
		return ;
	Position tmp = p->next ;
	p->next = tmp->next ;
	free( tmp ) ;
	return ;
}

Position findPrevious( ElementType x, List l )
{
	Position p = l ;
	while( p->next && p->next->element != x )
		p = p->next ;
	return p ;	
}	

void insert( ElementType x, List l, Position p )
{
	assert( p ) ;
	Position tmp = (Position)malloc( sizeof(struct Node) ) ;
	assert( tmp ) ;
	tmp->element = x ;
	tmp->next = p->next ;
	p->next = tmp ;
}

// 删除链表时，从第一个节点遍历到尾节点删除，最后删除头节点
void deleteList( List l )
{
	if( l == NULL ) return ;
	Position p = l->next ;
	Position tmp ;
	while( p )
	{
		tmp = p ;    // 更新p前保存，方便后续的删除
		p = p->next ;
		free( tmp ) ;	
	}		
	free( l ) ;
}

Position header( List l )
{
	return l ;
}

Position first( List l )
{
	assert( l ) ;
	return l->next ;	
}

Position advance( Position p )
{
	assert( p ) ;
	return p->next ;
}

ElementType retrieve( Position p )
{
	assert( p ) ;
	return p->element ;
}

void printList( List l )
{
	if( l == NULL ) return ;
	Position p = l->next ;
	while( p )
	{
		printf( "%d ", p->element ) ;
		p = p->next ;
	}		
	printf( "\n" ) ;
}
