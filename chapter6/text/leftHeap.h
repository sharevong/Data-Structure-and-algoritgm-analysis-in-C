#ifndef LEFT_HEAP_H
#define LEFT_HEAP_H

struct TreeNode ;
typedef struct TreeNode* PriorityQueue ;

// 合并后，新堆使用原堆的节点，不应再使用原堆进行操作

PriorityQueue Initialize( void ) ;
ElementType FindMin( PriorityQueue H ) ;
int IsEmpty( PriorityQueue H ) ;
PriorityQueue Merge( PriorityQueue H1, PriorityQueue H2 ) ;

// 二叉堆的插入无返回值，为了兼容，使用宏
#define Insert( X, H ) ( H = Insert1( (X), H ) )
PriorityQueue Insert1( ElementType X, PriorityQueue H ) ;

// 删除操作与插入操作相同，使用宏做兼容
// TODO: define delete macro
PriorityQueue DeleteMin1( PriorityQueue H ) ;

#endif