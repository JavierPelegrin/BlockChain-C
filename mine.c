#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "queue.h"
#include "BlockChain.h"
#include "transaction.h"
#include "sha256.h"
#include "sha256_utils.h"

void calculHash(char hash[SHA256_BLOCK_SIZE*2+1], char *infos){
  char *item = malloc(sizeof(Block));
  sha256ofString((BYTE *)infos,item);
  strcpy(hash,item);
  free(item);
}

void createHash(Block *block){
  char *item, *nbrTransaction, *nonce, *index;
  item = malloc(sizeof(Block)*sizeof(char)+(sizeof(TurnChar(block->transaction,0)) * block->nbrTransaction));
  nbrTransaction = malloc(sizeof(int));
  nonce = malloc(sizeof(int));
  index = malloc(sizeof(int));

  sprintf(nbrTransaction, "%d",block->nbrTransaction); // cast pour convertir integer to string
	strcpy(item,nbrTransaction);
	sprintf(nonce, "%ld",block->nonce);
	strcat(item,nonce);
  sprintf(index,"%d",block->index);
  strcat(item,index);
	strcat(item,block->timestamp);
  for(int i = 0; i < block->nbrTransaction; i++){
    strcat(item,TurnChar(block->transaction, i));
  }
  strcat(item,block->merkleRoot);
  sha256ofString((BYTE *)item,block->hash);
  free(item);free(nbrTransaction);free(nonce);free(index);
}

bool verifieHash(char *hash, int d){
  char at[d];
  char Dificulty[d];
  int i;
  for(i = 0; i < d; i++){
    at[i] = hash[i];
    Dificulty[i] = '0';
  }
  return strcmp(at,Dificulty);
}

void mineBlock(Block *block){
  block->nonce = -1;
  do {
    block->nonce++;
    createHash(block);
  } while(verifieHash(block->hash,DIFICULTY));
}

char *calculmarkleTree(char (*transactionList)[TRANSACTION_SIZE], int imaxl, int il, Queue *q, int imaxq, int iq){
  char skt[(SHA256_BLOCK_SIZE*2+1)*2];
  if (il < imaxl-1){
    strcpy(skt,transactionList[il]);
    strcpy(skt,transactionList[il+1]);
    calculHash(skt,skt);
    q = queuePush(q,skt);
    return calculmarkleTree(transactionList, imaxl, il+2, q, imaxq, iq);
  }else if (queueSize(q) > 1){
    // char top1[SHA256_BLOCK_SIZE*2+1];
    // char top2[SHA256_BLOCK_SIZE*2+1];
    //strcpy(skt,queueTop(q));
    // printf("%d :Estoy aqui llamondo a pop helo, %s\n", queueSize(q),top1 );
    strcpy(skt,queueTop(q));
    q = queuePop(q);
    // printf("Estoy aqui llamondo a pop helo, %s\n", top2 );

    q = queuePop(q);
    // strcpy(skt,top1);
    // strcpy(skt,top2);
    calculHash(skt,skt);
    q = queuePush(q,skt);
    return calculmarkleTree(transactionList, imaxl, il, q, imaxq, iq+2);
  }
  return queueTop(q);
}

char *calculmerkleRoot(Block *block){
  Queue *q;
  int i = block->nbrTransaction;
  double buff;
  char *Root = malloc(SHA256_BLOCK_SIZE*2+1);
  q = createQueue();
  if (modf(log(block->nbrTransaction)/log(2),&buff) > 0){ // logaritomo de base 2
    while (modf(log(i)/log(2),&buff) > 0){ // logaritomo de base 2
      i++;
    }
  }
  char transactionList[i][TRANSACTION_SIZE];
  for(int k = 0; k < block->nbrTransaction; k++){
    strcpy(transactionList[k], TurnChar(block->transaction,k));
  }
  if (modf(log(block->nbrTransaction)/log(2),&buff) > 0){ // logaritomo de base 2
    for(int k = block->nbrTransaction-1; k < i; k++){
      strcpy(transactionList[k],TurnChar(block->transaction,block->nbrTransaction-1));
    }
  }

  strcpy(Root,calculmarkleTree(transactionList,i,0,q,(i+(i%2))/2,0));
  deleteQueue(&q);
  return Root;//calculmarkleTree(transactionList,i,0,q,(i+(i%2))/2,0);
}
