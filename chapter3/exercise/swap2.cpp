/********************************************
* 3.3 调整指针交换双链表中的相邻元素
*
********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node
{
    int element ;
    struct Node* pre ;
    struct Node* next ;
} ;

typedef struct Node* pNode ;
typedef struct Node* List ;
typedef struct Node* Position ;

List makeEmpty()
{
    List l = (List)malloc( sizeof(struct Node) ) ;
    assert( l ) ;
    l->element = 0 ;
    l->pre = NULL ;
    l->next = NULL ;
    return l ;    
}

List insert( int x, List l, Position p )
{
    assert( l ) ;
    assert( p ) ;
    Position tmp = p->next ;
    pNode node = (pNode)malloc( sizeof(struct Node) ) ;
    node->element = x ;
    node->pre = p ;
    node->next = tmp ;
    if( tmp )  tmp->pre = node ;  // 需要注意当插入链表末尾时的情况
    p->next = node ;            
}

void deleteList( List l )
{
    Position p = l ;
    while( p )
    {
        Position tmp = p ;
        p = p->next ;
        free( tmp ) ;        
    }    
}

void printList( List l )
{
    if( !l )  return ;
    
    printf( "from head to tail:\n" ) ;
    Position p = l->next ;
    while( p )
    {
        printf( "%d ", p->element ) ;
        p = p->next ;
    }
    printf( "\n" ) ;

    printf( "from tail to head:\n" ) ;
    p = l->next ;
    while( p->next ) p = p->next ;
    while( p->pre )
    {
        printf( "%d ", p->element ) ;
        p = p->pre ;
    }
    printf( "\n" ) ;                
}

// swap p -> nextp
void swap2( Position p )
{
    Position prep = p->pre ;
    Position nextp = p->next ;
    p->next = nextp->next ;
    p->pre = nextp ;
    if( nextp->next ) nextp->next->pre = p ;  // 注意p是链表倒数第二个元素的情况，此时nextp->next为NULL
    nextp->pre = prep ;
    nextp->next = p ;
    prep->next = nextp ;    
}

int main( int argc, char** argv )
{
    List l = makeEmpty() ;
    for( int i = 10;i >= 0;i-- )
        insert( i, l, l ) ;    
    printList( l ) ;

    Position p = l->next ;
    swap2( p ) ;

    printList( l ) ;    

    p = l->next ;
    while( p->next && p->next->next )
    {        
        p = p->next ;
    }
    swap2( p ) ;

    printList( l ) ;

    deleteList( l ) ;
}
