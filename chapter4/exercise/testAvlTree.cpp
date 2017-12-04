/****************************************
 * 4.18 avl单旋转和双旋转例程测试
 *
 ****************************************/
#include "avlTree.hpp"
#include <stdlib.h>

int main( int argc, char** argv )
{
   AvlTree t = NULL ;
   int arr[] = { 2, 1, 4, 5, 9, 3, 6, 7 } ;
   int size = sizeof(arr) / sizeof(arr[0]) ;
   for( int i = 0;i < size;i++ )
   {
      t = insertTree( t, arr[i] ) ;
   }
   printTree( t ) ;
   makeEmpty( t ) ;
}
