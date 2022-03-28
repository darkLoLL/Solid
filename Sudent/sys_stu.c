//仍然有很多不合理的地方
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
//结构体和枚举申明
//学生信息

#define id_long 12
#define name_long 15
typedef struct _student
{
    char id[id_long];     //编号
    char name[name_long]; //姓名
    int physical;         //物理
    int chemical;         //化学
    int biological;       //生物
    int grade;            //总成绩
} Student;

typedef struct _stu_list
{
    Student stu;
    struct _stu_list *next;
} Stu_List;
//枚举对应类型
typedef enum _stu_s
{
    stu_id = 0,
    stu_name = 1,
    stu_physical = 2,
    stu_chemical = 3,
    stu_biological = 4,
    stu_grade = 5,
} stu_s;
//排序方式
typedef enum _sort_type
{
    asc = 0, //降序
    des = 1  //升序
} sort_type;
//基础函数声明

void show_table();                                                      //?展示 table
int stu_create(Student *new);                                           //!创建student 信息,返回数字为0则创建失败
Stu_List *add_information(Stu_List *head, Student new);                 //!新建学生信息写入list
int list_free(Stu_List *head);                                          //!清空所有list
int display_all(Stu_List *head);                                        //*展示所有信息
int dis_stu(Student *student);                                          //*展示单个信息
Stu_List *insert_dataup(Stu_List *head, int index, const Student *new); //?通过索引插入学生信息数据
Stu_List *find_stu(Stu_List *head, const char *str, enum _stu_s type);  //?查询学生信息 返回指针
int index_find_stu(Stu_List *head, const char *str, enum _stu_s type);  //?查询学生信息 返回第几个位置
Stu_List *del_stu(Stu_List *head, int index);                           //删除第几位的信息
int cheak(int score);                                                   //!成绩检查，返回 1 则正确
int cheak_stu(Student *sample);                                         //!检查 student 是否规范
int cheak_list(Stu_List *head);                                         //!检查链表
int count(Stu_List *head);                                              //统计 list 内容
Stu_List *sort_list(Stu_List *head, sort_type mode);                    //*排序两种模式
int list_long(Stu_List *head);                                          //*计算 list 长度
Stu_List *fin_index(Stu_List *head, int index);                         //*通过下标返回stu_list
void clear_str(char *p, int size);                                      // 清理字符串
//文件操作

Stu_List *fstu_r();          //!文件读取
void fstu_w(Stu_List *head); //!文件写入
//系统操作函数

void entry_sys();  //录入信息|
void find_sys();   //查询信息|
void ch_sys();     // 修改学生信息
void del_sys();    //删除信息
void insert_sys(); // 插入学生信息
void sort_sys();   // 依据成绩排序
void spc_sys();    // 学生人数统计|
void show_sys();   // 展示信息|
void showmain();   //选择界面|

int main(int argc, char const *argv[])
{
    int key_down = 0;
    do
    {
        system("cls");
        showmain();
        key_down = getch();
        switch (key_down)
        {
        case 48:
            key_down = 0;
            break;
        case 49:
        case 65:
        case 97:
            entry_sys(); //录入
            break;
        case 50:
        case 70:
        case 102:
            find_sys(); //查找
            break;
        case 51:
        case 67:
        case 99:
            ch_sys(); // 修改
            break;
        case 52:
        case 68:
        case 100:
            del_sys(); // 删除
            break;
        case 53:
        case 73:
        case 105:
            insert_sys(); // 插入
            break;
        case 54:
        case 83:
        case 115:
            sort_sys(); // 排序
            break;
        case 55:
        case 84:
        case 116:
            spc_sys(); // 统计
            break;
        case 56:
        case 72:
        case 104:
            show_sys(); //显示所有信息
            break;
        default:
            break;
        }
    } while (key_down);
    return 0;
}
///系统操作

