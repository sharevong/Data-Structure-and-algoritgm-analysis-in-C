#ifndef HASH_SEP_H
#define HASH_SEP_H

struct ListNode ;
typedef struct ListNode* Position ;
struct HashTbl ;
typedef struct HashTbl* HashTable ;

HashTable InitializeTable( int TableSize ) ;
void DestroyTable( HashTable H ) ;
Position Find( ElementKey Key, HashTable H ) ;
void Insert( ElementKey Key, HashTable H ) ;
ElementKey Retrieve( Position P ) ;
// TODO: 删除操作和清空散列表操作 Delete MakeEmpty

#endif