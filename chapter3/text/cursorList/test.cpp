#include <stdio.h>
#include "cursor.hpp"

int main( int argc, char** argv )
{
	initCursorSpace() ;
	List l = 0 ;
	l = makeEmpty( l ) ;
	printf( "list is empty? %d\n", isEmpty(l) ) ;
	Position p = l ;
	insert( 1, l, p ) ;
	insert( 2, l, p ) ;
	insert( 3, l, p ) ;
	insert( 4, l, p ) ;
	printList( l ) ;
	printf( "list is empty? %d\n", isEmpty(l) ) ;
	deleteElement( 3, l ) ;
	printList( l ) ;
	p = find( 2, l ) ;
	printf( "find element 2: %d\n", retrieve( p ) ) ;
	p = findPrevious( 2, l ) ;
	printf( "find element before 2: %d\n", retrieve( p ) ) ;
	deleteList( l ) ;
}
