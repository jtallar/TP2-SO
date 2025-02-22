#include <process.h>
#include <stack.h>
#include <scheduler.h>
#include <memoryManager.h>

#include <resources.h>
#include <console.h>

static uint64_t c_pid = 0;

uint64_t create(void * entryPoint, char * name, level context) {
    Process data = createNoSched(entryPoint, name, context);
    /* Add process to scheduler */
    add(data);
    if (context == FORE && data.pid > 1)
        block(SCREEN);
    return data.pid;
}

Process createNoSched(void * entryPoint, char * name, level context) {
    void * processStack = malloc(STACK_SIZE);
    if (processStack == 0) { // ERROR --> NO HAY MAS MEMORIA --> VER QUE DEVUELVO

        // return 0;
    }

    /* Creates stack for process */
    char * lastAddress = (char *) getLastAddress(processStack);
    char * stackBase = lastAddress - sizeof(uint64_t);
    StackFrame stack = initStack(entryPoint, (void *) stackBase);
    memcpy(lastAddress - sizeof(StackFrame), &stack, sizeof(StackFrame));
    
    /* Creates process data */
    Process data;
    data.name = name;
    data.pid = c_pid++;
    data.ppid = getPid();
    data.sp = (uint64_t) lastAddress - sizeof(StackFrame);
    data.bp = (uint64_t) stackBase;
    data.priority = 3;
    data.context = context;
    data.state = READY;
    data.stack = processStack;
    data.resource = 0;

    /* Prints result on console */
    //printProcessStack(data);
    return data;
}

void remove(Process p) {
    freeResources(p);
    free(p.stack);
}

void freeResources(Process p) {
    if (p.state == BLOCKED) return;
    switch(p.resource) {
        case NONE: return;
        case TIME: removeNodeT(p.pid); break;
        case READ: removeNodeR(p.pid); break;
        case WRITE: removeNodeW(p.pid); break;
        default: return;
    }
}

void printProcessStack(Process p) {
    char * lastAddress = (char *) getLastAddress(p.stack);
    print("\nProcess %d \n", p.pid);
    uint64_t * aux;
    for (aux = (uint64_t *) p.sp; aux < (uint64_t *) lastAddress; aux++) {
        print("- Address: 0x");
        printHex((uint64_t)aux);
        print(" - Content: 0x");
        printHex(*aux);
        print("\n");
    }
    print("\n-----------------------\n");
}