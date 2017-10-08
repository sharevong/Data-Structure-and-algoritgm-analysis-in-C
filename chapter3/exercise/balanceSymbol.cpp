/***************************************
 * 3.18 检查平衡符号
 *      ()[]{}
 *      使用链表实现栈
 ***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct node
{
   char c ;  // 字符
   struct node* next ;
} ;
typedef struct node* Node ;  // 节点
typedef struct node* Stack ; // 栈

// 创建栈（创建链表）
Stack createStack()
{
   Stack s = (Stack)malloc( sizeof(struct node) ) ;
   assert( s ) ;
   s->c = 0 ;
   s->next = NULL ;
   return s ;
}

// 判断栈为空
bool isEmpty( Stack s )
{
   assert( s ) ;
   return s->next == NULL ;
}

// 入栈（链表头插入）
void push( Stack s, char ch )
{
   assert( s ) ;
   Node n = (Node)malloc( sizeof(struct node) ) ;
   assert( n ) ;
   n->c = ch ;
   n->next = s->next ;
   s->next = n ;
}

// 出栈（删除链表首节点）
char pop( Stack s )
{
   assert( !isEmpty( s ) ) ;
   char ch = s->next->c ;
   Node tmp = s->next ;
   s->next = s->next->next ;
   free( tmp ) ;
   return ch ;
}

// 获取栈顶元素（获取链表首节点）
char top( Stack s )
{
   assert( !isEmpty( s ) ) ;
   return s->next->c ;
}

// 删除栈（删除链表）
void deleteStack( Stack s )
{
   assert( s ) ;
   Node n = s ;
   while( n )
   {
      Node tmp = n ;
      n = n->next ;
      free( tmp ) ;
   }
}

// 判断平衡符号
bool isBalance( const char* str )
{
   bool res = false ;
   Stack s = createStack() ;
   int len = strlen( str ) ;
   for( int i = 0;i < len;i++ )
   {
      char ch = str[i] ;
      if( ch == '{' || ch == '[' || ch == '(' ) // 左符号时入栈
         push( s, ch ) ;
      if( ch == '}' && pop( s ) != '{' )   // 右符号时出栈，并检查是否匹配
         goto error ;
      if( ch == ']' && pop( s ) != '[' )
         goto error ;
      if( ch == ')' && pop( s ) != '(' )
         goto error ;
   }
   if( isEmpty( s ) )   // 最后检查栈是否为空，注意多余符号的情况如(()
      res = true ;
done:
   deleteStack( s ) ;
   return res ;
error:
   goto done ;
}

int main( int argc, char** argv )
{
   const char* str1 = "{[()]}" ;
   const char* str2 = "{ [ } ] ( )" ;
   printf( "%s is balance? %d\n", str1, isBalance( str1 ) ) ;
   printf( "%s is balance? %d\n", str2, isBalance( str2 ) ) ;
}