//录入信息
void entry_sys()
{
    Stu_List *head = NULL;
    head = fstu_r();
    char key = 0;
    Student temp_new = {0};
    do
    {
        system("cls");
        system("cls");
        display_all(head);
        printf("是否新建学生信息,请输入(y/n)进入下一步.\n");
        key = getch();
        switch (key)
        {
        case 0:
        case 27:
            printf("exit.\n");
            getch();
            key = 0;
            break;
        case 89:
        case 121:
            //输入yes创建新的信息
            if (stu_create(&temp_new))
            {
                head = add_information(head, temp_new);
            }
            else
            {
                printf("请继续.\n");
            }
            break;
        case 110:
        case 78:
            key = 0;
            break;
        default:
            break;
        }
    } while (key);
    fstu_w(head);
    list_free(head);
}
//查询信息
void find_sys()
{
    int key = 0;
    char index_id[id_long];
    char index_name[name_long];
    Stu_List *head = NULL;
    head = fstu_r();
    Stu_List *temp = NULL;
    int mode = 1;
    do
    {
        if (mode)
        {
            display_all(head);
            printf("按编号(id)查找输入 1.\n");
            printf("按姓名(name)查找输入 2.\n");
            printf("请输入查找模式:");
        }
        key = getch();
        switch (key)
        {
        case 49: //输入 1
            system("cls");
            printf("当前查找模式为 id 查找模式.\n");
            printf("请输入 id ");
            gets(index_id);
            index_id[id_long - 1] = '\0';
            temp = find_stu(head, index_id, 0);
            if (temp)
            {
                printf("%12s |%15s |%9s |%9s |%11s |%6s\n", "id", "name", "physical", "chemical", "biological", "grade");
                if (printf("%12s |%15s |%9d |%9d |%11d |%6d\n", temp->stu.id, temp->stu.name, temp->stu.physical, temp->stu.chemical, temp->stu.biological, temp->stu.grade) >= 0)
                {
                    mode = 0;
                }
            }
            break;
        case 50: //输入 2
            system("cls");
            printf("当前查找模式为 name 查找模式.\n");
            printf("请输入 name ");
            gets(index_name);
            index_name[name_long - 1] = '\0';
            temp = find_stu(head, index_name, 1);
            if (temp)
            {
                printf("%12s |%15s |%9s |%9s |%11s |%6s\n", "id", "name", "physical", "chemical", "biological", "grade");
                if (printf("%12s |%15s |%9d |%9d |%11d |%6d\n", temp->stu.id, temp->stu.name, temp->stu.physical, temp->stu.chemical, temp->stu.biological, temp->stu.grade) >= 0)
                {
                    mode = 0;
                }
            }
            break;
        default:
            break;
        }

    } while (key);
    fstu_w(head);
    list_free(head);
}
//显示单个数据
int dis_stu(Student *student)
{
    int i = 0;
    if (printf("%12s |%15s |%9d |%9d |%11d |%6d\n", student->id, student->name, student->physical, student->chemical, student->biological, student->grade) >= 0)
    {
        i = 1;
    }
    else
    {
        printf("display error.\n");
    }
    return i;
}

//展示所有信息
int display_all(Stu_List *head)
{
    Stu_List *last = head;
    int i = 0;
    if (last)
    {
        printf("%12s |%15s |%9s |%9s |%11s |%6s\n", "id", "name", "physical", "chemical", "biological", "grade");
        while (last)
        {
            if (dis_stu(&(last->stu)))
            {
                last = last->next;
                i++;
            }
            else
            {
                printf("display error.\n");
                last = NULL;
            }
        }
    }
    else
    {
    }
    return i;
}
//创建学生信息
int stu_create(Student *new)
{
    printf("请依次输入id name physical cheical biological,按enter\n");
    if (scanf("%s%s%d%d%d", new->id, new->name, &(new->physical), &(new->chemical), &(new->biological)) == 5)
    {
        new->id[id_long - 1] = '\0';
        new->name[name_long - 1] = '\0';
        while (cheak(new->physical) == 0)
        {
            printf("physics grade error,please re-enter your physics score.\n");
            if (scanf("%d", &(new->physical)) != 1)
            {
                printf("input error\n");
            }
        }
        while (cheak(new->chemical) == 0)
        {
            printf("chemical grade error,please re-enter your chemical score.\n");
            if (scanf("%d", &(new->chemical)) != 1)
            {
                printf("input error\n");
            }
        }
        while (cheak(new->biological) == 0)
        {
            printf("biological grade error,please re-enter your biological score.\n");
            if (scanf("%d", &(new->biological)) != 1)
            {
                printf("input error\n");
            }
        }
        new->grade = new->physical + new->chemical + new->biological;
        return 1;
    }
    else
    {
        printf("输入数据错误:\n");
    }
    return 0;
}
//成绩检查，返回0则错误
int cheak(int score)
{
    if (score >= 0 && score <= 100)
    {
        return 1;
    }
    return 0;
}
//创建 Stu_List 链表
Stu_List *add_information(Stu_List *head, Student new)
{
    Stu_List *p = (Stu_List *)malloc(sizeof(Stu_List));
    p->stu = new;
    p->next = NULL;
    Stu_List *last = head;
    if (last)
    {
        //找到最后一个节点
        while (last->next)
        {
            last = last->next;
        }
        //将节点插入到最后
        last->next = p;
    }
    else
    {
        head = p;
    }
    return head;
}

