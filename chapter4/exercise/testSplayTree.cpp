/***********************************
 * 4.25 测试伸展树内部路径长
 *
 *
 ***********************************/
#include "splayTree.hpp"
#include <stdlib.h>
#include <stdio.h>

int getInnerLen( splayTree t,int level )
{
   if( t == NULL )
      return 0 ;
   int len = level ;
   len += getInnerLen( t->left, level+1 ) ;
   len += getInnerLen( t->right, level+1 ) ;
   return len ;
}

int main( int argc, char** argv )
{
   // int arr[] = { 1, 2, 3, 4, 5 } ;
   // int size = sizeof( arr ) / sizeof( arr[0] ) ;
   splayTree t = NULL ;
   for( int i = 1;i <= 6;i++ )
   {
      t = insertTree( t, i ) ;
   }
   printTree( t, 0 ) ;
   printf( "1-1024 splayTree InnerLen: %d\n", getInnerLen( t, 0 ) ) ;
  
   for( int i = 1;i <= 1;i++ )
   {
      t = findTree( t, i ) ;
      printTree( t, 0 ) ; 
      printf( "after find %d, splayTree InnerLen: %d\n", 
              i, getInnerLen( t, 0 ) ) ;
   }

   makeEmpty( t ) ;
}
