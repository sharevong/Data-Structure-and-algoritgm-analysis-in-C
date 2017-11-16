#include "binarySearchTree.h"

struct TreeNode
{
   ElementType Element ;
   SearchTree Left ;
   SearchTree Right ;
} ;

SearchTree MakeEmpty( SearchTree T )
{
   if( T != NULL )
   {
      MakeEmpty( T->Left ) ;
      MakeEmpty( T->Right ) ;
      free( T ) ;
   }
   return NULL ;
}

Position Find( ElementType X, SearchTree T )
{
   if( T == NULL )   // 递归时首先判断null,终止条件,必要检查
      return NULL ;
   if( X < T->Element )
      Find( X, T->Left ) ;
   else if( X > T->Element )
      Find( X, T->Right ) ;
   else
      return T ;
}

Position FindMin( SearchTree T )
{
   if( T == NULL )
      return NULL ;
   if( T->Left == NULL )
      return T ;
   return FindMin( T->Left ) ;
}

Position FindMax( SearchTree T )
{
   if( T == NULL )
      return NULL ;
   while( T->Right )
      T = T->Right ;  // 改变T没有问题，因为是拷贝
   return T ;
}

SearchTree Insert( ElementType X, SearchTree T )
{
   if( T == NULL )  // 插入第一个元素作为根节点
   {
      T = malloc( sizeof(struct TreeNode) ) ;
      if( T == NULL )
         FatalError( "Out of space" ) ;
      T->Element = X ;
      T->Left = T->Right = NULL ;
   }
   else
   {
      if( X > T->Element )
         Insert( X, T->Right ) ;
      else if( X < T->Element )
         Insert( X, T->Left ) ;  // 插入重复值时，不做处理
   }                             // 一种处理方式是，在节点定义中加入一个变量，标记值出现的次数
   return T ;                    // 这样删除时，只要将该值减1即可，为0时实际删除
}

SearchTree Delete( ElementType X, SearchTree T )
{
   Position tmpCell ;
   if( T == NULL )
      FatalError( "Element not found" ) ;
   else if( X < T->Element )
      Delete( X, T->Left ) ;
   else if( X > T->Element )
      Delete( X, T->Right ) ;
   else
   {
      if( T->Left && T->Right )  // 如果删除的节点有左右子树
      {                          // 则将节点的值替换为右子树中最小值，并删除右子树中对应节点
         tmpCell = findMin( T->Right ) ;  // 也可以将节点的值替换为左子树的最大值
         T->Element = tmpCell->Element ;  // 目前的删除策略会使树向左子树倾斜,可以使用随机
                                          // 删除左子树最大值和右子树最小值的方法解决该问题
         T->Right = Delete( X, T->Right ) ;   // 懒惰删除策略:在节点中加删除标记
      }
      else  // 如果删除的节点只有左子树或只有右子树或无子树时，将该节点替换为它的子树或NULL
      {
         tmpCell = T ;
         if( T->Left == NULL )
            T = T->Right ;
         else if( T->Right == NULL )
            T = T->Left ;
         free( tmpCell ) ;
      }
   }
   return T ;
}

ElementType Retrieve( Position P )
{
   if( P == NULL )
      FatalError( "NULL pointer" ) ;
   return P->Element ;
}
