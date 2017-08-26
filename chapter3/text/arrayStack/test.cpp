#include "stack.hpp"
#include <stdio.h>

int main( int argc, char** argv )
{
	int maxElements = 10 ;
	Stack s = createStack( maxElements ) ;
	if( s == NULL )
	{
		printf( "Cannot create stack\n" ) ;
		return 0 ;
	}
	printf( "stack is empty? %d\n", isEmpty(s) ) ;
	push( 3, s ) ;
	push( 4, s ) ;
	push( 5, s ) ;
	printf( "stack is empty? %d\n", isEmpty(s) ) ;
	printf( "stack top: %d\n", top(s) ) ;
	pop( s ) ;
	printf( "stack top: %d\n", topAndPop(s) ) ;
	disposeStack( s ) ;
}
