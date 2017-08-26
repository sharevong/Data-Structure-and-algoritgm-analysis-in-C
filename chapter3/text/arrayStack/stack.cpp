#include "stack.hpp"
#include <stdlib.h>
#include <assert.h>

// 栈的最小大小
#define MIN_SIZE 5

// 栈的数组存储
struct StackArr
{
	int capacity ;      // 数组大小
	int topOfStack ;    // 栈顶位置
	ElementType* arr ;  // 数组
} ;

// 空栈时栈顶位置为-1
int isEmpty( Stack s )
{
	return s->topOfStack == -1 ;
}

// 栈满时栈顶位置为数组最后一个位置
int isFull( Stack s )
{
	return s->topOfStack == s->capacity-1 ;
}


Stack createStack( int maxElements )
{
	assert( maxElements >= MIN_SIZE ) ;
	Stack s = (Stack)malloc( sizeof(struct StackArr) ) ;
	assert( s ) ;
	s->arr = (ElementType*)malloc( maxElements * sizeof(ElementType) ) ;
	assert( s->arr ) ;
	s->capacity = maxElements ;
	s->topOfStack = -1;
	return s ;
}

void disposeStack( Stack s )
{
	assert( s ) ;
	free( s->arr ) ;
	free( s ) ;	
}

void makeEmpty( Stack s )
{
	assert( s ) ;
	s->topOfStack = -1 ;
}

void push( ElementType x, Stack s )
{
	assert( s ) ;
	assert( !isFull(s) ) ;
	s->topOfStack++ ;
	s->arr[s->topOfStack] = x ;
}

ElementType top( Stack s )
{
	assert( s ) ;
	assert( !isEmpty(s) ) ;
	return s->arr[s->topOfStack] ;					
}

void pop( Stack s )
{
	assert( s ) ;
	assert( !isEmpty(s) ) ;
	s->topOfStack-- ;
}

ElementType topAndPop( Stack s )
{
	assert( s ) ;
	assert( !isEmpty(s) ) ;
	ElementType x = s->arr[s->topOfStack] ;
	s->topOfStack-- ;
	return x ;		
}