//查询学生信息 返回指针
Stu_List *find_stu(Stu_List *head, const char *str, enum _stu_s type)
{
    Stu_List *last = head;
    switch (type)
    {
    case 0:
        while (last)
        {
            if (strcmp(last->stu.id, str) == 0)
            {
                return last;
            }
            else
            {
                last = last->next;
            }
        }
        break;
    case 1:
        while (last)
        {
            if (strcmp(last->stu.name, str) == 0)
            {
                return last;
            }
            else
            {
                last = last->next;
            }
        }
        break;
    default:
        break;
    }
    return NULL;
}

//插入学生信息数据
Stu_List *insert_dataup(Stu_List *head, int index, const Student *new)
{
    int real_loc = index - 1;
    Stu_List *last = head;
    Stu_List *p = (Stu_List *)malloc(sizeof(Stu_List));
    p->stu = *new;
    p->next = NULL;
    if (real_loc > 0)
    {
        for (int i = 0; i < real_loc - 1; i++)
        {
            if (last->next)
            {
                last = last->next;
            }
            else
            {
                printf("The subscript crossing the line.\n");
                printf("将自动出入到末尾.\n");
                getch();
                break;
            }
        }
        if (last)
        {
            p->next = last->next;
            last->next = p;
        }
    }
    else if (real_loc == 0)
    {
        p->next = head;
        head = p;
    }
    else
    {
        printf("index error.\n");
    }
    return head;
}

//清理链表
int list_free(Stu_List *head)
{
    int i = 0;
    Stu_List *now = head;
    Stu_List *last = now->next;
    while (now)
    {
        last = now->next;
        free(now);
        now = last;
        i++;
    }
    return i;
}
//文件的读写

//文件读
Stu_List *fstu_r()
{
    FILE *stufile = fopen("student.txt", "rb");
    Stu_List *head = NULL;
    if (stufile)
    {
        rewind(stufile);
        fgetc(stufile);
        if (!feof(stufile))
        {
            fseek(stufile, 0L, SEEK_SET);
            Student temp = {0};
            while (!feof(stufile))
            {
                if (fread(&temp, sizeof(Student), 1, stufile) == 1)
                {
                    head = add_information(head, temp);
                }
                else
                {
                    // printf("read error.\n");
                    printf(".\n");
                    ferror(stufile);
                }
            }
        }
    }
    else
    {
        stufile = fopen("student.txt", "w+b");
    }
    fclose(stufile);
    return head;
}
//文件写入
void fstu_w(Stu_List *head)
{
    FILE *stufile = fopen("student.txt", "w+b");
    if (stufile)
    {
        Stu_List *last = head;
        while (last)
        {
            if (fwrite(&(last->stu), sizeof(Student), 1, stufile) == 1)
            {
                last = last->next;
            }
            else
            {
                printf("Write error\n");
            }
        }
    }
    else
    {
        printf("File writing error.\n");
    }
    fclose(stufile);
}

