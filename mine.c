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
  item = malloc(sizeof(Block)*sizeof(char));
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
//
// int calculMarkelTree(Block *block){
//   Queue *q;
//   int i = block->nbrTransaction;
//   q = createQueue();
//   if ((int)sqrt(block->nbrTransaction)%2 > 0){
//     while((int)sqrt(i)%2 > 0){
//       i++;
//     }
//   }
//   char *transactionList[i];
//   for(int k = 0; k < block->nbrTransaction; k++){
//     strcpy(transactionList[k],(block->transaction[k]));
//   }
//   if ((int)sqrt(block->nbrTransaction)%2 > 0){
//     for(int k = block->nbrTransaction-1; k < i; k++){
//       strcpy(transactionList[k],*(block->transaction[block->nbrTransaction-1]));
//     }
//   }
//   deleteQueue(&q);
//   return i;
// }
