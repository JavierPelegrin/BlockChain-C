/*
  Header de la BlockChain

*/

#ifndef __BLOCKCHAIN_H__
#define __BLOCKCHAIN_H__

#include <stdbool.h>
#include "sha256_utils.h"
#include "transaction.h"

#define DIFICULTY 4
#define BLOCKCHAIN_SIZE_MAX 1000

typedef struct s_BlockChain BlockChain;

char * getTimeStamp();

BlockChain *createBlockChain();

void createBlock(BlockChain *blockChain);

/*
  pas fait encore
*/
void removeBlock(BlockChain *blockChain, int position);

Block blockFirst(BlockChain *blockChain);

int blockchainSize(BlockChain *blockChain);

char *blockHash(BlockChain *blockChain);

char *BlockTransaction(BlockChain *blockChain, int i);

#endif
