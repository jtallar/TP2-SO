#include <scheduler.h>
#include <time.h>

#define SIZE 4000

static Node *search(uint64_t pid);
static Node * newNode();
static void freeNode(Node * node);
static void cleanMem();

static Node *current;
static Node *address;

typedef union node {
    struct {
        int used;
        int times;
        Process process;
        Node * next;
    } n;
    long x; // Here happens the align 
} Node;

uint64_t scheduler(uint64_t sp)
{
}

uint8_t add(Process p)
{
    Node *node; // HACER MALLOC
    if (current == 0)
        current = node;
    else
    {
        Node * aux;
        aux = current->n.next;
        current->n.next = node;
        node->n.next = aux;
    }
}

uint8_t kill(uint64_t pid)
{
    Node *node = current;
    uint64_t first = node->n.process.pid;
    do
    {
        if (pid == node->n.next->n.process.pid)
        { // si es el de adelante
            remove(node->n.next->n.process);
            // free del nodo
            node->n.next = node->n.next->n.next; // lo puenteo
            return 1;
        }
        node = node->n.next;
    } while (node->n.next->n.process.pid != first); // si el siguiente no lo vi aun
    return -1;                          // No existe
}

uint8_t setPriority(uint64_t pid, uint8_t n)
{
}

uint8_t setState(uint64_t pid, states state)
{
    Node *node = search(pid);
}

Node *search(uint64_t pid)
{
    Node *node = 0;
    uint64_t first = node->n.process.pid;
    do
    {
        if (pid == node->n.next->n.process.pid) // si es el de adelante
            return node;
        node = node->n.next;
    } while (node->n.next->n.process.pid != first);
    return 0;
}

void listAll()
{
}

void initScheduler() {
    current = 0;
    address = (Node *)malloc(SIZE);
    cleanMem();
}

/* Memory manager for the nodes */
/* Returns direction of a new Node */
static Node * newNode() {
    for (size_t i = 0; i < SIZE / sizeof(Node); i++) {
        if ((address+i)->n.used == 0) {
            (address+i)->n.used = 1;
            return address+i;
        }
    }
    return 0;    
}

/* Frees the Node given */
static void freeNode(Node * node) {
    node->n.used = 0;
}

/* Sets all available places to free */
static void cleanMem() {
    Node * node;
    node->n.used = 0;
    for (size_t i = 0; i < SIZE / sizeof(Node); i++)
        *(address+i) = node;    
}
