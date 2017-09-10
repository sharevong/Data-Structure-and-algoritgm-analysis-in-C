/***********************************************
* 3.7 多项式相乘
* 3.8 多项式F(X)，求( F(x) )^P
*
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 多项式的项
struct Node
{
	double coef ; // 系数
	int exp ;  // 指数
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

// 按幂次从小到大排序，在多项式中插入新一项
void insert( double coef, int exp, List l )
{
	Position tmp = (Position)malloc( sizeof(struct Node) ) ;
    assert( tmp ) ;
    tmp->coef = coef ;
    tmp->exp = exp ; 
	
	Position p1 = l ;
	Position p2 = p1->next ;
	while( p2 && p2->exp < exp )  // 在多项式中查找合适的位置
	{
		p1 = p2 ;
		p2 = p1->next ;	
	}
	if( p2 == NULL )
	{
		tmp->next = NULL ;
		p1->next = tmp ;
	} 
	else if( p2->exp == exp )
	{
		free( tmp ) ;
		p2->coef += coef ;
	}	
	else
	{
		tmp->next = p2 ;
		p1->next = tmp ;	
	}	
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

// 多项式相乘（两个多项式按幂次排列）
// 时间复杂度 MN*MN 假设M为l1项数 N为l2项数
List multiPoly( List l1, List l2 )
{
	List l = makeEmpty() ;
	Position p1 = l1->next ;
	Position p2 = l2->next ;
	while( p1 )
	{
		p2 = l2->next ;  // 每次进入内层循环时重置p2为多项式l2的第一项
		while( p2 )
		{
			double coef = p1->coef * p2->coef ;
			int exp = p1->exp + p2->exp ;
			insert( coef, exp, l ) ;
			p2 = p2->next ;
		}	
		p1 = p1->next ;
	}	
	
	return l ;	
}

int main( int argc, char** argv )
{
	List a = makeEmpty() ;
	insert( 3, 2, a ) ;
	insert( 4, 1, a ) ;
	printList( a ) ; 	

	List b = makeEmpty() ;
	insert( 1, 2, b ) ;
	insert( 2, 4, b ) ;
	printList( b ) ;
	
	List l = multiPoly( a, b ) ;
	printList( l ) ;

	deleteList( a ) ;
	deleteList( b ) ;
	deleteList( l ) ;	
}
