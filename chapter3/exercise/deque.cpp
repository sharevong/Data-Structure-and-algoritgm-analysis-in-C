/****************************************
 * 3.26 双端队列，在队列两端进行插入删除
 *      使用双向队列
 *
 ****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

struct node
{
   int number ;
   struct node* prev ;
   struct node* next ;
} ;
typedef struct node* Node ;

struct deque
{
   Node front ;
   Node rear ;
} ;
typedef struct deque* Deque ;

Deque createDeque()
{
   Deque dq = (Deque)malloc( sizeof(struct deque) ) ;
   assert( dq ) ;
   dq->front = dq->rear = NULL ;
   return dq ;
}

int isEmpty( Deque dq )
{
   return dq->front == NULL ;
}

// 插入队列头
void push( Deque dq, int x )
{
   assert( dq ) ;
   Node n = (Node)malloc( sizeof(struct node) ) ;
   assert( n ) ;
   n->number = x ;
   n->prev = n->next = NULL ;
   if( isEmpty( dq ) )
   {
      // 插入队列第一个元素，队列头队列尾指向该元素
      dq->front = dq->rear = n ;
   }
   else
   {
      // 更新队列头
      n->next = dq->front ;
      dq->front->prev = n ;
      dq->front = n ;
   }
}

// 从队列头删除并获取元素
int pop( Deque dq )
{
   assert( dq ) ;
   assert( !isEmpty( dq ) ) ;
   int ret = dq->front->number ;
   if( dq->front == dq->rear )
   {
      // 删除队列最后一个元素，更新队列头尾
      free( dq->front ) ;
      dq->front = dq->rear = NULL ;
   }
   else
   {
      Node tmp = dq->front ;
      dq->front = dq->front->next ;
      dq->front->prev = NULL ;
      free( tmp ) ;
   }
   return ret ;
}

// 从队列尾插入元素
void inject( Deque dq, int x )
{
   assert( dq ) ;
   Node n = (Node)malloc( sizeof(struct node) ) ;
   assert( n ) ;
   n->number = x ;
   n->prev = n->next = NULL ;
   if( isEmpty( dq ) )
   {
      dq->front = dq->rear = n ;
   }
   else
   {
      dq->rear->next = n ;
      n->prev = dq->rear ;
      dq->rear = n ;
   }
}

// 从队列尾删除并获取元素
int eject( Deque dq )
{
   assert( dq ) ;
   assert( !isEmpty( dq ) ) ;
   int ret = dq->rear->number ; 
   if( dq->rear == dq->front )
   {
      free( dq->rear ) ;
      dq->rear = dq->front = NULL ;
   }
   else
   {
      Node tmp = dq->rear ;
      dq->rear = dq->rear->prev ;
      dq->rear->next = NULL ;
      free( tmp ) ;
   }
   return ret ;
}

void printDeque( Deque dq )
{
   assert( dq ) ;
   printf( "deque: " ) ;
   Node n = dq->front ;
   while( n )
   {
      printf( "%d ", n->number ) ;
      n = n->next ;
   }
   printf( "\n" ) ;
}

void deleteDeque( Deque dq )
{
   assert( dq ) ;
   Node n = dq->front ;
   while( n )
   {
      Node tmp = n ;
      n = n->next ;
      free( tmp ) ;
   }
}

int main( int argc, char** argv )
{
   Deque dq = createDeque() ;
   for( int i = 0;i < 5;i++ )
   {
      push( dq, i ) ;     
   }
   for( int i = 5;i < 10;i++ )
   {
      inject( dq, i ) ;
   }
   printDeque( dq ) ;
   for( int i = 0;i < 5;i++ )
   {
      printf( "front: %d, rear: %d\n", pop( dq ), eject( dq ) ) ;
   }
   deleteDeque( dq ) ;
}
