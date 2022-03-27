#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define _long 15

struct _course
{
    char cou_id[15];      // 课程编号
    char cou_name[15];    // 课程名称
    char cou_qua[15];     // 课程性质
    int cou_period;       // 学时
    int cou_less_time;    // 授课学时
    int cou_test_time;    // 实验或上机学时
    float cou_gra;        // 学分
    char cou_term[_long]; // 开课学期
};
typedef struct _course course;
//数据节点
struct _node
{
    course data;
    struct _node *next;
};
typedef struct _node node;
//链表
typedef struct _list
{
    node *head;
    int len;
} list;

//链表基础函数

// 链表初始化
void ini_list(list *list);
//尾插法添加节点
void add(list *list, course _new);
//找到第i个节点返回内容
course *find(list list, const int i);
//删除第i个数据
void del(list *list, const int i);