// message queue
#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "mq.h"
#include "memlayout.h"
#include "riscv.h"
#include "proc.h"
#include "defs.h"

struct spinlock mqlock;

static struct storageunit storage[NMQS];
static void *page[NMQPG];

static struct queuemember queue[NMQM];
static struct queuemember *queuehead = NULL;// 队列头，即pop的方向
static struct queuemember *queuetail = NULL;// 队列尾，即push的方向

int findemptystorage()
{
  for(int i = 0; i < NMQS; i++){
    if(storage[i].used == 0)
      return i;
  }
  return -1;
}

int storagemovein(struct message *m, char *buff, int n)
{
  int index;
  struct storageunit **last = &m->s;
  m->size = n;
  struct proc* p = myproc();
  while(n > NMQS_SIZE){
    index = findemptystorage();
    if(index == -1)
      return -1;
    copyin(p->pagetable, storage[index].content, (uint64)buff, NMQS_SIZE);
    n -= NMQS_SIZE;
    buff += NMQS_SIZE;
    *last = &storage[index];
    storage[index].used = 1;
    last = &(*last)->p;
  }
  index = findemptystorage();
  if(index == -1)
    return -1;
  copyin(p->pagetable, storage[index].content, (uint64)buff, n);
  *last = &storage[index];
  storage[index].used = 1;
  last = &(*last)->p;
  storage[index].p = NULL;
  return 0;
}

int storagemoveout(struct message m, char *buff, int n)
{
  int length = 0;
  struct proc* p = myproc();
  if(n > m.size)
    n = m.size;
  struct storageunit *cur = m.s;
  while(length + NMQS_SIZE < n){
    copyout(p->pagetable, (uint64)buff, cur->content, NMQS_SIZE);
    buff += NMQS_SIZE;
    length += NMQS_SIZE;
    cur->used = 0;
    cur=cur->p;
  }
  copyout(p->pagetable, (uint64)buff, cur->content, n - length);
  length += n - length;
  cur->used = 0;
  cur=cur->p;
  while(cur != NULL){
    cur->used = 0;
    cur=cur->p;
  }
  return length;
}

int qpush(struct message m)
{
  int unused = 0;
  for(unused = 0; unused < NMQM; unused++){
    if(queue[unused].used == 0)
      break;
  }
  if(unused == NMQM)
    return -1;
  queue[unused].m = m;
  queue[unused].type = m.type;
  queue[unused].used = 1;
  queue[unused].p = NULL;
  if(queuetail != NULL)
    queuetail->p = &queue[unused];
  else
    queuehead = &queue[unused];
  queuetail = &queue[unused];
  return 0;
}

int qpop(struct message *m)
{
  if(queuehead == NULL)
    return -1;
  *m = queuehead->m;
  queuehead->used = 0;
  queuehead = queuehead->p;
  if(queuehead == NULL)
    queuetail = NULL;
  return 0;
}

int qtypepop(int type, struct message *m)
{
  struct queuemember **last = &queuehead;
  while(*last != NULL){
    if((*last)->type == type)
      break;
    last = &(*last)->p;
  }
  if(*last == NULL)
    return -1;
  *m = (*last)->m;
  (*last)->used = 0;
  *last = (*last)->p;
  if(queuehead == NULL)
    queuetail = NULL;
  return 0;
}

void mqinit()
{
  char *addr;
  int index = 0;
  for(int i = 0; i < NMQPG; i++){
    page[i] = kalloc();
    addr = (char*)page[i];
    for(int j = 0; j < NMQS / NMQPG; j++){
      storage[index].content = addr;
      addr += NMQS_SIZE;
      index++;
    }
  }
}

int mqpush(int type, char *buff, int n)
{
  acquire(&mqlock);
  struct message tem;
  storagemovein(&tem, buff, n);
  tem.type = type;
  qpush(tem);
  release(&mqlock);
  return 0;
}

int mqpop(int *type, char *buff, int n)
{
  acquire(&mqlock);
  struct message tem;
  int ans;
  ans = qpop(&tem);
  if(ans == -1){
    release(&mqlock);
    return -1;
  }
  copyout(myproc()->pagetable, (uint64)type, (char*)&tem.type, sizeof(tem.type));
  ans = storagemoveout(tem, buff, n);
  release(&mqlock);
  return ans;
}

int mqtypepop(int type, char *buff, int n)
{
  acquire(&mqlock);
  struct message tem;
  int ans;
  ans = qtypepop(type, &tem);
  if(ans == -1){
    release(&mqlock);
    return -1;
  }
  ans = storagemoveout(tem, buff, n);
  release(&mqlock);
  return ans;
}