/************************************
 * 4.15 高度为h的avl树最少节点数
 *
 ************************************/
#include <stdio.h>

int main( int argc, char** argv )
{
   int nodenum[100] ;
   nodenum[0] = 1 ;  // 高度为0的avl树最少1个节点，根节点
   nodenum[1] = 2 ;  // 高度为1的avl树最少2个节点，根节点加一个左节点或右节点
   for( int i = 2;i < 100;i++ )
   {
      // 高度为h的avl树最少节点数：左右子树高度一个为h-1，一个为h-2，加上根节点
      // 使用递推公式可求
      nodenum[i] = nodenum[i-1] + nodenum[i-2] + 1 ;
   }
   printf( "height: 50, least nodes: %d\n", nodenum[50] ) ;
}
