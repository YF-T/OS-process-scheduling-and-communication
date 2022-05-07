struct semaphore {
  struct spinlock lock; 
  int count;
  int status;
};
extern struct semaphore sem[NSEM];
