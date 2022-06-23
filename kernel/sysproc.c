#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_semalloc(void)
{
  int count;

  if(argint(0, &count) < 0)
    return -1;
  return semalloc(count);
}

uint64
sys_semfree(void)
{
  int semid;
  
  if(argint(0, &semid) < 0)
    return -1;
  semfree(semid);
  return 0;
}

uint64
sys_sempend(void)
{
  int semid;
  
  if(argint(0, &semid) < 0)
    return -1;
  sempend(semid);
  return 0;
}

uint64
sys_sempost(void)
{
  int semid;
  
  if(argint(0, &semid) < 0)
    return -1;
  sempost(semid);
  return 0;
}

uint64
sys_shmalloc(void)
{
  return shmalloc();
}

uint64
sys_shmfree(void)
{
  int shmid;
  
  if(argint(0, &shmid) < 0)
    return -1;
  shmfree(shmid);
  return 0;
}

uint64
sys_shmread(void)
{
  int shmid, n;
  uint64 buff;
  
  if(argint(0, &shmid) < 0)
    return -1;
  if(argaddr(1, &buff) < 0)
    return -1;
  if(argint(2, &n) < 0)
    return -1;
  return shmread(shmid, (void*)buff, n);
}

uint64
sys_shmwrite(void)
{
  int shmid, n;
  uint64 buff;
  
  if(argint(0, &shmid) < 0)
    return -1;
  if(argaddr(1, &buff) < 0)
    return -1;
  if(argint(2, &n) < 0)
    return -1;
  return shmwrite(shmid, (void*)buff, n);
}

uint64
sys_mqpush(void)
{
  int type, n;
  uint64 buff;
  
  if(argint(0, &type) < 0)
    return -1;
  if(argaddr(1, &buff) < 0)
    return -1;
  if(argint(2, &n) < 0)
    return -1;
  return mqpush(type, (char*)buff, n);
}

uint64
sys_mqpop(void)
{
  int n;
  uint64 type, buff;
  
  if(argaddr(0, &type) < 0)
    return -1;
  if(argaddr(1, &buff) < 0)
    return -1;
  if(argint(2, &n) < 0)
    return -1;
  return mqpop((int*)type, (char*)buff, n);
}

uint64
sys_mqtypepop(void)
{
  int type, n;
  uint64 buff;
  
  if(argint(0, &type) < 0)
    return -1;
  if(argaddr(1, &buff) < 0)
    return -1;
  if(argint(2, &n) < 0)
    return -1;
  return mqtypepop(type, (char*)buff, n);
}