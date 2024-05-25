#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
	if (q == NULL)
		return 1;
	return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
	/* TODO: put a new process to queue [q] */
	if (q->size >= MAX_QUEUE_SIZE)
	{
		return;
	}
	q->proc[q->size++] = proc;
}

struct pcb_t *dequeue(struct queue_t *q)
{
	/* TODO: return a pcb whose prioprity is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	int i, highestPriority = 0;
	if (q->size > 0)
	{
		for (i = 1; i < q->size; i++)
		{
			// printf("PRIO: %d\n", (int)q->proc[i]->prio);
			if (q->proc[highestPriority]->prio > q->proc[i]->prio)
			{
				highestPriority = i;
			}
		}
		struct pcb_t *tmp_proc = q->proc[highestPriority];
		for (i = highestPriority; i < q->size - 1; i++)
			q->proc[i] = q->proc[i + 1];
		q->size--;
		return tmp_proc;
	}
	return NULL;
}