/********************************************
 * 自顶向下伸展树的实现例程
 * 自订向下伸展树与自底向上伸展有部分区别
 * 当伸展树为以下情形
 *           6
 *          /
 *         5
 *        /
 *       4
 *      /
 *     3
 *    /
 *   2
 *  /
 * 1
 * 查找数字1，使用不同方式生成的新伸展树不同
 *     1                1
 *      \                \
 *       6                5
 *      /                / \
 *     4                3   6
 *    / \              / \
 *   2   5            2   4
 *    \
 *     3
 *  自底向上          自顶向下
 *
 *  伸展树的插入/查找/删除操作
 *  当存在值时：
 *  插入查找会使相应值作为根，
 *  删除会执行删除，并使最接近的值作为根
 *  当不存在值时：
 *  插入会插入新值并作为根
 *  查找删除会使最接近的值作为根
 *
 ********************************************/ 
#ifndef SPLAY_TREE_HPP_
#define SPLAY_TREE_HPP_

struct splayNode
{
   int element ;
   struct splayNode* left ;
   struct splayNode* right ;
} ;
typedef struct splayNode* splayTree ;

void makeEmpty( splayTree t ) ;
splayTree insertTree( splayTree t, int x ) ;
splayTree findTree( splayTree t, int x ) ;
splayTree deleteTree( splayTree t, int x ) ;
void printTree( splayTree t, int tab ) ;

splayTree splay( splayTree t, int x ) ;
splayTree singleRotateWithLeft( splayTree t ) ;
splayTree singleRotateWithRight( splayTree t ) ;

#endif
