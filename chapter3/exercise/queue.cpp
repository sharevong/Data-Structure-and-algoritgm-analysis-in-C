/*********************************************
 * 3.25 编写实现队列的例程
 *  a. 数组见text部分
 *  b. 链表
 *     1 -> 2 -> 3 -> 4 ->...
 *     队列头               队列尾
 *********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

struct node
{
   int number ;
   struct node* next ;
} ;
typedef struct node* Node ;

struct queue
{
   Node front ;  // 队列头
   Node rear ;   // 队列尾
} ;
typedef struct queue* Queue ;

Queue createQueue()
{
   Queue q = (Queue)malloc( sizeof(struct queue) ) ;
   assert( q ) ;
   q->front = q->rear = NULL ;
   return q ;
}

int isEmpty( Queue q )
{
   return q->front == NULL ;
}

// 入队
void enqueue( Queue q, int x )
{
   assert( q ) ;
   Node n = (Node)malloc( sizeof(struct node) ) ;
   assert( n ) ;
   n->number = x ;
   n->next = NULL ;
   if( isEmpty( q ) )
   {
      // 第一个元素入队时，队列头队列尾指向该元素
      q->front = n ;
      q->rear = n ;
   }
   else
   {
      // 更新队列尾
      q->rear->next = n ;
      q->rear = n ;
   }
}

// 出队
void dequeue( Queue q )
{
   assert( q ) ;
   assert( !isEmpty( q ) ) ;
   Node tmp = q->front->next ;
   if( q->front == q->rear )
   {
      // 队列中只有一个元素时，同时更新队列头队列尾
      free( q->front ) ;
      q->front = q->rear = NULL ;
   }
   else
   {
      // 更新队列头
      free( q->front ) ;
      q->front = tmp ;
   }
}

int front( Queue q )
{
   assert( q ) ;
   assert( !isEmpty( q ) ) ;
   return q->front->number ;
}

void deleteQueue( Queue q )
{
   assert( q ) ;
   Node n = q->front ;
   while( n )
   {
      Node tmp = n ;
      n = n->next ;
      free( tmp ) ;
   }
}

int main( int argc, char** argv )
{
   Queue q = createQueue() ;
   for( int i = 0;i < 10;i++ )
   {
      enqueue( q, i ) ;
   }
   for( int i = 0;i < 10;i++ )
   {
      printf( "front: %d\n", front( q ) ) ;
      dequeue( q ) ;
   }
   deleteQueue( q ) ;
}
