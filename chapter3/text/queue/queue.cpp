#include "queue.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 队列最小长度
#define MinQueueSize 5

struct QueueRecord
{
	int capacity ;   // 最大长度
	int front ;		 // 队列头位置
	int rear ;		 // 队列尾位置
	int size ;		 // 队列当前长度
	ElementType* arr ;	// 队列使用的数组
} ;

int isEmpty( Queue q )
{
	return q->size == 0 ;
}

int isFull( Queue q )
{
	return q->size == q->capacity ;
}

Queue createQueue( int maxElements )
{
	int size = maxElements > MinQueueSize ? maxElements : MinQueueSize ;
	Queue q = (Queue)malloc( sizeof(struct QueueRecord) ) ;
	assert( q ) ;
	q->arr = (ElementType*)malloc( size * sizeof(ElementType) ) ;
	assert( q->arr ) ;
	q->capacity = size ;
	q->front = 1 ;  // front=1 rear=0 第一个入队元素在arr[1]位置
	q->rear = 0 ;
	q->size = 0 ;	
}

void disposeQueue( Queue q )
{
	if( q )
	{
		if( q->arr )
			free( q->arr ) ;
		free( q ) ;
	}
}

void makeEmpty( Queue q )
{
	q->size = 0 ;
	q->front = 1 ;
	q->rear = 0 ;	
}
               
void enqueue( ElementType x, Queue q )
{
	assert( !isFull(q) ) ;
	q->size++ ;
	q->rear++ ;
	if( q->rear == q->capacity )  // 入队时如果rear值超过数组最大下标，重置为0环绕数组
		q->rear = 0 ;
	q->arr[q->rear] = x ;	
}
             
ElementType front( Queue q )
{
	assert( !isEmpty(q) ) ;
	return q->arr[q->front] ;	
}
                            
void dequeue( Queue q )
{
	assert( !isEmpty(q) ) ;
	q->size-- ;
	q->front++ ;
	if( q->front == q->capacity )  // 出队时同理
		q->front = 0 ;		
}
                            
ElementType frontAndDequeue( Queue q )
{
	assert( !isEmpty(q) ) ;
	q->size-- ;
	ElementType res = front( q ) ;
	dequeue( q ) ;
	return res ;	
}

void printQueue( Queue q )
{
	assert( !isEmpty(q) ) ;
	int i ;
	if( q->rear > q->front )  // 如果没有发生环绕数组的情况直接打印front->rear
	{
		for( i = q->front;i <= q->rear;i++ )
			printf( "%d ", q->arr[i] ) ;
		printf( "\n" ) ;
	}
	else   // 如果发生了数组环绕，则先打印front->数组尾，再打印0->rear
	{
		for( i = q->front;i < q->capacity;i++ )
			printf( "%d ", q->arr[i] ) ;
		for( i = 0;i <= q->rear;i++ )
			printf( "%d ", q->arr[i] ) ;
		printf( "\n" ) ;
	}	
}
