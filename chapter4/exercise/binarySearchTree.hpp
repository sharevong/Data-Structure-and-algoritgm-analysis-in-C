/***************************************
 * 二叉查找树的实现例程
 * 
 ***************************************/
#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

struct node
{
   int element ;   // 节点数据
   struct node* left ;   // 左子树
   struct node* right ;  // 右子树
} ;
typedef struct node* Node ;
typedef struct node* Tree ;

// 插入数据
Tree insertTree( Tree t, int x ) ;

// 最小值
int findMin( Tree t ) ;

// 最大值
int findMax( Tree t ) ;

// 删除数据
Tree deleteTree( Tree t, int x ) ;

// 从小到大的顺序打印树
void printTree( Tree t ) ;

// 删除树
void makeEmpty( Tree t ) ;

#endif
