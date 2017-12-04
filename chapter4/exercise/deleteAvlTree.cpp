/***********************************
 * 4.20 avl树的非懒惰删除
 *
 *
 ***********************************/
#include "avlTree.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <stack>

AvlTree deleteTreeNonLazy( AvlTree t, int x )
{
   stack<AvlTree> s ;
   AvlTree root = t ;
   while( true )
   {
      if( t == NULL )
      {
         printf( "Element %d not found in tree.\n", x ) ;
         return root ;
      }
      else if( x > t->element )
      {
         s.push( t ) ;
         t = t->right ;
      }
      else if( x < t->element )
      {
         s.push( t ) ;
         t = t->left ;
      }
      else
      {

      }
   }

}
