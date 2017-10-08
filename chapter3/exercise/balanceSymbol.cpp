/***************************************
 * 3.18 检查平衡符号
 *      ()[]{}
 *
 ***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct node
{
  char c ;
  struct node* next ;
} ;
typedef struct node* Node ;
typedef struct node* Stack ;

Stack createStack()
{
  Stack s = (Stack)malloc( sizeof(struct node) ) ;
  assert( s ) ;
  s->c = 0 ;
  s->next = NULL ;
  return s ;
}

bool isEmpty( Stack s )
{
  assert( s ) ;
  return s->next == NULL ;
}

void push( Stack s, char ch )
{
  assert( s ) ;
  Node n = (Node)malloc( sizeof(struct node) ) ;
  assert( n ) ;
  n->c = ch ;
  n->next = s->next ;
  s->next = n ;
}

char pop( Stack s )
{
  assert( !isEmpty( s ) ) ;
  char ch = s->next->c ;
  Node tmp = s->next ;
  s->next = s->next->next ;
  free( tmp ) ;
  return ch ;
}

char top( Stack s )
{
  assert( !isEmpty( s ) ) ;
  return s->next->c ;
}

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

bool isBalance( const char* str )
{
  bool res = false ;
  Stack s = createStack() ;
  int len = strlen( str ) ;
  for( int i = 0;i < len;i++ )
  {
    char ch = str[i] ;
    if( ch == '{' || ch == '[' || ch == '(' )
      push( s, ch ) ;
    if( ch == '}' && pop( s ) != '{' )
      goto error ;
    if( ch == ']' && pop( s ) != '[' )
      goto error ;
    if( ch == ')' && pop( s ) != '(' )
      goto error ;
  }
  if( isEmpty( s ) )
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
