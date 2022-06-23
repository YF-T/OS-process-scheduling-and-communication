#define NSHM 256
#define NSHM_IN_PROC 8
struct sharedmemory
{
  void *addr;
  struct spinlock lock;
  int status;
  int length;
  int token;
  int count;
  int creator;
  int last_modifier;
};

extern struct sharedmemory shm[NSHM];