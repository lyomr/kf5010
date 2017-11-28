#include<sched.h>
#include<stdio.h>
int main()
{
  printf("Max priority for SCHED_OTHER %d\n", sched_get_priority_max(SCHED_OTHER));
  printf("Min priority for SCHED_OTHER %d\n", sched_get_priority_min(SCHED_OTHER));
  printf("Max priority for SCHED_FIFO %d\n", sched_get_priority_max(SCHED_FIFO));
  printf("Min priority for SCHED_FIFO %d\n", sched_get_priority_min(SCHED_FIFO));
  printf("Max priority for SCHED_RR %d\n", sched_get_priority_max(SCHED_RR));
  printf("Min priority for SCHED_RR %d\n", sched_get_priority_min(SCHED_RR));
  return 0;
}
