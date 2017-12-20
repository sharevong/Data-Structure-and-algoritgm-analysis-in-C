/*******************************
 * 伸展树的实现例程
 *
 *******************************/
#ifndef SPLAYTREE_H
#define SPLAYTREE_H

struct SplayNode ;
typedef struct SplayNode* SplayTree ;

SplayTree MakeEmpty( SplayTree T ) ;
SplayTree Find( ElementType X, SplayTree T ) ;
SplayTree FindMin( SplayTree T ) ;
SplayTree FindMax( SplayTree T ) ;
SplayTree Initialize( void ) ;
SplayTree Insert( ElementType X, SplayTree T ) ;
SplayTree Remove( ElementType X, SplayTree T ) ;
ElementType Retrieve( SplayTree T ) ;

#endif
