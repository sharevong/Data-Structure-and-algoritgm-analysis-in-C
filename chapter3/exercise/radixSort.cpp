/*********************************************************
 * 3.13 使用社会安全号码对学生排序，基数排序
 * 假设数组为 64 8 216 512 27 729 0 1 343 125
 * 每轮分别按某一位的数进行排序
 * 第一轮按个位数排序：0 1 512 343 64 125 216 27 8 729
 * 第二轮按十位数排序: 0 1 8 512 216 125 27 729 343 64
 * 第三轮按百位数排序：0 1 8 27 64 125 216 343 512 729
 * 
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node
{
    int no ;
    struct Node* next ;
} ;
typedef struct Node* Position ;
typedef struct Node* List ;

// 创建空链表
List createList()
{
    List l = (List)malloc( sizeof(struct Node) ) ;
    assert( l ) ;
    l->no = -1 ;
    l->next = NULL ;   
}

// 在链表尾部插入元素
void insertList( List l, int x )
{
    if( l == NULL ) l = createList() ;
    Position p = l ;
    while( p->next ) p = p->next ;
    Position tmp = (Position)malloc( sizeof(struct Node) ) ;
    assert( tmp ) ;
    tmp->no = x ;
    tmp->next = NULL ;
    p->next = tmp ;      
}

// 在链表尾部插入节点
void appendNode( List l, Position p )
{
    assert( l ) ;
    Position tmp = l ;
    while( tmp->next ) tmp = tmp->next ;
    tmp->next = p ;
    p->next = NULL ;
}

// 打印链表
void printList( List l )
{
    if( l == NULL ) return ;
    Position p = l->next ;
    while( p )
    {
        printf( "%d ", p->no ) ;
        p = p->next ;
    }
    printf( "\n" ) ;
}

// 两个链表连接成一个链表
void appendList( List src, List dst )
{
    assert( src ) ;
    assert( dst ) ;
    Position p = src ;
    while( p->next ) p = p->next ;
    p->next = dst->next ;   
}

// 清空链表
void makeEmpty( List l )
{
    l->next = NULL ;
}

// 删除链表
void deleteList( List l )
{
    if( l == NULL )  return ;
    Position p = l ;
    while( p )
    {
        Position tmp = p ;
        p = p->next ;
        free( tmp ) ;
    }   
}


int main( int argc, char** argv )
{
    int arr[] = { 64, 8, 216, 512, 27, 729, 0, 1, 343, 125 } ;
    int size = sizeof(arr) / sizeof(arr[0]) ;
    List sortList ;   // 保存每轮排序后的数组
    List lists[10] ;  // 每个链表保存对应位数为0-9的值 如lists[0]在第一轮保存在个位位数为0的值
    for( int i = 0;i < 10;i++ )
    {
        lists[i] = createList() ;
    }
    sortList = createList() ;

    for( int i = 0;i < size;i++ )  // 首先将数组中的值放入排序链表中
    {
        insertList( sortList, arr[i] ) ;   
    }
    printList( sortList ) ;

    bool flag = true ;  // 标记，当某一次循环所有数字在对应位的值都是0时，退出循环
    int digit = 1 ;  // 位数，以10的倍数不断向上增加
    while( flag )
    {
        flag = false ;  // 循环开始时，置标记为false
        for( int i = 0;i < 10;i++ )  // 清空辅助链表
        {
            makeEmpty( lists[i] ) ;     
        }
      
        while( sortList->next )  // 遍历排序链表，将排序链表中的节点放入辅助链表中直到排序链表为空
        {
            int number = sortList->next->no ;
            int idx = ( number / digit ) % 10 ;
            if( idx != 0 )  flag = true ;  // 出现在当前位不为0的数字时，置标记为true
            Position tmp = sortList->next->next ;  // 需要保存下一位置作为新的第一个节点，因为下一步的函数调用会将sortList->next->next置为NULL
            appendNode( lists[idx], sortList->next ) ;
            sortList->next = tmp ;                
        }

        for( int i = 0;i < 10;i++ )  // 重新将各个辅助链表的值合并为一个链表
        {
            appendList( sortList, lists[i] ) ;
        }

        if( flag == false ) break ;  // 判断标记
        digit *= 10 ;  // 位数提高一位
    }  

    printList( sortList ) ;
 
   for( int i = 0;i < 10;i++ )
    {
        deleteList( lists[i] ) ;  
    }
    deleteList( sortList ) ;  
}
