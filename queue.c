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
    InternalQueue *head;
    InternalQueue *tail;
    int size;
};

Queue *createQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->head = q->tail = NULL;
    q->size = 0;
    return (q);
}

void deleteQueue(ptrQueue *q) {
    InternalQueue *toDelete = (*q)->head;
    while (toDelete) {
        InternalQueue *f = toDelete;
        toDelete = toDelete->next;
        free(f);
    }
    free(*q);
    *q = NULL;
}

Queue *queuePush(Queue *q, char *v) {
    // InternalQueue **insert_at = (q->size ? &(q->tail->next) : &(q->head));
    InternalQueue *new = malloc(sizeof(InternalQueue)+SHA256_BLOCK_SIZE*2+1);
    if (q->size == 0){
      strcpy((new->value),v);
      new->next = NULL;
      q->head = new;
    }else{
      strcpy((new->value),v);
      new->next = NULL;
      q->tail->next = new;
    }
    q->tail = new;
    ++(q->size);
    return (q);
}

Queue *queuePop(Queue *q) {
    assert (!queueEmpty(q));
    q->head = q->head->next;
    q->size--;
    return (q);
}

char *queueTop(Queue *q) {
    assert (!queueEmpty(q));
    return (q->head->value);
}

bool queueEmpty(Queue *q) {
    return (q->size == 0);
}

unsigned int queueSize(Queue *q) {
    return q->size;
}
