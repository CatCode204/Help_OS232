#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
        if (q == NULL) return 1;
	return (q->size == 0);
}

#ifdef MLQ_SCHED
void ReheapUp(struct queue_t* q, int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    if (q->proc[index]->priority < q->proc[parent]->priority) {
        struct pcb_t* tmp = q->proc[index];
        q->proc[index] = q->proc[parent];
        q->proc[parent] = tmp;
        ReheapUp(q, index);
    }
}

void ReheapDown(struct queue_t* q,int index) {
    int p = index;
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    if (l < q->size && q->proc[l]->priority < q->proc[p]->priority) p = l;
    if (r < q->size && q->proc[r]->priority < q->proc[p]->priority) p = r;
    if (index != p) {
        struct pcb_t* tmp = q->proc[index];
        q->proc[index] = q->proc[p];
        q->proc[p] = tmp;
        ReheapDown(q, p);
    }
}
#endif

void enqueue(struct queue_t * q, struct pcb_t * proc) {
    if (q->size == MAX_QUEUE_SIZE || proc == NULL) return;
    #ifdef MLQ_SCHED
    q->size++;
    q->top = (q->top + 1) % MAX_QUEUE_SIZE;
    q->proc[q->top] = proc;
    #else
    q->proc[q->size++] = proc;
    ReheapUp(q,q->size - 1);
    #endif
}

struct pcb_t * dequeue(struct queue_t * q) {
    if (q->size == 0) return NULL;
    struct pcb_t* rt = NULL;
    #ifdef MLQ_SCHED
    --q->size;
    rt = q->proc[q->bot];
    q->bot = (q->bot + 1) % MAX_QUEUE_SIZE;
    #else
    rt = q->proc[0];
    q->proc[0] = q->proc[--q->size]; 
    ReheapDown(q,0);
    #endif
    return rt;
}