//展示 table
void show_table()
{
    printf("%12s |%15s |%9s |%9s |%11s |%6s\n", "id", "name", "physical", "chemical", "biological", "grade");
}
//检查链表
int cheak_list(Stu_List *head)
{
    Stu_List *last = head;
    if (last)
    {
        while (last)
        {
            cheak_stu(&(last->stu));
            last = last->next;
        }
        printf("检查完毕.\n");
    }
    else
    {
        printf("没有信息检测...\n");
    }
    return 0;
}
//检查 student 是否规范
int cheak_stu(Student *sample)
{
    char *cl = NULL; //指向空
    char *move = NULL;
    int i;
    int change = 0;
    cl = sample->id;
    move = cl;
    for (i = 0; i < id_long; i++, move++)
    {
        if (*cl == '\0' && *move != '\0')
        {
            *cl = *move;
            *move = '\0';
            cl++;
            change = 1;
        }
    }
    sample->id[id_long - 1] = '\0';
    if (change)
    {
        printf("id: %s 以修改.\n", sample->id);
        change = 0;
    }
    // name cheak
    cl = sample->name;
    move = cl;
    for (i = 0; i < name_long; i++, move++)
    {
        if (*cl == '\0' && *move != '\0')
        {
            *cl = *move;
            *move = '\0';
            cl++;
            change = 1;
        }
    }
    sample->name[name_long - 1] = '\0';
    if (change)
    {
        printf("name: %s 以修改.\n", sample->name);
        change = 0;
    }
    //检查三门成绩
    dis_stu(sample);
    while (!cheak(sample->physical))
    {
        printf("physical grade error,please re-enter your physical score.\n");
        if (scanf("%d", &(sample->physical)) != 1)
        {
            printf("input error\n");
        }
    }
    while (!cheak(sample->chemical))
    {
        printf("chemical grade error,please re-enter your chemical score.\n");
        if (scanf("%d", &(sample->chemical)) != 1)
        {
            printf("input error\n");
        }
    }
    while (!cheak(sample->biological))
    {
        printf("physical grade error,please re-enter your physical score.\n");
        if (scanf("%d", &(sample->biological)) != 1)
        {
            printf("input error\n");
        }
    }
    sample->grade = sample->physical + sample->chemical + sample->biological;
    return 0;
}

//计算 list 长度
int list_long(Stu_List *head)
{
    int l_long = 0;
    Stu_List *last = head;
    while (last)
    {
        l_long++;
        last = last->next;
    }
    return l_long;
}
//用下标找出
Stu_List *fin_index(Stu_List *head, int index)
{
    Stu_List *last = head;
    if (index < 1)
    {
        return NULL;
    }
    for (int i = 0; i < index - 1; i++)
    {
        last = last->next;
    }
    return last;
}
//排序 list
Stu_List *sort_list(Stu_List *head, sort_type mode)
{
    int l_long = list_long(head);
    if (l_long < 2)
    {
        return head;
    }
    Student temp = {0};
    Stu_List *m1 = NULL;
    Stu_List *m2 = NULL;
    for (int i = 0; i < l_long - 1; i++)
    {
        for (int j = 0; j < l_long - 1 - i; j++)
        {
            m1 = fin_index(head, j + 1);
            m2 = fin_index(head, j + 2);
            if (mode == 0)
            {
                if (m1->stu.grade < m2->stu.grade)
                {
                    temp = m1->stu;
                    m1->stu = m2->stu;
                    m2->stu = temp;
                }
            }
            if (mode == 1)
            {
                if (m1->stu.grade > m2->stu.grade)
                {
                    temp = m1->stu;
                    m1->stu = m2->stu;
                    m2->stu = temp;
                }
            }
            m1 = NULL;
            m2 = NULL;
        }
    }
    return head;
}

//统计 list 内容
int count(Stu_List *head)
{
    return list_long(head);
}

void spc_sys() // 学生人数统计
{
    Stu_List *head = fstu_r();
    int l_long = 0;
    system("cls");
    if (head)
    {
        l_long = list_long(head);
        display_all(head);
        printf("---------------------\n");
        printf("总计 %d 人.\n", l_long);
    }
    else
    {
        printf("没有学生信息.\n");
        printf("总计 %d 人.\n", l_long);
    }
    getch();
    list_free(head);
}
void show_sys() // 展示信息
{
    Stu_List *head = fstu_r();
    if (head)
    {
        system("cls");
        display_all(head);
    }
    else
    {
        printf("没有学生信息.\n");
    }
    getch();
    list_free(head);
}

