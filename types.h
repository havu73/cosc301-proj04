typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
typedef struct __lock_t {
	int locked;//locked should be 0 when unlocked, 1 when locked
} lock_t;
typedef struct __thread_stack_t{
	uint pid;
	void * stack;	
}thrStack_t;


