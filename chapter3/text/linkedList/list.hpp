/****************************************
* 链表的指针实现
*
****************************************/
#ifndef LIST_HPP_
#define LIST_HPP_

struct Node ;  					// 节点
typedef struct Node* pNode ;
typedef pNode List ;			// 链表的头节点指针
typedef pNode Position ;        // 链表的节点指针
typedef int ElementType ;       // 节点元素类型

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