void insert_sys() // 插入学生信息
{
    Stu_List *list = fstu_r();
    if (list == NULL)
    {
        printf("现在没有数据.\n");
        getch();
    }
    int key_down = 0;
    Student newstu = {0};
    do
    {
        system("cls");
        display_all(list);
        printf("是否插入数据(y/n):\n");
        key_down = getch();
        switch (key_down)
        {
            // 输入为Y/y
        case 89:
        case 121:
        case 13:
            if (stu_create(&newstu))
            {
                printf("请输入你要插入的位置.(位置大于0)\n");
                int loc;
                do
                {
                    while (scanf("%d", &loc) != 1)
                    {
                        printf("input error.\n");
                    }
                } while (loc < 1);
                if (fin_index(list, loc))
                {
                    list = insert_dataup(list, loc, &newstu);
                }
            }
            break;
        case 78:
        case 110:
            key_down = 0;
            break;
        default:
            break;
        }
    } while (key_down);
    printf("按任意键返回.\n");
    getch();
    fstu_w(list);
    list_free(list);
}

// 清理字符串
void clear_str(char *p, int size)
{
    for (int i = 0; i < size; i++)
    {
        p[i] = '\0';
    }
}

void ch_sys() // 修改学生信息
{
    Stu_List *list = fstu_r();
    Stu_List *temp = NULL;
    char index_id[id_long], index_name[name_long];
    int key = 0;
    int mode = 0;
    system("cls");
    if (list)
    {
        int keydown = 0;
        do
        {
            system("cls");
            display_all(list);
            printf("是否修改数据.(y/n)\n");
            keydown = getch();
            switch (keydown)
            {
            case 13:
            case 89:
            case 121:
                printf("按编号(id)查找输入 1.\n");
                printf("按姓名(name)查找输入 2.\n");
                printf("请输入查找模式:");
                mode = getch();
                switch (mode)
                {
                case 49: //输入 1
                    printf("\n当前查找模式为 id 查找模式.\n");
                    printf("请输入 id: ");
                    gets(index_id);
                    index_id[id_long - 1] = '\0';
                    temp = find_stu(list, index_id, 0);
                    break;
                case 50: //输入2
                    printf("\n当前查找模式为 name 查找模式.\n");
                    printf("请输入 name: ");
                    gets(index_name);
                    index_name[id_long - 1] = '\0';
                    temp = find_stu(list, index_name, 1);
                    break;
                }
                break;
            case 78:
            case 110:
                keydown = 0;
                break;
            default:
                break;
            }
            if (temp)
            {
                do
                {
                    key = 0;
                    system("cls");
                    show_table();
                    dis_stu(&(temp->stu));
                    printf("请选择你要修改的内容.\n");
                    printf("修改 id   1\n");
                    printf("修改 name 2\n");
                    printf("修改 物理 3\n");
                    printf("修改 化学 4\n");
                    printf("修改 生物 5\n");
                    printf("不修改    0\n");
                    printf("选择");
                    switch (key = getch())
                    {
                    case 48:
                        key = 0;
                        cheak_stu(&(temp->stu));
                        temp = NULL;
                        break;
                    case 49:
                        system("cls");
                        show_table();
                        dis_stu(&(temp->stu));
                        printf(" id -> ");
                        scanf("%s", index_id);
                        index_id[id_long - 1] = '\0';
                        strcpy(temp->stu.id, index_id);
                        clear_str(index_id, id_long);
                        break;
                    case 50:
                        system("cls");
                        show_table();
                        dis_stu(&(temp->stu));
                        printf(" name -> ");
                        scanf("%s", index_name);
                        index_name[name_long - 1] = '\0';
                        strcpy(temp->stu.name, index_name);
                        clear_str(index_name, name_long);
                        break;
                    case 51:
                        system("cls");
                        show_table();
                        dis_stu(&(temp->stu));
                        printf(" 物理 -> ");
                        scanf("%d", &(temp->stu.physical));
                        break;
                    case 52:
                        system("cls");
                        show_table();
                        dis_stu(&(temp->stu));
                        printf(" 化学 -> ");
                        scanf("%d", &(temp->stu.chemical));
                        break;
                    case 53:
                        system("cls");
                        show_table();
                        dis_stu(&(temp->stu));
                        printf(" 生物 -> ");
                        scanf("%d", &(temp->stu.biological));
                        break;
                    default:
                        break;
                    }
                } while (key);
            }
        } while (keydown);
    }
    else
    {
        printf("没有数据可供修改.\n");
        printf("按任意键返回.\n");
        getch();
    }
    if (list)
    {
        fstu_w(list);
        list_free(list);
        printf("修改数据成功\n");
    }
    getch();
}

