#include "course.h"
#include <stdlib.h>

// 链表初始化
void ini_list(list *list)
{
    list->head = NULL;
    list->len = 0;
}

//尾插法添加节点
void add(list *list, const course _new)
{
    node *p = (node *)malloc(sizeof(node));
    p->data = _new;
    p->next = NULL;
    node *last = list->head;
    if (last)
    {
        //找到最后一个节点
        while (last->next)
        {
            last = last->next;
        }
        //将新的节点接到最后
        last->next = p;
        list->len++; //计数加1
    }
    else
    {
        list->head = p; //将新节点定链表头
        list->len++;    //计数加1
    }
}

//找到第i个节点返回内容
course *find(list list, const int i)
{
    if (i < list.len)
    {
        int n = 0;
        node *last = list.head;
        while (last)
        {
            if (n == i)
            {
                return &(last->data);
            }
            last = last->next;
            n++;
        }
    }
    else
    {
        return NULL;
    }
}

//删除第i个数据
void del(list *list, const int i)
{
    if (i < list->len)
    {
        int n = 0;
        node *last = list->head;
        if (i == 0)
        {
            list->head = last->next;
            free(last);
            list->len--;
        }
        else if (i > 0)
        {
            node *temp = list->head;
            last = temp->next;
            int k;
            for (k = 0; k < i - 1; k++)
            {
                temp = last;
                last = temp->next;
            }
            temp->next = last->next;
            if (last)
            {
                free(last);
            }
        }
    }
}