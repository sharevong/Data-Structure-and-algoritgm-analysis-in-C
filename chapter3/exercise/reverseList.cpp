/*********************************************
* 3.12 反转单链表
*  
*********************************************/
#include "common.h"

// 单链表反转  l->A->B->C->NULL   NULL<-A<-B<-C<-l
List reverseList( List l )
{
    if( l == NULL )  return l ;
    Position pre = NULL ;   // 构造两个遍历节点pre p，分别初始化为NULL和第一个节点
    Position p = l->next ;
    while( p )  // 遍历到链表末尾，循环结束时p为NULL pre为C
    {
        Position tmp = p ;  // 更新next指针，使pre p反转并更新（注意操作顺序）
        p = p->next ;       
        tmp->next = pre ;
        pre = tmp ;
    }
    l->next = pre ;  // 最后需要更新头节点!!
    return l ;
}

int main( int argc, char** argv )
{
    List l = createList() ;
    for( int i = 0;i < 10;i++ )
        insertList( l, i ) ;
    printList( l ) ;
 
    l = reverseList( l ) ;    
   
    printList( l ) ;
    deleteList( l ) ;
}
