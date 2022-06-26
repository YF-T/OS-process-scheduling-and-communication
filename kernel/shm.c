// shared memory

#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "shm.h"
#include "memlayout.h"
#include "riscv.h"
#include "proc.h"
#include "defs.h"

struct sharedmemory shm[NSHM];

int
shmalloc() // 分配内存
{
  for(int i = 0; i < NSHM; i++){
    acquire(&shm[i].lock);
    if(shm[i].status == 0){
      shm[i].status = 1;
      shm[i].addr = kalloc();
      if(shm[i].addr == 0){
        shm[i].status = 0;
        release(&shm[i].lock);
        return -1;
      }
      release(&shm[i].lock);
      return i;
    }
    release(&shm[i].lock);
  }
  return -1;
}

void
shmfree(int shmid) // 释放共享内存
{
  acquire(&shm[shmid].lock);
  kfree(shm[shmid].addr);
  shm[shmid].status = 0;
  release(&shm[shmid].lock);
}

int
shmread(int shmid, void* buff, int start, int n) // 共享内存读操作
{
  acquire(&shm[shmid].lock);
  if(n + start > shm[shmid].length){
    n = shm[shmid].length - start;
  }
  struct proc* p = myproc();
  copyout(p->pagetable, (uint64)buff, (char*)shm[shmid].addr + start, n);
  release(&shm[shmid].lock);
  return n;
}

int
shmwrite(int shmid, void* buff, int start, int n) // 共享内存写操作
{
  acquire(&shm[shmid].lock);
  if(start + n > PGSIZE){
    release(&shm[shmid].lock);
    return -1;
  }
  struct proc* p = myproc();
  copyin(p->pagetable, (char*)shm[shmid].addr + start, (uint64)buff, n);
  shm[shmid].length = start + n;
  release(&shm[shmid].lock);
  return n;
}