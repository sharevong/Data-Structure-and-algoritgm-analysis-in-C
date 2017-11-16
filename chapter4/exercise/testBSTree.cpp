/****************************************
 * 4.10 二叉查找树操作的例程测试
 * 4.11
 *
 ****************************************/
#include "binarySearchTree.hpp"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char** argv )
{
   Tree t = NULL ;
   int arr[] = { 3, 1, 4, 6, 9, 2, 5, 7 } ;
   int size = sizeof(arr) / sizeof(arr[0]) ;
   for( int i = 0;i < size;i++ )
      t = insertTree( t, arr[i] ) ;
   printTree( t ) ;
   printf( "\n" ) ;

   t = deleteTree( t, 7 ) ;
   printTree( t ) ;
   printf( "\n" ) ;
 
   t = deleteTree( t, 1 ) ;
   printTree( t ) ;
   printf( "\n" ) ;
   
   t = deleteTree( t, 6 ) ;
   printTree( t ) ;
   printf( "\n" ) ;

   printf( "min: %d, max: %d\n", findMin( t ), findMax( t ) ) ;

   makeEmpty( t ) ;
}
