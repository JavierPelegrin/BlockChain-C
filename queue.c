/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)

 Implantation du TAD Queue étudié en cours.

 */
/*-----------------------------------------------------------------*/
#include "queue.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

/* Full definition of the queue structure */
typedef struct s_internalQueue {
    char value[SHA256_BLOCK_SIZE*2+1];
    struct s_internalQueue *next;
} InternalQueue;

struct s_queue {
    InternalQueue *top;
    int size;
};

Queue *createQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->top = NULL;
    q->size = 0;
    return (q);
}

void deleteQueue(ptrQueue *q) {
    InternalQueue *toDelete = (*q)->top;
    while (toDelete) {
        InternalQueue *f = toDelete;
        toDelete = toDelete->next;
        free(f);
    }
    free(*q);
    *q = NULL;
}

Queue *queuePush(Queue *q, char *v) {
    InternalQueue *new = malloc(sizeof(InternalQueue));
    strcpy(new->value,v);
    new->next = q->top;
    q->top = new;
    ++(q->size);
    return (q);
}

Queue *queuePop(Queue *q) {
    assert (!queueEmpty(q));
    q->top = q->top->next;
    q->size--;
    return (q);
}

char *queueTop(Queue *q) {
    assert (!queueEmpty(q));
    return (q->top->value);
}

bool queueEmpty(Queue *q) {
    return (q->size == 0);
}

unsigned int queueSize(Queue *q) {
    return q->size;
}
