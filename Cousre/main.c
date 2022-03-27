#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "course.h"
// 录入数据
void entry_sys(list *list);
// 查找
void find_sys(list *list);
// 修改
void ch_sys(list *list);
// 删除
void del_sys(list *list);
// // 统计
// void spc_sys(list *list);
// 显示所有信息
void show_sys(list *list);
// 从文件读取数据
void read_list(list *list);
// 将数据写入文件
void write_list(list *list);
// // 对数据进行检验
// int cheak(const course value);

int main(int argc, char const *argv[])
{
    list list;
    ini_list(&list);
    read_list(&list);
    int key_down = 0;
    do
    {
        system("cls");
        // showmain();
        printf("按1录入数据\n");
        printf("按2查找数据\n");
        printf("按3修改数据\n");
        printf("按4删除\n");
        printf("按6显示所有数据\n");
        key_down = getch();
        switch (key_down)
        {
        case 48:
            key_down = 0;
            break;
        case 49:
        // case 65:
        // case 97:
            // 按下 1 A a均可录入
            entry_sys(&list); //录入
            break;
        case 50:
        // case 70:
        // case 102:
            // 2 B b
            find_sys(&list); //查找
            break;
        case 51:
        // case 67:
        // case 99:
            // 3 C c
            ch_sys(&list); // 修改
            break;
        case 52:
        // case 68:
        // case 100:
            // 4 D d
            del_sys(&list); // 删除
            break;
        case 53:
        // case 84:
        // case 116:
            // 5 E e
            // spc_sys(&list); // 统计
            break;
        case 54:
        // case 72:
        // case 104:
            // 6 F f
            show_sys(&list); //显示所有信息
            getch();
            break;
        default:
            key_down = 0;
            printf("按任意键退出");
            break;
        }
    } while (key_down);
    write_list(&list);
    return 0;
}
// 显示所有信息
void show_sys(list *list)
{
    node *last = list->head;
    int i = 1;
    while (last)
    {
        printf("%d %s  %s  %s  %d  %d  %d  %f  %s\n", i, last->data.cou_id, last->data.cou_name, last->data.cou_qua, last->data.cou_period, last->data.cou_less_time, last->data.cou_test_time, last->data.cou_gra, last->data.cou_term);
        i++;
        last = last->next;
    }
}
// 查找
void find_sys(list *list)
{
    char p[_long];
    printf("请输入你要查找的课程编号或名字:");
    scanf("%s", p);
    course *d;
    for (int i = 0; i < list->len; i++)
    {
        d = find(*list, i);
        if (d && (strcmp(d->cou_id, p) == 0 || strcmp(d->cou_name, p)))
        {
            printf("%d %s  %s  %s  %d  %d  %d  %f  %s\n", i, d->cou_id, d->cou_name, d->cou_qua, d->cou_period, d->cou_less_time, d->cou_test_time, d->cou_gra, d->cou_term);
        }
    }
    getch();
}
// 修改
void ch_sys(list *list)
{
    char p[_long];
    printf("输入你要更改的编号或名字:");
    scanf("%s", p);
    course *d;
    for (int i = 0; i < list->len; i++)
    {
        d = find(*list, i);
        if (d && (strcmp(d->cou_id, p) == 0 || strcmp(d->cou_name, p) == 0))
        {
            printf("%d %s  %s  %s  %d  %d  %d  %f  %s\n", i, d->cou_id, d->cou_name, d->cou_qua, d->cou_period, d->cou_less_time, d->cou_test_time, d->cou_gra, d->cou_term);
            printf("输入你要更改的信息\n");
            printf("输入课程编号:");
            scanf("%s", d->cou_id);
            d->cou_id[_long - 1] = '\0';
            printf("输入课程名称:");
            scanf("%s", d->cou_name);
            d->cou_name[_long - 1] = '\0';
            printf("输入课程性质:");
            scanf("%s", d->cou_qua);
            d->cou_qua[_long - 1] = '\0';
            printf("输入课程学时:");
            scanf("%d", &d->cou_period);
            printf("输入课程授课学时:");
            scanf("%d", &d->cou_less_time);
            printf("输入课程实践或实验学时:");
            scanf("%d", &d->cou_test_time);
            printf("输入课程学分:");
            scanf("%f", &d->cou_gra);
            printf("输入课程开课时间:");
            scanf("%s", d->cou_term);
            d->cou_term[_long - 1] = '\0';
            break;
        }
    }
    printf("按任意键退出\n");
    getch();
    write_list(list);
}
// 删除
void del_sys(list *list)
{
    int index, key;
    show_sys(list);
    printf("按y进入删除:");
    key = getch();
    while (key)
    {
        switch (key)
        {
        case 13:
        case 89:
        case 121:
            system("cls");
            show_sys(list);
            printf("选择删除的序号:");
            scanf("%d", &index);
            if (index <= list->len && index > 0)
            {
                del(list, index - 1);
            }
            else
            {
                printf("index错误\n");
            }
            printf("按y or enter继续\n");
            key = getch();
            break;
        default:
            printf("按任意键退出\n");
            getch();
            key = 0;
            break;
        }
    }

    write_list(list);
}
// 录入数据
void entry_sys(list *list)
{
    int key;
    course temp;
    // system("cls");
    show_sys(list);
    printf("按y录入数据...\n");
    key = getch();
    switch (key)
    {

    case 121:
    case 89:
        printf("输入课程编号:");
        scanf("%s", temp.cou_id);
        temp.cou_id[_long - 1] = '\0';
        printf("输入课程名称:");
        scanf("%s", temp.cou_name);
        temp.cou_name[_long - 1] = '\0';
        printf("输入课程性质:");
        scanf("%s", temp.cou_qua);
        temp.cou_qua[_long - 1] = '\0';
        printf("输入课程学时:");
        scanf("%d", &temp.cou_period);
        printf("输入课程授课学时:");
        scanf("%d", &temp.cou_less_time);
        printf("输入课程实践或实验学时:");
        scanf("%d", &temp.cou_test_time);
        printf("输入课程学分:");
        scanf("%f", &temp.cou_gra);
        printf("输入课程开课时间:");
        scanf("%s", temp.cou_term);
        temp.cou_term[_long - 1] = '\0';
        // 加入链表
        add(list, temp);
        printf("按y继续输入\n");
        key = getch();
        break;
    default:
        printf("按任意键退出...\n");
        getch();
        key = 0;
        break;
    }
}

// 从文件读取数据
void read_list(list *list)
{
    FILE *infile = fopen("cousre.txt", "r");
    if (infile)
    {
        course temp;
        fgetc(infile);
        while (!feof(infile))
        {
            fseek(infile, -1, SEEK_CUR);
            if (fscanf(infile, "%s%s%s%d%d%d%f%s\n", temp.cou_id, temp.cou_name, temp.cou_qua, &temp.cou_period, &temp.cou_less_time, &temp.cou_test_time, &temp.cou_gra, temp.cou_term))
            {
                add(list, temp);
            }
        }
    }
    else
    {
        infile = fopen("cousre.txt", "w+");
    }
    fclose(infile);
}
// 将数据写入文件
void write_list(list *list)
{
    FILE *outfile = fopen("cousre.txt", "w+");
    if (outfile)
    {
        node *last = list->head;
        while (last)
        {
            fprintf(outfile, "%s %s %s %d %d %d %f %s\n", last->data.cou_id, last->data.cou_name, last->data.cou_qua, last->data.cou_period, last->data.cou_less_time, last->data.cou_test_time, last->data.cou_gra, last->data.cou_term);
            last = last->next;
        }
    }
    fclose(outfile);
}