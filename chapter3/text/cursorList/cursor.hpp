/****************************************************************
* 链表的游标实现
* 使用节点数组存储元素 节点的next存储下一个节点在数组中的下标
* 将数组的第0个元素作为NULL使用
* 节点之间通过next将数组中的元素串联成链表
* 数组第0个元素的next作为一个存储空闲位置的链表
* 通过更新第0个元素的next实现malloc free的功能
*
****************************************************************/
#ifndef CURSOR_HPP_
#define CURSOR_HPP_

typedef int pNode ;
typedef pNode List ;			// 链表的头节点指针
typedef pNode Position ;        // 链表的节点指针
typedef int ElementType ;       // 节点元素类型

// 创建游标数组
void initCursorSpace() ;

// 创建空链表
List makeEmpty( List l ) ;

// 检查链表是否为空
int isEmpty( List l ) ;

// 检查节点是否是链表尾节点
int isLast( Position p, List l ) ;

// 在链表中查找元素，返回元素第一次出现的位置，未找到返回NULL
Position find( ElementType x, List l ) ;

// 在链表中删除元素
void deleteElement( ElementType x, List l ) ;

// 在链表中查找元素，返回元素第一次出现的位置之前的一个位置
Position findPrevious( ElementType x, List l ) ;

// 在链表中的特定位置之后插入元素
void insert( ElementType x, List l, Position p ) ;

// 删除链表
void deleteList( List l ) ;

// 返回链表头节点
Position header( List l ) ;

// 返回链表的第一个元素节点
Position first( List l ) ;

// 返回节点的下一个节点
Position advance( Position p ) ;

// 获取节点中的元素
ElementType retrieve( Position p ) ;

// 打印链表
void printList( List l ) ;

#endif
