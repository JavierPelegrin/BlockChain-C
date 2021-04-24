#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#include "sha256_utils.h"

#define TRANSACTION_SIZE 60
#define TRANSACTION_MAX 5

typedef struct s_Transaction Transaction;

typedef struct s_Block {
  int index;
  char *timestamp;
  char hashPrev[SHA256_BLOCK_SIZE*2+1];
  int nbrTransaction;
  Transaction *transaction[TRANSACTION_MAX];
  char merkleRoot[SHA256_BLOCK_SIZE*2+1];
  char hash[SHA256_BLOCK_SIZE*2+1];
  long int nonce;
} Block;


void createGenesisT(Block *b);

void create1Transaction(Block *b,int i);

void createNTransaction(Block *b);

char *TurnChar(Transaction **t, int i);


#endif
