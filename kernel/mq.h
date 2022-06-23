#define NULL 0
struct storageunit
{
  char *content;
  int used;
  struct storageunit *p;
};

#define NMQS 512 // 存储管理单元的个数
#define NMQS_SIZE 32 // 一个存储单元的大小
#define NMQPG 4 // 存储单元总共占的页数
#define NMQM 256 // 队列管理单元的个数

struct message
{
  int type;
  struct storageunit *s;
  int size;
};

struct queuemember
{
  struct message m;
  struct queuemember *p;
  int type;
  int used;
};