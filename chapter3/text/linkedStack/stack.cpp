#include "stack.hpp"
#include <stdlib.h>
#include <assert.h>

struct Node
{
	ElementType element ;
	pNode next ;
} ;

int isEmpty( Stack s )
{
	return s->next == NULL ;
}

Stack createStack()
{
	Stack s = (Stack)malloc( sizeof(struct Node) ) ;
	if( s == NULL )
		return NULL ;
	s->element = 0 ;
	s->next = NULL ;
	return s ;
}

void disposeStack( Stack s )
{
	assert( s ) ;
	while( !isEmpty(s) )
		pop( s ) ;
	free( s ) ;		
}

void makeEmpty( Stack s )
{
	assert( s ) ;
	while( !isEmpty(s) )
		pop( s ) ;
}

// 入栈 在链表头节点后插入数据 头插法
void push( ElementType x, Stack s )
{
	assert( s ) ;
	pNode tmp = (pNode)malloc( sizeof(struct Node) ) ;
	assert( tmp ) ;
	tmp->element = x ;
	tmp->next = s->next ;
	s->next = tmp ;
}

ElementType top( Stack s )
{
	assert( s ) ;
	assert( !isEmpty(s) ) ;
	return s->next->element ;					
}

// 出栈 删除链表的第一个元素
void pop( Stack s )
{
	assert( s ) ;
	assert( !isEmpty(s) ) ;
	pNode tmp = s->next ;
	s->next = tmp->next ;
	free( tmp ) ;		
}
