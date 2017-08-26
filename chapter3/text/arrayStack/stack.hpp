/*******************************************************
* 栈的数组实现 需要确定数组大小
* 栈的结构体定义包括一个数组大小 栈顶位置和一个数组指针
* 空栈时栈顶位置为-1
* 入栈时，使栈顶位置+1，然后在数组的栈顶位置处插入数据
* 出栈时，更新栈顶-1
* 相比链表实现的优点：不用频繁调用malloc free
*               缺点：需要提前声明数组大小
*
*******************************************************/
#ifndef STACK_HPP_
#define STACK_HPP_

struct StackArr ;
typedef struct StackArr* Stack ;
typedef int ElementType ;

// 判断空栈 
int isEmpty( Stack s ) ;

// 判断栈是否已满（数组被用完）
int isFull( Stack s ) ;

// 指定数组大小创建栈
Stack createStack( int maxElements ) ;

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

// 获取栈顶元素并将元素出栈
ElementType topAndPop( Stack s ) ;

#endif
