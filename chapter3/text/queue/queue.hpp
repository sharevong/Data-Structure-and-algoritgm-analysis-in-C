/**********************************************************************************
* 队列的数组实现
* 使用front指定队列头下标 rear指定队列尾下标
* 使用capacity指定数组大小（队列最大长度）
* 使用size表示当前队列长度
* 入队时从队列尾入队，使rear加1，然后新的rear位置设置值
* 出队时从队列头出队，使front加1，如果需要返回值，返回之前front位置上的值
* 入队时需要判断队列是否已满(size=capacity)，出队时需要判断队列是否为空(size=0)
* 入队出队导致front rear值到数组最后一个位置之后时，重置为0（循环数组）
* 初始化队列时，front=1 rear=0，第一个入队元素放在arr[1]
*
**********************************************************************************/
#ifndef QUEUE_HPP_
#define QUEUE_HPP_

struct QueueRecord ;
typedef struct QueueRecord* Queue ;
typedef int ElementType ;

// 队列是否为空
int isEmpty( Queue q ) ;

// 队列是否已满
int isFull( Queue q ) ;

// 创建最大长度为指定值的空队列
Queue createQueue( int maxElements ) ;

// 释放队列
void disposeQueue( Queue q ) ;

// 队列置空
void makeEmpty( Queue q ) ;

// 入队
void enqueue( ElementType x, Queue q ) ;

// 获取队头元素
ElementType front( Queue q ) ;

// 出队
void dequeue( Queue q ) ;

// 获取队头元素并出队
ElementType frontAndDequeue( Queue q ) ;

// 打印队列，从队列头到队列尾
void printQueue( Queue q ) ;

#endif
