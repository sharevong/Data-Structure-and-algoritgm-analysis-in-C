/******************************************
 * 3.19 计算后缀表达式 eg: 1 2 * 3 + 
 *                       1 * 2 + 3 = 5 
 *
 ******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

// 数字字符串最大长度
#define MAX_NUMBER_STRING_LEN 20

struct node
{
   double n ;  // 数字
   struct node* next ;
} ;
typedef struct node* Node ;
typedef struct node* Stack ;

Stack createStack()
{
   Stack s = (Stack)malloc( sizeof(struct node) ) ;
   assert( s ) ;
   s->n = 0.0 ;
   s->next = NULL ;
   return s ;
}

bool isEmpty( Stack s )
{
   assert( s ) ;
   return s->next == NULL ;
}

void push( Stack s, double number )
{
   assert( s ) ;
   Node node = (Node)malloc( sizeof(struct node) ) ;
   assert( node ) ;
   node->n = number ;
   node->next = s->next ;
   s->next = node ;
}

double pop( Stack s )
{
   assert( !isEmpty( s ) ) ;
   Node tmp = s->next ;
   s->next = s->next->next ;
   double ret = tmp->n ;
   free( tmp ) ;
   return ret ;
}

double top( Stack s )
{
   assert( !isEmpty( s ) ) ;
   return s->next->n ;
}

void deleteStack( Stack s )
{
   assert( s ) ;
   Node node = s ;
   while( node )
   {
      Node tmp = node ;
      node = node->next ;
      free( tmp ) ;
   }
}

// 计算后缀表达式
double computePostfix( const char* str )
{
   Stack s = createStack() ;
   int len = strlen( str ) ;
   char tmp[ MAX_NUMBER_STRING_LEN ] = { 0 } ;
   for( int i = 0;i < len;i++ )
   {
      char ch = str[i] ;
      if( ch == ' ' )  // 跳过空字符
         continue ;
      int idx = 0 ;
      memset( tmp, 0, sizeof(tmp) ) ;  // 数字字符数组重置为0
      while( ( ch >= '0' && ch <= '9' ) || ch == '.' )  // 数字字符存入字符数组
      {
         tmp[idx++] = ch ;
         ch = str[++i] ;
      }
      if( tmp[0] != 0 )   // 将数字字符串转为数字入栈
         push( s, atof( tmp ) ) ;  
      // 遇到符号时，从栈中取出数字并计算，将计算结果入栈
      if( ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' )
      {
         double a = pop( s ) ;
         double b = pop( s ) ;
         if( ch == '+' )
            push( s, b+a ) ;
         if( ch == '-' )
            push( s, b-a ) ;
         if( ch == '*' )
            push( s, b*a ) ;
         if( ch == '/' )
            push( s, b/a ) ;
         if( ch == '^' )
            push( s, pow( b, a ) ) ;
      }
   }
   double ret = pop( s ) ;  // 最后栈中的数字为后缀表达式计算结果
   deleteStack( s ) ;
   return ret ;
}

int main( int argc, char** argv )
{
   const char* str = "1 2 + 3 * 10 2 / + 2 2 2 ^ ^ -" ;
   printf( "compute postfix: %s, res: %f\n", str, computePostfix( str ) ) ;
}
