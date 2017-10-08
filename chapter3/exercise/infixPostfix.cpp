/*************************************************
 * 3.20 中缀表达式转后缀表达式 
 *      eg: 1 * 2 + 3 --> 1 2 * 3 +
 *      使用数组实现栈
 *************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#define MAX_STACK_SIZE  100  // 栈的最大大小
#define MAX_STRING_LEN  50   // 后缀表达式最大长度

struct stack
{
   char str[ MAX_STACK_SIZE ] ;
   int pos ;
} ;
typedef struct stack* Stack ;

// 创建栈（分配结构体内存，数组清零，栈顶设置-1）
Stack createStack()
{
   Stack s = (Stack)malloc( sizeof(struct stack) ) ;
   assert( s ) ;
   memset( s->str, 0, sizeof( s->str ) ) ;
   s->pos = -1 ;
   return s ;
}

// 判断栈空（检查栈顶是否为-1）
bool isEmpty( Stack s )
{
   return s->pos == -1 ;
}

// 判断栈满（检查栈顶是否为数组最后一个位置）
bool isFull( Stack s )
{
   return s->pos == MAX_STACK_SIZE - 1 ;
}

// 入栈（栈顶位置加1，然后赋值）
void push( Stack s, char ch )
{
   assert( !isFull( s ) ) ;
   s->str[++s->pos] = ch ;
}

// 出栈（获取元素后栈顶位置减1）
char pop( Stack s )
{
   assert( !isEmpty( s ) ) ; 
   return s->str[s->pos--] ;
}

// 获取栈顶元素
char top( Stack s )
{
   assert( !isEmpty( s ) ) ;
   return s->str[s->pos] ;
}

// 删除栈（释放结构体内存）
void deleteStack( Stack s )
{
   assert( s ) ;
   free( s ) ;
}

// 获取运算符号的优先级
int getPriority( char ch )
{
   switch( ch )
   {
      case '+':
      case '-': return 1 ;
      case '*':
      case '/': return 2 ;
      case '^': return 3 ;
      case '(': return 4 ;
      default: return 0 ;
   }
}

// 中缀表达式转后缀表达式
void infixToPostfix( const char* infix, char* postfix )
{
   int len = strlen( infix ) ;
   Stack s = createStack() ;
   int idx = 0 ;
   for( int i = 0;i < len;i++ )
   {
      char ch = infix[i] ;
      // 数字字符时直接复制
      if( ( ch >= '0' && ch <= '9' ) || ch == '.' || ch == ' ' )
         postfix[idx++] = ch ;
      // 运算符号时
      if( ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' )
      {
         // 栈为空时入栈
         if( isEmpty( s ) )
         {
            push( s, ch ) ;
         }
         // 当前符号优先级大于栈顶元素时入栈 
         else if( getPriority( ch ) > getPriority( top( s ) ) )
         {
            push( s, ch ) ;
         }
         // 当前符号优先级小于栈顶元素时，出栈直到栈空或者栈顶元素优先级小于当前符号或者栈顶元素为左括号
         // 然后入栈当前符号
         else
         {
            while( !isEmpty( s ) && getPriority( ch ) <= getPriority( top( s ) ) && top( s ) != '(' )
            {
               if( ch == '^' && top( s ) == '^' )
                  break ;
               postfix[idx++] = ' ' ;
               postfix[idx++] = pop( s ) ;
            }
            push( s, ch ) ;
         }
      }
      // 左括号时入栈
      if( ch == '(' )
         push( s, ch ) ;
      // 右括号时出栈直到栈空（出现这种情况说明括号不匹配，表达式非法）或者碰到左括号
      // 最后把左括号出栈
      if( ch == ')' )
      {
         while( !isEmpty( s ) && top( s ) != '(' )
         {
            postfix[idx++] = ' ' ; 
            postfix[idx++] = pop( s ) ;
         }
         pop( s ) ;
      }
   }
   // 最后把栈中残留的符号输出
   while( !isEmpty( s ) )
   {
      postfix[idx++] = ' ' ;
      postfix[idx++] = pop( s ) ;
   }
   deleteStack( s ) ;
}

int main( int argc, char** argv )
{
   const char* infix = "(1 + 2) * 3 + 10 / 2 - 2 ^ 2 ^ 2" ;
   char postfix[ MAX_STRING_LEN ] = { 0 } ;
   infixToPostfix( infix, postfix ) ;
   printf( "infix: %s, postfix: %s\n", infix, postfix ) ;
}
