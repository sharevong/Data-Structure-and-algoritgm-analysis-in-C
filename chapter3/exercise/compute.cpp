/***********************************************************
* 3.9 编写任意精度整数运算包，使用多项式
*	  计算2^4000次方中0-9的分布
*     使用多项式可以表示任意大的数字
*	  如 1024 = 1*10^3 + 0*10^2 + 2*10^1 + 4*10^0
*     使用多项式运算从而实现任意精度整数的运算
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 多项式的项，以10为底数
struct Node
{
	int coef ; // 系数
	int exp ;  // 指数
	struct Node* next ;
} ;

typedef struct Node* Position ;
typedef struct Node* List ;

List makeEmpty()
{
	List l = (List)malloc( sizeof(struct Node) ) ;
	assert( l ) ;
	l->coef = 0 ;
	l->exp = 0 ;
	l->next = NULL ;
	return l ;
}

// 按位数从大到小排序（千百十个），在多项式中插入新一项
void insert( int coef, int exp, List l )
{
	Position tmp = (Position)malloc( sizeof(struct Node) ) ;
    assert( tmp ) ;
    tmp->coef = coef ;
    tmp->exp = exp ; 
	
	Position p1 = l ;
	Position p2 = p1->next ;
	while( p2 && p2->exp > exp )  // 在多项式中查找合适的位置
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

// 按位输出数字多项式和数字0-9的分布
void printList( List l )
{
	int count[10] = { 0 } ;   // 保存0-9在数字中出现的次数
	if( l == NULL )  return ;
	if( l->next == NULL ) return ;
	Position p = l->next ;
	while( p )
	{
		printf( "%d", p->coef ) ;  // 从高位开始输出每一位的数字
		count[p->coef]++ ;
		p = p->next ;
	}
	printf( "\n" ) ;	
	for( int i = 0;i < 10;i++ )
	{
		printf( "%d: %d times\n", i, count[i] ) ;  // 输出0-9出现的次数
	}
}

// 多项式相乘（两个多项式按幂次排列）
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
			int coef = p1->coef * p2->coef ;
			int exp = p1->exp + p2->exp ;
			if( coef >= 10 )   // 当两个数相乘等于或超过10时，分成两项进行插入
			{
				insert( coef/10, exp+1, l ) ;
				insert( coef%10, exp, l ) ;
			}
			else   // 两个数相乘不超过10时，插入一项
			{
				insert( coef, exp, l ) ;
			}
			p2 = p2->next ;
		}	
		p1 = p1->next ;
	}	
	
	return l ;	
}

int main( int argc, char** argv )
{
	List a = makeEmpty() ;
	insert( 2, 0, a ) ;   // 构造多项式 2*10^0
	printList( a ) ; 	

	List l = a ;
	int times = 4000 ;  // 次数为4000
	int count = 1 ;
	for( int i = 1;i < times;i++ )
	{
		l = multiPoly( a, l ) ; 	// 计算2^4000
	}
	printList( l ) ;

	deleteList( a ) ;
	deleteList( l ) ;	
}
