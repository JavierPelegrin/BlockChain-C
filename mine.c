#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

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

void createHash(Block **block){
  char *item, *nbrTransaction, *nonce, *index;
  item = malloc(sizeof((*block)->timestamp)+sizeof(int)+((SHA256_BLOCK_SIZE*2+1)*2)+sizeof(long int)+sizeof(char)*(TRANSACTION_SIZE * (*block)->nbrTransaction));
  nbrTransaction = malloc(sizeof(int));
  nonce = malloc(sizeof(int));
  index = malloc(sizeof(int));


  sprintf(nbrTransaction, "%d",(*block)->nbrTransaction); // cast pour convertir integer to string
	strcpy(item,nbrTransaction);
	sprintf(nonce, "%ld",(*block)->nonce);
	strcat(item,nonce);
  sprintf(index,"%d",(*block)->index);
  strcat(item,index);
	strcat(item,(*block)->timestamp);
  strcat(item,(*block)->hashPrev);
  for(int i = 0; i < (*block)->nbrTransaction; i++){
    strcat(item,TurnChar((*block)->transaction, i));
  }
  strcat(item,(*block)->merkleRoot);
  sha256ofString((BYTE *)item,(*block)->hash);
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

void mineBlock(Block **block, int Dificulty){
  (*block)->nonce = -1;
  do {
    (*block)->nonce++;
    createHash(block);
  } while(verifieHash((*block)->hash,Dificulty));
}

char *calculmarkleTree(char **transactionList, int imaxl, int il, Queue *q){
  char hash[(SHA256_BLOCK_SIZE*2+1)*2];
  char skt[((SHA256_BLOCK_SIZE*2+1)*2)*2];
  if (il < imaxl-1){
    strcpy(skt,transactionList[il]);
    strcat(skt,transactionList[il+1]);
    calculHash(hash,skt);
    q = queuePush(q,hash);
    return calculmarkleTree(transactionList, imaxl, il+2, q);
  }else if (queueSize(q) > 1){
    strcpy(hash,queueTop(q));
    q = queuePop(q);
    strcpy(skt,queueTop(q));
    strcat(skt,hash);

    q = queuePop(q);
    calculHash(hash,skt);
    q = queuePush(q,hash);
    return calculmarkleTree(transactionList, imaxl, il, q);
  }
  return queueTop(q);
}

void testMerkleTreeFunction(){
  char *transactionList[4];
  char hash1[SHA256_BLOCK_SIZE*2+1];
  char hash2[SHA256_BLOCK_SIZE*2+1];
  char hash3[SHA256_BLOCK_SIZE*2+1];

  for(int i = 0; i < 4; i++){
    transactionList[i] = malloc(SHA256_BLOCK_SIZE*2+1);
  }
  strcpy(transactionList[0], "Source user10-Destination user20, quantite: 14bnb");
  strcpy(transactionList[1], "Source user20-Destination user30, quantite: 14bnb");
  strcpy(transactionList[2], "Source user30-Destination user40, quantite: 14bnb");
  strcpy(transactionList[3], "Source user40-Destination user50, quantite: 14bnb");
  for(int i = 0; i < 4; i++){
    calculHash(transactionList[i],transactionList[i]);
  }
  Queue *q;
  q = createQueue();
  printf("este es el de la funcion %s\n",calculmarkleTree(transactionList,4,0,q));
  for(int i = 0; i < 4; i++){
  }
  deleteQueue(&q);
  strcat(transactionList[0], transactionList[1]);
  strcat(transactionList[2], transactionList[3]);
  calculHash(hash1,transactionList[0]);
  calculHash(hash2,transactionList[2]);
  strcat(hash1,hash2);
  calculHash(hash3,hash1);
  printf("este es el iterativo     %s\n",hash3);
}

char *calculmerkleRoot(Block *block){
  Queue *q;
  int i = block->nbrTransaction;
  double buff;
  char *Root = malloc(SHA256_BLOCK_SIZE*2+1);
  q = createQueue();
  if (modf(log(block->nbrTransaction)/log(2),&buff) > 0){
    while (modf(log(i)/log(2),&buff) > 0){
      i++;
    }
  }
  if(block->nbrTransaction == 1){
    i = 2;
  }
  char *transactionList[i];
  for(int k = 0; k < block->nbrTransaction; k++){
    transactionList[k] = malloc(sizeof(char)*(SHA256_BLOCK_SIZE*2+1));
    strcpy(transactionList[k], TurnChar(block->transaction,k));
    calculHash(transactionList[k],transactionList[k]);
  }
  if (modf(log(block->nbrTransaction)/log(2),&buff) > 0 || block->nbrTransaction == 1){
    for(int k = block->nbrTransaction-1; k < i; k++){
      transactionList[k] = malloc(sizeof(char)*(SHA256_BLOCK_SIZE*2+1));
      strcpy(transactionList[k],TurnChar(block->transaction,block->nbrTransaction-1));
      calculHash(transactionList[k],transactionList[k]);
    }
  }
  strcpy(Root,calculmarkleTree(transactionList,i,0,q));
  free(*transactionList);
  deleteQueue(&q);
  return Root;
}
