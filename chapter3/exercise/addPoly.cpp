/***********************************************
* 3.6 多项式相加
*
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 多项式的项
struct Node
{
    double coef ; // 系数
    int exp ;        // 指数
    struct Node* next ;
} ;

typedef struct Node* Position ;
typedef struct Node* List ;

List makeEmpty()
{
    List l = (List)malloc( sizeof(struct Node) ) ;
    assert( l ) ;
    l->coef = 0.0 ;
    l->exp = 0 ;
    l->next = NULL ;
    return l ;
}

// 在链表l的位置p后插入新一项
void insert( double coef, int exp, List l, Position p )
{
    Position tmp = (Position)malloc( sizeof(struct Node) ) ;
    assert( tmp ) ;
    tmp->coef = coef ;
    tmp->exp = exp ;
    tmp->next = p->next ;
    p->next = tmp ;                
}

void deleteList( List l )
{
    if( l == NULL )  return ;
    Position p = l->next ;
    while( p )
    {
        Position tmp = p ;
        p = p->next ;
        free( tmp ) ;
    }    
    free( l ) ;    
}

// 打印多项式
void printList( List l )
{
    if( l == NULL )  return ;
    if( l->next == NULL ) return ;
    Position p = l->next ;
    while( p )
    {
        if( p != l->next && p->coef > 0 )  // 当不是第一项且系数大于0时，在前面输出+号
            printf( "+ " ) ;
        printf( "%.2f*x^%d ", p->coef, p->exp ) ;
        p = p->next ;
    }
    printf( "\n" ) ;    
}

// 多项式相加（两个多项式按幂次排列）
List addPoly( List l1, List l2 )
{
    List l = makeEmpty() ;
    Position p = l ;
    Position p1 = l1->next ;
    Position p2 = l2->next ;
    while( p1 && p2 )
    {
        if( p1->exp < p2->exp )
        {
            insert( p1->coef, p1->exp, l, p ) ;
            p1 = p1->next ;
            p = p->next ;
        }
        else if( p1->exp > p2->exp )
        {
            insert( p2->coef, p2->exp, l, p ) ;
            p2 = p2->next ;
            p = p->next ;
        }    
        else  // 指数相同时，系数相加
        {
            double coef = p1->coef + p2->coef ;
            if( coef != 0.0 )  // 检查系数和是否为0，为0时跳过
            {
                insert( coef, p1->exp, l, p ) ;
                p = p->next ;
            }
            p1 = p1->next ;
            p2 = p2->next ;
        }    
    }    
    if( p1 ) p->next = p1 ;
    else if( p2 ) p->next = p2 ;
    return l ;    
}

int main( int argc, char** argv )
{
    List a = makeEmpty() ;
    insert( -2.5, 5, a, a ) ;
    insert( 3.2, 3, a, a ) ;
    insert( 2.5, 1, a, a ) ;
    insert( 1.2, 0, a, a ) ;
    printList( a ) ;  // a: 1.2 + 2.5x + 3.2x^3 -2.5x^5    

    List b = makeEmpty() ;
    insert( 5.4, 10, b, b ) ;
    insert( 2.5, 5, b, b ) ;
    insert( 3.2, 3, b, b ) ;
    insert( 2.5, 1, b, b ) ;
    insert( -1.2, 0, b, b ) ;
    printList( b ) ;  // b: -1.2 + 2.5x + 3.2x^3 + 2.5x^5 + 5.4x^10
    
    List l = addPoly( a, b ) ;
    printList( l ) ; // l: a+b = 5x + 6.4x^3 + 5.4x^10

    deleteList( a ) ;
    deleteList( b ) ;
    deleteList( l ) ;    
}
