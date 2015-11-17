#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "param.h"
#define NULL 0
int countThr=0;
thrStack_t * thrstList[NPROC];
lock_t uLock;
/*
 * This is where you'll need to implement the user-level functions
 */

void lock_init(lock_t *lock) {
	lock->locked=0;
}

int testAndSet(lock_t * lock,int num){
	int result=lock->locked;
	if (lock->locked!=num){
		lock->locked=num;
	}
	return result;
	
}
void lock_acquire(lock_t *lock) {
	while (testAndSet(lock,1)){}
}

void lock_release(lock_t *lock) {
	lock->locked=0;
}

int thread_join(int pid) { 
	int i;
	//printf(1,"Before killing: %d\n",pid);
	uint resultpid=join(pid);
	//printf(1,"Killing Pid: %s\n",resultpid);
	if (resultpid>0){
		for (i=0; i<countThr; i++){
			if (thrstList[i]->pid==resultpid){
				free(thrstList[i]->stack);
				countThr--;
				thrstList[i]=NULL;
			}
		}
		//printf (1,"Done Killing\n;");

	}
	return resultpid;
}

int thread_create(void (*start_routine)(void *), void *arg) {
	void *stack = malloc(PGSIZE*2);
	//assert(stack != NULL);
	if((uint)stack % PGSIZE)
		stack = stack + (PGSIZE - (uint)stack % PGSIZE);
   int clone_pid = clone(start_routine, arg, stack);
	if (clone_pid==-1){
		free(stack);
	}
   if (clone_pid>0){
	   thrStack_t * thrst = thrstList[countThr];
	   countThr ++;
	   //thrst=&(thrstList[countThr-1]);
	   thrst->pid=clone_pid;
	   thrst->stack=stack;
	}
   return clone_pid;
}
