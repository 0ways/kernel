#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "kernel.h"
// 创建并初始化双向链表
list* CreateList( void )
{
    list* List = (list*)malloc(sizeof(list)*1);

    listItem* head  = (listItem*)malloc(sizeof(listItem)*1);
    listItem* tail  = (listItem*)malloc(sizeof(listItem)*1);
    head->next      = tail;
    head->previous  = NULL;
    head->tcb       = NULL;
    head->message   = NULL;
    tail->tcb       = NULL;
    tail->previous  = head;
    tail->next      = NULL;
    tail->message   = NULL;
    List->list_head = head;
    List->list_tail = tail;

    return List;
}
// 创建并初始化 TCB
TCB* CreateTCB(void (*PC)(), uint deadline)
{
    TCB* tcb      = (TCB*)malloc(sizeof(TCB)*1);
    tcb->PC       = PC;
    tcb->DeadLine = deadline;

    return tcb;
}
// 测试函数for TCB
void function1()
{
    printf("你好, 我是function1!\n");
}
void function2()
{
    printf("你好, 我是function2!\n");
}
void function3()
{
    printf("你好, 我是function3!\n");
}
void function4()
{
    printf("你好, 我是function4!\n");
}
// 将项插入到双向链表当中
void InsertItem(list* List, listItem* item, uint tag)
{
    int length = SizeList(List);
    listItem *first;
    first  = List->list_head->next;
    if (List == NULL || item == NULL) {
        fprintf(stderr, "这是一个 无效 链表, 插入错误\n");
        exit(-1);
    }
    if (length == 0) {
        item->next                = List->list_tail;
        item->previous            = List->list_head;
        List->list_head->next     = item;
        List->list_tail->previous = item;
        return;
    }
    if (tag == 1 || tag == 2) {
        if (length == 1)
        {
            // 需要插入到 head 后面
            if (item->tcb->DeadLine <= first->tcb->DeadLine) {
                item->next            = first;
                item->previous        = List->list_head;
                List->list_head->next = item;
                first->previous       = item;
                return;
            }
            // 需要插入到 tail 前面的情况
            else if (item->tcb->DeadLine > first->tcb->DeadLine)
            {
                item->next                = List->list_tail;
                item->previous            = first;
                first->next               = item;
                List->list_tail->previous = item;
                return;
            }
        }
        // 链表长度为2 个以上的情况
        else if (length >= 2)
        {
            // 需要插入到head 后面
            if (item->tcb->DeadLine <= first->tcb->DeadLine) {
                item->next            = first;
                item->previous        = List->list_head;
                List->list_head->next = item;
                first->previous       = item;
                return;
            }
            // 需要插入到 tail 前面的情况
            else if ( item->tcb->DeadLine >= List->list_tail->previous->tcb->DeadLine )
            {
                listItem* tmp             = List->list_tail->previous;

                item->next                = List->list_tail;
                item->previous            = tmp;
                tmp->next                 = item;
                List->list_tail->previous = item;
                return;
            }
            // 需要插入到中间的情况
            while (first->next->tcb != NULL) {
                if (item->tcb->DeadLine >= first->tcb->DeadLine
                        && item->tcb->DeadLine <= first->next->tcb->DeadLine) {
                    item->next            = first->next;
                    item->previous        = first;
                    first->next->previous = item;
                    first->next           = item;
                    return;
                }
                first = first->next;
            }
        }
    }
    if (tag == 3) {
        // 链表长度为1的情况
        if (length == 1)
        {
            // 需要插入到 head 后面
            if (item->delay_time <= first->delay_time) {
                item->next            = first;
                item->previous        = List->list_head;
                List->list_head->next = item;
                first->previous       = item;
                return;
            }
            // 需要插入到 tail 前面的情况
            else if (item->delay_time > first->delay_time)
            {
                item->next                = List->list_tail;
                item->previous            = first;
                first->next               = item;
                List->list_tail->previous = item;
                return;
            }
        }
        // 链表长度为2 个以上的情况
        else if (length >= 2)
        {
            // 需要插入到head 后面
            if (item->delay_time <= first->delay_time) {
                item->next            = first;
                item->previous        = List->list_head;
                List->list_head->next = item;
                first->previous       = item;
                return;
            }
            // 需要插入到 tail 前面的情况
            else if ( item->delay_time >= List->list_tail->previous->delay_time )
            {
                listItem* tmp             = List->list_tail->previous;

                item->next                = List->list_tail;
                item->previous            = tmp;
                tmp->next                 = item;
                List->list_tail->previous = item;
                return;
            }
            // 需要插入到中间的情况
            while (first->next->tcb != NULL) {
                if (item->delay_time >= first->delay_time
                        && item->delay_time <= first->next->delay_time) {
                    item->next            = first->next;
                    item->previous        = first;
                    first->next->previous = item;
                    first->next           = item;
                    return;
                }
                first = first->next;
            }
        }
    }
}
listItem* CreateItem(TCB* tcb, uint delay_time, msgItem* msg)
{
    listItem* item   = (listItem*)malloc(sizeof(listItem)*1);
    item->tcb        = tcb;
    item->delay_time = delay_time;
    item->message    = msg;

    return item;
}
bool NewTask(list* List, void (*PC)(), uint deadline,int delay_time)
{
    TCB* tcb = CreateTCB(PC, deadline);
    listItem* listitem = CreateItem(tcb, delay_time, NULL);
    InsertItem(List, listitem, 1);
    return TRUE;
}
int SizeList(list* List)
{
    int size = 0;
    if (List->list_head->next == NULL || List->list_head->next == List->list_tail) {
        /* printf("这是一个空的链表! \n"); */
        return size;
    }
    listItem *p1 = List->list_head->next;
    while (p1->tcb != NULL) {
        size++;
        p1 = p1->next;
    }
    return size;
}
int extractItem(list* src, uint arg, list* dest, uint tag1, uint tag2, char* info)
{
    listItem* item = src->list_head->next;
    if (src->list_head == NULL || src->list_head->next == src->list_tail) {
        fprintf(stderr, "空链表无法抽取元素!\n");
        return 0;
    }
    if (dest->list_head == NULL) {
        fprintf(stderr, "无法向非法的链表中插入元素!\n");
        return 0;
    }
    while (item->tcb != NULL) {
        if ((tag1 == 1 && tag2 == 2) || (tag1 == 1 && tag2 == 3) || (tag1 == 2 && tag2 == 1)) {
            if (item->tcb->DeadLine == arg) {
                listItem* pr = item->previous;
                listItem* pn = item->next;
                pr->next     = pn;
                pn->previous = pr;
                InsertItem(dest, item, tag2);
                return 1;
            }
        }
        if (tag1 == 3 && tag2 == 1) {
            if (item->delay_time == arg) {
                listItem* pr = item->previous;
                listItem* pn = item->next;
                pr->next     = pn;
                pn->previous = pr;
                InsertItem(dest, item, tag2);
                return 1;
            }
        }
        item = item->next;
    }
    printf("%s 中不存在相应任务!\n", info);
    return 0;
}
void showList(list* List, char* arg, uint tag)
{
    int i = 1;
    listItem * tmp = List->list_head->next;
    printf("下面是%s 的 information!\n////////////////////////////////\n", arg);
    while (tmp->tcb != NULL) {
        if (tag == 1 || tag == 2 || tag == 3) {
            printf("DeadLine: %d\n", tmp->tcb->DeadLine);
        }
        if (tag == 1)
        {
            printf("即将调用第%d 个任务代码!!\n", i++);
            tmp->tcb->PC();
        }
        if (tag == 3) {
            printf("DelayTime: %d\n", tmp->delay_time);
        }
        tmp = tmp->next;
    }
    printf("////////////////////////////////\n%s的最终长度是: %d\n", arg, SizeList(List));
}
int main(void)
{
    /* 创建Ready List */
    list* List = CreateList();
    if (!NewTask(List, function1, 100, 10) || !NewTask(List, function2, 69, 20)
            || !NewTask(List, function3, 70, 60) || !NewTask(List, function4, 82, 29)) {
        fprintf(stderr, "新建任务失败\n");
    }
    showList(List, (char *)"ReadyList", 1);
    /* 创建 wait List */
    list* List1 = CreateList();
    showList(List1, (char *)"WaitList", 2);
    // 从 Reay List 提取元素到Wait List 当中
    printf("😄  从ReayList 提取元素到 WaitLit 😄  \n");
    if (!extractItem(List, 70, List1, 1, 2, (char *)"ReadyList")){
        fprintf(stderr, "从 ReadyList 向 WaitList 提取元素失败!\n");
    }
    if (!extractItem(List, 82, List1, 1, 2, (char *)"ReadyList")){
         fprintf(stderr, "从 ReadyList 向 WaitList 提取元素失败\n");
    }
    showList(List, (char *)"ReadyList", 1);
    showList(List1, (char *)"WaitList", 2);
    // 将元素从Wait List 提取回 Ready List
    printf("😄 将元素从 WaitList 提取回 ReadyList 😄 \n");
    if (!extractItem(List1, 82, List, 2, 1, (char *)"WaitList")){
        fprintf(stderr, "从 WaitList 向 ReadyList 提取失败!\n");
    }
    showList(List, (char *)"ReadyList", 1);
    showList(List1, (char *)"WaitList", 2);
    // 创建一个TimerList
    list* List2 = CreateList();
    showList(List2, (char *)"TimerList", 3);
    // 从 Reay List 提取元素到Wait List 当中
    printf("😄  从ReayList 提取元素到TimerList 😄  \n");
    if (!extractItem(List, 69, List2, 1, 3, (char *)"ReadyList")){
        fprintf(stderr, "从 ReadyList 向 TimerList 提取元素失败!\n");
    }
    if (!extractItem(List, 100, List2, 1, 3, (char *)"ReadyList")){
        fprintf(stderr, "从 ReadyList 向 TimerList 提取元素失败!\n");
    }
    showList(List, (char *)"ReadyList", 1);
    showList(List2, (char *)"TimerList", 3);
    // 将元素从Wait List 提取回 Ready List
    printf("😄 将元素从TimerList 提取回 ReadyList 😄 \n");
    if (!extractItem(List2, 20, List, 3, 1, (char *)"TimerList")){
        fprintf(stderr, "从 TimerList 向 ReadyList 提取失败!\n");
    }
    showList(List, (char *)"ReadyList", 1);
    showList(List2, (char *)"TimerList", 3);
    printf("***************Total****************\n");
    showList(List, (char *)"ReadyList", 1);
    showList(List1, (char *)"WaitList", 2);
    showList(List2, (char *)"TimerList", 3);
    return 0;
}