//排序系统
void sort_sys()
{
    system("cls");
    Stu_List *list = fstu_r();
    display_all(list);
    int key_down = 0;
    do
    {
        printf("请输入排序模式(降序 0,升序 1)\n");
        key_down = getch();
        system("cls");
        switch (key_down)
        {
        case 48:
            list = sort_list(list, 0);
            break;
        case 49:
            list = sort_list(list, 1);
            break;
        }
        display_all(list);
    } while (key_down);
    printf("按任意键返回.\n");
    fstu_w(list);
    list_free(list);
    getch();
}
//显示菜单
void showmain()
{
    system("cls");
    printf("\n\n\n|****************学生成绩管理系统****************|\n");
    printf("|\n");
    printf("|%10s%s\n", " ", "1. 录入学生成绩(a)");
    printf("|%10s%s\n", " ", "2. 查找学生信息(f)");
    printf("|%10s%s\n", " ", "3. 修改学生信息(c)");
    printf("|%10s%s\n", " ", "4. 删除学生信息(d)");
    printf("|%10s%s\n", " ", "5. 插入学生信息(i)");
    printf("|%10s%s\n", " ", "6. 按总绩点排序(s)");
    printf("|%10s%s\n", " ", "7. 统计学生总数(t)");
    printf("|%10s%s\n", " ", "8. 显示所有学生信息(h)");
    printf("|%10s%s\n", " ", "0. 退出系统(esc)");
    printf("|\n");
    printf("|*********************************************|\n\n");
    printf("|%8s", "请输入:");
}

int index_find_stu(Stu_List *head, const char *str, enum _stu_s type) //?查询学生信息 返回第几个位置
{
    int loc = 0;
    Stu_List *last = head;
    switch (type)
    {
    case 0:
        while (last)
        {
            loc++;
            if (strcmp(last->stu.id, str) == 0)
            {
                return loc;
            }
            else
            {
                last = last->next;
            }
        }
        break;
    case 1:
        while (last)
        {
            loc++;
            if (strcmp(last->stu.name, str) == 0)
            {
                return loc;
            }
            else
            {
                last = last->next;
            }
        }
        break;
    default:
        break;
    }
    return 0;
}
Stu_List *del_stu(Stu_List *head, int index) //删除第几位的信息
{
    Stu_List *last = head;
    Stu_List *temp = last;
    if (index == 1)
    {
        head = last->next;
        free(last);
        return head;
    }
    else if (index > 1)
    {
        temp = head;
        last = temp->next;
        for (int i = 0; i < index - 2; i++)
        {
            temp = last;
            last = temp->next;
        }
    }
    temp->next = last->next;
    if (last)
    {
        free(last);
    }
    return head;
}
// 删除信息
void del_sys()
{
    Stu_List *list = fstu_r();
    char index_id[id_long], index_name[name_long];
    int key_down = 0;
    int mode = 0;
    int index = 0;
    Stu_List *temp = NULL;
    do
    {
        system("cls");
        display_all(list);
        printf("是否删除数据.(y/n)\n");
        key_down = getch();
        switch (key_down)
        {
        case 13:
        case 89:
        case 121:
            printf("按编号(id)查找输入 1.\n");
            printf("按姓名(name)查找输入 2.\n");
            printf("请输入查找模式:");
            mode = getche();
            switch (mode)
            {
            case 49: //输入 1
                printf("\n当前查找模式为 id 查找模式.\n");
                printf("请输入 id: ");
                gets(index_id);
                index_id[id_long - 1] = '\0';
                index = index_find_stu(list, index_id, 0);
                break;
            case 50: //输入2
                printf("\n当前查找模式为 name 查找模式.\n");
                printf("请输入 name: ");
                gets(index_name);
                index_name[name_long - 1] = '\0';
                index = index_find_stu(list, index_name, 1);
                break;
            }
            break;
        case 78:
        case 110:
            key_down = 0;
            break;
        default:
            break;
        }
        if (index)
        {
            int key = 0;
            printf("是否删除(y/n) %d\n", index);
            key = getch();
            switch (key)
            {
            case 89:
            case 121:
                list = del_stu(list, index);
                break;
            }
        }
    } while (key_down);
    getch();
    list_free(list);
    fstu_w(list);
}