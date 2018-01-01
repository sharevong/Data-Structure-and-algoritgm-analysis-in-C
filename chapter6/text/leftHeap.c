#include "leftHeap.h"

struct TreeNode
{
	ElementType Element ;
	PriorityQueue Left ;
	PriorityQueue Right ;
	int Npl ;  // 零路径长
} ;

PriorityQueue Initialize( void ) ;
ElementType FindMin( PriorityQueue H ) ;
int IsEmpty( PriorityQueue H ) ;

PriorityQueue Merge( PriorityQueue H1, PriorityQueue H2 )
{
	if( H1 == NULL )
		return H2 ;
	if( H2 == NULL )
		return H1 ;
	if( H1->Element < H2->Element )
		return Merge1( H1, H2 ) ;
	else
		return Merge1( H2, H1 ) ;
}

PriorityQueue Merge1( PriorityQueue H1, PriorityQueue H2 )
{
	if( H1->Left == NULL )  // 当H1无左儿子时，根据左式堆性质，此时H1为一个节点，Npl为0不需要更新
		H1->Left = H2 ;     // 将H2设置为H1的左儿子即可
	else
	{
		H1->Right = Merge( H1->Right, H2 ) ;  // 使用Merge而不是Merge1进行递归，判断其中一个左式堆为NULL的情况
		if( H1->Left->Npl < H1->Right->Npl )
			SwapChildren( H1 ) ;
		H1->Npl = H1->Right->Npl + 1 ;
	}
	return H1 ;
}

PriorityQueue Insert1( ElementType X, PriorityQueue H )
{
	PriorityQueue SingleNode = malloc( sizeof( struct TreeNode ) ) ;
	if( SingleNode == NULL )
		FatalError( "Out of space!!!" ) ;
	else
	{
		SingleNode->Element = X ;
		SingleNode->Left = SingleNode->Right = NULL ;
		SingleNode->Npl = 0 ;
		H = Merge( SingleNode, H ) ;
	}
	return H ;
}

PriorityQueue DeleteMin1( PriorityQueue H )
{
	PriorityQueue LeftHeap, RightHeap ;
	if( IsEmpty( H ) )
	{
		Error( "Priority queue is empty" ) ;
		return H ;
	}
	LeftHeap = H->Left ;
	RightHeap = H->Right ;
	free( H ) ;
	return Merge( LeftHeap, RightHeap ) ;
	
}