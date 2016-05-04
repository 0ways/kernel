#ifndef KERNEL_H
#define KERNEL_H
// Debug option
//#define       _DEBUG
/*********************************************************/
/** Global variabels and definitions                     */
/*********************************************************/
#include <stdlib.h>

#ifdef texas_dsp
#define CONTEXT_SIZE 34 - 2
#else
#define CONTEXT_SIZE 13
#define STACK_SIZE 100
#endif

#define TRUE 1
#define FALSE !TRUE
#define RUNNING 1
#define INIT !RUNNING
#define FAIL 0
#define SUCCESS 1
#define OK 1
#define DEADLINE_REACHED 0
#define NOT_EMPTY 0
#define SENDER +1
#define RECEIVER -1

typedef int exception;
typedef int bool;
typedef unsigned int uint;
typedef int action;

struct listItem;  // Forward declaration
// Task Control Block, TCB 任务控制块的数据结构
#ifdef texas_dsp
typedef struct
{
    void (*PC)(); // 任务代码指针
    uint *SP; // 堆栈指针
    uint Context[CONTEXT_SIZE];
    uint StackSeg[STACK_SIZE]; // 堆栈数组
    uint DeadLine; // 任务截至期限
}
TCB;
#else
typedef struct
{
    uint Context[CONTEXT_SIZE];
    uint *SP;
    void (*PC)();
    uint SPSR;
    uint StackSeg[STACK_SIZE];
    uint DeadLine;
}
TCB;
#endif
// Message items 信息项的数据结构
typedef struct msgItem
{
    char *Data; // 信息数据
    exception Status; // 信息项的状态
    struct listItem *belongListItem; // 指向所属的任务控制块
    struct msgItem *previous; // 前一个信息项目
    struct msgItem *next; // 后一个信息项
}
msgItem;
// Mailbox structure // 邮箱的数据结构
typedef struct
{
    msgItem *mailboxHead; // 邮箱头
    msgItem *mailboxTail; // 邮箱尾部
    int mailboxDataSize;
    int MaxMessagesMialbox;
    int numMessagesMailbox;
    int numBlockedMsgMailbox;
}
mailbox;
// Generic list item
typedef struct listItem
{
    TCB *tcb;
    uint delay_time; // 任务项目的延时时间
    msgItem *message; // 指向所拥有的信息项
    struct listItem *previous;
    struct listItem *next;
}
listItem;
// Generic list
typedef struct
{
    listItem *list_head;
    listItem *list_tail;
}
list;

// 自定义部分
/**********************************************************************
*                           创立一个双向链表的抽象方法                            *
**********************************************************************/
// 创建并初始化链表
list*     CreateList( void );
listItem* CreateItem(TCB* tcb,uint delay_time,msgItem* msg);
TCB*      CreateTCB(void (*PC)(), uint deadline);
void      InsertItem(list* list, listItem* item, uint tag);
// 删除一个任务节点从 ReadyList 当中 TODO
void DeleteItem(listItem* item);
bool NewTask (list* List, void (*PC)(), uint deadline,int delay_time);
int  SizeList(list* List);
void showList(list* List, char* arg, uint tag);
// msgItem* CreateMsg(char* data, exception status, listItem* belongListItem, msgItem* pre, msgItem* next);
// bool SetListItemForMsg(msgItem* msg, listItem* listitem);
int extractItem(list* src, uint arg, list* dest, uint tag1, uint tag2, char* info);

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////以下是内核函数/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Task administration
int init_kernel(void);
exception create_task(void (*body)(), uint d);
void terminate(void);
void run(void);

// Communication
mailbox *create_mailbox(uint nMessages, uint nDataSize);
int no_messages(mailbox *mBox);

exception send_wait(mailbox *mBox, void *pData);
exception receive_wait(mailbox *mBox, void *pData);
exception send_no_wait(mailbox *mBox, void *pData);
int receive_no_wait(mailbox *mBox, void *pData);

// Timing
// exception wait(uint nTicks);
exception custom_wait(uint nTicks);
void set_ticks(uint no_of_ticks);
uint ticks(void);
uint deadline(void);
void set_deadline(uint nNew);

// Interrupt
extern void isr_off(void);
extern void isr_on(void);
extern void SaveContext(
    void);  // Stores DSP registers in TCB pointed to by Running
extern void LoadContext(
    void);  // Restores DSP registers from TCB pointed to by Running

#endif
