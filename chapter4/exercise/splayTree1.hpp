/********************************************
 * 自底向上伸展树的实现例程
 *
 *
 ********************************************/ 
#ifndef SPLAY_TREE1_HPP_
#define SPLAY_TREE1_HPP_

struct splayNode1
{
   int element ;
   struct splayNode1* left ;
   struct splayNode1* right ;
} ;
typedef struct splayNode1* splayTree1 ;

void makeEmpty( splayTree1 t ) ;
splayTree1 insertTree( splayTree1 t, int x ) ;
splayTree1 findTree( splayTree1 t, int x ) ;
splayTree1 deleteTree( splayTree1 t, int x ) ;
void printTree( splayTree1 t, int tab ) ;

splayTree1 splay( splayTree1 t, int x ) ;
splayTree1 singleRotateWithLeft( splayTree1 t ) ;
splayTree1 singleRotateWithRight( splayTree1 t ) ;

#endif
