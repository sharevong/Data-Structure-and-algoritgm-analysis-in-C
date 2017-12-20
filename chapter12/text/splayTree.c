/*******************************
 * 伸展树的实现例程
 *
 *******************************/
#include "splayTree.h"

struct SplayNode
{
   ElementType Element ;
   SplayTree Left ;
   SplayTree Right ;
} ;

typedef struct SplayNode* Position ;
static Position NullNode = NULL ;

SplayTree MakeEmpty( SplayTree T ) ;

SplayTree Find( ElementType X, SplayTree T ) ;

SplayTree FindMin( SplayTree T ) ;

SplayTree FindMax( SplayTree T ) ;

SplayTree Initialize( void )
{
   if( NullNode == NULL )
   {
      NullNode = (Position)malloc( sizeof(struct SplayNode) ) ;
      if( NullNode == NULL )
         FatalError( "Out of space!!" ) ;
      NullNode->Left = NullNode->Right = NULL ;
   }
   return NullNode ;
}

SplayTree Insert( ElementType Item, SplayTree T )
{
   static Position NewNode = NULL ;
   if( NewNode == NULL )
   {
      NewNode = malloc( sizeof(struct SplayNode) ) ;
      if( NewNode == NULL )
         FatalError( "Out of space!!" ) ;
   }
   NewNode->Element = Item ;

   if( T == NullNode )
   {
      NewNode->Left = NewNode->Right = NullNode ;
      T = NewNode ;
   }
   else
   {
      T = Splay( Item, T ) ;
      if( Item < T->Element )
      {
         NewNode->Left = T->Left ;
         NewNode->Right = T ;
         T->Left = NullNode ;
         T = NewNode ;
      }
      else if( Item > T->Element )
      {
         NewNode->Left = T ;
         NewNode->Right = T->Right ;
         T->Right = NullNode ;
         T = NewNode ;
      }
      else 
         return T ;
   }
   NewNode = NULL ;
   return T ;
}

SplayTree Remove( ElementType Item, SplayTree T )
{
   Position NewTree ;
   if( T != NullNode )
   {
      T = Splay( Item, T ) ;
      if( Item == T->Element )
      {
         if( T->Left == NullNode )
            NewTree = T->Right ;
         else
         {
            NewTree = T->Left ;
            NewTree = Splay( Item, NewTree ) ;
            NewTree->Right = T->Right ;
         }
         free( T ) ;
         T = NewTree ;
      }
   }
   return T ;
}

ElementType Retrieve( SplayTree T ) ;

SplayTree Splay( ElementType Item, Position X )
{
   static struct SplayNode Header ;
   Position LeftTreeMax, RightTreeMin ;
   Header.Left = Header.Right = NullNode ;
   LeftTreeMax = RightTreeMin = &Header ;
   NullNode->Element = Item ;

   while( Item != X->Element )
   {
      if( Item < X->Element )
      {
         if( Item < X->Left->Element )
            X = singleRotateWithLeft( X ) ;
         if( X->Left == NullNode )
            break ;
         RightTreeMin->Left = X ;
         RightTreeMin = X ;
         X = X->Left ;
      }
      else
      {
         if( Item > X->Right->Element )
            X = singleRotateWithRight( X ) ;
         if( X->Right == NullNode )
            break ;
         LeftTreeMax->Right = X ;
         LeftTreeMax = X ;
         X = X->Right ;
      }
   }
   LeftTreeMax->Right = X->Left ;
   RightTreeMin->Left = X->Right ;
   X->Left = Header.Right ;
   X->Right = Header.Left ;

   return X ;
}

#endif
