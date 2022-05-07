#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "semaphore.h"
#include "riscv.h"
#include "proc.h"
#include "defs.h"

struct semaphore sem[NSEM];

int
semalloc(int count)
{
  for(int i = 0; i < NSEM; i++){
    acquire(&sem[i].lock);
    if(sem[i].status == 0){
      sem[i].count = count;
      sem[i].status = 1;
      release(&sem[i].lock);
      return i;
    }
    release(&sem[i].lock);
  }
  return -1;
}

void
semfree(int semid)
{
  acquire(&sem[semid].lock);
  sem[semid].status = 0;
  sem[semid].count = 0;
  release(&sem[semid].lock);
}

void
sempend(int semid)
{
  acquire(&sem[semid].lock);
  while(1){
    if(sem[semid].count > 0){
      sem[semid].count -= 1;
      release(&sem[semid].lock);
      return;
    }
    sleep(&sem[semid], &sem[semid].lock);
  }
  release(&sem[semid].lock);
}

void
sempost(int semid)
{
  acquire(&sem[semid].lock);
  sem[semid].count += 1;
  wakeup(&sem[semid]);
  release(&sem[semid].lock);
}