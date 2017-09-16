/********************************************************
* 3.10 josephus问题：
* N个人从1到N编号，围成一个圆圈，从1号开始传递土豆，
* M次传递后拿到土豆的人离开，下一个人重新开始继续游戏，
* 最后剩下的人获胜
* 如果M=0 N=5 则5号获胜
* 如果M=1 N=5 则3号获胜
*
*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 算法1：使用循环链表
// 也可以使用数组模拟
struct Node
{
    int no ;    // 数字序号
    struct Node* next ;
} ;

typedef struct Node* Position ;
typedef struct Node* List ;

// 在链表尾部插入
List insertList( List l, int no )
{
    if( l == NULL )  // 插入第一个元素时创建循环链表（无头节点）
    {
        l = (List)malloc( sizeof(struct Node) ) ;
        assert( l ) ;
        l->no = no ;
        l->next = l ;   // 第一个元素的下一个节点是其本身
    }
    else  // 插入其他元素，找到末尾位置（指向第一个节点的节点），进行插入
    {
        Position p = l ;
        while( p->next != l ) p = p->next ;
        Position tmp = (Position)malloc( sizeof(struct Node) ) ;
        assert( tmp ) ;
        tmp->no = no ;
        tmp->next = l ;   // 使新建节点指向第一个节点
        p->next = tmp ;   // 原来的末尾节点指向新建节点
    }
    return l ;
}

// 打印链表，从第一个节点打印直到再次打印第一个节点
void printList( List l )
{
    if( l == NULL )  return ;
    Position p = l ;
    while( p->next != l )
    {
        printf( "%d ", p->no ) ;
        p = p->next ;
    }
    printf( "%d %d\n", p->no, p->next->no ) ;
}

// 删除链表，不断删除并更新第二个元素直到只剩下第一个元素，最后释放第一个元素
void deleteList( List l )
{
    if( l == NULL )  return ;
    Position p = l->next ;
    while( p != l )
    {
        Position tmp = p ;  // 不能直接释放p，p是循环变量
        p = p->next ; 
        free( tmp ) ;
        l->next = p ; 
    }
    free( l ) ;         
}

// 删除链表中的一个元素
List deleteElement( List l, Position p )
{
    Position tmp = l ;
    while( tmp->next != p ) tmp = tmp->next ;
    tmp->next = p->next ;
    if( p == l )  l = l->next ;  // 删除考虑删除第一个元素的特殊情况
    free( p ) ;
    return l ;    
}

// 算法2：使用数组
int joseph( int M, int N )
{
    int result ;
    int* arr = (int*)malloc( N*sizeof(int) ) ;
    assert( arr ) ;
    for( int i = 0;i < N;i++ )
    {
        arr[i] = 1 ;   // 分配一个N个元素的数组，所有数值初始化为1，清除一个元素时将其值设置为0
    }
    int num = N ;  // 保存数组中数值为1的元素个数，每清除一个元素减1，num为1时结束

    int count = 0 ; // 保存传递次数
    for( int i = 0;;i++ )  // 不断在数组中循环
    { 
        if( i == N )  i = 0 ;  // 越界时重置为0，首先判断越界，防止越界访问
        if( count == M )
        {
            arr[i] = 0 ;
            num-- ;
            count = 0 ;   // 清除后传递次数重置为0
            if( num == 1 ) break ;  // 循环结束条件
        }
        else
        {
            if( arr[i] == 1 ) count++ ; // 当碰到正常值时，才增加传递次数
        }
    }
    for( int i = 0;i < N;i++ )  // 最后遍历数组，找到剩下的最后一个为1的元素
    {
        if( arr[i] == 1 )
        {
            result = i+1 ;  // 因为数组下标从0开始，编号从1开始，结果需要加1
            break ;
        }
    }
    free( arr ) ;
    return result ;     
}


int main( int argc, char** argv )
{
    int M = 1 ;   // 0 1 --> 5 3
    int N = 5 ;

    /**使用循环链表
    List l = NULL ;
    for( int i = 1;i <= N;i++ )
    {
        l = insertList( l, i ) ;
    }         
    printList( l ) ;

    Position pre = l ;  // 设置前后两个位置pre p，初始分别是最后一个节点和最后一个节点
    while( pre->next != l ) pre = pre->next ; 
    Position p = pre->next ;  // 遍历时两个节点同时前进，删除时效率较高（比使用链表删除函数效率高）
    int count = 0 ;
    while( l->next != l )
    {
        if( count == M )  // 当满足条件时，删除p，并更新pre p
        {
            Position tmp = p ;
            pre->next = p->next ;
            if( p == l )  l = p->next ;  // 删除p时注意p=l的特殊情形
            p = p->next ;
            free( tmp ) ; 
            count = 0 ;
        }
        else
        {
            pre = pre->next ;
            p = p->next ;
            count++ ;
        }
    }

    printf( "the last is %d\n", l->no ) ;      

    deleteList( l ) ;
    */
    // 使用数组
    printf( "the last is %d\n", joseph( M, N ) ) ;
}
