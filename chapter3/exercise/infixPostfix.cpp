/*************************************************
* 3.20 中缀表达式转后缀表达式 
*      eg: 1 * 2 + 3 --> 1 2 * 3 +
*
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_STACK_SIZE  100
#define MAX_STRING_LEN  50 

struct stack
{
  char str[ MAX_STACK_SIZE ] ;
  int pos ;
} ;
typedef struct stack* Stack ;

Stack createStack()
{
  Stack s = (Stack)malloc( sizeof(struct stack) ) ;
  assert( s ) ;
  memset( s->str, 0, sizeof( s->str ) ) ;
  s->pos = -1 ;
  return s ;
}

bool isEmpty( Stack s )
{
  return s->pos == -1 ;
}

bool isFull( Stack s )
{
  return s->pos = MAX_STACK_SIZE - 1 ;
}

void push( Stack s, char ch )
{
  assert( !isFull( s ) ) ;
  s->str[++s->pos] = ch ;
}

char pop( Stack s )
{
  assert( !isEmpty( s ) ) 
  return s->str[s->pos--] ;
}

char top( Stack s )
{
  assert( !isEmpty( s ) ) ;
  return s->str[s->pos] ;
}

void deleteStack( Stack s )
{
  assert( s ) ;
  free( s ) ;
}

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

void infixToPostfix( const char* infix, char* postfix )
{
  int len = strlen( infix ) ;
  Stack s = createStack() ;
  int idx = 0 ;
  for( int i = 0;i < len;i++ )
  {
    char ch = infix[i] ;
    if( ch >= '0' && ch <= '9' || ch == '.' || ch == ' ' )
      postfix[idx++] = ch ;
    if( ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' )
    {
      if( isEmpty( s ) )
      {
        push( s, ch ) ;
      }
      else if( getPriority( ch ) > getPriority( top( s ) ) )
      {
        push( s, ch ) ;
      }
      else
      {
        while( !isEmpty( s ) && getPriority( ch ) <= getPriority( top( s ) ) && top( s ) != '(' )
        {
          if( ch == '^' && top( s ) == '^' )
            break ;
          postfix[idx++] = pop( s ) ;
          postfix[idx++] = ' ' ;
        }
        push( s, ch ) ;
      }
    }
    if( ch == '(' )
      push( s, ch ) ;
    if( ch == ')' )
    {
      while( !isEmpty( s ) && top( s ) != '(' )
      {
        postfix[idx++] = pop( s ) ;
        postfix[idx++] = ' ' ;
      }
      pop( s ) ;
    }
  }
  while( !isEmpty( s ) )
  {
    postfix[idx++] = ' ' ;
    postfix[idx++] = pop( s ) ;
  }
  deleteStack( s ) ;
}

int main( int argc, char** argv )
{
  const char* infix = "(1 + 2) * 3" ;
  char postfix[ MAX_STRING_LEN ] = { 0 } ;
  infixToPostfix( infix, postfix ) ;
  printf( "infix: %s, postfix: %s\n", infix, postfix ) ;
}
