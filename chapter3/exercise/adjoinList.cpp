/*******************************************
* 3.14 将图读入邻接表
* 图：student1 -> course1 course3
*     student2 -> course2 course4
*     student3 -> course1 course3
*     student4 -> course1 course3 course4
*     student5 -> course2 course3
*
*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_STUDENT_NUM 100   // 最大学生数量
#define MAX_COURSE_NUM  10    // 最大课程数量

struct Node  // 节点定义
{
    char* stuName ;   // 学生姓名
    char* cosName ;   // 课程姓名
    struct Node* nextStu ;  // 该课程的下一个学生：课程链表  无头节点的循环链表
    struct Node* nextCos ;  // 该学生的下一门课程：学生链表  无头节点的循环链表
} ;
typedef struct Node* Position ;
typedef struct Node* List ;

// 在学生链表中添加课程，在课程链表中增加学生
void registerStudent( List* slist, List* clist, const char* sname, const char* cname )
{
    // 学生链表 和 课程链表 共用一个节点
    Position p = (Position)malloc( sizeof(struct Node) ) ;
    assert( p ) ;
    p->stuName = (char*)malloc( strlen(sname)+1 ) ;
    assert( p->stuName ) ;
    strcpy( p->stuName, sname ) ;
    p->cosName = (char*)malloc( strlen(cname)+1 ) ;
    assert( p->cosName ) ;
    strcpy( p->cosName, cname ) ;

    if( *slist == NULL )  // 学生链表，该学生的第一门课程
    {
        *slist = p ;
        p->nextCos = p ; 
    }
    else  // 将该课程插入学生链表的尾部
    {
        Position tmp = *slist ;
        while( tmp->nextCos != *slist ) tmp = tmp->nextCos ;
        tmp->nextCos = p ;
        p->nextCos = *slist ;       
    }

    if( *clist == NULL )  // 课程链表，该课程的第一个学生
    {
        *clist = p ;
        p->nextStu = p ;   
    }      
    else  // 将该学生插入课程链表的尾部
    {
        Position tmp = *clist ;
        while( tmp->nextStu != *clist ) tmp = tmp->nextStu ;
        tmp->nextStu = p ;
        p->nextStu = *clist ;
    }
}

// 打印学生链表：一个学生的所有课程(从第一个课程开始直到再次打印第一个课程)
void printSList( List slist, const char* sname )
{
    Position p = slist ;
    if( slist == NULL ) return ;  
    if( strcmp( sname, p->stuName ) )  return ;  // 检查链表是否符合条件
    printf( "student %s: ", p->stuName ) ;
    while( p->nextCos != slist )
    {
        printf( "%s ", p->cosName ) ;
        p = p->nextCos ;
    }    
    printf( "%s %s\n", p->cosName, p->nextCos->cosName ) ;  // 最后再次输出第一个课程，验证循环
}   

// 打印课程链表：一个课程的所有学生(从第一个学生开始直到再次打印第一个学生)
void printCList( List clist, const char* cname )
{
    Position p = clist ;
    if( clist == NULL )  return ;
    if( strcmp( cname, clist->cosName ) )  return ;
    printf( "course %s: ", p->cosName ) ;
    while( p->nextStu != clist )
    {
        printf( "%s ", p->stuName ) ;
        p = p->nextStu ;
    }
    printf( "%s %s\n", p->stuName, p->nextStu->stuName ) ;
}

// 删除学生链表(因为学生链表和课程链表共用节点，所以把所有学生链表删除即可清除所有节点)
void deleteSList( List slist )
{
    if( slist == NULL )  return ;
    Position p = slist->nextCos ;  // 从链表的第二个节点开始删除
    while( p != slist )  // 注意循环链表删除的特殊性，使用valgrind检查内存泄漏
    {
        Position node = p ;
        p = p->nextCos ;
        free( node->stuName ) ;
        free( node->cosName ) ;
        free( node ) ;
    }
    free( slist->stuName ) ;   // 最后删除第一个节点
    free( slist->cosName ) ;
    free( slist ) ;   
}

int main( int argc, char** argv )
{
    const char* students[] = { "student1", "student2", "student3", "student4", "student5" } ;  // 学生列表
    const char* courses[] = { "course1", "course2", "course3", "course4" } ;   // 课程列表
    const char* stuCourses[][3] = { { "course1", "course3", "" },    // 每个学生的课程，使用空串补齐
                                    { "course2", "course4", "" },
                                    { "course1", "course3", "" },
                                    { "course1", "course3", "course4" },
                                    { "course2", "course3", "" } } ;
    int stuNum = sizeof(students) / sizeof(students[0] ) ;
    int cosNum = sizeof(courses) / sizeof(courses[0]) ;
    List slists[ MAX_STUDENT_NUM ] ;   // 定义学生链表数组和课程链表数组，与学生列表和课程列表下标对应
    List clists[ MAX_COURSE_NUM ] ;    // 0号学生对应0号学生链表，0号课程对应0号课程链表
    for( int i = 0;i < stuNum;i++ ) slists[i] = NULL ;
    for( int i = 0;i < cosNum;i++ ) clists[i] = NULL ;

    for( int i = 0;i < stuNum;i++ )  // 循环遍历每个学生
    {
        int stuCosNum = sizeof(stuCourses[i]) / sizeof(stuCourses[i][0]) ;
        for( int j = 0;j < stuCosNum;j++ )  // 循环遍历一个学生的课程表
        {
            for( int k = 0;k < cosNum;k++ )  // 循环遍历课程链表，找到对应的课程链表
            {
                if( strcmp( stuCourses[i][j], courses[k] ) == 0 )
                {
                    // 将学生注册到对应的学生链表和课程链表中
                    registerStudent( &(slists[i]), &(clists[k]), students[i], stuCourses[i][j] ) ;
                }
            }   
        }
    }   
 
    // 打印所有学生的注册课程
    for( int i = 0;i < stuNum;i++ )
    {
        printSList( slists[i], students[i] ) ;
    }   
    printf( "\n" ) ;

    // 打印所有课程的注册学生
    for( int i = 0;i < cosNum;i++ )
    {
        printCList( clists[i], courses[i] ) ;   
    }

    // 删除链表
    for( int i = 0;i < stuNum;i++ )
    {
        deleteSList( slists[i] ) ;
    }
}
