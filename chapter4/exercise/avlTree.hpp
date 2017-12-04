/*******************************
 * avl树的实现例程
 *
 *******************************/
#ifndef AVLTREE_HPP
#define AVLTREE_HPP

struct AvlNode
{
   int element ;
   struct AvlNode* left ;
   struct AvlNode* right ;
   int height ;
} ;
typedef struct AvlNode* Position ;
typedef struct AvlNode* AvlTree ;

void makeEmpty( AvlTree t ) ;
AvlTree insertTree( AvlTree t, int x ) ;
AvlTree deleteTree( AvlTree t, int x ) ;
Position findTree( AvlTree t, int x ) ;
int findMin( AvlTree t ) ;
int findMax( AvlTree t ) ;
int getHeight( AvlTree t ) ;
int getElement( Position p ) ;
void printTree( AvlTree t ) ;

void printTree1( AvlTree t, int tab ) ;
int max( int a, int b ) ;
AvlTree singleRotateWithLeft( AvlTree t ) ;
AvlTree singleRotateWithRight( AvlTree t ) ;
AvlTree doubleRotateWithLeft( AvlTree t ) ;
AvlTree doubleRotateWithRight( AvlTree t ) ;

#endif
