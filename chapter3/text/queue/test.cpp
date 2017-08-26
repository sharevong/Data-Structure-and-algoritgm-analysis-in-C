#include "queue.hpp"
#include <stdio.h>

int main( int argc, char** argv )
{
	Queue q = createQueue( 7 ) ;
	for( int i = 0;i < 7;i++ )
		enqueue( i, q ) ;
	printQueue( q ) ;
	printf( "Queue is full? %d\n", isFull(q) ) ;
	printf( "front element: %d\n", front(q) ) ;
	dequeue( q ) ;
	enqueue( 10, q ) ;
	printQueue( q ) ;
	for( int i = 0;i < 7;i++ )
		dequeue( q ) ;
	printf( "Queue is empty? %d\n", isEmpty(q) ) ;
}
