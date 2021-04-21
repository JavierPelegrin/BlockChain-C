#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

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

void calculMarkelTree(Block *block){
  Transaction *t[TRANSACTION_MAX];
  char *item = malloc(sizeof(TRANSACTION_SIZE)*TRANSACTION_MAX);
  if (block->nbrTransaction%2 != 0{
    srtcat(t[TRANSACTION_MAX-1],block->transaction[TRANSACTION_MAX-1]);
  }
  for(int i = 0; i < TRANSACTION_MAX-1; i++){

  }

}
