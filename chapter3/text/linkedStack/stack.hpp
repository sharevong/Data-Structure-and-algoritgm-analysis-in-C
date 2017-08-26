/********************************************
* 栈的链表实现
*
********************************************/
#ifndef STACK_HPP_
#define STACK_HPP_

struct Node ;
typedef struct Node* pNode ;
typedef struct Node* Stack ;
typedef int ElementType ;

// 判断栈为空
int isEmpty( Stack s ) ;

// 创建空栈
Stack createStack() ;

// 删除栈
void disposeStack( Stack s ) ;

// 清空栈
void makeEmpty( Stack s ) ;

// 入栈
void push( ElementType x, Stack s ) ;

// 获取栈顶元素
ElementType top( Stack s ) ;

// 出栈
void pop( Stack s ) ;

#endif
