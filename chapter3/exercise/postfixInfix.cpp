/******************************************************************
 * 3.20 后缀表达式转中缀表达式 
 *      eg: 1 2 + 3 * --> ( 1 + 2 ) * 3
 * 算法：
 * 遍历后缀表达式字符串，将数字存入栈中，1 2
 * 当碰到运算符号时，
 *   首先取出栈中的变量b放入临时栈                 2
 *   然后将运算符号放入临时栈，                    +
 *   最后取出栈中的变量a放入临时栈                 1
 *   在原有栈上依次加入左括号，临时栈内容，右括号 （ 1 + 2 ）
 *   从而使原有栈中的 a b 变成 （ a + b )
 *   a b 可能是包含括号的子表达式
 *   所有运算都加入括号，不考虑优先级
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <string.h>

// 生成的中缀表达式最大长度
#define MAX_STRING_LEN   1024

struct node
{
   char c ;  // 字符
   struct node* next ;
} ;
typedef struct node* Node ;
typedef struct node* Stack ;

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
void push( Stack s, const char ch )
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

// 从栈中取出一个参与运算的变量，放入临时栈
void pushVar( Stack s, Stack tmp )
{
   int leftBracketCnt = 0 ;  // 左括号计数
   int rightBracketCnt = 0 ; // 右括号计数
   while( !isEmpty(s) )
   {
      char c = pop( s ) ;
      if( c == ')' )
      {
         rightBracketCnt++ ;
         push( tmp, c ) ;
      }
      else if( c == '(' )
      {
         leftBracketCnt++ ;
         push( tmp, c ) ;
         // 左右括号匹配时，表达式变量获取完成
         if( leftBracketCnt == rightBracketCnt ) break ;
      }
      // 当获取到数字且没有右括号时，数值变量获取完成
      else if( c >= '0' && c <= '9' && rightBracketCnt == 0 )
      {
         push( tmp, c ) ;
         // 多位数时需获取完整数字
         // 使用top时需判断栈空，否则当获取到栈底部的数字时会core
         while( !isEmpty( s ) && top( s ) >= '0' && top( s ) <= '9' )
            push( tmp, pop( s ) ) ;
         break ;
      }
      else
      {
         push( tmp, c ) ;
      }
   }
}

// 处理后缀表达式中的运算符
void processSymbol( Stack s, char ch )
{
   Stack tmp = createStack() ;
   pushVar( s, tmp ) ;  // 从栈中取出运算变量b放入临时栈
   push( tmp, ' ' ) ;   
   push( tmp, ch ) ;    // 将运算符和一个空格放入临时栈
   pushVar( s, tmp ) ;  // 从栈中取出运算变量a放入临时栈

   push( s, '(' ) ;  // 在栈中加入左括号
   push( s, ' ' ) ;
   while( !isEmpty( tmp ) )   // 在栈中加入临时栈的内容  
      push( s, pop( tmp ) ) ;
   push( s, ')' ) ;  // 在栈中加入右括号

   deleteStack( tmp ) ;
}

// 从栈中获取最后生成的中缀表达式
// 由于表达式按照栈底-->栈顶方向排列
// 使用临时栈翻转原有栈后，再将临时栈从栈顶-->栈底输出到字符串中
void getInfix( Stack s, char infix[] )
{
   Stack tmp = createStack() ;
   while( !isEmpty( s ) )
   {
      push( tmp, pop( s ) ) ;
   }
   int idx = 0 ;
   while( !isEmpty( tmp ) )
   {
      infix[idx++] = pop( tmp ) ;
   }
   deleteStack( tmp ) ;
}

// 后缀表达式转中缀表达式
void postfixInfix( const char* postfix, char infix[] )
{
   Stack s = createStack() ;
   int len = strlen( postfix ) ;
   
   for( int i = 0;i < len;i++ )
   {
      char ch = postfix[i] ;
      if( ch == ' ' )
      {
         push( s, ch ) ;
      }
      else if( ch >= '0' && ch <= '9' )
      {
         // 数字直接入栈
         push( s, ch ) ;
      }
      else if( ch == '+' || ch == '-' || ch == '*' ||
               ch == '/' || ch == '^' )
      {
         // 处理运算符
         processSymbol( s, ch ) ;
      }
      else
      {
         printf( "Unkobown symbol: %c\n", ch ) ;
         return ;
      }
   }
   // 获取中缀表达式
   getInfix( s, infix ) ;

   deleteStack( s ) ;
}

int main( int argc, char** argv )
{
   const char* postfix = "1 2 + 3 * 10 2 / + 2 2 2 ^ ^ -" ;
   char infix[ MAX_STRING_LEN ] = { 0 } ;
   postfixInfix( postfix, infix ) ;
   printf( "postfix: %s\n", postfix ) ;
   printf( "infix: %s\n", infix ) ;
}
