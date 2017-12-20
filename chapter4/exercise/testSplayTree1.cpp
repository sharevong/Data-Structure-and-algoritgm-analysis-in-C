/***********************************
 * 4.25 测试伸展树内部路径长
 * splayTree   自顶向下伸展树
 * splayTree1  自底向上伸展树
 *
 ***********************************/
#include "splayTree1.hpp"
#include <stdlib.h>
#include <stdio.h>

// 获取树的内部路径长(所有节点到根节点路径长之和)
int getInnerLen( splayTree1 t,int level )
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
   splayTree1 t = NULL ;
   for( int i = 1;i <= 1024;i++ )
   {
      t = insertTree( t, i ) ;
   }
   // printTree( t, 0 ) ;
   printf( "1-1024 splayTree1 InnerLen: %d\n", getInnerLen( t, 0 ) ) ;
  
   for( int i = 1;i <= 15;i++ )
   {
      t = findTree( t, i ) ;
      // printTree( t, 0 ) ; 
      printf( "after find %d, splayTree1 InnerLen: %d\n", 
              i, getInnerLen( t, 0 ) ) ;
   }

   makeEmpty( t ) ;
}
