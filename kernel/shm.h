#define NSHM 256
#define NSHM_IN_PROC 8
struct sharedmemory
{
  void *addr;
  struct spinlock lock;
  int status;
  int length;
};

extern struct sharedmemory shm[NSHM];